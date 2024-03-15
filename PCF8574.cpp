/* Dependencies */
#include "PCF8574.h"

/*********************************************
Function: PCF8574()
Purpose:  Constructor to PCF8574 class
Input:    Reference to TWI class & address
Return:   None
*********************************************/
PCF8574::PCF8574(__TWI__* twi, const uint8_t address)
{
    this->twi = twi;
    this->address = address;
}

/*********************************************
Function: ~PCF8574()
Purpose:  Destructor to PCF8574 class
Input:    None
Return:   None
*********************************************/
PCF8574::~PCF8574()
{
    this->twi = NULL;
    this->address = 0x00;
}

/*********************************************
Function: begin()
Purpose:  Begin PCF8574
Input:    None
Return:   Status of PCF8574 connection
*********************************************/
const uint8_t PCF8574::begin(void)
{
    this->twi->begin();           /* Start TWI bus */
    return (this->isConnected()); /* Check if device is connected */
}

/*********************************************
Function: isConnected()
Purpose:  Check connection with PCF8574
Input:    None
Return:   Flag of PCF8574 connection
*********************************************/
const uint8_t PCF8574::isConnected(void)
{
    const uint8_t isConnected = this->twi->beginTransmission(this->address); /* Begin the transmission with PCF8574 */
    this->twi->endTransmission();                                            /* End the transmission with PCF8574 */
    return (isConnected);                                                    /* Return isConnected flag */
}

/*********************************************
Function: setMode()
Purpose:  Set the mode of operation of a bit
Input:    Bit and mode of operation
Return:   None
*********************************************/
void PCF8574::setMode(uint8_t bit, const uint8_t mode)
{
    bit = bit % 8;                          /* Protect bit for out of bound value using modulo */
    switch (mode)
    {
        case OUTPUT:
            this->direction &= ~(1 << bit); /* Clear the bit */
            break;
        case INPUT:
            this->direction |= (1 << bit);  /* Set the bit */
            break;
        default:
            break;
    }
    this->write(this->direction);           /* Write the direction configuration to the port */
}

/*********************************************
Function: read()
Purpose:  Read the logic level of a bit
Input:    Bit to be read
Return:   Logic level of bit
*********************************************/
const uint8_t PCF8574::read(uint8_t bit)
{
    bit = bit % 8;                         /* Protect bit for out of bound value using modulo */
    return ((this->read() >> bit) & 0x01); /* Return the logic level of the bit */
}

/*********************************************
Function: read()
Purpose:  Read the logic level of a port
Input:    None
Return:   Logic level of port
*********************************************/
const uint8_t PCF8574::read(void)
{
    this->twi->requestFrom(this->address, (const uint8_t)0x01); /* Request 1 byte from PCF8574 */
    this->input = (const uint8_t)this->twi->read();             /* Read into the input buffer the value received */
    return (this->input);                                       /* Return the input buffer */
}

/*********************************************
Function: write()
Purpose:  Write the logic level of a bit
Input:    Bit to be written and its logic level
Return:   Logic level of port
*********************************************/
void PCF8574::write(uint8_t bit, const uint8_t data)
{
    bit = bit % 8;                       /* Protect bit for out of bound value using modulo */
    switch (data)
    {
        case LOW:
            this->output &= ~(1 << bit); /* Clear the bit */
            break;
        case HIGH:
            this->output |= (1 << bit);  /* Set the bit */
            break;
        case TOGGLE:
            this->output ^= (1 << bit);  /* Toggle the bit */
            break;
        default:
            break;
    }
    this->write(this->output);           /* Write the output buffer to the port */
}

/*********************************************
Function: write()
Purpose:  Write the logic level of a port
Input:    Logic level of port to be written
Return:   None
*********************************************/
void PCF8574::write(const uint8_t data)
{
    this->output = data;                         /* Write the data into the output buffer */
    this->twi->beginTransmission(this->address); /* Start the transmission to PCF8574 */
    this->twi->write(this->output);              /* Write the output buffer */
    this->twi->endTransmission();                /* End the transmissionwith PCF8574 */
}

/*********************************************
Function: end()
Purpose:  End PCF8574
Input:    None
Return:   None
*********************************************/
void PCF8574::end(void)
{
    this->twi->end();
}
