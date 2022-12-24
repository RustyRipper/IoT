#!/usr/bin/env python3

import os
import board
import neopixel
import w1thermsensor
import busio
import adafruit_bme280.advanced as adafruit_bme280
import lib.oled.SSD1331 as SSD1331
import time
from config import *  
from PIL import Image, ImageDraw, ImageFont


class OledController:

    def __init__(self) -> None:
        self.i2c = busio.I2C(board.SCL, board.SDA)
        self.bme280 = adafruit_bme280.Adafruit_BME280_I2C(self.i2c, 0x76)
        self.bme280.sea_level_pressure = 1013.25
        self.bme280.standby_period = adafruit_bme280.STANDBY_TC_500
        self.bme280.iir_filter = adafruit_bme280.IIR_FILTER_X16
        self.bme280.overscan_pressure = adafruit_bme280.OVERSCAN_X16
        self.bme280.overscan_humidity = adafruit_bme280.OVERSCAN_X1
        self.bme280.overscan_temperature = adafruit_bme280.OVERSCAN_X2
        self.temp = self.bme280.temperature
        self.hum = self.bme280.humidity
        self.alti = self.bme280.altitude
        self.press = self.bme280.pressure
        self.fontSmall = ImageFont.truetype('./lib/oled/Font.ttf', 13)
        self.disp = SSD1331.SSD1331()
        self.disp.Init()
        self.up = Image.open('./lib/oled/up.png')
        self.down = Image.open('./lib/oled/down.png')
    

    def update_values(self):
        self.temp = self.bme280.temperature
        self.hum = self.bme280.humidity
        self.alti = self.bme280.altitude
        self.press = self.bme280.pressure


    def update_oled(self):
        self.disp.clear()
        image1 = Image.new("RGB", (self.disp.width, self.disp.height), "WHITE")
        draw = ImageDraw.Draw(image1)
        print("- draw text")
        draw.text((12, 40), 'Temp: '+self.temp, font=self.fontSmall, fill="BLUE")
        draw.text((12, 40), 'Humi: '+self.hum, font=self.fontSmall, fill="BLUE")
        draw.text((12, 40), 'Alti: '+self.alti, font=self.fontSmall, fill="BLUE")
        draw.text((12, 40), 'Pres: '+self.press, font=self.fontSmall, fill="BLUE")

        if(self.temp > 25):
            self.disp.ShowImage(self.up, 0, 0)
        else:
            self.disp.ShowImage(self.down, 0, 0)

        if(self.hum > 50):
            self.disp.ShowImage(self.up, 0, 0)
        else:
            self.disp.ShowImage(self.down, 0, 0)  

        if(self.alti > 150):
            self.disp.ShowImage(self.up, 0, 0)
        else:
            self.disp.ShowImage(self.down, 0, 0)  

        if(self.press > 1000):
            self.disp.ShowImage(self.up, 0, 0)
        else:
            self.disp.ShowImage(self.down, 0, 0)
        
        time.sleep(2)                  


oled_controller : OledController = OledController()


if __name__ == "__main__":
    while True:
        oled_controller.update_values()
        oled_controller.update_oled()
