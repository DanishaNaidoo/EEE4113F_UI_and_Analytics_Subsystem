# EEE4113F_UI_and_Analytics_Subsystem
Github repo for the EEE4113F - Group 9 - User Interface and Analytics Subsystem 

# Description
This project provides a way to wirelessly transfer data from an ESP32 microcontroller to a web page by setting up a Wi-Fi access point, asynchronous server, and web application. The ESP32 acts as a Wi-Fi access point, allowing devices to connect to it and send/receive data. The asynchronous server handles incoming requests from connected devices and serves as an interface between the ESP32 and the web application.

The web application allows users to view close to real-time temperature data. It provides a user-friendly interface for interacting with the system remotely, making it easy to monitor temperature levels without needing to make physical contact with the nest. 

This system is a part of a larger nest temperature maintaining and monitoring project, which aims to create an efficient solution for maintaining optimal temperature levels in a nest or enclosure. By wirelessly transmitting temperature data to a web page, users can monitor the temperature conditions and ensure the comfort and well-being of the inhabitants.

# Contents
The contents of this repo include:
1. The Arduino IDE Sketch upload: This file sets up the access point and server
2. The index.html: This file contains the web page HTML, CSS styling and JavaScript
3. The data.txt: This file contains data from which the ESP32 can read from
4. The README file: This explains the project contents 

# File Structure
The following file structure should be kept for the project as it allows the ESP32 to access the index.html and data.txt using the SPIFFS filesystem uploader:
README
EEE4113F_Final/
-> EEE4113F_Final.ino
-> data/
  -> index.html
  -> data.txt

# Example usage
1. Upload the sketch to the ESP32 using the Arduino IDE
2. Start the program
3. Connect to the access point titled "Hornbill Detect - ESP32 AP"
4. Enter the following IP address into a browser: 192.168.4.1
5. Once loaded, the user interface will display and can be used
