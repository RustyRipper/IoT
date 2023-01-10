#!/usr/bin/env python3
# pylint: disable=no-member

from config import *  # pylint: disable=unused-wildcard-import
import RPi.GPIO as GPIO
import time
import RPi.GPIO as GPIO
from config import * # pylint: disable=unused-wildcard-import
from mfrc522 import MFRC522
import neopixel
import board
from datetime import datetime

class Ex2:

    def __init__(self) -> None:
        self.pixels = neopixel.NeoPixel(board.D18, self.amount_of_diods, brightness=1.0 / 32, auto_write=False)
        self.MIFAREReader = MFRC522()
        self.is_read = False

    
    def led(self):
        self.pixels.fill((0, 255, 0))
        time.sleep(3)
        self.pixels.fill((0, 0, 0))


    def buzzer(self):     
        GPIO.output(buzzerPin, False)
        time.sleep(1)
        GPIO.output(buzzerPin, False)  # pylint: disable=no-member

        
    def rfidRead(self):
        (status, TagType) = self.MIFAREReader.MFRC522_Request(self.MIFAREReader.PICC_REQIDL)
        if status == self.MIFAREReader.MI_OK:
            (status, uid) = self.MIFAREReader.MFRC522_Anticoll()
            if status == self.MIFAREReader.MI_OK:
                num = 0
                for i in range(0, len(uid)):
                    num += uid[i] << (i*8)
                print(f"Card read UID: {uid} > {num}")

                if(not self.is_read):
                    now = datetime.now()
                    current_time = now.strftime("%H:%M:%S")
                    print("Current Time =", current_time)
                    self.buzzer()
                    self.led()
                    self.is_read = False
                else:
                    self.is_read = False
        else:
            self.is_read = False

ex2: Ex2 = Ex2()

if __name__ == "__main__":
    while True:
        ex2.rfidRead()