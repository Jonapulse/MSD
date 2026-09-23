from google import genai

client = genai.Client(api_key="xxxxxx")

response = client.models.list()
for model in response:
    print(f"Model Name: {model.name}, Description: {getattr(model,'description', 'No desc.')}")