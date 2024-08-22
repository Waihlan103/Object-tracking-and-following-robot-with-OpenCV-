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

def send_command(command, pwm_char):
    """Send command and PWM value as character over serial."""
    pwm = ord(pwm_char)  # Convert PWM character to its ASCII value
    command_str = f"{command}{pwm_char}".encode()  # Create command string
    try:
        ser.write(command_str)
        print(f"Command Sent: {command_str}")
    except serial.SerialException as e:
        print(f"Failed to send command: {e}")

def forward(pwm_char='A'):
    send_command('F', pwm_char)

def backward(pwm_char='A'):
    send_command('B', pwm_char)

def left(pwm_char='A'):
    send_command('L', pwm_char)

def right(pwm_char='A'):
    send_command('R', pwm_char)

def stop():
    send_command('S', 'A')  # Default PWM character for stop is 'A'

def parse_input(user_input):
    """Parse the user input to extract command and PWM character."""
    if not user_input:
        return None, None
    
    command = user_input[0].upper()
    
    if command not in ['F', 'B', 'L', 'R', 'S']:
        return None, None

    if len(user_input) > 1:
        pwm_char = user_input[1].upper()
        if pwm_char < 'A' or pwm_char > 'Z':
            return None, None
    else:
        pwm_char = 'A' if command == 'S' else 'A'  # Default PWM character for stop is 'A'
    
    return command, pwm_char

def main():
    while True:
        user_input = input("Enter your choice (e.g., FZ, BQ, LM, RY, S): ").strip()
        command, pwm_char = parse_input(user_input)

        if command is None:
            print("Invalid input. Please enter commands in the format FZ, BQ, LM, RY, or S.")
            continue

        if command == 'F':
            forward(pwm_char)
        elif command == 'B':
            backward(pwm_char)
        elif command == 'L':
            left(pwm_char)
        elif command == 'R':
            right(pwm_char)
        elif command == 'S':
            stop()

if __name__ == "__main__":
    main()
