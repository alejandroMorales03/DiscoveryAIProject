import requests
from bs4 import BeautifulSoup

url = "https://parking.fiu.edu"
html = requests.get(url)

s = BeautifulSoup(html.content, "html.parser")
results = s.find(id="ResultContainer")

available = s.find_all("strong", class_="donut-content")

if available:
    print(available[0].text)
else:
    print("No data available")
