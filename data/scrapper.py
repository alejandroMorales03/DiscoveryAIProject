from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import csv
from datetime import datetime
import schedule
import time

def scrape_and_save_data():
    driver = webdriver.Safari()
    driver.get('https://parking.fiu.edu')

    try:
        wait = WebDriverWait(driver, 10)
        element_present = wait.until(EC.presence_of_element_located((By.XPATH, '//*[@id="parking-widget"]/div/div/ul/li[6]/div/div/div[2]/div/div/strong')))

        iterations = 6
        row_data = [datetime.now().strftime('%H:%M:%S')]

        with open("location_data.csv", "a") as file:
            csv_writer = csv.writer(file, delimiter=',')
            for i in range(iterations):
                element = driver.find_element(By.XPATH, '//*[@id="parking-widget"]/div/div/ul/li[' + str(i + 1) + ']/div/div/div[2]/div/div/strong')
                element_text = element.text
                row_data.append(element_text)
            csv_writer.writerow(row_data)
            file.close()

    except Exception as e:
        print(f"Error: {e}")

    driver.quit()

# Schedule the scraping task to run every hour
schedule.every(0.25).hours.do(scrape_and_save_data)

while True:
    schedule.run_pending()
    time.sleep(1)
