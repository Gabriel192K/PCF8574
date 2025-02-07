/**
 * @file PCF8574.cpp
 * @brief Implementation file for PCF8574 I/O expander control
 */
#include "PCF8574.h"

/**
 * @brief Constructor for the PCF8574 class.
 * 
 * This constructor initializes the PCF8574 instance with the given I2C address and TWI (I2C) interface.
 * It sets the `address` for the PCF8574 device and associates the provided TWI interface to communicate 
 * with the device over I2C.
 * 
 * @param address The I2C address of the PCF8574 device.
 * @param twi A pointer to the TWI (I2C) interface used for communication with the device.
 */
PCF8574::PCF8574(const uint8_t address, __TWI__* twi)
{
    this->address = address; /**< Set the I2C address of the PCF8574 device */
    this->twi = twi;         /**< Store the pointer to the TWI interface for communication */
}


/**
 * @brief Destructor for the PCF8574 class.
 * 
 * This destructor cleans up the PCF8574 instance by resetting the I2C address to an invalid value
 * (0xFF) and setting the TWI interface pointer to NULL, effectively disassociating the I2C communication.
 */
PCF8574::~PCF8574()
{
    this->address = 0xFF; /**< Reset the I2C address to an invalid value (0xFF) */
    this->twi = NULL;     /**< Set the TWI interface pointer to NULL */
}


/**
 * @brief Initializes the PCF8574 device.
 * 
 * This method sets up the I2C communication and initializes the input and output buffers to 0. 
 * It also begins the I2C communication using the provided TWI interface and checks if the device 
 * is successfully connected. If the device has already been initialized, it will return 0 to indicate 
 * no action was taken.
 * 
 * @return uint8_t Returns 1 if initialization is successful and the device is connected, 
 *         otherwise returns 0.
 */
const uint8_t PCF8574::begin(void)
{
    if (this->began)
        return (0); /**< If the device has already been initialized, return 0 */
    this->began = 1; /**< Mark the device as initialized */

    this->inputBuffer = 0x00; /**< Initialize the input buffer to 0 */
    this->outputBuffer = 0x00; /**< Initialize the output buffer to 0 */

    this->twi->begin(); /**< Start the I2C communication */
    return (this->isConnected()); /**< Check if the device is connected and return the result */
}


/**
 * @brief Checks if the PCF8574 device is connected via I2C.
 * 
 * This method attempts to begin a transmission to the device at the specified address and 
 * checks if the device acknowledges the connection. It uses the TWI interface to start the 
 * transmission and checks the response using the `endTransmission()` function.
 * 
 * @return uint8_t Returns 1 if the device successfully acknowledges the connection (i.e., it is connected), 
 *         otherwise returns 0.
 */
const uint8_t PCF8574::isConnected(void)
{
    this->twi->beginTransmission(this->address); /**< Start the I2C transmission to the device */
    return (this->twi->endTransmission() == TW_MT_SLA_ACK); /**< Check if the device acknowledged the connection */
}


/**
 * @brief Reads the state of a specific pin on the PCF8574.
 * 
 * This method reads the value of a specific pin (0-7) on the PCF8574 I/O expander. 
 * It retrieves the current value of all pins using the `read()` function and then 
 * extracts the state of the specified pin by shifting the result and masking the 
 * desired bit.
 * 
 * @param pin The pin number (0-7) to read the state from.
 * 
 * @return uint8_t Returns the state of the specified pin (0 or 1).
 *         - Returns 0 if the pin is in a low state.
 *         - Returns 1 if the pin is in a high state.
 *         - Returns 0 if the specified pin number is out of range (greater than 7).
 */
const uint8_t PCF8574::read(const uint8_t pin)
{
    if (pin > 7) /**< Check if the pin number is within the valid range (0-7) */
        return (0); /**< Return 0 if the pin number is invalid */
    
    return ((this->read() >> pin) & 1); /**< Read the pin state by shifting and masking */
}


/**
 * @brief Reads the input values of all pins from the PCF8574.
 * 
 * This method requests the input values from the PCF8574 I/O expander. It communicates 
 * with the device using the TWI (I2C) interface, retrieves the current values of all 
 * pins, and stores them in the `inputBuffer`. If the request to the device fails, it 
 * returns the previous value stored in the `inputBuffer`.
 * 
 * @return uint8_t The current input values of all pins. Each bit represents the state 
 *         of a corresponding pin (0 for low, 1 for high).
 *         - Returns the previously stored input buffer if the request fails.
 */
