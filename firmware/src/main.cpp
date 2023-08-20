#include "Arduino.h"
#include <LiquidCrystal_I2C.h>
#define CLK 4
#define DIO_V 2
#define DIO_I 3
#define EXT_V_REF 4.55

LiquidCrystal_I2C lcd(0x3f, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
    Serial.begin(9600);

    lcd.init(); // initialize the lcd
    // Print a message to the LCD.
    lcd.backlight();
    // lcd.setCursor(3, 0);
    // lcd.print("Hello, world!");
    // lcd.setCursor(2, 1);
    // lcd.print("Ywrobot Arduino!");
    // lcd.setCursor(0, 2);
    // lcd.print("Arduino LCM IIC 2004");

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
    lcd.setCursor(0, 0);
    lcd.print("12V");
    lcd.setCursor(0, 1);
    lcd.print("1.25A");
    lcd.setCursor(11, 0);
    lcd.print(temp);
    lcd.setCursor(14, 0);
    lcd.print(" C");

    delay(1000);
}