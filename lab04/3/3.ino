#include <LiquidCrystal_I2C.h>
int sensorPin = A0;
int sensorValue = 0;
float volt =0.0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcdInit()
{
    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("ZAD 3");
    delay(500);
}
void lcdUpdate(){
    lcd.setCursor(5, 1);
    lcd.print("ADC =     ");
    lcd.setCursor(11, 1);
    lcd.print(sensorValue);
    lcd.setCursor(7, 0);
    lcd.print("V =     ");
    lcd.setCursor(11, 0);
    lcd.print(volt);
}
void setup()
{
    lcdInit();

 }

 void loop()
 {
    sensorValue = analogRead(sensorPin);
    float j = (float) sensorValue;
    volt = j*5.0/1024.0;
    lcdUpdate();

 }
