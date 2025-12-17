
#include "SoftI2C.h"
DFRobot_SoftI2C softWire(SDA_PIN, SCL_PIN);
DFRobot_SoftI2C::DFRobot_SoftI2C(uint8_t dataPin, uint8_t clockPin, bool usePullup /*=false*/)
{
  _sda    = dataPin;
  _scl    = clockPin;
  _pullup = usePullup;
}

void DFRobot_SoftI2C::begin(void)
{
  _rxBufferIndex  = 0;
  _rxBufferLength = 0;
  _error          = 0;
  _isTransmitting = false;

  i2cInit();
}

void DFRobot_SoftI2C::end(void) {}

void DFRobot_SoftI2C::beginTransmission(uint8_t address)
{
  if (_isTransmitting) {
    _error = (i2cRepStart((address << 1) | I2C_WRITE) ? 0 : 2);
  } else {
    _error = (i2cStart((address << 1) | I2C_WRITE) ? 0 : 2);
  }
  _isTransmitting = 1;
}

void DFRobot_SoftI2C::beginTransmission(int address)
{
  beginTransmission((uint8_t)address);
}

uint8_t DFRobot_SoftI2C::endTransmission(uint8_t sendStop)
{
  uint8_t transferError = _error;
  if (sendStop) {
    i2cStop();
    _isTransmitting = 0;
  }
  _error = 0;
  return transferError;
}

uint8_t DFRobot_SoftI2C::endTransmission(void)
{
  return endTransmission(true);
}

size_t DFRobot_SoftI2C::write(uint8_t data)
{
  if (i2cWrite(data)) {
    return 1;
  } else {
    if (_error == 0)
      _error = 3;
    return 0;
  }
}

size_t DFRobot_SoftI2C::write(const uint8_t *data, size_t quantity)
{
  size_t progress = 0;
  for (size_t i = 0; i < quantity; ++i) {
    progress += write(data[i]);
  }
  return progress;
}

uint8_t DFRobot_SoftI2C::requestFrom(uint8_t address, uint8_t quantity, uint32_t iaddress, uint8_t isize, uint8_t sendStop)
{
  _error              = 0;
  uint8_t localerror = 0;
  if (isize > 0) {
    beginTransmission(address);
    // the maximum size of internal address is 3 bytes
    if (isize > 3) {
      isize = 3;
    }
    // write internal register address - most significant byte first
    while (isize-- > 0) {
      write((uint8_t)(iaddress >> (isize * 8)));
    }
    endTransmission(false);
  }
  // clamp to buffer length
  if (quantity > I2C_BUFFER_LENGTH) {
    quantity = I2C_BUFFER_LENGTH;
  }
  if (_isTransmitting) {
    localerror = !i2cRepStart((address << 1) | I2C_READ);
  } else {
    localerror = !i2cStart((address << 1) | I2C_READ);
  }
  if (_error == 0 && localerror)
    _error = 2;
  // perform blocking read into buffer
  for (uint8_t count = 0; count < quantity; count++) {
    _rxBuffer[count] = i2cRead(count == quantity - 1);
  }
  // set rx buffer iterator vars
  _rxBufferIndex  = 0;
  _rxBufferLength = _error ? 0 : quantity;
  if (sendStop) {
    _isTransmitting = 0;
    i2cStop();
  }
  return _rxBufferLength;
}

uint8_t DFRobot_SoftI2C::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint32_t)0, (uint8_t)0, (uint8_t)sendStop);
}

uint8_t DFRobot_SoftI2C::requestFrom(int address, int quantity, int sendStop)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}

