#ifndef REAL_PRESSURE_SENSOR_H
#define REAL_PRESSURE_SENSOR_H

#include "PressureSensor.h"
#include <Adafruit_MPRLS.h>
#include <Wire.h>

class RealPressureSensor : public PressureSensor {
public:
  /**
   * Constructor.
   * @param resetPin Optional hardware reset pin (-1 to skip).
   * @param EOC_Pin Optional End-of-Conversion pin (-1 to poll status).
   * @param PSI_min Minimum pressure in PSI (default 0).
   * @param PSI_max Maximum pressure in PSI (default 25).
   * @param OUTPUT_min Lower percentage of ADC range corresponding to PSI_min (default 10%).
   * @param OUTPUT_max Upper percentage of ADC range corresponding to PSI_max (default 90%).
   * @param convFactor Conversion factor from PSI to hPa (default: PSI_to_HPA).
   */
  RealPressureSensor(int8_t resetPin = -1, int8_t EOC_Pin = -1,
                             uint16_t PSI_min = 0, uint16_t PSI_max = 25,
                             float OUTPUT_min = 10.0, float OUTPUT_max = 90.0,
                             float convFactor = PSI_to_HPA);

  bool begin(uint8_t i2c_addr = MPRLS_DEFAULT_ADDR, TwoWire *twoWire = &Wire) override;

  // Read pressure in hPa
  float readPressure_hPa() override;

private:
  Adafruit_MPRLS mpr;
};

#endif  // REAL_PRESSURE_SENSOR_H
