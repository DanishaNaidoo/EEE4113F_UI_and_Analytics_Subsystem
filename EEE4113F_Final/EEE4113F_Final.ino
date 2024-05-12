/* EEE4113F Design Project - Hornbill Detect Server and AP
 * By Danisha Naidoo (NDXDAN019) 
 * 1st April 2024
 * 
 * Description:
 * This program reads data from a txt file and wirelessly sends it to a web page using the ESP-WROOM-32 microcontroller. 
 * It sets up a Wi-Fi access point, asynchronous server, and utilizes the SPIFFS filesystem to interact with the web page and other files.
 * 
 * License: 
 * ***********
   Rui Santos
   Complete project details at https://RandomNerdTutorials.com
  
   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files.
  
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
   ***********
 */

// Import libraries 
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

// Define access point name and password
const char* ssid     = "HornBill Detect - ESP32 AP";
const char* password = "123456789";

// Set web server port number to 80
AsyncWebServer server(80);


// Function to read the temperature data from a txt file stored on the ESP32 flash memory
String readFileTemperature() {
  File file = SPIFFS.open("/data.txt", "r");
  if (!file) {
    Serial.println("Failed to open data file");
    return "Failed to read temperature";
  }

  // Skip header line
  file.readStringUntil('\n');

  // Read temperature data
  String temperature;
  while (file.available()) {
    String line = file.readStringUntil('\n');
    int commaIndex = line.lastIndexOf(',');
    if (commaIndex == -1) {
      Serial.println("Invalid data format in the file");
      file.close();
      return "Invalid data format in the file";
    }
    temperature += line.substring(commaIndex + 1) + "\n";
  }

  file.close();
  return temperature;
}


// Function to read the time data from a txt file stored on the ESP32 flash memory
String readFileTime() {
  File file = SPIFFS.open("/data.txt", "r");
  if (!file) {
    Serial.println("Failed to open data file");
    return "Failed to read time";
  }

  // Skip header line
  file.readStringUntil('\n');

  // Read date-time data
  String dateAndTime;
  while (file.available()) {
    String line = file.readStringUntil('\n');
    int commaIndex = line.indexOf(',');
    int secondCommaIndex = line.indexOf(',', commaIndex + 1);
    int thirdCommaIndex = line.indexOf(',', secondCommaIndex + 1);
    // Check if the line has enough commas
    if (commaIndex == -1 || secondCommaIndex == -1 || thirdCommaIndex == -1) {
      Serial.println("Invalid data format in the file");
      file.close();
      return "Invalid data format in the file";
    }
    String date = line.substring(line.indexOf(',') + 1, secondCommaIndex);
    String time = line.substring(secondCommaIndex + 1, thirdCommaIndex); // Assuming time format HH:MM:SS

    // Ensure consistent date format (YYYY-MM-DD)
    String formattedDate = formatDate(date);
    
    // Adjust time format to "YYYY-MM-DDTHH:MM:SS"
    time = formattedDate + "T" + time;
    dateAndTime += time + "\n";
  }

  file.close();
  return dateAndTime;
}

// Function to format the date string to "YYYY-MM-DD"
String formatDate(String dateString) {
  // Split the date string by '-' separator
  String parts[3];
  int partIndex = 0;
  for (int i = 0; i < dateString.length(); i++) {
    if (dateString[i] == '-') {
      partIndex++;
    } else {
      parts[partIndex] += dateString[i];
    }
  }

  // Ensure each part has two digits (pad with zero if necessary)
  for (int i = 0; i < 3; i++) {
    if (parts[i].length() == 1) {
      parts[i] = "0" + parts[i];
    }
  }

  // Combine the parts to form the formatted date string
  return parts[0] + "-" + parts[1] + "-" + parts[2];
}

void setup() {
  Serial.begin(115200);

  // Initialize SPIFFS filesystem 
  if(!SPIFFS.begin()){
  Serial.println("An Error has occurred while mounting SPIFFS");
  return;
  }

  // Create access point and display IP address to serial monitor
  Serial.println("Setting Wi-Fi access point…");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.println("AP IP address: ");
  Serial.println(IP);

  // Handle requests for web page (index.html)
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });

  // Handle requests for data
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readFileTemperature().c_str());
  });

  server.on("/time", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readFileTime().c_str());
  });

  server.begin();
}

void loop(){
  
}
