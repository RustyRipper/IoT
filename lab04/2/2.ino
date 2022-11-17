#include <LiquidCrystal_I2C.h>
#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3
int led[] = {LED_RED, LED_GREEN, LED_BLUE};

void initRGB()
{
    pinMode(LED_RED, OUTPUT);
    analogWrite(LED_RED, 0);

    pinMode(LED_GREEN, OUTPUT);
    analogWrite(LED_GREEN, 0);

    pinMode(LED_BLUE, OUTPUT);
    analogWrite(LED_BLUE, 0);
}

void initSerial()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
}
LiquidCrystal_I2C lcd(0x27, 16, 2);
void lcdInit()
{
    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("ZAD 2");
}
void setup()
{
    lcdInit();
    initRGB();
    initSerial();
}

char *strings[6];
char *ptr = nullptr;

void loop()

{

    if (Serial.available() > 0)
    {
        String command = Serial.readStringUntil('\n');
        command.trim();
        if (command.substring(0, 3) == "rgb")
        {
            char array[20];
            command.toCharArray(array, sizeof(array));
            int index = 0;
            ptr = strtok(array, " "); // delimiter
            while (ptr != nullptr)
            {
                strings[index] = ptr;
                index++;
                ptr = strtok(nullptr, " ");
            }

            for (int i = 1; i < 4; i++)
            {
                Serial.println(atoi(strings[i]));

                analogWrite(led[i-1], atoi(strings[i]));
            }
        }

        Serial.println();
    }
}
