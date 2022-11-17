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

bool blocker = true;
int currentTime = 0;
int currentMinutes = 0;
unsigned long lastBlinkChange = 0UL;
int currentSeconds=0;
int current10seconds=0;

void timer()
{
    const unsigned long BlinkChangePeriod = 1000UL;

    if (millis() - lastBlinkChange >= BlinkChangePeriod)
    {
      currentTime++;
      currentSeconds++;
      if(currentTime % 10 ==0){
        current10seconds++;
        currentSeconds=0;
      }
      if(currentTime % 12 ==0){
        current10seconds=0;
        currentTime=0;
        currentMinutes++;
        currentSeconds=0;
      }
        
        lastBlinkChange += BlinkChangePeriod;
    }
}

LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcdInit()
{
    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("ZAD 3");
    delay(5000);
}
void stoperInit()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("STOPER");

      lcd.setCursor(3, 1);
      lcd.print(0);
      lcd.setCursor(4, 1);
      lcd.print(":");
      lcd.setCursor(5, 1);
      lcd.print(0);
      lcd.setCursor(6, 1);
      lcd.print(0);
}

void lcdUpdate()
{

    
      lcd.setCursor(3, 1);
      lcd.print(currentMinutes);
      lcd.setCursor(4, 1);
      lcd.print(":");
      lcd.setCursor(5, 1);
      lcd.print(current10seconds);
      lcd.setCursor(6, 1);
      lcd.print(currentSeconds);
    
}

void setup()
{
    initRGB();
    initButtons();
    lcdInit();
    stoperInit();
}

int led_index = 0;
void loop()
{
    delay(50);
    if (isGreenButtonPressed())
    {
        digitalWrite(led[led_index], LOW);
        led_index = ++led_index % 3;
        digitalWrite(led[led_index], HIGH);
        blocker = !blocker;
        if (!blocker)
        {
            lastBlinkChange = millis();
        }
    }
    if (isRedButtonPressed())
    {
        blocker = true;
        lcd.clear();
        currentTime = 0;
        stoperInit();
        currentMinutes=0;
        current10seconds=0;
        currentSeconds=0;
    }
    if (!blocker)
    {
        timer();
    }
    lcdUpdate();
}
