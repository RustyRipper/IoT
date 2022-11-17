//4000000
#include <LiquidCrystal_I2C.h>
#define RED_BUTTON 2
#define GREEN_BUTTON 4

void initButtons()
{
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}
LiquidCrystal_I2C lcd(0x27, 16, 2);
void lcdInit()
{
    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("ZAD 1 delay");
}
void setup()
{
    lcdInit();
    initButtons();
    Serial.begin(9600);
    while (!Serial)
    {    /* just wait */
    }
}

int greenB = 0;
int redB = 0;
int result =0;
void loop()
{
    
    if(digitalRead(GREEN_BUTTON)==LOW)
    {
        greenB = 1;
  
    }
    else if(digitalRead(GREEN_BUTTON)==HIGH){
        greenB=0;
    }
    if(digitalRead(RED_BUTTON)==LOW)
    {
        redB = 1;
    }
    else if(digitalRead(RED_BUTTON)==HIGH){
        redB=0;
    }
    delay(200);
    result=greenB+redB;
    String str = String(result);
    Serial.println(str);

}