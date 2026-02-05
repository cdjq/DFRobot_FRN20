/*!
 * @file DFRobot_FRN20.cpp
 * @brief DFRobot_FRN20 class infrastructure
 * @copyright  Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [fary](feng.yang@dfrobot.com)
 * @version V1.0
 * @date 2025-04-10
 * @url https://github.com/DFRobot/DFRobot_FRN20
 */
#include "DFRobot_FRN20.h"
byte DFRobot_FRN20::begin(void)
{
  _pWire->begin();
#if defined(ESP8266)
  _pWire->setClockStretchLimit(2000);
#endif
  _pWire->beginTransmission(_deviceAddr);
  byte ret = _pWire->endTransmission();
  if (ret == 0) {
    while (!readParams()) {
      DBG("Failed, readParams error!");
      delay(500);
    }
  }
  return ret;
}

uint8_t DFRobot_FRN20::readReg(uint16_t command, void *pBuf, size_t size)
{
  if (pBuf == NULL) {
    DBG("pBuf ERROR!! : null pointer");
    return -1;
  }
  uint8_t *pBuffer = (uint8_t *)pBuf;

  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(command >> 8);
  _pWire->write(command & 0xFF);

  if (_pWire->endTransmission() != 0) {
    DBG("endTransmission ERROR!! : null pointer");
    return 0;
  }

  delay(3);

  if (_pWire->requestFrom(_deviceAddr, (uint8_t)size) != size) {
    DBG("requestFrom ERROR!! : size mismatch");
    return 0;
  }
  for (size_t i = 0; i < size; i++) {
    pBuffer[i] = _pWire->read();
  }

  return size;
}

uint8_t DFRobot_FRN20::readRawFlowData(void)
{
  memset(_buf, 0, 5);
  if (readReg(FRN20_COMMAND_READ_FLOW, _buf, 5) == 5) {
    _rawFlowData = ((uint16_t)_buf[0] << 8) | _buf[1];
    return 1;
  }
  return 0;
}

uint8_t DFRobot_FRN20::readMassFlowData(void)
{
  if (readRawFlowData()) {
    int32_t delta = (int32_t)_rawFlowData - (int32_t)_params.offset;
    massFlowData  = (float)delta / (float)_params.mediumCoeff;
    return 1;
  }
  return 0;
}

uint8_t DFRobot_FRN20::readParams(void)
{
  memset(_buf, 0, FRN20_PARAM_FRAME_LEN);
  if (readReg(FRN20_COMMAND_READ_PARAMS, _buf, FRN20_PARAM_FRAME_LEN) == FRN20_PARAM_FRAME_LEN) {
    _params.unit        = ((uint16_t)_buf[4] << 8) | _buf[5];
    _params.range       = ((uint16_t)_buf[6] << 8) | _buf[7];
    _params.offset      = ((uint16_t)_buf[8] << 8) | _buf[9];
    _params.mediumCoeff = ((uint16_t)_buf[10] << 8) | _buf[11];
    _params.voutMinmV   = ((uint32_t)_buf[16] << 24) | ((uint32_t)_buf[17] << 16) | ((uint32_t)_buf[18] << 8) | (uint32_t)_buf[19];
    _params.voutMaxmV   = ((uint32_t)_buf[20] << 24) | ((uint32_t)_buf[21] << 16) | ((uint32_t)_buf[22] << 8) | (uint32_t)_buf[23];
    if(_params.unit != 0x15 && _params.unit != 0x16){
      return 0;
    }
    return 1;
  }
  return 0;
}