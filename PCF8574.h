#ifndef __PCF8574_H__
#define __PCF8574_H__

/* Dependecies */
#include "../TWI/TWI.h"
#include "../IO/IO.h"

class PCF8574
{
    public:
        PCF8574(__TWI__* twi, const uint8_t address);
        ~PCF8574();
        const uint8_t begin      (void);
        const uint8_t isConnected(void);
        void          setMode    (uint8_t bit, const uint8_t mode);
        const uint8_t read       (uint8_t bit);
        const uint8_t read       (void);
        void          write      (uint8_t bit, const uint8_t data);
        void          write      (const uint8_t data);
        void          end        (void);
    private:
        __TWI__* twi;
        uint8_t address, direction, input, output;
};

#endif
