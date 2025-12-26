# BME280 I2C Driver for RP2040 (Pico SDK)

This project provides a complete **BME280 I2C driver** for the **RP2040**
(Raspberry Pi Pico and compatible boards) using the **Raspberry Pi Pico SDK**.

⚠️ **Disclaimer / Test Status**  
This driver has been **tested only with a BME280 sensor**.  
It has **not been tested with a BMP280**.  
Although the BME280 and BMP280 are closely related, there may be
**incompatibilities or bugs** if this driver is used with a BMP280
(especially regarding humidity-related registers and calibration data).

---

The project is organized with a clear separation between:
- the **application example** (`src/main.c`)
- the **sensor driver implementation** (`src/BME280_i2c.c`)
- the **driver configuration and API definitions** (`include/BME280_i2c.h`)

All I2C parameters (pins, speed, interface, address) are configurable
from a single header file.

---

## Features

- Temperature measurement (°C)
- Humidity measurement (%RH)
- Barometric pressure measurement (hPa)
- I2C communication using Pico SDK
- Configurable I2C interface, pins, and baudrate
- Modular and reusable driver
- Compatible with all RP2040-based boards

---

## Hardware Requirements

- RP2040 microcontroller (Raspberry Pi Pico or compatible)
- **BME280 sensor module** (I2C mode)
- Breadboard and jumper wires
- USB cable for power and programming

---

## Electrical Connections (Default Configuration)

| BME280 Pin | RP2040 Pin |
|------------|------------|
| VCC        | 3.3V       |
| GND        | GND        |
| SDA        | GPIO 4     |
| SCL        | GPIO 5     |

⚠️ **Important:**  
The BME280 works with **3.3V logic only**. Do **not** use 5V.

---

## I2C Address

The BME280 supports two possible I2C addresses depending on the SDO pin:

- `0x76` (default)
- `0x77` (SDO pulled high)

The address is configurable in the header file.

---

## Project Structure

project_root/
├── CMakeLists.txt
├── include/
│ └── BME280_i2c.h
├── src/
│ ├── main.c
│ └── BME280_i2c.c



### File Description

- **`src/main.c`**  
  Application example demonstrating how to initialize the I2C interface,
  initialize the BME280 sensor, and read environmental data.

- **`src/BME280_i2c.c`**  
  Implementation of the BME280 driver and low-level I2C communication.

- **`include/BME280_i2c.h`**  
  Driver API declarations and **all configurable parameters**.

---

## Configuration (Single Header)

All I2C-related settings can be modified in:

include/BME280_i2c.h