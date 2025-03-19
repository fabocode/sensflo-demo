#include "RealPressureSensor.h"
#include <Arduino.h>

RealPressureSensor::RealPressureSensor(int8_t resetPin, int8_t EOC_Pin,
                             uint16_t PSI_min, uint16_t PSI_max,
                             float OUTPUT_min, float OUTPUT_max,
                             float convFactor)
  : mpr(resetPin, EOC_Pin, PSI_min, PSI_max, OUTPUT_min, OUTPUT_max, convFactor)
{
}

bool RealPressureSensor::begin(uint8_t i2c_addr, TwoWire *twoWire) {
  return mpr.begin(i2c_addr, twoWire);
}

float RealPressureSensor::readPressure_hPa() {
  // Adafruit_MPRLS::readPressure() returns pressure in hPa.
  return mpr.readPressure();
}
