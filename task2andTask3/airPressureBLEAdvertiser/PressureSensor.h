#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include <Wire.h>
#include "Config.h"

class PressureSensor {
public:
  virtual ~PressureSensor() {}

  virtual bool begin(uint8_t i2c_addr = 0x18, TwoWire *wire = &Wire) = 0;

  // Read the sensor and return pressure in hPa.
  virtual float readPressure_hPa() = 0;

  // Return pressure in PSI
  virtual float readPressurePSI() {
    return readPressure_hPa() * HPA_TO_PSI_CONVERSION;
  }
};

#endif  // PRESSURE_SENSOR_H
