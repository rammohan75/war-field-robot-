import serial
import time

# Replace with your correct COM port (e.g., 'COM5' on Windows or '/dev/ttyUSB0' on Linux)
bluetooth_port = 'COM5'
baud_rate = 9600

try:
    bluetooth = serial.Serial(bluetooth_port, baud_rate)
    print(f"Connected to {bluetooth_port} at {baud_rate} baud.")

    while True:
        command = input("Enter command (f=forward, b=back, l=left, r=right, s=stop, q=quit): ").lower()
        if command == 'q':
            print("Exiting...")
            break
        elif command in ['f', 'b', 'l', 'r', 's']:
            bluetooth.write(command.encode())
            print(f"Sent: {command}")
        else:
            print("Invalid command.")

except serial.SerialException:
    print("Could not open port. Check COM port and wiring.")

except KeyboardInterrupt:
    print("Program interrupted.")

finally:
    if 'bluetooth' in locals():
        bluetooth.close()
        print("Serial port closed.")
