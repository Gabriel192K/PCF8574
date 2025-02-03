/**
 * @file PCF8574.cpp
 * @brief Implementation file for PCF8574 I/O expander control
 */
#include "PCF8574.h"

/**
 * @brief Constructor for PCF8574 class
 * @param address I2C address of the PCF8574 device
 * @param twi Pointer to TWI (I2C) interface object
 */
PCF8574::PCF8574(const uint8_t address, __TWI__* twi)
{
    this->address = address;
    this->twi = twi;
}

/**
 * @brief Destructor for PCF8574 class
 * Resets address and TWI pointer
 */
PCF8574::~PCF8574()
{
    this->address = 0xFF;
    this->twi = NULL;
}

/**
 * @brief Initializes the PCF8574 device
 * @return 0 if already initialized, otherwise returns connection status
 */
const uint8_t PCF8574::begin(void)
{
    if (this->began)
        return (0);
    this->began = 1;

    this->inputBuffer = 0x00;
    this->outputBuffer = 0x00;

    this->twi->begin();
    return (this->isConnected());
}

/**
 * @brief Checks if PCF8574 device is connected and responding
 * @return 1 if device responds, 0 if no response
 */
const uint8_t PCF8574::isConnected(void)
{
    this->twi->beginTransmission(this->address);
    return (this->twi->endTransmission() == TW_MT_SLA_ACK);
}

/**
 * @brief Reads the state of a specific pin
 * @param pin Pin number (0-7) to read
 * @return State of the pin (0 or 1), returns 0 if invalid pin
 */
const uint8_t PCF8574::read(const uint8_t pin)
{
    if (pin > 7)
        return (0);
    
    return ((this->read() >> pin) & 1);
}

/**
 * @brief Reads the state of all pins
 * @return 8-bit value representing all pin states
 */
const uint8_t PCF8574::read(void)
{
    if (this->twi->requestFrom(address, (const uint8_t)1) != 1);
        return (this->inputBuffer);
    
    this->inputBuffer = this->twi->read();
    
    return (this->inputBuffer);
}


/**
 * @brief Sets the state of a specific pin
 * @param pin Pin number (0-7) to write to
 * @param state Desired state (LOW, HIGH, or TOGGLE)
 * @return 0 if invalid pin/state, otherwise returns transmission status
 */
const uint8_t PCF8574::write(const uint8_t pin, const uint8_t state)
{
    if (pin > 7)
        return (0);
    
    switch (state)
    {
        case LOW:
            this->outputBuffer = this->outputBuffer & ~(1 << pin);
            break;
        case HIGH:
            this->outputBuffer = this->outputBuffer | (1 << pin);
            break;
        case TOGGLE:
            this->outputBuffer = this->outputBuffer ^ (1 << pin);
            break;
        default:
            return (0);
    }

    return (this->write(this->outputBuffer));
}


/**
 * @brief Writes data to all pins simultaneously
 * @param data 8-bit value to write to all pins
 * @return I2C transmission status
 */
const uint8_t PCF8574::write(const uint8_t data)
{
    this->outputBuffer = data;
    this->twi->beginTransmission(this->address);
    this->twi->write((const uint8_t)this->outputBuffer);
    return (this->twi->endTransmission());
}

/**
 * @brief Terminates the PCF8574 I/O expander operations
 * 
 * This function resets the device state by:
 * - Checking if device was previously initialized
 * - Setting the initialization flag to false
 * - Clearing both input and output buffers
 * 
 * @return 0 if device was not initialized, 1 if successfully terminated
 */
const uint8_t PCF8574::end(void)
{
    if (!this->began)
        return (0);
    this->began = 0;
    
    this->inputBuffer = 0x00;
    this->outputBuffer = 0x00;

    return (1);
}