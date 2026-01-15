# DFRobot_FRN20

## Overview
The FRN20 is a high-precision flow sensor designed for accurate measurement of gas or liquid flow rates. It features an I2C communication interface, compact size, high accuracy, and fast response time, making it suitable for applications in gas analysis, medical devices, industrial automation, and more.

The sensor includes built-in temperature compensation to ensure measurement accuracy across different environmental conditions. Each FRN20 sensor is factory calibrated and can be easily integrated into your project via the I2C interface.

## Product Link
[FRN20 Flow Sensor](https://www.dfrobot.com/)

## Table of Contents
* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)


## Summary
This library provides a way to drive the FRN20 flow sensor under the Arduino IDE. It allows you to read flow data, sensor parameters, and perform configuration operations.

## Installation
1. To use this library, first download the library file, paste it into the Arduino libraries directory, then open the examples folder and run the demo.

## Methods
```C++
/**
 * @fn DFRobot_FRN20
 * @brief Constructor, passing in I2C bus device
 * @param pWire I2C bus object
 */
DFRobot_FRN20(DFRobot_SoftI2C *pWire = &dfrobotSoftWire);

/**
 * @fn begin
 * @brief Check whether the FRN20 device exists on the I2C bus
 * @return Whether the sensor device is found
 * @retval 0: Sensor device exists, other values: Sensor device does not exist
 */
byte begin(void);

/**
 * @fn readParams
 * @brief Read sensor parameters
 * @return Operation result
 * @retval 1: Success
 * @retval 0: Failure
 */
uint8_t readParams(void);

/**
 * @fn readRawFlowData
 * @brief Read raw flow data
 * @return Operation result
 * @retval 1: Success
 * @retval 0: Failure
 */
uint8_t readRawFlowData(void);

/**
 * @fn readMassFlowData
 * @brief Read mass flow data
 * @return Operation result
 * @retval 1: Success
 * @retval 0: Failure
 */
uint8_t readMassFlowData(void);
```

## Compatibility
| MCU | Work Well | Work Wrong | Untested | Remarks |
|-----|-----------|------------|----------|---------|
| Arduino UNO | √ | | | |
| Arduino MEGA2560 | √ | | | |
| Arduino Leonardo | √ | | | |
| ESP32 | √ | | | |
| ESP8266 | √ | | | |
| STM32 | √ | | | |
| Micro:bit | √ | | | |

## History
- Date: 2025-12-17
- Version: V1.0.0

## Credits
Written by fary (feng.yang@dfrobot.com), 2025.12-17
[DFRobot Website](https://www.dfrobot.com/)
