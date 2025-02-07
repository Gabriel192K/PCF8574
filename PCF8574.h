/* Dependencies */
#include <TWI.h>

/* Macros */
#ifndef LOW
#define LOW (const uint8_t)0 /**< Macro definition for LOW state (0) */
#endif
#ifndef HIGH
#define HIGH (const uint8_t)1 /**< Macro definition for HIGH state (1) */
#endif
#ifndef TOGGLE
#define TOGGLE (const uint8_t)2 /**< Macro definition for TOGGLE state (2) */
#endif

/**
 * @class PCF8574
 * @brief Class for interfacing with the PCF8574 I/O expander using I2C.
 * 
 * The PCF8574 class provides an interface to communicate with the PCF8574 I/O 
 * expander over I2C. It allows you to control the pins of the I/O expander and 
 * read their states. The class provides methods to initialize communication, 
 * read input states, write output states, and manage the connection to the PCF8574.
 */
class PCF8574
{
    public:
        /**
         * @brief Constructor to initialize the PCF8574 with the given I2C address and TWI object.
         * @param address The I2C address of the PCF8574 device.
         * @param twi Pointer to the I2C (TWI) interface used for communication.
         */
        PCF8574(const uint8_t address, __TWI__* twi);

        /**
         * @brief Destructor to clean up the PCF8574 object.
         */
        ~PCF8574();

        /**
         * @brief Initializes communication with the PCF8574 device.
         * @return 1 if the device is successfully initialized, 0 if already initialized or failed.
         */
        const uint8_t begin(void);

        /**
         * @brief Checks if the PCF8574 is connected and responding to I2C requests.
         * @return 1 if the device is connected, 0 if not connected.
         */
        const uint8_t isConnected(void);

        /**
         * @brief Reads the state of a specific pin on the PCF8574.
         * @param pin The pin number (0-7) to read.
         * @return The state of the pin (0 or 1).
         */
        const uint8_t read(const uint8_t pin);

        /**
         * @brief Reads the entire 8-bit input buffer from the PCF8574.
         * @return The 8-bit value of the input buffer.
         */
        const uint8_t read(void);

        /**
         * @brief Writes the state to a specific pin on the PCF8574.
         * @param pin The pin number (0-7) to write.
         * @param state The state to set the pin to (LOW, HIGH, TOGGLE).
         * @return 1 if the write was successful, 0 if the pin is invalid.
         */
        const uint8_t write(const uint8_t pin, const uint8_t state);

        /**
         * @brief Writes an 8-bit value to the PCF8574, setting the state of all output pins.
         * @param data The 8-bit data to write to the output pins.
         * @return 1 if the write was successful, 0 if the write failed.
         */
        const uint8_t write(const uint8_t data);

        /**
         * @brief Ends communication with the PCF8574 device.
         * @return 1 if communication was successfully ended, 0 if the device was not initialized.
         */
        const uint8_t end(void);

    private:
        uint8_t address; /**< The I2C address of the PCF8574 device */
        __TWI__* twi; /**< Pointer to the TWI (I2C) interface for communication */
        uint8_t began; /**< Flag indicating whether the device has been initialized */
        uint8_t inputBuffer, outputBuffer; /**< Buffers for reading and writing data to the PCF8574 */
};

