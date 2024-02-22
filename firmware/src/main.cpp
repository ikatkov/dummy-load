#include "Arduino.h"
#include <SevenSegmentTM1637.h>
#include <MCP4725.h>
#include <ADS1X15.h>

// LiquidCrystal_I2C lcd(0x3f, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
MCP4725 MCP(0x60); //  0x62 or 0x63
ADS1115 ads(0x48);

// display
#define DIO_PIN 10
#define CLK_PIN 11

TM1637Display display(CLK_PIN, DIO_PIN);

void setup()
{
    Serial.begin(38400);
    Serial.println("Booting up");
    MCP.begin();
    MCP.setValue(30);
    Serial.println("DAC is up");

    display.setBrightness(255, true);
    display.clear();

    display.showNumberDec(8888);
    delay(1000);

    Wire.begin();
    ads.begin();
    ads.setGain(8); // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
    ads.setMode(1); // single shot mode
    Serial.println("ADS is up");

    display.clear();
}

void loop()
{
    Serial.println("Type value (max 4095): ");
    while (Serial.available() == 0)
    {
    }
    int choice = Serial.parseInt();
    Serial.print("set value to: ");
    Serial.println(choice);
    MCP.setValue(choice);
    delay(100);

    for (size_t i = 0; i < 10; i++)
    {
        int16_t adc0;
        float volts0;
        ads.requestADC(0);
        adc0 = ads.getValue();
        volts0 = ads.toVoltage(adc0) * 1000;
        Serial.println("-----------------------------------------------------------");
        Serial.print("AIN0: ");
        Serial.print(adc0);
        Serial.print("  ");
        Serial.print(volts0);
        Serial.println("mV");
        delay(100);
    }

    // int sensorValue = analogRead(PIN_A0);
    // // Convert the ADC reading (which goes from 0 - 1023) to a voltage reading (0 - 5V):
    // float voltage = (sensorValue + 0.5) * EXT_V_REF / 1024.0;
    // float temp = voltage * 25.21025227 - 2.20439897;
    // Serial.println(temp);
    // lcd.setCursor(0, 0);
    // lcd.print("12V");
    // lcd.setCursor(0, 1);
    // lcd.print("1.25A");
    // lcd.setCursor(11, 0);
    // lcd.print(temp);
    // lcd.setCursor(14, 0);
    // lcd.print(" C");
}