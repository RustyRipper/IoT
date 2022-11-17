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
    lcd.print("ZAD 1");
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
#define DEBOUNCE_PERIOD 10UL

bool isGreenButtonPressed()
{
    static int debounced_button_state = HIGH;
    static int previous_reading = HIGH;
    static unsigned long last_change_time = 0UL;
    bool isPressed = false;

    int current_reading = digitalRead(GREEN_BUTTON);

    if (previous_reading != current_reading)
    {
        last_change_time = millis();
    }

    if (millis() - last_change_time > DEBOUNCE_PERIOD)
    {
        if (current_reading != debounced_button_state)
        {
            if (debounced_button_state == HIGH && current_reading == LOW)
            {
                isPressed = true;
            }
            debounced_button_state = current_reading;
        }
    }

    previous_reading = current_reading;

    return isPressed;
}

bool isRedButtonPressed()
{
    static int debounced_button_state = HIGH;
    static int previous_reading = HIGH;
    static unsigned long last_change_time = 0UL;
    bool isPressed = false;

    int current_reading = digitalRead(RED_BUTTON);

    if (previous_reading != current_reading)
    {
        last_change_time = millis();
    }

    if (millis() - last_change_time > DEBOUNCE_PERIOD)
    {
        if (current_reading != debounced_button_state)
        {
            if (debounced_button_state == HIGH && current_reading == LOW)
            {
                isPressed = true;
            }
            debounced_button_state = current_reading;
        }
    }

    previous_reading = current_reading;

    return isPressed;
}
bool isGreenButtonUnPressed()
{
    static int debounced_button_state = HIGH;
    static int previous_reading = HIGH;
    static unsigned long last_change_time = 0UL;
    bool isUnPressed = false;

    int current_reading = digitalRead(GREEN_BUTTON);

    if (previous_reading != current_reading)
    {
        last_change_time = millis();
    }

    if (millis() - last_change_time > DEBOUNCE_PERIOD)
    {

        if (current_reading != debounced_button_state)
        {

            if (debounced_button_state == LOW && current_reading == HIGH)
            {
                isUnPressed = true;
            }

            debounced_button_state = current_reading;
        }
    }

    previous_reading = current_reading;

    return isUnPressed;
}
bool isRedButtonUnPressed()
{
    static int debounced_button_state = HIGH;
    static int previous_reading = HIGH;
    static unsigned long last_change_time = 0UL;
    bool isUnPressed = false;

    int current_reading = digitalRead(RED_BUTTON);

    if (previous_reading != current_reading)
    {
        last_change_time = millis();
    }

    if (millis() - last_change_time > DEBOUNCE_PERIOD)
    {

        if (current_reading != debounced_button_state)
        {

            if (debounced_button_state == LOW && current_reading == HIGH)
            {
                isUnPressed = true;
            }

            debounced_button_state = current_reading;
        }
    }

    previous_reading = current_reading;

    return isUnPressed;
}
int greenB = 0;
int redB = 0;
int result =0;
void loop()
{
    
    if(isGreenButtonPressed())
    {
        greenB = 1;
    }
    else if(isGreenButtonUnPressed()){
        greenB=0;
    }
    if(isRedButtonPressed())
    {
        redB = 1;
    }
    else if(isRedButtonUnPressed()){
        redB=0;
    }
    result=greenB+redB;
    String str = String(result);
    Serial.println(str);

}