# Air Pressure Sensor BLE Demo

This demo project for the ESP32-S3 illustrates how to measure air pressure using two Adafruit MPRLS sensors (0–25 PSI) via I2C and stream the readings over Bluetooth Low Energy (BLE). In addition, the firmware demonstrates a counter that increments whenever both sensor readings rise above 10 PSI. If the real sensor hardware is not available, a fake sensor implementation simulates the pressure values.

## Driver Hardware Approach Notes
This demo uses the Adafruit MPRLS sensor as the selected hardware to fit the task requirements.

- I have decided to use this sensor because it matches with the 0-25 PSI Max pressure sensor range readings.
- The only drawback this sensor has is that it can only work with one I2C Slave Address.
- This requires that we use two different I2C buses, the ESP32-S3 has hardware capabilities to support this.

## Steps to Implement Sensor Driver
1. Research for options that can be considered to fit the project requirements, this Air Pressure Sensor required to work at 25 PSI max
2. Study the datasheet to understand its communication protocol (this can vary depending of the hardware selected), also check if the hardware selected can be managed by the microcontrollers hardware.
3. Plan the hardware Connections
4. Write code for initialization, this should start communication with the hardware and allow to fetch data from it. (If team allows it, start with TDD development).
5. Write code for data actquisition.
6. Convert raw data into readable physical data units
7. Start Error Checking and check corner cases
8. Test the driver and check corner cases.
9. Integrate driver into project's source system code.

## Overview

The project achieves the following:
- **Dual Sensor Measurements:**  
  Two MPRLS sensors are connected on separate I2C buses (the default bus and a secondary bus) to avoid address conflicts.
- **Fallback Dummy Sensor:**  
  If a real sensor is not detected on either bus, a dummy sensor is used that simulates realistic pressure data.
- **Data Processing:**  
  Sensor readings are converted from hPa (as provided by the Adafruit library) into PSI.
- **Counter Mechanism:**  
  A counter increments on a rising edge event when both sensor values exceed 10 PSI. The counter value is output both over Serial and via a dedicated BLE characteristic.
- **BLE Communication:**  
  The ESP32-S3 functions as a BLE server advertising two characteristics:
  - One characteristic transmits the current sensor readings (in PSI).
  - A second characteristic transmits the counter value.

## Requirements

- **Hardware:**
  - ESP32-S3 development board (or another compatible ESP32 board with multiple I2C capabilities)
  - Two Adafruit MPRLS Pressure Sensor Breakouts (0–25 PSI) or equivalent hardware
  - Appropriate wiring for I2C connections (using two separate I2C buses: e.g., default Wire and Wire1)
  - Optional: BLE-capable smartphone or tablet with an app like [nRF Connect](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Connect-for-mobile) for testing BLE notifications

- **Software:**
  - Arduino IDE with ESP32 board support installed
  - Libraries:
    - Adafruit_MPRLS (provided by [Adafruit](https://github.com/adafruit/Adafruit_MPRLS))
    - BLEDevice, BLEServer, BLEUtils, BLE2902 (ESP32 BLE Arduino libraries)
    - FreeRTOS (Packaged with the ESP32 Arduino framework)
