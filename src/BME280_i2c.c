#include "BME280_i2c.h"
/**
 * @brief Sensor initialisation with the right i2c interface and speed. Setting the right pins and internal pull-up.
 *
 */
void init()
{
    stdio_init_all();

    // I2C Initialisation. Using it at 100kHz.
    i2c_init(I2C_PORT, 100 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

/**
 * @brief Read 1 Byte for the register's sensor
 *
 * @param address register that will read
 * @return uint8_t : data in the register
 */

uint8_t read_reg(uint8_t address)
{
    uint8_t dest = address;
    uint8_t data;
    i2c_write_blocking(I2C_PORT, ADDR, &dest, 1, true);
    i2c_read_blocking(I2C_PORT, ADDR, &data, 1, false);
    return data;
}

/**
 * @brief Tell you is your sensor is BME280 or BMP280 by looking at the id register.
 * Prints which one have been dectected and prints the ID
 * 0x58 --> BMP280
 * 0x60 --> BME280
 *
 */

void sensor_id()
{
    uint8_t id = read_reg(ID_REG);
    switch (id)
    {
    case BMP_280_ID:
        printf("BMP280 detected, ID = 0x58\n");
        break;
    case BME_280_ID:
        printf("BME280 detected, ID = 0x60\n");
        break;
    default:
        printf("No BME/BMP280 sensor detected");
    }
}

/**
 * @brief Print each bits from a uint8_t as text (usefull during debugging).
 *
 * @param value uint8_t that you want to print.
 */
void print_uint8_binary(uint8_t value)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

/**
 * @brief Reset the sensor.
 *
 */
void reset()
{
    uint8_t data[2] = {ID_REG, RESET_VALUE};
    i2c_write_blocking(I2C_PORT, ADDR, data, 2, false);
}

/**
 * @brief Set the humidity oversampling (none, 1 , 2 , 4 , 8 , 16)
 *
 * @param oversampling [0,1,2,4,8,16]
 */
void set_humidity_oversampling(uint8_t oversampling)
{
    uint8_t data[2];
    data[0] = CTRL_HUM_REG;
    switch (oversampling)
    {
    case 0:
        data[1] = HUM_OVERSAMPLING_0_VALUE;
        break;
    case 1:
        data[1] = HUM_OVERSAMPLING_1_VALUE;
        break;
    case 2:
        data[1] = HUM_OVERSAMPLING_2_VALUE;
        break;
    case 4:
        data[1] = HUM_OVERSAMPLING_4_VALUE;
        break;
    case 8:
        data[1] = HUM_OVERSAMPLING_8_VALUE;
        break;
    case 16:
        data[1] = HUM_OVERSAMPLING_16_VALUE;
        break;
    default:
        printf("Wrong humidity oversampling parameter, no oversampling applied.\n");
        data[1] = HUM_OVERSAMPLING_0_VALUE;
        break;
    }
    i2c_write_blocking(I2C_PORT, ADDR, data, 2, false);
}

/**
 * @brief Set the temperature oversampling (none, 1 , 2 , 4 , 8 , 16)
 *
 * @param oversampling [0,1,2,4,8,16]
 */
void set_temperature_oversampling(uint8_t oversampling)
{
    uint8_t data[2];

    data[0] = CTRL_MEAS_REG;

    // getting the current state of the register
    i2c_write_blocking(I2C_PORT, ADDR, data, 1, false);
    i2c_read_blocking(I2C_PORT, ADDR, &data[1], 1, false);

    data[1] &= 0x1F; // clear temperature oversampling bits [7:5]

    switch (oversampling)
    {
    case 0:
        // data[1] |= TEMP_OVERSAMPLING_0_VALUE; Already put to 0
        break;
    case 1:
        data[1] |= TEMP_OVERSAMPLING_1_VALUE;
        break;
    case 2:
        data[1] |= TEMP_OVERSAMPLING_2_VALUE;
        break;
    case 4:
        data[1] |= TEMP_OVERSAMPLING_4_VALUE;
        break;
    case 8:
        data[1] |= TEMP_OVERSAMPLING_8_VALUE;
        break;
    case 16:
        data[1] |= TEMP_OVERSAMPLING_16_VALUE;
        break;
    default:
        printf("Wrong temperature oversampling parameter, no oversampling applied.\n");
        // data[1] = TEMP_OVERSAMPLING_0_VALUE; Already put to 0;
        break;
    }
    i2c_write_blocking(I2C_PORT, ADDR, data, 2, false);
}

/**
 * @brief Set the pressure oversampling (none, 1 , 2 , 4 , 8 , 16)
 *
 * @param oversampling [0,1,2,4,8,16]
 */
void set_pressure_oversampling(uint8_t oversampling)
{
    uint8_t data[2];

    data[0] = CTRL_MEAS_REG;

    // getting the current state of the register
    i2c_write_blocking(I2C_PORT, ADDR, data, 1, false);
    i2c_read_blocking(I2C_PORT, ADDR, &data[1], 1, false);

    data[1] &= 0xE3; // clear pressure oversampling bits [5:2]

    switch (oversampling)
    {
    case 0:
        // data[1] |= PRESS_OVERSAMPLING_0_VALUE; Already put to 0
        break;
    case 1:
        data[1] |= PRESS_OVERSAMPLING_1_VALUE;
        break;
    case 2:
        data[1] |= PRESS_OVERSAMPLING_2_VALUE;
        break;
    case 4:
        data[1] |= PRESS_OVERSAMPLING_4_VALUE;
        break;
    case 8:
        data[1] |= PRESS_OVERSAMPLING_8_VALUE;
        break;
    case 16:
        data[1] |= PRESS_OVERSAMPLING_16_VALUE;
        break;
    default:
        printf("Wrong pressure oversampling parameter, no oversampling applied.\n");
        // data[1] = PRESS_OVERSAMPLING_0_VALUE; Already put to 0;
        break;
    }
    i2c_write_blocking(I2C_PORT, ADDR, data, 2, false);
}

/**
 * @brief Set the working mode [sleep, forced, normal]
 *
 * @param mode [0x00,0x01,0x03]
 */
void set_mode(uint8_t mode)
{
    uint8_t data[2];

    data[0] = CTRL_MEAS_REG;

    // getting the current state of the register
    i2c_write_blocking(I2C_PORT, ADDR, data, 1, false);
    i2c_read_blocking(I2C_PORT, ADDR, &data[1], 1, false);

    // Applying a mask to that register to avoid data loose
    data[1] &= 0xFC;
    data[1] |= mode;

    i2c_write_blocking(I2C_PORT, ADDR, data, 2, false);
}

/**
 * @brief Set the standby time for the temperature only work in normal mode
 * Skipped in the other mode
 *
 * @param standby constant defined in the .h file
 */
void set_standby(uint8_t standby)
{
    if ((standby >> 5) <= 0x07 && (standby >> 5) >= 0x00)
    {
        uint8_t data[2];

        data[0] = CONFIG_REG;

        // getting the current state of the register
        i2c_write_blocking(I2C_PORT, ADDR, data, 1, false);
        i2c_read_blocking(I2C_PORT, ADDR, &data[1], 1, false);
        data[1] &= 0x1F;
        data[1] |= standby;
        i2c_write_blocking(I2C_PORT, ADDR, data, 2, false);
    }
    else
    {
        printf("Wrong standby parameter\n");
    }
}

/**
 * @brief Set the iir filter coefficent [none, 1 , 2 , 4 , 8 , 16]
 *
 * @param coefficent constant defined in the .h file
 */
void set_iir_coefficent(uint8_t coefficent)
{
    if ((coefficent >> 2) <= 0x07 && (coefficent >> 2) >= 0x00)
    {
        uint8_t data[2];

        data[0] = CONFIG_REG;

        // getting the current state of the register
        i2c_write_blocking(I2C_PORT, ADDR, data, 1, false);
        i2c_read_blocking(I2C_PORT, ADDR, &data[1], 1, false);
        data[1] &= 0xE3;
        data[1] |= coefficent;
        i2c_write_blocking(I2C_PORT, ADDR, data, 2, false);
    }
    else
    {
        printf("Wrong coefficient\n");
    }
}

/**
 * @brief Enable the sensor's spi communication
 * 
 */
void enable_spi()
{
    uint8_t data[2];

    data[0] = CONFIG_REG;

    // getting the current state of the register
    i2c_write_blocking(I2C_PORT, ADDR, data, 1, false);
    i2c_read_blocking(I2C_PORT, ADDR, &data[1], 1, false);
    data[1] |= 0x01;
    i2c_write_blocking(I2C_PORT, ADDR, data, 2, false);
}

/**
 * @brief Disable the sensor's spi communication 
 * 
 */
void disable_spi()
{
    uint8_t data[2];

    data[0] = CONFIG_REG;

    // getting the current state of the register
    i2c_write_blocking(I2C_PORT, ADDR, data, 1, false);
    i2c_read_blocking(I2C_PORT, ADDR, &data[1], 1, false);
    data[1] &= ~(0x01);
    i2c_write_blocking(I2C_PORT, ADDR, data, 2, false);
}


/**
 * @brief Calculate the t_fine value used for the temperature, pressure and humidity calculation.
 * 
 * @return int32_t - t_fine 
 */
int32_t get_t_fine()
{
    uint16_t dig_T1 = 0;
    int16_t dig_T2 = 0, dig_T3 = 0;
    uint8_t address = CALIB00_REG;
    int32_t t_fine;
    // Getting the values from the CALIB registers.
    uint8_t data[6];

    i2c_write_blocking(I2C_PORT, ADDR, &address, 1, true);
    i2c_read_blocking(I2C_PORT, ADDR, data, 6, false);

    dig_T1 = (uint16_t)(data[0] | (data[1] << 8));
    dig_T2 = (int16_t)(data[2] | (data[3] << 8));
    dig_T3 = (int16_t)(data[1] | (data[5] << 8));

    uint32_t raw_temp = get_raw_temp();
    int32_t var_1;
    int32_t var_2;
    var_1 = ((((raw_temp >> 3) - ((long signed int)dig_T1 << 1))) * ((long signed int)dig_T2)) >> 11;
    var_2 = (((((raw_temp >> 4) - ((long signed int)dig_T1)) * ((raw_temp >> 4) - ((long signed int)dig_T1))) >> 12) * ((long signed int)dig_T3)) >> 14;
    t_fine = var_1 + var_2;
    return t_fine;
}

// Pressure fonctions

/**
 * @brief Get the raw pressure from the sensor
 *
 * @return uint32_t - pressure (unusable)
 */
uint32_t get_raw_press()
{
    uint32_t pressure = 0;
    uint8_t reg = PRESS_MSB_REG;
    uint8_t buf[3];
    i2c_write_blocking(I2C_PORT, ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, ADDR, buf, 3, false);
    pressure = ((uint32_t)buf[0] << 12) |
               ((uint32_t)buf[1] << 4) |
               ((uint32_t)buf[2] >> 4);
    return pressure;
}


/**
 * @brief Calculate the compensate pressure, need to be divided by 256 to get Pa 
 * 
 * @return uint32_t - pressure (unusable)
 */
uint32_t get_compensate_pressure()
{
    uint16_t dig_P1 = 0;
    int16_t dig_P2 = 0, dig_P3 = 0, dig_P4 = 0, dig_P5 = 0,
            dig_P6 = 0, dig_P7 = 0, dig_P8 = 0, dig_P9 = 0;
    uint8_t buf[18];
    uint8_t reg = CALIB06_REG;
    i2c_write_blocking(I2C_PORT, ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, ADDR, buf, 18, false);
    dig_P1 = (uint16_t)(buf[0] | (buf[1] << 8));
    dig_P2 = (int16_t)(buf[2] | (buf[3] << 8));
    dig_P3 = (int16_t)(buf[4] | (buf[5] << 8));
    dig_P4 = (int16_t)(buf[6] | (buf[7] << 8));
    dig_P5 = (int16_t)(buf[8] | (buf[9] << 8));
    dig_P6 = (int16_t)(buf[10] | (buf[11] << 8));
    dig_P7 = (int16_t)(buf[12] | (buf[13] << 8));
    dig_P8 = (int16_t)(buf[14] | (buf[15] << 8));
    dig_P9 = (int16_t)(buf[16] | (buf[17] << 8));

    int64_t var1, var2, pressure;
    var1 = ((int64_t)get_t_fine()) - 128000;
    var2 = var1 * var1 * (int64_t)dig_P6;
    var2 = var2 + ((var1 * (int64_t)dig_P5 << 17));
    var2 = var2 + (((int64_t)dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;
    if (var1 == 0)
    {
        return 0; // avoid exception caused by division by zero (datasheet)
    }
    pressure = 1048576 - get_raw_press();
    pressure = (((pressure << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)dig_P9) * (pressure >> 13) * (pressure >> 13)) >> 25;
    var2 = (((int64_t)dig_P8) * pressure) >> 19;
    pressure = ((pressure + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);
    return ((uint32_t)pressure);
}

/**
 * @brief Calculate the pressure in Pascal with a 1 decimal accuracy
 * 
 * @return float - temperature (Pa)
 */
float get_pressure_in_Pa()
{
    return (get_compensate_pressure() / 256.0);
}

// Temperature fonctions

/**
 * @brief Get the raw temperature for the sensor
 *
 * @return uint32_t - temperature (unusable)
 */
uint32_t get_raw_temp(void)
{
    uint8_t reg = TEMP_MSB_REG;
    uint8_t buf[3];
    uint32_t temp;

    i2c_write_blocking(I2C_PORT, ADDR, &reg, 1, true);

    i2c_read_blocking(I2C_PORT, ADDR, buf, 3, false);

    temp = ((uint32_t)buf[0] << 12) |
           ((uint32_t)buf[1] << 4) |
           ((uint32_t)buf[2] >> 4);

    return temp;
}

/**
 * @brief Calculate the compensate temperature time 100 (20°C --> 2000) 
 * 
 * @return int32_t - temperature
 */
int32_t get_compensate_temperature()
{
    return (((get_t_fine()) * 5 + 128) >> 8);
}

/**
 * @brief Calculate the temperature in °C with 2 decimals accuracy 
 * 
 * @return float - temperature (°C)
 */
float get_temp_celsius()
{
    return (get_compensate_temperature() / 100.0f);
}

// Humidity fonctions

/**
 * @brief Get the raw humbidity from the sensor
 *
 * @return uint16_t - humidity (unusable)
 */
uint32_t get_raw_humidity()
{
    uint32_t hum = 0;
    uint8_t reg = HUM_MSB_REG;
    uint8_t buf[2];
    i2c_write_blocking(I2C_PORT, ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, ADDR, buf, 2, false);

    hum = ((uint32_t)buf[0] << 8) |
          ((uint32_t)buf[1]);

    return hum;
}


/**
 * @brief Calculate the compensate humidity. Need to be divided by 1024.0 to have the humidity in %
 * 
 * @return uint32_t - humidity
 */
uint32_t get_compensate_humidity()
{
    uint8_t reg = CALIB25_REG;
    uint8_t dig_H1, dig_H3;
    int16_t dig_H2, dig_H4, dig_H5;
    int8_t dig_H6;
    i2c_write_blocking(I2C_PORT, ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, ADDR, &dig_H1, 1, false);
    reg = CALIB26_REG;
    uint8_t buf[8];
    i2c_write_blocking(I2C_PORT, ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, ADDR, buf, 8, false);
    dig_H2 = (int16_t)(buf[0] | buf[1] << 8);
    dig_H3 = buf[2];
    dig_H4 = (int16_t)(((int16_t)buf[3] << 4) | (buf[4] & 0x0F));
    dig_H5 = (int16_t)(((int16_t)buf[6] << 4) | ((buf[5] & 0xF0) >> 4));
    dig_H6 = (int8_t)buf[7];
    int32_t calculation = (get_t_fine() - ((int32_t)76800));
    calculation = (((((get_raw_humidity() << 14 ) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * calculation)) + ((int32_t)16384)) >> 15 ) * ((((((( calculation * ((int32_t)dig_H6)) >> 10) * ((( calculation * ((int32_t)dig_H3)) >> 11 ) + ((int32_t)32768))) >> 10 ) + ((int32_t)2097152)) * ((int32_t)dig_H2) + 8192 ) >> 14));
    calculation = (calculation - ((((( calculation >> 15) * (calculation >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
    calculation = (calculation < 0 ? 0 : calculation);
    calculation = (calculation > 419430400 ? 419430400 : calculation);
    return ((uint32_t)(calculation >> 12)); 
}

/**
 * @brief Calculate the actual humidity in %
 * 
 * @return float - humidity (%)
 */
float get_humidity_percentage()
{
    return (get_compensate_humidity() / 1024.0);
}
