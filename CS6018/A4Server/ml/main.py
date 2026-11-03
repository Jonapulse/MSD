import io

import torch
from fastapi import FastAPI, HTTPException, Request
from PIL import Image, ImageOps, UnidentifiedImageError
from starlette.concurrency import run_in_threadpool
from transformers import BlipForConditionalGeneration, BlipProcessor

MODEL_ID = "Salesforce/blip-image-captioning-base"

# Loaded once at startup, not per request
processor = BlipProcessor.from_pretrained(MODEL_ID)
model = BlipForConditionalGeneration.from_pretrained(MODEL_ID)
model.eval()

app = FastAPI()


@app.get("/health")
def health():
    return {"status": "ok"}


def generate_caption(image: Image.Image) -> str:
    inputs = processor(images=image, return_tensors="pt")
    with torch.no_grad():
        out = model.generate(**inputs, max_new_tokens=30)
    return processor.decode(out[0], skip_special_tokens=True)


@app.post("/caption")
async def caption(request: Request):
    data = await request.body()
    try:
        # exif_transpose applies the camera's rotation tag so the model sees it upright
        image = ImageOps.exif_transpose(Image.open(io.BytesIO(data))).convert("RGB")
    except UnidentifiedImageError:
        raise HTTPException(status_code=400, detail="Not a valid image")
    # Run the slow model call in a worker thread so the server stays responsive
    text = await run_in_threadpool(generate_caption, image)
    return {"caption": text}