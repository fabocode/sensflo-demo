#include <Arduino.h>
#include <Wire.h>
#include "Config.h"
#include "PressureSensor.h"
#include "RealPressureSensor.h"
#include "FakePressureSensor.h"

// FreeRTOS includes
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "BLEServerMgr.h"

RealPressureSensor realSensor1;  // Air Press Sensor 1 on default I2C (Wire)
RealPressureSensor realSensor2;  // Air Press Sensor 2 on alternate I2C (Wire1)
FakePressureSensor fakeSensor1;  // Dummy sensor 1
FakePressureSensor fakeSensor2;  // Dummy sensor 2

PressureSensor* sensor1 = nullptr;
PressureSensor* sensor2 = nullptr;

// Mutex to protect sensor access.
SemaphoreHandle_t sensorMutex;

// BLE manager
BLEServerMgr bleServerMgr;

PressureSensor* initSensor(RealPressureSensor &realSensor, FakePressureSensor &fakeSensor,
                  uint8_t i2c_addr, TwoWire* wire, const char* sensorLabel) {
  if (realSensor.begin(i2c_addr, wire)) {
    Serial.print(sensorLabel);
    Serial.println(": Real sensor initialized.");

    return &realSensor;
  } else {
    Serial.print(sensorLabel);
    Serial.println(": Real sensor not detected. Using fake sensor.");

    fakeSensor.begin(i2c_addr, wire);

    return &fakeSensor;
  }
}

void sensorReadingTask(void * parameter) {
  char buf[50];
  const float THRESHOLD_PSI = 10.0; // Threshold for both sensors in PSI.
  bool aboveThreshold = false;  // Tracks if both sensors were above threshold on previous reading.
  uint32_t counter = 0;

  for (;;) {
    if (xSemaphoreTake(sensorMutex, portMAX_DELAY) == pdTRUE) {
      float pressure1_PSI = sensor1->readPressurePSI();
      float pressure2_PSI = sensor2->readPressurePSI();

      snprintf(buf, sizeof(buf), "S1: %.2f, S2: %.2f", pressure1_PSI, pressure2_PSI);
      Serial.println(buf);

      // Check if both sensors exceed 10 PSI.
      if (pressure1_PSI > THRESHOLD_PSI && pressure2_PSI > THRESHOLD_PSI) {
        if (!aboveThreshold) {  // Rising edge detected.
          counter++;

          Serial.print("Counter incremented: ");
          Serial.println(counter);

          // Update the counter characteristic.
          bleServerMgr.updateCounterData(counter);
          aboveThreshold = true;
        }
      } else {
        aboveThreshold = false;
      }

      // Update the sensor reading characteristic if BLE client is connected.
      if (bleServerMgr.isConnected()) {
        bleServerMgr.updatePressureData(buf);
      }

      xSemaphoreGive(sensorMutex);
    }

    vTaskDelay(SENSOR_READ_DELAY / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Air Pressure Sensors BLE Demo");

  sensorMutex = xSemaphoreCreateMutex();

  // Initialize sensor 1 on default I2C bus (Wire)
  sensor1 = initSensor(realSensor1, fakeSensor1, MPRLS_I2C_ADDRESS, &Wire, "Sensor 1 on Wire");

  // Initialize sensor 2 on I2C bus (Wire1)
  Wire1.begin(I2C2_SDA_PIN, I2C2_SCL_PIN);
  sensor2 = initSensor(realSensor2, fakeSensor2, MPRLS_I2C_ADDRESS, &Wire1, "Sensor 2 on Wire1");

  bleServerMgr.init("AirPressureSensor");
  xTaskCreate(sensorReadingTask, "SensorReadingTask", SENSOR_TASK_STACK_SIZE, NULL, SENSOR_TASK_PRIORITY, NULL);
}

void loop() {
  vTaskDelay(SENSOR_READ_DELAY / portTICK_PERIOD_MS);
}
