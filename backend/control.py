import serial
import time

# Replace with the correct serial port name for your system
port = 'COM3'  # For Windows
# port = '/dev/ttyUSB0'  # For Linux

baud_rate = 9600
arduino = serial.Serial(port, baud_rate, timeout=1)
time.sleep(2)  # Wait for connection

def send_command(cmd):
    arduino.write(cmd.encode())
    print(f"Sent: {cmd}")

while True:
    cmd = input("Enter command (F/B/L/R/S for stop): ").strip().upper()
    if cmd in ['F', 'B', 'L', 'R', 'S']:
        send_command(cmd)
    else:
        print("Invalid command. Use F/B/L/R/S.")
