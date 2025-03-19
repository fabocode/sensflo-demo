# OTA Update Demo Using ESP32-S3

## Overview
This project demonstrates how to remotely update Arduino or Arduino-compatible hardware using Over-the-Air (OTA) updates. The source code uses an ESP32-S3 and the ArduinoOTA library to implement remote firmware updates over WiFi local network.

## Setup and Usage
1. **Configure WiFi Credentials:**
   - Edit the `secrets.h` file with your WiFi SSID and PASSWORD.
2. **Compile and Upload:**
   - Use the Arduino IDE to compile and upload the code to your ESP32-S3.
3. **OTA Update Process:**
   - Once the device connects to your WiFi network, its IP address will be printed to the Serial Monitor.
   - Use the Arduino IDE’s OTA upload feature to update the firmware remotely. This basically uses the ESP32 to "publish" its IP local address so that you can select it in the Arduino IDE as a wireless port, all the code edited after the `ArduinoOTA.handle();` should be updated once the firmware update is completed.

## Files Description

- **`sensFloDemo.ino`:** The main sketch responsible for WiFi connectivity, non-blocking LED blinking as visual feedback, and handling OTA updates.
- **`OTAWiFiUpdater.h / OTAWiFiUpdater.cpp`:** These files encapsulate all OTA-related functionalities including callbacks and initialization.
- **`secrets.h`:** A header file that stores sensitive WiFi credentials (SSID and PASSWORD).

## Requirements
- **Software:**
  - Arduino IDE.
  - ESP32 Board Package installed in the IDE.
  - Required libraries:
    - WiFi
    - ESPmDNS
    - WiFiUdp
    - ArduinoOTA

- **Network:**
  - A working WiFi network.
  - Correct WiFi credentials set in the `secrets.h` file.

## Hardware Used
- **ESP32-S3**
- **Built-In LED:** Used to provide visual feedback during operation (blinking to indicate active status), you can disconnect the ESP32 from here to try different changes to the source code to see how OTA affects the microcontroller behavior.


## Additional Notes
- **Security:**  
  OTA authentication is enabled using a password (default is "admin"). For production deployments, is recommended consider using a stronger password or its MD5 hash.
