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
#include "TWI\TWI.h"

class PCF8574
{
    public:
        PCF8574(__TWI__* twi, const uint8_t address);
        uint8_t  begin      (void);
        uint8_t  isConnected(void);
        void     pinMode    (uint8_t pin, uint8_t mode);
        uint8_t  read       (uint8_t pin);
        uint8_t read        (void);
        void     write      (uint8_t pin, uint8_t state);
        void     write      (uint8_t state);
        void     end        (void);
    private:
        uint8_t isOn;
        __TWI__* twi;
        uint8_t address, direction, input, output;

};

class PCF8574A
{
    public:
        PCF8574A(__TWI__* twi, const uint8_t address);
        uint8_t  begin      (void);
        uint8_t  isConnected(void);
        void     pinMode    (uint8_t pin, uint8_t mode);
        uint8_t  read       (uint8_t pin);
        uint8_t  read       (void);
        void     write      (uint8_t pin, uint8_t state);
        void     write      (uint8_t state);
        void     end        (void);
    private:
        uint8_t isOn;
        __TWI__* twi;
        uint8_t address, direction, input, output;

};

#endif
