#ifndef FAKE_PRESSURE_SENSOR_H
#define FAKE_PRESSURE_SENSOR_H

#include "PressureSensor.h"
#include <Wire.h>

// Dummy sensor that simulates pressure readings.
class FakePressureSensor : public PressureSensor {
private:
  // Simulated pressure value.
  float pressure;

  // Change in pressure per reading.
  float delta;

public:
  FakePressureSensor();
  bool begin(uint8_t i2c_addr = 0x18, TwoWire *wire = &Wire) override;
  float readPressure_hPa() override;
};

#endif  // FAKE_PRESSURE_SENSOR_H
