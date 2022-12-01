#include "MyRGB.h"


MyRGB::MyRGB(int pinRed, int pinGreen, int pinBlue)
{
    redPin = pinRed;
    greenPin = pinGreen;
    bluePin = pinBlue;
}

void MyRGB::init()
{
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
}

void MyRGB::writeRgb(int redValue, int greenValue, int blueValue)
{
    Color color(redValue, greenValue, blueValue);
    setRGB(color);
}

void MyRGB::writeColor(String colorName)
{
    Color color(colorName);
    setRGB(color);
}

void MyRGB::setRGB(Color color)
{
    analogWrite(redPin, color.getRed());
    analogWrite(greenPin, color.getGreen());
    analogWrite(bluePin, color.getBlue());
}

//=====================================================

Color::Color(String colorName) {
    if(colorName == "red") {
        setRgb(RED);
    }
    else if(colorName == "green") {
        setRgb(GREEN);
    }
    else if(colorName == "blue") {
        setRgb(BLUE);
    }
    else if(colorName == "yellow") {
        setRgb(YELLOW);
    }
    else if(colorName == "cyan") {
        setRgb(CYAN);
    }
    else if(colorName == "magenta") {
        setRgb(MAGENTA);
    }
    else if(colorName == "white") {
        setRgb(WHITE);
    }
    else if(colorName == "black") {
        setRgb(BLACK);
    }
};

Color::Color(int redValue, int greenValue, int blueValue) {
    setRGB(redValue, greenValue, blueValue);
};


void Color::setRgb(int redValue, int greenValue, int blueValue){
    red = redValue;
    green = greenValue;
    blue = blueValue;
}
void Color::setRgb(int[] rgb){
    red = rgb[0];
    green = rgb[1];
    blue = rgb[2];
}

int Color::getRed() {
    return red;
}

int Color::getGreen() {
    return green;
}

int Color::getBlue() {
    return blue;
}