# PCF8574 I/O Expander Library

A lightweight C++ library to control the **PCF8574 I/O Expander** over I2C/TWI, designed for embedded systems using direct TWI interface communication.  

## 📦 Features

- Initialize and manage communication with **PCF8574** devices via I2C.
- Read the state of individual pins or all pins at once.
- Write `HIGH`, `LOW`, or `TOGGLE` states to individual pins.
- Write an entire byte to all output pins.
- Check if the device is properly connected.
- Cleanly terminate communication and release resources.

## 🚀 Usage

```cpp
/* Dependencies */
#include "PCF8574.h"

/* Macros */
#define PCF8574_TWI_ADDRESS (const uint8_t)0x38
#define PCF8574_TWI_BUS     TWI

/* Instances */
PCF8574 pcf8574(PCF8574_TWI_ADDRESS, PCF8574_TWI_BUS);

int main(void)
{
    const uint8_t is_connected = pcf8574.begin();
    while (1)
    {
        const uint8_t pin_state = pcf8574.read(0);
        const uint8_t pins_state = pcf8574.read();
        pcf8574.write(1, TOGGLE);
        pcf8574.write(0b10100101);
    }
    return (0);
}
```

## Compatibility

Expects a ```__TWI__``` type of class for the ***TWI(I2C)*** communication so ***it is not*** directly compatible with ***Arduino IDE's Wire*** implementation. Future updates may include this if tested.

For now it is fully compatible with ***Arduino IDE*** and ***Microchip Studio IDE*** using this ***TWI*** implementation
[TWI](https://github.com/Gabriel192K/TWI).

