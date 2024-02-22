#include "Arduino.h"
#include <SevenSegmentTM1637.h>
#include <MCP4725.h>
#include <ADS1X15.h>
#include <EncButton2.h>

// LiquidCrystal_I2C lcd(0x3f, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
MCP4725 MCP(0x60); //  0x62 or 0x63
ADS1115 ads(0x48);

// display
#define DIO_PIN 10
#define CLK_PIN 11

SevenSegmentTM1637 display(CLK_PIN, DIO_PIN);

#define ROTARY_PIN_1 8
#define ROTARY_PIN_2 9
#define ROTARY_PIN_BTN 12
EncButton2<EB_ENCBTN> enc(INPUT, ROTARY_PIN_1, ROTARY_PIN_2, ROTARY_PIN_BTN);

void setup()
{
    Serial.begin(38400);
    Serial.println("Booting up");
    MCP.begin();
    MCP.setValue(30);
    Serial.println("DAC is up");

    display.begin();
    display.setBacklight(100);
    display.clear();
    display.print(1);

    Wire.begin();
    ads.begin();
    ads.setGain(8); // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
    ads.setMode(1); // single shot mode
    Serial.println("ADS is up");
}

void loop()
{
    enc.tick();
    if (enc.turn())
    {
    }

//     Serial.println("Type value (max 4095): ");
//     while (Serial.available() == 0)
//     {
//     }
//     int choice = Serial.parseInt();
//     Serial.print("set value to: ");
//     Serial.println(choice);
//     MCP.setValue(choice);
//     delay(100);

//     for (size_t i = 0; i < 10; i++)
//     {
//         int16_t adc0;
//         float volts0;
//         ads.requestADC(0);
//         adc0 = ads.getValue();
//         volts0 = ads.toVoltage(adc0) * 1000;
//         Serial.println("-----------------------------------------------------------");
//         Serial.print("AIN0: ");
//         Serial.print(adc0);
//         Serial.print("  ");
//         Serial.print(volts0);
//         Serial.println("mV");
//         delay(100);
//     }

// }