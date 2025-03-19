#ifndef CONFIG_H
#define CONFIG_H

// I2C settings for the MPRLS sensors
#define MPRLS_I2C_ADDRESS      0x18  // default sensor address (can't be changed by datasheet)

// I2C pins for second I2C bus (Wire1) on ESP32-S3
#define I2C2_SDA_PIN           21
#define I2C2_SCL_PIN           22

// Task thread parameters
#define SENSOR_READ_DELAY      1000    // delay between sensor readings (ms)
#define SENSOR_TASK_STACK_SIZE 4096    // stack size for sensor task
#define SENSOR_TASK_PRIORITY   1       // task priority

// conversion: 1 hPa ≈ 0.0145038 PSI
#define HPA_TO_PSI_CONVERSION 0.0145038

#endif  // CONFIG_H
