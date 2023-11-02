from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import csv


driver = webdriver.Safari()

# Navigate to the webpage with JavaScript content
driver.get('https://parking.fiu.edu')

# Wait for a specific element to be present (adjust timeout as needed)
wait = WebDriverWait(driver, 10)
element_present = wait.until(EC.presence_of_element_located((By.XPATH, '//*[@id="parking-widget"]/div/div/ul/li[6]/div/div/div[2]/div/div/strong')))

# Once the element is present, you can scrape it
iterations = 6
with open("location_data.csv", "a") as file:
    for i in range(iterations):
        element = driver.find_element(By.XPATH, '//*[@id="parking-widget"]/div/div/ul/li[' + str(i+1) + ']/div/div/div[2]/div/div/strong')
        element_text = element.text
        file.write('\t\t\t\t' + element_text)
    file.close()

# Print or process the scraped data


# Close the WebDriver when done
driver.quit()
