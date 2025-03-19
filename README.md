# Arduino Based IoT Demonstration Projects

## Overview
This repository contains multiple demonstration projects for the ESP32-S3, Including:
- **Over-the-Air (OTA) updates**
- **Air pressure sensor integration**
- **A counter mechanism based on pressure readings**

## Features Implemented

### 1. OTA Update for Arduino-Compatible Hardware
- Demonstrates how to remotely update Arduino-compatible firmware using **OTA (Over-the-Air)** updates over WiFi.
- Uses an **ESP32-S3** running the **ArduinoOTA** library.
- Enables remote firmware updates via a **WiFi local network**, allowing the ESP32 to be programmed wirelessly.
- Provides **visual feedback** using a built-in LED.

### 2 and 3. Air Pressure Sensor Integration with Dual I2C Bus
- Demonstrates how to read air pressure data from **two Adafruit MPRLS sensors** (0–25 PSI).
- Utilizes **two separate I2C buses** due to the sensor's single address limitation.
- Includes a **fallback dummy sensor** that simulates pressure values in case real hardware is unavailable.
- Implements a **counter that increments** when both pressure sensors detect values above **10 PSI**.
- Provides a **BLE interface** to broadcast:
  - Current sensor readings (in PSI).
  - The counter value.
- Allows communication over **Bluetooth Low Energy (BLE)** for remote monitoring.

## Hardware Requirements

### Hardware:
- **ESP32-S3 development board**

## Additional Notes
- The OTA functionality requires a **local WiFi connection**.
- The pressure sensor demo supports **simulated data** when hardware is not connected.
