#include <LiquidCrystal_I2C.h>
#include <util/atomic.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2

#define ENCODER1 A2
#define ENCODER2 A3

#define DEBOUNCING_PERIOD 100

int encoderValue = 0;
int lastEn1 = LOW;

volatile int encoder1 = HIGH;
volatile int encoder2 = HIGH;
volatile unsigned long encoderTimestamp = 0UL;

unsigned long lastChangeTimestamp = 0UL;
int encoderValueForButton = 0;

bool buttonLastValue = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);

int led[] = {LED_RED, LED_GREEN, LED_BLUE};
char *myStrings[] = {"LED_RED", "LED_GREEN", "LED_BLUE", "RESET"};

unsigned int lastValue = 0;
bool markerTop = true;
unsigned int value = 0;

ISR(PCINT1_vect)
{
    encoder1 = digitalRead(ENCODER1);
    encoder2 = digitalRead(ENCODER2);
    encoderTimestamp = millis();
}

#define DEBOUNCE_PERIOD 10UL
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
void printResults(int val)
{
    value = val;

    char buffer[40];

    lcd.clear();

    if (val >= lastValue)
    {
        if (val == 0)
        {
            sprintf(buffer, "%s", myStrings[0]);
            lcd.setCursor(3, 0);
            lcd.print(buffer);

            sprintf(buffer, "%s", myStrings[1]);
            lcd.setCursor(3, 1);
            lcd.print(buffer);

            markerTop = true;
        }
        else if (val == 1)
        {
            sprintf(buffer, "%s", myStrings[0]);
            lcd.setCursor(3, 0);
            lcd.print(buffer);

            sprintf(buffer, "%s", myStrings[1]);
            lcd.setCursor(3, 1);
            lcd.print(buffer);

            markerTop = false;
        }
        else if (val == 3 && lastValue == 3)
        {
            sprintf(buffer, "%s", myStrings[2]);
            lcd.setCursor(3, 0);
            lcd.print(buffer);

            sprintf(buffer, "%s", myStrings[3]);
            lcd.setCursor(3, 1);
            lcd.print(buffer);
        }
        else
        {
            sprintf(buffer, "%s", myStrings[lastValue]);
            lcd.setCursor(3, 0);
            lcd.print(buffer);

            sprintf(buffer, "%s", myStrings[val]);
            lcd.setCursor(3, 1);
            lcd.print(buffer);

            markerTop = false;
        }
    }
    else
    {
        if (val == 3)
        {
            sprintf(buffer, "%s", myStrings[2]);
            lcd.setCursor(3, 0);
            lcd.print(buffer);

            sprintf(buffer, "%s", myStrings[3]);
            lcd.setCursor(3, 1);
            lcd.print(buffer);

            markerTop = false;
        }
        else if (val == 2)
        {
            sprintf(buffer, "%s", myStrings[2]);
            lcd.setCursor(3, 0);
            lcd.print(buffer);

            sprintf(buffer, "%s", myStrings[3]);
            lcd.setCursor(3, 1);
            lcd.print(buffer);

            markerTop = true;
        }
        else
        {
            sprintf(buffer, "%s", myStrings[val]);
            lcd.setCursor(3, 0);
            lcd.print(buffer);

            sprintf(buffer, "%s", myStrings[lastValue]);
            lcd.setCursor(3, 1);
            lcd.print(buffer);

            markerTop = true;
        }
    }

    lcd.setCursor(0, markerTop ? 0 : 1);
    lcd.print("->");

    lastValue = val;
}

void myAction(int val)
{
    printResults(val);
}

void myActionLed(int val)
{
    if (value == 3)
    {
        analogWrite(led[0], 0);
        analogWrite(led[1], 0);
        analogWrite(led[2], 0);
    }
    else
        analogWrite(led[value], val);
}

void setup()
{
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    analogWrite(LED_RED, 0);
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_BLUE, 0);
    pinMode(ENCODER1, INPUT_PULLUP);
    pinMode(ENCODER2, INPUT_PULLUP);
    pinMode(RED_BUTTON, INPUT_PULLUP);
    lcd.init();
    lcd.backlight();
    myAction(0);
    myActionLed(0);

    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << PCINT10);
}

void loop()
{
    int en1;
    int en2;
    unsigned long timestamp;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        en1 = encoder1;
        en2 = encoder2;
        timestamp = encoderTimestamp;
    }

    if (!buttonLastValue)
    {

        if (en1 == LOW && lastEn1 == HIGH && timestamp > lastChangeTimestamp + DEBOUNCING_PERIOD)
        {
            if (en2 == HIGH)
            {
                if (encoderValue < 3)
                    encoderValue += 1;
            }
            else
            {
                if (encoderValue > 0)
                    encoderValue -= 1;
            }
            lastChangeTimestamp = timestamp;

            myAction(encoderValue);
        }
        lastEn1 = en1;
    }
    else
    {
        if (en1 == LOW && lastEn1 == HIGH && timestamp > lastChangeTimestamp + DEBOUNCING_PERIOD)
        {
            if (en2 == HIGH)
            {
                if (encoderValueForButton < 255)
                    encoderValueForButton += 15;
            }
            else
            {
                if (encoderValueForButton > 0)
                    encoderValueForButton -= 15;
            }
            lastChangeTimestamp = timestamp;
        }
        lastEn1 = en1;

        myActionLed(encoderValueForButton);
    }

    if (isRedButtonUnPressed())
    {
        if (buttonLastValue)
        {
            encoderValueForButton = 0;
        }
        buttonLastValue = !buttonLastValue;
    }
}