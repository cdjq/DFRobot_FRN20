/*!
 * @file DFRobot_FRN20.h
 * @brief DFRobot_FRN20 class infrastructure
 * @copyright  Copyright (c) 2026 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [PLELES] (https://github.com/PLELES)
 * @version V1.0
 * @date 2026-01-26
 * @url https://github.com/DFRobot/DFRobot_FRN20
 */
#ifndef _DFROBOT_FRN20_H_
#define _DFROBOT_FRN20_H_

#include <Arduino.h>
#include <Wire.h>
#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...)                 \
  {                              \
    Serial.print("[");           \
    Serial.print(__FUNCTION__);  \
    Serial.print("(): ");        \
    Serial.print(__LINE__);      \
    Serial.print(" ] ");         \
    Serial.println(__VA_ARGS__); \
  }
#else
#define DBG(...)
#endif

#define FRN20_IIC_ADDRESS         0x40   /*!< FRN20 I2C address */
#define FRN20_COMMAND_READ_FLOW   0x1000 /*!< Command to read flow data, returns 5 bytes */
#define FRN20_COMMAND_READ_PARAMS 0xCCDD /*!< Command to read parameters, returns 41 bytes only read 32 bytes */
#define FRN20_PARAM_FRAME_LEN     32     /*!< Length of parameter frame */
#define FRN20_FLOW_FRAME_LEN      5      /*!< Length of flow data frame */

class DFRobot_FRN20 {
public:
  /**
   * @fn DFRobot_FRN20
   * @brief Constructor, passing in I2C bus device
   * @param pWire I2C bus object
   */
  DFRobot_FRN20(TwoWire *pWire = &Wire)
  {
    _pWire      = pWire;
    _deviceAddr = FRN20_IIC_ADDRESS;
  }

  /**
   * @fn begin
   * @brief Check whether the FRN20 device exists on the I2C bus
   * @return Whether the sensor device is found
   * @retval 0: Sensor device exists
   * @retval Other values: Sensor device does not exist
   */
  byte begin(void);


  /**
   * @fn readMassFlowData
   * @brief Read mass flow data
   * @return Operation result
   * @retval 1: Success
   * @retval 0: Failure
   */
  uint8_t readMassFlowData(void);

  float     massFlowData; /*!< Mass flow data */

protected:
  /**
   * @fn readReg
   * @brief Read data from register
   * @param command Command to send
   * @param pBuf Buffer to store read data
   * @param size Size of data to read
   * @return Number of bytes read
   */
  uint8_t readReg(uint16_t command, void *pBuf, size_t size);

private:
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
   * @struct sParams_t
   * @brief FRN20 sensor parameters structure
   */
  typedef struct {
    uint16_t unit;        /*!< Data5-6: Unit (0x15 mL/min, 0x16 L/min, etc.) */
    uint16_t range;       /*!< Data7-8: Measurement range */
    uint16_t offset;      /*!< Data9-10: Offset value */
    uint16_t mediumCoeff; /*!< Data11-12: Medium conversion coefficient */
    uint32_t voutMinmV;   /*!< Data17-20: Minimum output voltage in mV */
    uint32_t voutMaxmV;   /*!< Data21-24: Maximum output voltage in mV */
  } sParams_t;

  sParams_t _params;       /*!< Sensor parameters */
  TwoWire *_pWire;      /*!< I2C bus object */
  uint16_t  _rawFlowData;  /*!< Raw flow data */
  uint8_t  _deviceAddr; /*!< Device address */
  uint8_t  _buf[32];    /*!< Data buffer */
};

#endif
