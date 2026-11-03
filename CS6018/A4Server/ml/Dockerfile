FROM python:3.12-slim
WORKDIR /app

# CPU-only PyTorch: the default pip install pulls in GPU libraries worth several GB
RUN pip install --no-cache-dir torch --index-url https://download.pytorch.org/whl/cpu

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Download the model at build time so container startup doesn't fetch ~1 GB each time
RUN python -c "from transformers import BlipProcessor, BlipForConditionalGeneration; m='Salesforce/blip-image-captioning-base'; BlipProcessor.from_pretrained(m); BlipForConditionalGeneration.from_pretrained(m)"

COPY main.py .
EXPOSE 8000
CMD ["uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8000"]