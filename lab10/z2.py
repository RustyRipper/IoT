#!/usr/bin/env python3
# pylint: disable=no-member

import time
import RPi.GPIO as GPIO
from config import * # pylint: disable=unused-wildcard-import
from mfrc522 import MFRC522
import neopixel
import board

class Ex2:

    def __init__(self) -> None:
        self.pixels = neopixel.NeoPixel(board.D18, self.amount_of_diods, brightness=1.0 / 32, auto_write=False)
        self.MIFAREReader = MFRC522()

    
    def led(self):
        self.pixels.fill((0, 255, 0))
        time.sleep(3)
        self.pixels.fill((0, 0, 0))


    def buzzer(self):
        pass

    def rfidRead(self):
        
        (status, TagType) = self.MIFAREReader.MFRC522_Request(self.MIFAREReader.PICC_REQIDL)
        if status == self.MIFAREReader.MI_OK:
            (status, uid) = self.MIFAREReader.MFRC522_Anticoll()
            if status == self.MIFAREReader.MI_OK:
                num = 0
                for i in range(0, len(uid)):
                    num += uid[i] << (i*8)
                print(f"Card read UID: {uid} > {num}")
                self.buzzer()
                self.led()
                time.sleep(0.5)


ex2: Ex2 = Ex2()

if __name__ == "__main__":
    while True:
        ex2.rfidRead()