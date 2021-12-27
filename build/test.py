import base64
import requests
import json
import time

s = "aGVsbG8gd29ybGQ="
_H = "application/json"

for i in range(100):
    start = time.time()
    r = requests.post(url="http://192.168.3.15:8080/api/infer/inference", data =json.dumps({"image":s}), headers={"Content-Type":_H})
    print(r.text)
    print(time.time() - start)
