#!/usr/bin/env python3

import time
import os
import board
import neopixel
import w1thermsensor
import busio
import adafruit_bme280.advanced as adafruit_bme280
from config import *    


class Sensors:
    def __init__(self) -> None:
        self.ds18b20_sensor = w1thermsensor.W1ThermSensor()
        self.i2c = busio.I2C(board.SCL, board.SDA)
        self.bme280 = adafruit_bme280.Adafruit_BME280_I2C(self.i2c, 0x76)
        self.bme280.sea_level_pressure = 1013.25
        self.bme280.standby_period = adafruit_bme280.STANDBY_TC_500
        self.bme280.iir_filter = adafruit_bme280.IIR_FILTER_X16
        self.bme280.overscan_pressure = adafruit_bme280.OVERSCAN_X16
        self.bme280.overscan_humidity = adafruit_bme280.OVERSCAN_X1
        self.bme280.overscan_temperature = adafruit_bme280.OVERSCAN_X2

class Diods:

    def __init__(self) -> None:
        self.amount_of_diods = 8
        self.pixels = neopixel.NeoPixel(board.D18, self.amount_of_diods, brightness=1.0 / 32, auto_write=False)
        
    def display_value(self, min_value, max_value, value):
        d = (max_value-min_value)/(self.amount_of_diods-1)
        number_of_diod = int ((value-min_value)/d)
        for diod in range(8):
            if diod <= number_of_diod:
                self.pixels[diod] = (255, 0, 0)
            else:
                self.pixels[diod] = (0, 0, 0)
        self.pixels.show()

    def display_menu(self, selected_nr):
        self.pixels.fill((0, 0, 0))
        self.pixels[selected_nr] = (0, 255, 0)
        self.pixels.show()


class DisplayController:
    
    def __init__(self) -> None:
        self.display_flag = False
        self.selected_mode = 0
        self.sensors: Sensors = Sensors()
        self.modes = [
            Sensor('tempDS',20,30, self.sensors),
            Sensor('tempBME', 20,30,self.sensors),
            Sensor('humidity',0,100,self.sensors),
            Sensor('pressure',950,1050,self.sensors),
            Sensor('altitude',50,200,self.sensors)
        ]
        self.diods: Diods = Diods()

    class Sensor():
        def __init__(self, name, min_value, max_value, sensors: Sensors) -> None:
            self.name = name
            self.min_value = min_value
            self.max_value = max_value
            self.sensors = sensors

        def get_value(self):
            if self.name == 'tempDS':
                return self.sensors.ds18b20.get_temperature()
            elif self.name == 'tempBME':
                return self.sensors.bme280.temperature
            elif self.name == 'humidity':
                return self.sensors.bme280.humidity
            elif self.name == 'pressure':
                return self.sensors.bme280.pressure
            elif self.name == 'altitude':
                return self.sensors.bme280.altitude                      

    def display_current_parameter(self):
        self.diods.display_value(
            self.modes[self.selected_mode].min_value,
            self.modes[self.selected_mode].max_value,
            self.modes[self.selected_mode].get_value()
            )
        
    def display_menu(self):
        self.diods.display_menu(self.selected_mode)

    def red_button_callback(self):
        self.display_flag  = not self.display_flag

    def encoder_left_callback(self):
        if GPIO.input(encoderRight) == 0:
            self.selected_mode = (self.selected_mode + 1) % len(self.modes)

    def encoder_right_callback(self):
        if GPIO.input(encoderLeft) == 0:
            self.selected_mode = (self.selected_mode + len(self.modes) - 1) % len(self.modes)

    def start_detect(self):
        GPIO.add_event_detect(encoderLeft, GPIO.FALLING, callback=self.encoder_left_callback, bouncetime=50)
        GPIO.add_event_detect(encoderRight, GPIO.FALLING, callback=self.encoder_right_callback, bouncetime=50)
        GPIO.add_event_detect(buttonRed, GPIO.FALLING, callback=self.red_button_callback, bouncetime=50) 

 

if __name__ == "__main__":
    display_controller: DisplayController = DisplayController()
    display_controller.start_detect()
    while True:
        if display_controller.display_flag:
            display_controller.display_current_parameter()
        else:
            display_controller.display_menu()