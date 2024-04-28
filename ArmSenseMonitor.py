import serial
import keyboard
import numpy as np

def receive_serial_data(port, baudrate):
    ser = serial.Serial(port, baudrate)
    print(f"Listening on {port} at {baudrate} baud rate...")

    while True:
        data = ser.readline().decode().strip()
        data = data[:-1]
        data = data.split(",")
        print(data)

bluetooth_port = "/dev/cu.ArmSense"
wired_port = "/dev/cu.usbserial-0001"
baud_rate = 115200

receive_serial_data(wired_port, baud_rate)