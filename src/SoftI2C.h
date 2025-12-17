/*!
 * @file SoftI2C.h
 * @brief SoftI2C class infrastructure for software I2C communication
 * @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [DFRobot](dfrobot.com)
 * @version V1.0.0
 * @date 2025-04-10
 * @url https://github.com/DFRobot/DFRobot_FRN20
 */
#ifndef _SoftWire_h
#define _SoftWire_h

#include <Arduino.h>
#include <inttypes.h>
#include "Stream.h"

#ifndef I2C_BUFFER_LENGTH
#define I2C_BUFFER_LENGTH 45  /*!< I2C buffer length */
#endif
#define SDA_PIN 2             /*!< Default SDA pin */
#define SCL_PIN 3             /*!< Default SCL pin */

#define WIRE_HAS_END 1        /*!< Wire has end transmission */
#define I2C_READ     1        /*!< I2C read mode */
#define I2C_WRITE    0        /*!< I2C write mode */
#define DELAY        500      /*!< Microsecond delay */
#define I2C_MAXWAIT  5000     /*!< Maximum I2C wait time */

class DFRobot_SoftI2C : public Stream {
private:
  /**
   * @fn setPinHigh
   * @brief Set the specified pin to a high state
   * @param pin Pin number to set high
   */
  void setPinHigh(uint8_t pin);
  
  /**
   * @fn setPinLow
   * @brief Set the specified pin to a low state
   * @param pin Pin number to set low
   */
  void setPinLow(uint8_t pin);
  
  /**
   * @fn i2cInit
   * @brief Initialize the I2C bus
   * @return True if initialization is successful, false otherwise
   */
  bool i2cInit(void);
  
  /**
   * @fn i2cStart
   * @brief Start an I2C transfer
   * @param addr 8-bit I2C address including R/W bit
   * @return True if slave acknowledges, false otherwise
   */
  bool i2cStart(uint8_t addr);
  
  /**
   * @fn i2cStartWait
   * @brief Start transfer and wait for ACK
   * @param addr 8-bit I2C address including R/W bit
   * @return True if slave acknowledges, false otherwise
   */
  bool i2cStartWait(uint8_t addr);
  
  /**
   * @fn i2cRepStart
   * @brief Generate repeated start condition
   * @param addr 8-bit I2C address including R/W bit
   * @return True if slave acknowledges, false otherwise
   */
  bool i2cRepStart(uint8_t addr);
  
  /**
   * @fn i2cStop
   * @brief Generate stop condition
   */
  void i2cStop(void);
  
  /**
   * @fn i2cWrite
   * @brief Write one byte to I2C bus
   * @param value Byte to write
   * @return True if slave acknowledges, false otherwise
   */
  bool i2cWrite(uint8_t value);
  
  /**
   * @fn i2cRead
   * @brief Read one byte from I2C bus
   * @param last True to send NAK after read, false to send ACK
   * @return Read byte
   */
  uint8_t i2cRead(bool last);

  uint8_t _rxBuffer[I2C_BUFFER_LENGTH];   /*!< Receive buffer */
  uint8_t _rxBufferIndex;                 /*!< Receive buffer index */
  uint8_t _rxBufferLength;                /*!< Receive buffer length */
  uint8_t _isTransmitting;                /*!< Transmission status */
  uint8_t _error;                         /*!< Error code */
  uint8_t _sda;                           /*!< SDA pin number */
  uint8_t _scl;                           /*!< SCL pin number */
  bool    _pullup;                        /*!< Pullup resistor usage */

public:
  /**
   * @fn SoftI2C
   * @brief Constructor
   * @param dataPin SDA pin number
   * @param clockPin SCL pin number
   * @param usePullup Use internal pullup resistors if true
   */
  DFRobot_SoftI2C(uint8_t dataPin, uint8_t clockPin, bool usePullup = false);
  
  /**
   * @fn begin
   * @brief Initialize the I2C bus
   */
  void begin(void);
  
  /**
   * @fn end
   * @brief End the I2C bus
   */
  void end(void);
  
  /**
   * @fn beginTransmission
   * @brief Begin a transmission to a device
   * @param address 7-bit device address
   */
  void beginTransmission(uint8_t address);
  
