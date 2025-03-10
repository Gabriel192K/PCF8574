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

### 1. Initialization

```cpp
PCF8574 pcf;
pcf.begin(0x20); // Replace 0x20 with your device's address
