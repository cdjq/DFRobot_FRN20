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
  _pWire->beginTransmission(_deviceAddr);
  return _pWire->endTransmission();
}

uint8_t DFRobot_FRN20::readReg(uint16_t command, void *pBufs, size_t size)    //wire库最多只能读取32个字节,所以要分批次读取
{
  if (pBuf == NULL) {
    DBG("pBuf ERROR!! : null pointer");
    return -1;
  }
  uint8_t *pBuf = (uint8_t *)pBufs;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(command >> 8);
  _pWire->write(command & 0xFF);

  if (_pWire->endTransmission() != 0) {
    DBG("endTransmission ERROR!! : null pointer");
    return 0;
  }
  _pWire->requestFrom(_deviceAddr, (uint8_t)size);
  for (size_t i = 0; i < size; i++) {
    pBuf[i] = _pWire->read();    //31
  }

  return size;
}

uint8_t DFRobot_FRN20::readRawFlowData(void)
{
  memset(_buf, 0, 5);
  readReg(FRN20_COMMAND_READ_FLOW, _buf, 5);
  if (calcCrc(_buf, FRN20_FLOW_FRAME_LEN - 1) == _buf[4]) {
    rawFlowData = ((uint16_t)_buf[0] << 8) | _buf[1];
    return 1;
  }
  return 0;
}

uint8_t DFRobot_FRN20::readMassFlowData(void)
{
  if (readRawFlowData()) {
    int32_t delta = (int32_t)rawFlowData - (int32_t)params.offset;
    massFlowData  = (float)delta / (float)params.mediumCoeff;
    return 1;
  }
  return 0;
}

uint8_t DFRobot_FRN20::readParams(void)
{
  memset(_buf, 0, FRN20_PARAM_FRAME_LEN);
  readReg(FRN20_COMMAND_READ_PARAMS, _buf, FRN20_PARAM_FRAME_LEN);
  uint8_t crcNum = calcCrc(_buf, FRN20_PARAM_FRAME_LEN - 1);
  if (crcNum == _buf[FRN20_PARAM_FRAME_LEN - 1]) {
    params.unit        = (_buf[4] << 8) | _buf[5];
    params.range       = (_buf[6] << 8) | _buf[7];
    params.offset      = (_buf[8] << 8) | _buf[9];
    params.mediumCoeff = (_buf[10] << 8) | _buf[11];
    params.voutMinmV   = (_buf[16] << 24) | (_buf[17] << 16) | (_buf[18] << 8) | _buf[19];
    params.voutMaxmV   = (_buf[20] << 24) | (_buf[21] << 16) | (_buf[22] << 8) | _buf[23];
    memcpy(params.productId, &_buf[29], 4);
    params.productId[4] = '\0';
    params.crc          = _buf[40];
    return 1;
  }
  return 0;
}

uint8_t DFRobot_FRN20::calcCrc(uint8_t *data, uint8_t len)
{
  uint8_t bit, byte, crc = 0x00;
  for (byte = 0; byte < len; byte++) {
    crc ^= data[byte];
    for (bit = 8; bit > 0; --bit) {
      if (crc & 0x80)
        crc = (crc << 1) ^ 0x131;
      else
        crc = (crc << 1);
    }
  }
  return crc;
}