  /**
   * @fn beginTransmission
   * @brief Begin a transmission to a device (overloaded)
   * @param address 7-bit device address as integer
   */
  void beginTransmission(int address);
  
  /**
   * @fn endTransmission
   * @brief End a transmission to a device
   * @param sendStop Send stop condition if true
   * @return Status code
   */
  uint8_t endTransmission(uint8_t sendStop);
  
  /**
   * @fn endTransmission
   * @brief End a transmission to a device (overloaded, sends stop)
   * @return Status code
   */
  uint8_t endTransmission(void);
  
  /**
   * @fn write
   * @brief Write a byte to the I2C bus
   * @param data Byte to write
   * @return Number of bytes written
   */
  size_t write(uint8_t data);
  
  /**
   * @fn write
   * @brief Write multiple bytes to the I2C bus
   * @param data Pointer to data buffer
   * @param quantity Number of bytes to write
   * @return Number of bytes written
   */
  size_t write(const uint8_t *data, size_t quantity);
  
  /**
   * @fn requestFrom
   * @brief Request data from a device with internal register address
   * @param address 7-bit device address
   * @param quantity Number of bytes to request
   * @param iaddress Internal register address
   * @param isize Size of internal register address
   * @param sendStop Send stop condition if true
   * @return Number of bytes received
   */
  uint8_t requestFrom(uint8_t address, uint8_t quantity, uint32_t iaddress, uint8_t isize, uint8_t sendStop);
  
  /**
   * @fn requestFrom
   * @brief Request data from a device
   * @param address 7-bit device address
   * @param quantity Number of bytes to request
   * @param sendStop Send stop condition if true
   * @return Number of bytes received
   */
  uint8_t requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop);
  
  /**
   * @fn requestFrom
   * @brief Request data from a device (overloaded)
   * @param address 7-bit device address as integer
   * @param quantity Number of bytes to request as integer
   * @param sendStop Send stop condition as integer
   * @return Number of bytes received
   */
  uint8_t requestFrom(int address, int quantity, int sendStop);
  
  /**
   * @fn requestFrom
   * @brief Request data from a device (overloaded, sends stop)
   * @param address 7-bit device address
   * @param quantity Number of bytes to request
   * @return Number of bytes received
   */
  uint8_t requestFrom(uint8_t address, uint8_t quantity);
  
  /**
   * @fn requestFrom
   * @brief Request data from a device (overloaded, sends stop)
   * @param address 7-bit device address as integer
   * @param quantity Number of bytes to request as integer
   * @return Number of bytes received
   */
  uint8_t requestFrom(int address, int quantity);
  
  /**
   * @fn available
   * @brief Get the number of bytes available for reading
   * @return Number of bytes available
   */
  int available(void);
  
  /**
   * @fn read
   * @brief Read a byte from the buffer
   * @return Byte read or -1 if no bytes available
   */
  int read(void);
  
  /**
   * @fn peek
   * @brief Peek at the next byte in the buffer
   * @return Byte peeked or -1 if no bytes available
   */
  int peek(void);
  
  /**
   * @fn flush
   * @brief Flush the buffer
   */
  void flush(void);
  
  /**
   * @fn write
   * @brief Write an unsigned long to the I2C bus (overloaded)
   * @param n Unsigned long to write
   * @return Number of bytes written
   */
  inline size_t write(unsigned long n)
  {
    return write((uint8_t)n);
  }
  
  /**
   * @fn write
   * @brief Write a long to the I2C bus (overloaded)
   * @param n Long to write
   * @return Number of bytes written
   */
  inline size_t write(long n)
  {
    return write((uint8_t)n);
  }
  
  /**
   * @fn write
   * @brief Write an unsigned int to the I2C bus (overloaded)
   * @param n Unsigned int to write
   * @return Number of bytes written
   */
  inline size_t write(unsigned int n)
  {
    return write((uint8_t)n);
  }
  
  /**
   * @fn write
   * @brief Write an int to the I2C bus (overloaded)
   * @param n Int to write
   * @return Number of bytes written
   */
  inline size_t write(int n)
  {
    return write((uint8_t)n);
  }
};

/**
 * @brief Global SoftI2C instance using default pins
 */
extern SoftI2C softWire;

#endif
#pragma once