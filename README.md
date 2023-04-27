# PCF8574
PCF8584 implementation for AVR platform

# Compatible with both PCF8574 & PCF8574A
The only difference is that their TWI address ranges differ

## PCF8584 is an 8 bit IO Expander(multiplexer & demultiplexer) capable of communicating with the MCU via a TWI bus

## Key features
- Begin and end functions for easy on/off logic
- Address out of bounds and connection checking
- Bit direction logic with default state as input
- Port or bit read and write operations (can read or write entire port or specific bit)

## Tested on
- ATmega328P @16MHz
