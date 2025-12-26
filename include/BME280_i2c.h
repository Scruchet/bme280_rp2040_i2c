#ifndef BMP280_H
#define BMP280_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define BME280

#define I2C_PORT i2c1
#define I2C_SDA 2
#define I2C_SCL 3
#define I2C_SPEED 100000

#define ADDR _u(0x76)
#define BME_280_ID _u(0x60)
#define BMP_280_ID _u(0x58)

// Register address
#ifdef BME280

// Humidity registers
#define HUM_LSB_REG _u(0xFE)
#define HUM_MSB_REG _u(0xFD)

// Temperature registers
#define TEMP_XLSB_REG _u(0xFC)
#define TEMP_LSB_REG _u(0xFB)
#define TEMP_MSB_REG _u(0xFA)

// Pressure registers
#define PRESS_XLSB_REG _u(0xF9)
#define PRESS_LSB_REG _u(0xF8)
#define PRESS_MSB_REG _u(0xF7)

// Control and configuration registers
#define CONFIG_REG _u(0xF5)
#define CTRL_MEAS_REG _u(0xF4)
#define STATUS_REG _u(0xF3)
#define CTRL_HUM_REG _u(0xF2)

// Reset and ID
#define RESET_REG _u(0xE0)
#define ID_REG _u(0xD0)

// Calibration registers (0..25)
#define CALIB00_REG _u(0x88)
#define CALIB01_REG _u(0x89)
#define CALIB02_REG _u(0x8A)
#define CALIB03_REG _u(0x8B)
#define CALIB04_REG _u(0x8C)
#define CALIB05_REG _u(0x8D)
#define CALIB06_REG _u(0x8E)
#define CALIB07_REG _u(0x8F)
#define CALIB08_REG _u(0x90)
#define CALIB09_REG _u(0x91)
#define CALIB10_REG _u(0x92)
#define CALIB11_REG _u(0x93)
#define CALIB12_REG _u(0x94)
#define CALIB13_REG _u(0x95)
#define CALIB14_REG _u(0x96)
#define CALIB15_REG _u(0x97)
#define CALIB16_REG _u(0x98)
#define CALIB17_REG _u(0x99)
#define CALIB18_REG _u(0x9A)
#define CALIB19_REG _u(0x9B)
#define CALIB20_REG _u(0x9C)
#define CALIB21_REG _u(0x9D)
#define CALIB22_REG _u(0x9E)
#define CALIB23_REG _u(0x9F)
#define CALIB24_REG _u(0xA0)
#define CALIB25_REG _u(0xA1)
#define CALIB26_REG _u(0xE1)
#define CALIB27_REG _u(0xE2)
#define CALIB28_REG _u(0xE3)
#define CALIB29_REG _u(0xE4)
#define CALIB30_REG _u(0xE5)
#define CALIB31_REG _u(0xE6)
#define CALIB32_REG _u(0xE7)
#define CALIB33_REG _u(0xE8)
#define CALIB34_REG _u(0xE9)
#define CALIB35_REG _u(0xEA)
#define CALIB36_REG _u(0xEB)
#define CALIB37_REG _u(0xEC)
#define CALIB38_REG _u(0xED)
#define CALIB39_REG _u(0xEE)
#define CALIB40_REG _u(0xEF)
#define CALIB41_REG _u(0xF0)

#define RESET_VALUE _u(0xB6)

#define HUM_OVERSAMPLING_0_VALUE _u(0x0)
#define HUM_OVERSAMPLING_1_VALUE _u(0x1)
#define HUM_OVERSAMPLING_2_VALUE _u(0x2)
#define HUM_OVERSAMPLING_4_VALUE _u(0x3)
#define HUM_OVERSAMPLING_8_VALUE _u(0x4)
#define HUM_OVERSAMPLING_16_VALUE _u(0x5)

#define PRESS_OVERSAMPLING_0_VALUE _u(0x00)
#define PRESS_OVERSAMPLING_1_VALUE _u(0x04)
#define PRESS_OVERSAMPLING_2_VALUE _u(0x08)
#define PRESS_OVERSAMPLING_4_VALUE _u(0x0F)
#define PRESS_OVERSAMPLING_8_VALUE _u(0x10)
#define PRESS_OVERSAMPLING_16_VALUE _u(0x14)

