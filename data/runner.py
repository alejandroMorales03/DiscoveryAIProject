import subprocess
import os
import csv

user_address = input("Enter the address of your destination: ")
os.environ["USER_ADD"] = user_address
destination = "/Users/alejandromorales/Desktop/parking/locateDestination.py"
subprocess.run(["python3", destination])

current = "/Users/alejandromorales/Desktop/parking/locateCurrent.py"
subprocess.run(["python3", current])

parking = "/Users/alejandromorales/Desktop/parking/locateParking.py"
subprocess.run(["python3", parking])

scrapper = "/Users/alejandromorales/Desktop/parking/scrapper.py"
subprocess.run(["python3", scrapper])
