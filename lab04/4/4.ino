#include <LiquidCrystal_I2C.h>
int sensorPin = A0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
void lcdInit()
{
    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("ZAD 4");
}
void setup()
{
    lcdInit();
    Serial.begin(9600);
    while (!Serial)
    {    /* just wait */
    }
}
int sensorValue = 0;
void loop()
{
    sensorValue = analogRead(sensorPin);
    String str = String(sensorValue);
    Serial.println(str);

}