#define TEMP_OVERSAMPLING_0_VALUE _u(0x0)
#define TEMP_OVERSAMPLING_1_VALUE _u(0x20)
#define TEMP_OVERSAMPLING_2_VALUE _u(0x40)
#define TEMP_OVERSAMPLING_4_VALUE _u(0x60)
#define TEMP_OVERSAMPLING_8_VALUE _u(0x80)
#define TEMP_OVERSAMPLING_16_VALUE _u(0xA0)

#define SLEEP_MODE _u(0x00)
#define FORCED_MODE _u(0x01)
#define NORMAL_MODE _u(0x03)

#define STANDBY_0_5_ms _u(0x00)
#define STANDBY_62_5_ms _u(0x20)
#define STANDBY_125_ms _u(0x40)
#define STANDBY_250_ms _u(0x60)
#define STANDBY_500_ms _u(0x80)
#define STANDBY_1000ms _u(0xA0)
#define STANDBY_10ms _u(0xC0)
#define STANDBY_20ms _u(0xE0)

#define FILTER_OFF _u(0x00)
#define FILTER_COEFFICIENT_2 _u(0x04)
#define FILTER_COEFFICIENT_4 _u(0x08)
#define FILTER_COEFFICIENT_8 _u(0x0C)
#define FILTER_COEFFICIENT_16 _u(0x10)


uint32_t get_raw_humidity();
uint32_t get_compensate_humidity();
float get_humidity_percentage();

#endif

#ifdef BMP280
#define TEMP_XLSB_REG _u(0xFC)
#define TEMP_LSB_REG _u(0xFB)
#define TEMP_MSB_REG _u(0xFA)
#define PRESS_XLSB_REG _u(0xF9)
#define PRESS_LSB_REG _u(0xF8)
#define PRESS_MSB_REG _u(0xF7)
#define CONFIG_REG _u(0xF5)
#define CTRL_MEAS_REG _u(0xF4)
#define STATUS_REG _u(0xF3)
#define RESET_REG _u(0xE0)
#define ID_REG _u(0xD0)
#define CALIB_25_REG _u(0xA1)
#define CALIB_24_REG _u(0xA0)
#define CALIB_23_REG _u(0x9F)
#define CALIB_22_REG _u(0x9E)
#define CALIB_21_REG _u(0x9D)
#define CALIB_20_REG _u(0x9C)
#define CALIB_19_REG _u(0x9B)
#define CALIB_18_REG _u(0x9A)
#define CALIB_17_REG _u(0x99)
#define CALIB_16_REG _u(0x98)
#define CALIB_15_REG _u(0x97)
#define CALIB_14_REG _u(0x96)
#define CALIB_13_REG _u(0x95)
#define CALIB_12_REG _u(0x94)
#define CALIB_11_REG _u(0x93)
#define CALIB_10_REG _u(0x92)
#define CALIB_9_REG _u(0x91)
#define CALIB_8_REG _u(0x90)
#define CALIB_7_REG _u(0x8F)
#define CALIB_6_REG _u(0x8E)
#define CALIB_5_REG _u(0x8D)
#define CALIB_4_REG _u(0x8C)
#define CALIB_3_REG _u(0x8B)
#define CALIB_2_REG _u(0x8A)
#define CALIB_1_REG _u(0x89)
#define CALIB_0_REG _u(0x88)
#endif

void init();
uint8_t read_reg(uint8_t address);
void sensor_id();
void print_uint8_binary(uint8_t value);
void reset();
void set_humidity_oversampling(uint8_t oversampling);
void set_temperature_oversampling(uint8_t oversampling);
void set_pressure_oversampling(uint8_t oversampling);
void set_mode(uint8_t mode);
void set_standby(uint8_t standby);
void set_iir_coefficent(uint8_t coefficent);
void enable_spi();
void disable_spi();
int32_t get_t_fine();
uint32_t get_raw_press();
uint32_t get_compensate_pressure();
float get_pressure_in_Pa();
uint32_t get_raw_temp();
int32_t get_compensate_temperature();
float get_temp_celsius();

#endif