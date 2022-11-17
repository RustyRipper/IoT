#include <LiquidCrystal_I2C.h>
#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3
#define RED_BUTTON 2
#define GREEN_BUTTON 4
int led[] = {LED_RED, LED_GREEN, LED_BLUE};
void initRGB()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, HIGH);

    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LOW);

    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LOW);
}

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
#define DEBOUNCE_PERIOD 10UL

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

void setup()
{
    lcdInit();
    initRGB();
    initButtons();
}

int led_index = 0;

void loop()
{

    if (isGreenButtonUnPressed() || isRedButtonUnPressed())
    {

        digitalWrite(led[led_index], LOW);
        delay(200);
        led_index = ++led_index % 3;
        digitalWrite(led[led_index], HIGH);
    }
}
