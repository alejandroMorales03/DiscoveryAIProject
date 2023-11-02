import geocoder
import csv

def get_current_location():
    location = geocoder.ip('me')
    return location

current_location = get_current_location()

if current_location.ok:
    with open("location_data.csv", "a") as file:
        latitude = round(current_location.latlng[0], 7)
        longitude = round(current_location.latlng[1], 7)
        writer = csv.writer(file, delimiter='\t')
        writer.writerow([latitude, longitude])
        file.seek(0, 2)
else:
    print("Unable to determine your current location")
