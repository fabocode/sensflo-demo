#include "FakePressureSensor.h"

// Initialize 650 and 750 hPa. For testing purposes, we will oscillate between these values.
FakePressureSensor::FakePressureSensor() : pressure(650.0), delta(5.0) {
}

bool FakePressureSensor::begin(uint8_t i2c_addr, TwoWire *wire) {
  // For the dummy sensor, let's simply ignore the parameters.
  return true;
}

// Simulate a reading that oscillates between 650 and 750 hPa. (PSI range: 9.43 to 10.88)
// This way we ensure that the BLE server will receive different values.
float FakePressureSensor::readPressure_hPa() {
  pressure += delta;

  // Reverse direction when limits are hit
  if (pressure >= 750.0) {
    pressure = 750.0;
    delta = -5.0;
  } else if (pressure <= 650.0) {
    pressure = 650.0;
    delta = 5.0;
  }

  return pressure;
}
