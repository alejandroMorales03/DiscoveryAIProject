import requests
import csv

api_key = "AIzaSyAXz4bYCw88DOYDTkD2atTcAFI1o6ZnJ88"

parking_address = ["10885 SW 16 St", "10880 SW 16 St", "1060 SW 113 Ave", "890 SW 109 Ave", "891 SW 109 Ave", "11200 SW 8 St"]

parking_urls = []
for address in parking_address:
    parking_urls.append(f"https://maps.googleapis.com/maps/api/geocode/json?address={address}&key={api_key}")

responses = []

for url in parking_urls:
    responses.append(requests.get(url))


for response in responses: 
    with open("location_data.csv", "a") as file:
        if response.status_code == 200:
            data = response.json()
            if data['status'] == 'OK':
                location = data['results'][0]['geometry']['location']
                latitude = str(round(location['lat'], 7))
                longitude = str(round(location['lng'], 7))
                file.write("\t\t\t\t" + latitude + '\t\t\t\t' + longitude)
            else:
                print("Geocoding was not successful")
        else:
            print("Unable to connect to the Google Maps Geocoding API")
    file.close()
            