const uint8_t PCF8574::read(void)
{
    if (this->twi->requestFrom(address, (const uint8_t)1) != 1) /**< Check if data is successfully requested from the device */
        return (this->inputBuffer); /**< Return the previous input buffer if the request fails */
    
    this->inputBuffer = this->twi->read(); /**< Read the input data and store it in the input buffer */
    
    return (this->inputBuffer); /**< Return the current input buffer with the updated pin states */
}



/**
 * @brief Writes a value (LOW, HIGH, or TOGGLE) to a specific pin on the PCF8574.
 * 
 * This method writes a specified state (LOW, HIGH, or TOGGLE) to a particular pin on the 
 * PCF8574 I/O expander. The state of the pin is updated in the `outputBuffer`. If the 
 * state is not one of the valid options (LOW, HIGH, or TOGGLE), the function returns 0.
 * After modifying the `outputBuffer`, the updated value is written to the device via I2C.
 * 
 * @param pin The pin number (0-7) to which the state is being written.
 * @param state The state to set the pin to:
 *              - `LOW` sets the pin to low (0).
 *              - `HIGH` sets the pin to high (1).
 *              - `TOGGLE` toggles the current state of the pin.
 * 
 * @return uint8_t Returns 0 if the pin number is invalid or the state is not recognized. 
 *                 Returns the result of the `write` operation otherwise.
 */
const uint8_t PCF8574::write(const uint8_t pin, const uint8_t state)
{
    if (pin > 7) /**< Check if the pin number is valid (0-7) */
        return (0); /**< Return 0 for invalid pin number */
    
    switch (state) /**< Perform an action based on the state provided */
    {
        case LOW:
            this->outputBuffer = this->outputBuffer & ~(1 << pin); /**< Set the pin to LOW (0) */
            break;
        case HIGH:
            this->outputBuffer = this->outputBuffer | (1 << pin); /**< Set the pin to HIGH (1) */
            break;
        case TOGGLE:
            this->outputBuffer = this->outputBuffer ^ (1 << pin); /**< Toggle the pin's state */
            break;
        default:
            return (0); /**< Return 0 if an invalid state is provided */
    }

    return (this->write(this->outputBuffer)); /**< Write the updated output buffer to the device */
}



/**
 * @brief Writes a byte of data to the PCF8574 I/O expander.
 * 
 * This method writes a byte of data (8 bits) to the PCF8574 device via I2C. The data is 
 * stored in the `outputBuffer` and transmitted over the I2C bus. The function first 
 * initiates an I2C transmission, writes the byte of data, and then ends the transmission. 
 * The function returns the result of the I2C transmission.
 * 
 * @param data The 8-bit data to be written to the device.
 * 
 * @return uint8_t The result of the `endTransmission` call.
 */
const uint8_t PCF8574::write(const uint8_t data)
{
    this->outputBuffer = data; /**< Store the data in the output buffer */
    this->twi->beginTransmission(this->address); /**< Begin I2C transmission with the device */
    this->twi->write((const uint8_t)this->outputBuffer); /**< Write the byte of data */
    return (this->twi->endTransmission()); /**< End the transmission and return the result */
}


/**
 * @brief Ends communication with the PCF8574 I/O expander.
 * 
 * This method stops communication with the PCF8574 device by resetting the internal 
 * flags and buffers. It marks the instance as not initialized, ensuring that the device 
 * is no longer active. The input and output buffers are cleared.
 * 
 * @return uint8_t
 * - 1 if the operation was successful (communication ended).
 * - 0 if the device was not initialized and could not be ended.
 */
const uint8_t PCF8574::end(void)
{
    if (!this->began) /**< Check if the device was not initialized */
        return (0); /**< Return 0 if the device was not initialized */
    
    this->began = 0; /**< Mark the device as no longer initialized */
    
    this->inputBuffer = 0x00; /**< Clear the input buffer */
    this->outputBuffer = 0x00; /**< Clear the output buffer */

    return (1); /**< Return 1 to indicate successful operation */
}

