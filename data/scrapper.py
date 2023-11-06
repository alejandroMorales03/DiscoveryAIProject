from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import csv
from datetime import datetime

driver = webdriver.Safari()

# Navigate to the webpage with JavaScript content
driver.get('https://parking.fiu.edu')

# Wait for a specific element to be present (adjust timeout as needed)
wait = WebDriverWait(driver, 10)
element_present = wait.until(EC.presence_of_element_located((By.XPATH, '//*[@id="parking-widget"]/div/div/ul/li[6]/div/div/div[2]/div/div/strong')))

# Once the element is present, you can scrape it
iterations = 6
with open("location_data.csv", "a") as file:
    csv_writer = csv.writer(file, delimiter=',')  # Specify the delimiter as a comma
    row_data = [datetime.now().strftime('%Y-%m-%d %H:%M:%S')]  # Add the current time
    for i in range(iterations):
        element = driver.find_element(By.XPATH, '//*[@id="parking-widget"]/div/div/ul/li[' + str(i+1) + ']/div/div/div[2]/div/div/strong')
        element_text = element.text
        row_data.append(element_text)  # Add the element's text to the row_data list
    csv_writer.writerow(row_data)  # Write the row_data list as a row
    file.close()

# Close the WebDriver when done
driver.quit()
