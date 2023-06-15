#ifndef __PCF8574_H__

/*
    Compatible with both PCF8574 & PCF8574A
*/
/* ADDRESS TABLE
| INPUTS | PCF8574 |
|   000  |   0x20  |
|   001  |   0x21  |
|   010  |   0x22  |
|   011  |   0x23  |
|   100  |   0x24  |
|   101  |   0x25  |
|   110  |   0x26  |
|   111  |   0x27  |
*/

/* ADDRESS TABLE
| INPUTS | PCF8574A |
|   000  |   0x38   |
|   001  |   0x39   |
|   010  |   0x3A   |
|   011  |   0x3B   |
|   100  |   0x3C   |
|   101  |   0x3D   |
|   110  |   0x3E   |
|   111  |   0x3F   |
*/

/* Dependecies */
#if defined(ARDUINO)
    #include <Arduino.h>
    #include <Wire.h>
#else
    #include "TWI\TWI.h"
#endif

/* Macros */
#ifndef LOW
#define LOW 0
#endif
#ifndef HIGH
#define HIGH 1
#endif
#ifndef TOGGLE
#define TOGGLE 2
#endif

class PCF8574
{
    public:
        #if defined(ARDUINO)
            PCF8574(TwoWire* twi, const uint8_t address);
        #else
            PCF8574(__TWI__* twi, const uint8_t address);
        #endif
        ~PCF8574();
        uint8_t begin      (void);
        uint8_t isConnected(void);
        void    pinMode    (uint8_t pin, uint8_t mode);
        uint8_t read       (uint8_t pin);
        uint8_t read       (void);
        void    write      (uint8_t pin, uint8_t state);
        void    write      (uint8_t state);
        void    end        (void);
    private:
        #if defined(ARDUINO)
            TwoWire* twi;
        #else
            __TWI__* twi;
        #endif
        uint8_t address, direction, input, output;
        uint8_t isOn;
};

class PCF8574A
{
    public:
        #if defined(ARDUINO)
            PCF8574A(TwoWire* twi, const uint8_t address);
        #else
            PCF8574A(__TWI__* twi, const uint8_t address);
        #endif
        ~PCF8574A();
        uint8_t begin      (void);
        uint8_t isConnected(void);
        void    pinMode    (uint8_t pin, uint8_t mode);
        uint8_t read       (uint8_t pin);
        uint8_t read       (void);
        void    write      (uint8_t pin, uint8_t state);
        void    write      (uint8_t state);
        void    end        (void);
    private:
        #if defined(ARDUINO)
            TwoWire* twi;
        #else
            __TWI__* twi;
        #endif
        uint8_t address, direction, input, output;
        uint8_t isOn;
};

#endif
