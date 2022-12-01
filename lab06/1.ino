#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

OneWire oneWire(A1);
DallasTemperature tempSensors(&oneWire);

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3
int led[] = {LED_RED, LED_GREEN, LED_BLUE};

void initRGB() {
    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, LOW);

    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LOW);

    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LOW);
}

void initLCD()
{
  	lcd.init();
    lcd.backlight();
  	lcd.print("ZAD 1");
  	delay(1000);
}

void setup()
{   
    initRGB();
  	initLCD();
    tempSensors.begin();
    lcd.clear();
}

float tempIn = 0;
float tempOut = 0;
float tempMax = tempOut;
float tempMin = tempOut;

void getTemperature() {
    tempSensors.requestTemperatures();
    tempIn = tempSensors.getTempCByIndex(1);
    tempOut = tempSensors.getTempCByIndex(0);
    
    if (tempOut >= tempMax) {
        tempMax = tempOut;
    }
    if (tempOut <= tempMin) {
        tempMin = tempOut;
    }
}

void displayTemperatures() 
{
    char buffer[40];
    sprintf(buffer, "IN%4s", String(tempIn, 2).c_str());
    lcd.setCursor(0, 0);
    lcd.print(buffer);

    sprintf(buffer, "OUT%4s", String(tempOut, 2).c_str());
    lcd.setCursor(0, 1);
    lcd.print(buffer);

    sprintf(buffer, "MIN%4s", String(tempMin, 2).c_str());
    lcd.setCursor(8, 0);
    lcd.print(buffer);

    sprintf(buffer, "MAX%4s", String(tempMax, 2).c_str());
    lcd.setCursor(8, 1);
    lcd.print(buffer);
}

void loop()
{
    getTemperature();
    displayTemperatures();
    
    if(tempOut< 26.0) {
        digitalWrite(LED_BLUE, LOW);
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_RED, LOW);
    }
    else if (tempOut >= 26.0 && tempOut <=27.0){
        digitalWrite(LED_BLUE, HIGH);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_RED, LOW);
    }
    else{
        digitalWrite(LED_BLUE, LOW);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_RED, HIGH);
    }
}