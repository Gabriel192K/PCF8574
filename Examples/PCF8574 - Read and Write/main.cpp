/*
 * PCF8574 - Read and Write.cpp
 *
 * Created: 3/15/2024 2:42:22 PM
 * Author : rotes
 */ 

#include "TWI/TWI.h"
#include "PCF8574/PCF8574.h"

PCF8574 pcf(&TWI, 0x38);

int main(void)
{
    pcf.begin();
    /* Read and write bits */
    pcf.setMode(0, OUTPUT);          /* Set bit as OUTPUT */
    pcf.setMode(1, INPUT);           /* Set bit as INPUT */
    pcf.write(0, HIGH);              /* Write bit as HIGH */
    const uint8_t bit = pcf.read(1); /* Read bit */

    /* Read and write port */
    for (uint8_t bit = 0; bit < 8; bit++)
        pcf.setMode(bit, OUTPUT);         /* Set port as OUTPUT */
    pcf.write(0xAA);                      /* Write port */
    for (uint8_t bit = 0; bit < 8; bit++)
        pcf.setMode(bit, INPUT);          /* Set port as OUTPUT */
    const uint8_t port = pcf.read();      /* Read port */
    while (1)
    {
    }
}