uint8_t DFRobot_SoftI2C::requestFrom(uint8_t address, uint8_t quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t DFRobot_SoftI2C::requestFrom(int address, int quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

int DFRobot_SoftI2C::available(void)
{
  return _rxBufferLength - _rxBufferIndex;
}

int DFRobot_SoftI2C::read(void)
{
  int value = -1;
  if (_rxBufferIndex < _rxBufferLength) {
    value = _rxBuffer[_rxBufferIndex];
    ++_rxBufferIndex;
  }
  return value;
}

int DFRobot_SoftI2C::peek(void)
{
  int value = -1;

  if (_rxBufferIndex < _rxBufferLength) {
    value = _rxBuffer[_rxBufferIndex];
  }
  return value;
}

void DFRobot_SoftI2C::flush(void) {}

/**
 * @brief Initializes the DFRobot_SoftI2C module.
 *
 * This function needs to be called once in the beginning to initialize the DFRobot_SoftI2C module.
 * It returns false if either the SDA or SCL lines are low, which may indicate an I2C bus lockup
 * or that the lines are not properly pulled up.
 *
 * @return True if initialization is successful, false otherwise.
 */
bool DFRobot_SoftI2C::i2cInit(void)
{
  digitalWrite(_sda, LOW);
  digitalWrite(_scl, LOW);
  setPinHigh(_sda);
  setPinHigh(_scl);
  if (digitalRead(_sda) == LOW || digitalRead(_scl) == LOW)
    return false;
  return true;
}

/**
 * @brief Start an I2C transfer.
 *
 * This function starts an I2C transfer by pulling the data line (SDA) low followed by the clock line (SCL).
 * The 8-bit I2C address (including the R/W bit) is passed as a parameter.
 *
 * @param addr The 8-bit I2C address to communicate with.
 * @return Returns true if the slave responds with an "acknowledge" signal, false otherwise.
 */
bool DFRobot_SoftI2C::i2cStart(uint8_t addr)
{
  setPinLow(_sda);
  delayMicroseconds(DELAY);
  setPinLow(_scl);
  return i2cWrite(addr);
}

/**
 * @brief Try to start transfer until an ACK is returned.
 *
 * This function attempts to start an I2C transfer to the specified address and
 * waits for an acknowledgment (ACK) to be returned. If the ACK is not received
 * within a certain number of retries, the function gives up and returns false.
 *
 * @param addr The 7-bit I2C address of the target device.
 * @return Returns true if the I2C start and ACK were successful, false otherwise.
 */
bool DFRobot_SoftI2C::i2cStartWait(uint8_t addr)
{
  long retry = I2C_MAXWAIT;
  while (!i2cStart(addr)) {
    i2cStop();
    if (--retry == 0)
      return false;
  }
  return true;
}

/**
 * @brief Repeated start function.
 *
 * After having claimed the bus with a start condition,
 * you can address another or the same chip again without an intervening
 * stop condition.
 *
 * @param addr The 7-bit address of the slave device.
 *
 * @return True if the slave replies with an "acknowledge", false otherwise.
 */
bool DFRobot_SoftI2C::i2cRepStart(uint8_t addr)
{
  setPinHigh(_sda);
  setPinHigh(_scl);
  delayMicroseconds(DELAY);
  return i2cStart(addr);
}

/**
 * @brief Issue a stop condition, freeing the bus.
 *
 * This function generates a stop condition on the I2C bus,
 * releasing the bus for other devices to use.
 */
void DFRobot_SoftI2C::i2cStop(void)
{
  setPinLow(_sda);
  delayMicroseconds(DELAY);
  setPinHigh(_scl);
  delayMicroseconds(DELAY);
  setPinHigh(_sda);
  delayMicroseconds(DELAY);
}

/**
 * @brief Write one byte to the slave chip that had been addressed by the previous start call.
 *
 * @param value The byte to be sent.
 * @return True if the slave replies with an "acknowledge," false otherwise.
 */
bool DFRobot_SoftI2C::i2cWrite(uint8_t value)
{
  for (uint8_t curr = 0X80; curr != 0; curr >>= 1) {
    if (curr & value)
      setPinHigh(_sda);
    else
      setPinLow(_sda);
    setPinHigh(_scl);
    delayMicroseconds(DELAY);
    setPinLow(_scl);
  }

  setPinHigh(_sda);
  setPinHigh(_scl);
  delayMicroseconds(DELAY / 2);
  uint8_t ack = digitalRead(_sda);
  setPinLow(_scl);
  delayMicroseconds(DELAY / 2);
  setPinLow(_sda);
  return ack == 0;
}

/**
 * @brief Read one byte from the I2C bus.
 *
 * This function reads a single byte from the I2C bus. If the parameter `last` is true,
 * a NAK (Not Acknowledge) signal is sent after receiving the byte to terminate the
 * read sequence.
 *
 * @param last Set to true if NAK should be sent after the byte read.
 * @return The byte read from the I2C bus.
 */
uint8_t DFRobot_SoftI2C::i2cRead(bool last)
{
  uint8_t receivedByte = 0;
  setPinHigh(_sda);
  for (uint8_t i = 0; i < 8; i++) {
    receivedByte <<= 1;
    delayMicroseconds(DELAY);
    setPinHigh(_scl);
    if (digitalRead(_sda))
      receivedByte |= 1;
    setPinLow(_scl);
  }
  if (last)
    setPinHigh(_sda);
  else
    setPinLow(_sda);
  setPinHigh(_scl);
  delayMicroseconds(DELAY / 2);
  setPinLow(_scl);
  delayMicroseconds(DELAY / 2);
  setPinLow(_sda);
  return receivedByte;
}
/**
 * @brief Set the specified pin to a low state.
 *
 * This function sets the specified pin to a low (logic level 0) state. If pull-up
 * is enabled, it first ensures that the pin is set to a low state and then sets it
 * as an output pin. Interrupts are temporarily disabled during this process.
 *
 * @param pin The pin to be set to a low state.
 */
void DFRobot_SoftI2C::setPinLow(uint8_t pin)
{
  noInterrupts();
  if (_pullup)
    digitalWrite(pin, LOW);
  pinMode(pin, OUTPUT);
  interrupts();
}

/**
 * @brief Set the specified pin to a high level and configure its mode.
 *
 * This function sets the specified pin to a high level and configures its mode
 * according to the pull-up setting.
 *
 * @param pin The pin number to set high and configure.
 */
void DFRobot_SoftI2C::setPinHigh(uint8_t pin)
{
  noInterrupts();
  if (_pullup)
    pinMode(pin, INPUT_PULLUP);
  else
    pinMode(pin, INPUT);
  interrupts();
}