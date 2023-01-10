#!/usr/bin/env python3

import paho.mqtt.client as mqtt
import tkinter
import time
#from config import *  # pylint: disable=unused-wildcard-import
#import RPi.GPIO as GPIO
import time
#import RPi.GPIO as GPIO
#from mfrc522 import MFRC522
#import neopixel
#import board
from datetime import datetime

# The terminal ID - can be any string.
terminal_id = "T0"
# The broker name or IP address.
broker = "localhost"
#broker = "127.0.0.1"
#broker = "10.0.0.1"

 # The MQTT client.
client = mqtt.Client()

 # Thw main window with buttons to simulate the RFID card usage.
window = tkinter.Tk()

def call_worker(nr):
    now = datetime.now()
    current_time = now.strftime("%H:%M:%S")
    client.publish("worker/name", nr+ "." + current_time,)


def create_main_window():
    window.geometry("300x200")
    window.title("SENDER")


    intro_label = tkinter.Label(window, text="Select employee:")
    intro_label.grid(row=0, columnspan=5)

    button_1 = tkinter.Button(window, text="Employee 1",
    command=lambda: call_worker("Employee 1"))
    button_1.grid(row=1, column=0)
    button_2 = tkinter.Button(window, text="Employee 2",
    command=lambda: call_worker("Employee 2"))
    button_2.grid(row=2, column=0)
    button_3 = tkinter.Button(window, text="Employee 3",
    command=lambda: call_worker("Employee 3"))
    button_3.grid(row=3, column=0)
    button_4 = tkinter.Button(window, text="Employee 4",
    command=lambda: call_worker("Employee 4"))
    button_4.grid(row=1, column=1)
    button_5 = tkinter.Button(window, text="Employee 5",
    command=lambda: call_worker("Employee 5"))
    button_5.grid(row=2, column=1)
    button_6 = tkinter.Button(window, text="Employee 6",
    command=lambda: call_worker("Employee 6"))
    button_6.grid(row=3, column=1)
    button_stop = tkinter.Button(window, text="Stop", command=window.quit)
    button_stop.grid(row=4, columnspan=2)


def connect_to_broker():
# Connect to the broker.
    client.connect(broker)
# Send message about conenction.
    call_worker("Client connected")


def disconnect_from_broker():
# Send message about disconenction.
    call_worker("Client disconnected")
# Disconnet the client.
    client.disconnect()


def run_sender(ex2):
    connect_to_broker()
    #create_main_window()

    # Start to display window (It will stay here until window is displayed)
    #window.mainloop()
    #time.sleep(5)
    #call_worker("12345678")
    while True:
        ex2.rfidRead()
    disconnect_from_broker()

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
                    call_worker(uid)
                    self.is_read = True
                else:
                    self.is_read = False   
        else:
            self.is_read = False        


ex2: Ex2 = Ex2()

if __name__ == "__main__":
    run_sender(ex2)