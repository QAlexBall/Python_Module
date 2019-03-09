from selenium import webdriver
import time
 
options = webdriver.ChromeOptions()
options.add_argument('--ignore-certificate-errors')
options.add_argument("--test-type")
options.binary_location = "/usr/bin/google-chrome"
driver = webdriver.Chrome(chrome_options=options)
driver.get('https://python.org')
