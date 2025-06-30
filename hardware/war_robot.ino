import RPi.GPIO as GPIO
import time
import serial

# Motor Pins (BCM pin numbering)
motor1Pin1 = 3
motor1Pin2 = 4
motor2Pin1 = 5
motor2Pin2 = 6

# Setup GPIO mode
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

# Setup motor pins
motor_pins = [motor1Pin1, motor1Pin2, motor2Pin1, motor2Pin2]
for pin in motor_pins:
    GPIO.setup(pin, GPIO.OUT)

# Setup serial communication
# Replace '/dev/rfcomm0' with your Bluetooth/USB serial port
ser = serial.Serial('/dev/rfcomm0', 9600)

def move_forward():
    GPIO.output(motor1Pin1, GPIO.HIGH)
    GPIO.output(motor1Pin2, GPIO.LOW)
    GPIO.output(motor2Pin1, GPIO.HIGH)
    GPIO.output(motor2Pin2, GPIO.LOW)

def move_backward():
    GPIO.output(motor1Pin1, GPIO.LOW)
    GPIO.output(motor1Pin2, GPIO.HIGH)
    GPIO.output(motor2Pin1, GPIO.LOW)
    GPIO.output(motor2Pin2, GPIO.HIGH)

def turn_left():
    GPIO.output(motor1Pin1, GPIO.LOW)
    GPIO.output(motor1Pin2, GPIO.HIGH)
    GPIO.output(motor2Pin1, GPIO.HIGH)
    GPIO.output(motor2Pin2, GPIO.LOW)

def turn_right():
    GPIO.output(motor1Pin1, GPIO.HIGH)
    GPIO.output(motor1Pin2, GPIO.LOW)
    GPIO.output(motor2Pin1, GPIO.LOW)
    GPIO.output(motor2Pin2, GPIO.HIGH)

def stop():
    for pin in motor_pins:
        GPIO.output(pin, GPIO.LOW)

# Main loop
try:
    while True:
        if ser.in_waiting > 0:
            command = ser.read().decode('utf-8').strip().upper()

            if command == 'F':
                move_forward()
            elif command == 'B':
                move_backward()
            elif command == 'L':
                turn_left()
            elif command == 'R':
                turn_right()
            elif command == 'S':
                stop()

except KeyboardInterrupt:
    GPIO.cleanup()
    ser.close()
