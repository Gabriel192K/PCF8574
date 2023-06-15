
/* Dependencies */
#include "PCF8574.h"

PCF8574A pcf(&Wire, 0x38);

/* Functions */
void setup(void)
{
    Serial.begin(115200);
    uint8_t status = pcf.begin(); /* Get the status of PCF */
    if (!status)
    {
        Serial.println(F("PCF is not working, please check wiring or address"));
        while(1);
    }
    else
        Serial.println(F("PCF is working"));
    pcf.pinMode(0, OUTPUT);
}

void loop(void)
{
    Serial.println(F("Pin 0 is TOGGLEING"));
    pcf.write(0, TOGGLE);
    delay(1000);
}