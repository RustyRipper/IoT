#include <LiquidCrystal_I2C.h>
#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

void setup()
{

    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, LOW);
    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LOW);
    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LOW);
}

void redLed()
{
    const unsigned long BlinkChangePeriod = 900UL;
    static int ledState = LOW;
    static unsigned long lastBlinkChange = 0UL;

    if (millis() - lastBlinkChange >= BlinkChangePeriod)
    {
        if (ledState == HIGH)
        {
            ledState = LOW;
        }
        else
        {
            ledState = HIGH;
        }

        digitalWrite(LED_RED, ledState);
        lastBlinkChange += BlinkChangePeriod;
    }
}
void greenLed()
{
    const unsigned long BlinkChangePeriod = 1000UL;
    static int ledState = LOW;
    static unsigned long lastBlinkChange = 0UL;

    if (millis() - lastBlinkChange >= BlinkChangePeriod)
    {
        if (ledState == HIGH)
        {
            ledState = LOW;
        }
        else
        {
            ledState = HIGH;
        }

        digitalWrite(LED_GREEN, ledState);
        lastBlinkChange += BlinkChangePeriod;
    }
}
void blueLed()
{
    const unsigned long BlinkChangePeriod = 1100UL;
    static int ledState = LOW;
    static unsigned long lastBlinkChange = 0UL;

    if (millis() - lastBlinkChange >= BlinkChangePeriod)
    {
        if (ledState == HIGH)
        {
            ledState = LOW;
        }
        else
        {
            ledState = HIGH;
        }

        digitalWrite(LED_BLUE, ledState);
        lastBlinkChange += BlinkChangePeriod;
    }
}
LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcdInit()
{
    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("ZAD 1");
}

void loop()
{
    redLed();
    greenLed();
    blueLed();
}
