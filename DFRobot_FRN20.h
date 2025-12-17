/*!
 * @file DFRobot_FRN20.h
 * @brief DFRobot_FRN20 class infrastructure
 * @copyright  Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [fary](feng.yang@dfrobot.com)
 * @version V1.0
 * @date 2025-04-10
 * @url https://github.com/DFRobot/DFRobot_FRN20
 */
#ifndef _DFROBOT_FRN20_H_
#define _DFROBOT_FRN20_H_

#include <Arduino.h>

#include "SoftI2C.h"
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
#define FRN20_COMMAND_READ_PARAMS 0xCCDD /*!< Command to read parameters, returns 41 bytes */
#define FRN20_PARAM_FRAME_LEN     41     /*!< Length of parameter frame */
#define FRN20_FLOW_FRAME_LEN      5      /*!< Length of flow data frame */

class DFRobot_FRN20 {
public:
  /**
   * @struct sParams_t
   * @brief FRN20 sensor parameters structure
   */
  typedef struct {
    uint16_t unit;         /*!< Data5-6: Unit (0x15 mL/min, 0x16 L/min, etc.) */
    uint16_t range;        /*!< Data7-8: Measurement range */
    uint16_t offset;       /*!< Data9-10: Offset value */
    uint16_t mediumCoeff;  /*!< Data11-12: Medium conversion coefficient */
    uint16_t voutMinmV;    /*!< Data17-20: Minimum output voltage in mV */
    uint16_t voutMaxmV;    /*!< Data21-24: Maximum output voltage in mV */
    uint8_t  productId[5]; /*!< Data30-33: Product ID in ASCII format with null termination */
    uint8_t  crc;          /*!< Data41: CRC checksum */
  } sParams_t;

  /**
   * @fn DFRobot_FRN20
   * @brief Constructor, passing in I2C bus device
   * @param pWire I2C bus object
   */
  DFRobot_FRN20(SoftI2C *pWire = &SoftWire)
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

  sParams_t params;       /*!< Sensor parameters */
  uint16_t  rawFlowData;  /*!< Raw flow data */
  float     massFlowData; /*!< Mass flow data */

protected:
  /**
   * @fn calcCrc
   * @brief Calculate CRC checksum
   * @param data Data to calculate CRC
   * @param len Length of data
   * @return Calculated CRC value
   */
  uint8_t calcCrc(uint8_t *data, uint8_t len);

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
  SoftI2C *_pWire;      /*!< I2C bus object */
  uint8_t  _deviceAddr; /*!< Device address */
  uint8_t  _buf[50];    /*!< Data buffer */
};

#endif
