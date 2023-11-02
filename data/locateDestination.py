import requests
import os
import csv

api_key = "AIzaSyAXz4bYCw88DOYDTkD2atTcAFI1o6ZnJ88"
address = "13031 SW 259 ST"  # Replace with your address

url = f"https://maps.googleapis.com/maps/api/geocode/json?address={address}&key={api_key}"
response = requests.get(url)

latitude = "N/A"
longitude = "N/A"

if response.status_code == 200:
    data = response.json()
    if data['status'] == 'OK':
        location = data['results'][0]['geometry']['location']
        latitude = str(round(location['lat'], 7))
        longitude = str(round(location['lng'], 7))
    else:
        print("Geocoding was not successful")

else:
    print("Unable to connect to the Google Maps Geocoding API")

with open("location_data.csv", 'a', newline='') as file:
    # Concatenate the latitude and longitude without a delimiter
    writer = csv.writer(file, lineterminator=',')
    file.write('\n')
    writer.writerow([latitude + longitude])

