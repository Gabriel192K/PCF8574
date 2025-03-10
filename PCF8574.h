/* Dependencies */
#include <TWI.h>

#ifndef LOW
#define LOW (const uint8_t)0    //< Macro definition for LOW state (0)
#endif
#ifndef HIGH
#define HIGH (const uint8_t)1   //< Macro definition for HIGH state (1)
#endif
#ifndef TOGGLE
#define TOGGLE (const uint8_t)2 //< Macro definition for TOGGLE state (2)
#endif
#define PCF8574_MAX_PINS 8      //< Maximum number of pins on the PCF8574 I/O expander

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
        PCF8574(const uint8_t address, __TWI__* twi);
        ~PCF8574();
        const uint8_t begin(void);
        const uint8_t isConnected(void);
        const uint8_t read(const uint8_t pin);
        const uint8_t read(void);
        const uint8_t write(const uint8_t pin, const uint8_t state);
        const uint8_t write(const uint8_t data);
        const uint8_t end(void);

    private:
        uint8_t address;                   //< The I2C address of the PCF8574 device
        __TWI__* twi;                      //< Pointer to the TWI (I2C) interface for communication
        uint8_t began;                     //< Flag indicating whether the device has been initialized
        uint8_t inputBuffer, outputBuffer; //< Buffers for reading and writing data to the PCF8574
};

