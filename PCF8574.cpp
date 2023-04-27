#include "PCF8574.h"

/*********************************************
Function: PCF8574()
Purpose:  Constructor to PCF8574 class
Input:    Reference to TWI class & address of PCF8574
Return:   None
*********************************************/
PCF8574::PCF8574(__TWI__* twi, const uint8_t address)
{
    this->twi = twi;
    this->address = address;
}

/*********************************************
Function: PCF8574A()
Purpose:  Constructor to PCF8574 class
Input:    Reference to TWI class & address of PCF8574
Return:   None
*********************************************/
PCF8574A::PCF8574A(__TWI__* twi, const uint8_t address)
{
    this->twi = twi;
    this->address = address;
}

/*********************************************
Function: begin()
Purpose:  Begin communication with device
Input:    TWI address of device
Return:   State of communication with device is successful or not
*********************************************/
uint8_t PCF8574::begin(void)
{
    if (this->isOn)                                   /* Check if device was already ON */
        return (0);
    if (this->address < 0x20 || this->address > 0x27) /* Check if device's specified address is out of bounds */
        return (0);
    this->twi->begin();                               /* Start TWI bus */
    this->isOn = this->isConnected();                 /* Check if device is connected */
    if (this->isOn)                                   /* Check if device ON */
        for (uint8_t i = 0; i < 8; i++)
            this->pinMode(i, INPUT);                  /* Configure everything as INPUT */
    return (this->isOn);                              /* Return status */
}

/*********************************************
Function: begin()
Purpose:  Begin communication with device
Input:    TWI address of device
Return:   State of communication with device is successful or not
*********************************************/
uint8_t PCF8574A::begin(void)
{
    if (this->isOn)                                   /* Check if device was already ON */
        return (0);
    if (this->address < 0x38 || this->address > 0x3F) /* Check if device's specified address is out of bounds */
        return (0);
    this->twi->begin();                               /* Start TWI bus */
    this->isOn = this->isConnected();                 /* Check if device is connected */
    if (this->isOn)                                   /* Check if device ON */
        for (uint8_t i = 0; i < 8; i++)
            this->pinMode(i, INPUT);                  /* Configure everything as INPUT */
    return (this->isOn);                              /* Return status */
}

/*********************************************
Function: isConnected()
Purpose:  Check communication status with device
Input:    None
Return:   Status of communication
*********************************************/
uint8_t PCF8574::isConnected(void)
{
    uint8_t state = this->twi->beginTransmission(address);
    this->twi->endTransmission();
    return (state);
}

/*********************************************
Function: isConnected()
Purpose:  Check communication status with device
Input:    None
Return:   Status of communication
*********************************************/
uint8_t PCF8574A::isConnected(void)
{
    uint8_t state = this->twi->beginTransmission(address);
    this->twi->endTransmission();
    return (state);
}

/*********************************************
Function: pinMode()
Purpose:  Set pin working mode
Input:    Specific pin and it's working mode
Return:   None
*********************************************/
void PCF8574::pinMode(uint8_t pin, uint8_t mode)
{
    if (!this->isOn)                                  /* Check if device is not ON */
        return;
    if (this->address < 0x20 || this->address > 0x27) /* Check if device's specified address is out of bounds */
        return;
    if (pin > 7)                                      /* Check if pin is out of bounds */
        return;
    switch (mode)
    {
        case OUTPUT: this->direction &= ~(1 << pin); break;
        case INPUT : this->direction |= (1 << pin);  break;
        default    :                                 break;
    }
    this->write(this->direction);
}

/*********************************************
Function: pinMode()
Purpose:  Set pin working mode
Input:    Specific pin and it's working mode
Return:   None
*********************************************/
void PCF8574A::pinMode(uint8_t pin, uint8_t mode)
{
    if (!this->isOn)                                  /* Check if device is not ON */
        return;
    if (this->address < 0x38 || this->address > 0x3F) /* Check if device's specified address is out of bounds */
        return;
    if (pin > 7)                                      /* Check if pin is out of bounds */
        return;
    switch (mode)
    {
        case OUTPUT: this->direction &= ~(1 << pin); break;
        case INPUT : this->direction |= (1 << pin);  break;
        default    :                                 break;
    }
    this->write(this->direction);
}

/*********************************************
Function: read()
Purpose:  Read entire IO bus of the device
Input:    None
Return:   Whole IO bus of the device
*********************************************/
uint8_t PCF8574::read(void)
{
    if (!this->isOn)                                   /* Check if device is not ON */
        return (0);
    if (this->address < 0x20 || this->address > 0x27)  /* Check if device's specified address is out of bounds */
        return (0);
    if (this->twi->requestFrom(this->address, 1) != 1) /* Check if request was successful */
        return(0);
    this->input = (uint8_t)this->twi->read();
    this->twi->endTransmission();
    return (this->input);
}

