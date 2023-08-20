#include "Arduino.h"
#include <TM1637Display.h>
#define CLK 4
#define DIO_V 2
#define DIO_I 3
#define EXT_V_REF 4.55

TM1637Display displayV(CLK, DIO_V);
TM1637Display displayI(CLK, DIO_I);
uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};

void setup()
{
    Serial.begin(9600);

    displayV.setBrightness(75);
    displayI.setBrightness(255);
    displayV.setSegments(data);
    displayI.setSegments(data);

    analogReference(EXTERNAL); // use AREF for reference voltage
}

// the loop function runs over and over again forever
int counter;
void loop()
{
    counter++;

    int sensorValue = analogRead(PIN_A0);
    // Convert the ADC reading (which goes from 0 - 1023) to a voltage reading (0 - 5V):
    float voltage = (sensorValue + 0.5) * EXT_V_REF / 1024.0;
    float temp = voltage * 25.21025227 - 2.20439897;
    Serial.println(temp);

    displayI.showNumberDecEx(temp, 0, false);
    displayV.showNumberDecEx(counter, 0b10000000, true);
    delay(1000);
}