# PCF8574
PCF8574 implementation for PCF8574 IO Expander

## Key features
- `Microchip Studio IDE` compatible (not tested on `Arduino IDE`)
- ```begin()``` and ```end()``` functions to easily enable or disable the `PCF8574`
- Configurable mode of operation using ```setMode()```
- Port and bit ```read()``` and ```write()``` functions

## Read and Write
```C
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
```
