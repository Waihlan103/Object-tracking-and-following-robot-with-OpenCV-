import serial
import time

# Configure the serial port
serial_port = '/dev/ttyACM0'  # Change this to your actual serial port
baud_rate = 9600

try:
    ser = serial.Serial(serial_port, baud_rate, timeout=1)
    time.sleep(2)  # Allow some time for the serial connection to initialize
except serial.SerialException as e:
    print(f"Failed to open serial port: {e}")
    exit(1)

def send_command(command, pwm):
    # Ensure PWM value is within 0-255
    pwm = max(0, min(255, pwm))
    pwm_char = chr(pwm)  # Convert PWM value to ASCII character
    command_str = f"{command}{pwm_char}".encode()  # Create command string
    try:
        ser.write(command_str)
        print(f"Command Sent: {command_str}")
    except serial.SerialException as e:
        print(f"Failed to send command: {e}")

def forward(pwm=0):
    send_command('F', pwm)

def backward(pwm=0):
    send_command('B', pwm)

def left(pwm=0):
    send_command('L', pwm)

def right(pwm=0):
    send_command('R', pwm)

def stop():
    send_command('S', 0)

def main():
    while True:
        choice = input("Enter your choice (e.g., F9, B9, L9, R9, SS): ").strip().upper()

        if choice.startswith('F') and choice[1:].isdigit():
            forward(int(choice[1:]))
        elif choice.startswith('B') and choice[1:].isdigit():
            backward(int(choice[1:]))
        elif choice.startswith('L') and choice[1:].isdigit():
            left(int(choice[1:]))
        elif choice.startswith('R') and choice[1:].isdigit():
            right(int(choice[1:]))
        elif choice == 'SS':
            stop()
        else:
            print("Invalid choice. Please enter commands in the format F9, B9, L9, R9, or SS.")

if __name__ == "__main__":
    main()
