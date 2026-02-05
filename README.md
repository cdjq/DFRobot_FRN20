# DFRobot_FRN20

- [中文版](./README_CN.md)

## Overview
The FRn20 series micro-flow gas mass flow sensor is specifically designed for various micro-flow process control applications. This product is an upgrade based on the FR20 series, offering significantly enhanced zero stability and full-scale signal stability. It is suitable for industrial process monitoring.      
##
Product Link: https://www.dfrobot.com/

```text
SKU: SEN0630
```

## Table of Contents
* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [Hardware Connection](#hardware-connection)
* [Troubleshooting](#troubleshooting)
* [History](#history)
* [Credits](#credits)

## Summary
This Arduino/C++ library provides drivers for the FRN20 flow sensor. It supports I2C communication to read raw and calibrated flow values, and to load sensor parameters (range, offset, conversion coefficients) from the device.

## Installation
1. Download or copy the library into your Arduino `libraries` directory.
2. Include the library in your sketch:

```cpp
#include <DFRobot_FRN20.h>
```

## Methods (Arduino C++ API)
```C++
/**
 * @fn DFRobot_FRN20
 * @brief Constructor, pass in I2C bus object
 * @param pWire I2C bus object (default: &Wire)
 */
DFRobot_FRN20(TwoWire *pWire = &Wire);

/**
 * @fn begin
 * @brief Initialize I2C and check device presence
 * @return byte Result of `Wire.endTransmission()` (0 = success)
 */
byte begin(void);

/**
 * @fn readMassFlowData
 * @brief Read and convert mass flow using loaded parameters
 * @return uint8_t 1 = success, 0 = failure
 */
uint8_t readMassFlowData(void);
```

## Compatibility
| Platform | Work Well | Work Wrong | Untested | Remarks |
|----------|:---------:|:----------:|:--------:|---------|
| Arduino UNO |  √|| | |
| Arduino MEGA2560 |  √| || |
| Arduino Leonardo |  √| |  | |
| FireBeeetle-M0 |  √| | | |
| FireBeeetle-ESP32-E |  √| |  | |
| ESP8266 | √  |  | | |
| Micro:bit |  √ | | | |

## History
- 2026/01/26 - Version 1.0.0 released.

## Credits
Written by PLELES (PLELES@dfrobot.com), 2026-01-26
[DFRobot Website](https://www.dfrobot.com/)