/*********************************************
Function: read()
Purpose:  Read entire IO bus of the device
Input:    None
Return:   Whole IO bus of the device
*********************************************/
uint8_t PCF8574A::read(void)
{
    if (!this->isOn)                                   /* Check if device is not ON */
        return (0);
    if (this->address < 0x38 || this->address > 0x3F)  /* Check if device's specified address is out of bounds */
        return (0);
    if (this->twi->requestFrom(this->address, 1) != 1) /* Check if request was successful */
        return(0);
    this->input = (uint8_t)this->twi->read();
    this->twi->endTransmission();
    return (this->input);
}

/*********************************************
Function: write()
Purpose:  Write entire IO bus of the device
Input:    Entire IO bus of the device
Return:   None
*********************************************/
void PCF8574::write(uint8_t data)
{
    if (!this->isOn)                                  /* Check if device is not ON */
        return;
    if (this->address < 0x20 || this->address > 0x27) /* Check if device's specified address is out of bounds */
        return;
    this->output = data;
    this->twi->beginTransmission(this->address);
    this->twi->write((uint8_t)this->output);
    this->twi->endTransmission();
}

/*********************************************
Function: write()
Purpose:  Write entire IO bus of the device
Input:    Entire IO bus of the device
Return:   None
*********************************************/
void PCF8574A::write(uint8_t data)
{
    if (!this->isOn)                                  /* Check if device is not ON */
        return;
    if (this->address < 0x38 || this->address > 0x3F) /* Check if device's specified address is out of bounds */
        return;
    this->output = data;
    this->twi->beginTransmission(this->address);
    this->twi->write((uint8_t)this->output);
    this->twi->endTransmission();
}

/*********************************************
Function: read()
Purpose:  Read specific pin from device
Input:    None
Return:   Specific pin from device
*********************************************/
uint8_t PCF8574::read(uint8_t pin)
{
    if (!this->isOn)                                  /* Check if device is not ON */
        return (0);
    if (this->address < 0x20 || this->address > 0x27) /* Check if device's specified address is out of bounds */
        return (0);
    if (pin > 7)                                      /* Check if pin is out of bounds */
        return (0);
    this->read();
    return ((this->input >> pin) & 1);
}

/*********************************************
Function: read()
Purpose:  Read specific pin from device
Input:    None
Return:   Specific pin from device
*********************************************/
uint8_t PCF8574A::read(uint8_t pin)
{
    if (!this->isOn)                                  /* Check if device is not ON */
        return (0);
    if (this->address < 0x38 || this->address > 0x3F) /* Check if device's specified address is out of bounds */
        return (0);
    if (pin > 7)                                      /* Check if pin is out of bounds */
        return (0);
    this->read();
    return ((this->input >> pin) & 1);
}

/*********************************************
Function: write()
Purpose:  Write specific pin to device
Input:    Data and specific pin to be written
Return:   None
*********************************************/
void PCF8574::write(uint8_t pin, uint8_t state)
{
    if (!this->isOn)                                  /* Check if device is not ON */
        return;
    if (this->address < 0x20 || this->address > 0x27) /* Check if device's specified address is out of bounds */
        return;
    if (pin > 7)                                      /* Check if pin is out of bounds */
        return;
    switch (state)
    {
        case LOW   : this->output &= ~(1 << pin); break;
        case HIGH  : this->output |= (1 << pin);  break;
        case TOGGLE: this->output ^= (1 << pin);  break;
        default    :                              break;
    }
    this->write(output);
}

/*********************************************
Function: write()
Purpose:  Write specific pin to device
Input:    Data and specific pin to be written
Return:   None
*********************************************/
void PCF8574A::write(uint8_t pin, uint8_t state)
{
    if (!this->isOn)                                  /* Check if device is not ON */
        return;
    if (this->address < 0x38 || this->address > 0x3F) /* Check if device's specified address is out of bounds */
        return;
    if (pin > 7)                                      /* Check if pin is out of bounds */
        return;
    switch (state)
    {
        case LOW   : this->output &= ~(1 << pin); break;
        case HIGH  : this->output |= (1 << pin);  break;
        case TOGGLE: this->output ^= (1 << pin);  break;
        default    :                              break;
    }
    this->write(output);
}

/*********************************************
Function: end()
Purpose:  End communication with device
Input:    None
Return:   None
*********************************************/
void PCF8574::end(void)
{
    this->isOn = 0;
}

/*********************************************
Function: end()
Purpose:  End communication with device
Input:    None
Return:   None
*********************************************/
void PCF8574A::end(void)
{
    this->isOn = 0;
}
