#ifndef MYRGB_H_
#define MYRGB_H_

#include "Arduino.h"

class MyRGB {
    public:
        myRGB(int pinRed, int pinGreen, int pinBlue);

        void init();
        void writeRgb(int redValue, int greenValue, int blueValue);
        void writeColor(String colorName);

    private:
        void setRGB();
        int redPin;
        int greenPin;
        int bluePin;
};

class Color {
    public:
        Color(String colorName);
        Color(int redValue, int greenValue, int blueValue);

        int getRed();
        int getGreen();
        int getBlue();

    private:
        void setRGB();

        int red;
        int green;
        int blue;

        int RED[3] = {255, 0, 0};
        int GREEN[3] = {0, 255, 0};
        int BLUE[3] = {0, 0, 255};
        int YELLOW[3] = {255, 255, 0};
        int CYAN[3] = {0, 255, 255};
        int MAGENTA[3] = {255, 0, 255};
        int BLACK[3] = {0, 0, 0};
        int WHITE[3] = {255, 255, 255};
};

#endif
