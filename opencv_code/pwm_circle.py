import serial
import time
import sys
import select

# Configure the serial port
serial_port = '/dev/ttyACM0'  # Change this to your actual serial port
baud_rate = 9600

try:
    ser = serial.Serial(serial_port, baud_rate, timeout=1)
    time.sleep(2)  # Allow some time for the serial connection to initialize
except serial.SerialException as e:
    print(f"Failed to open serial port: {e}")
    exit(1)

def send_command(command, pwm=None):
    """Send command and PWM value as character over serial."""
    if pwm is not None:
        pwm_char = chr(pwm)  # Convert PWM value to ASCII character
        command_str = f"{command}{pwm_char}".encode()  # Create command string
    else:
        command_str = f"{command}".encode()  # Create command string for stop
    try:
        ser.write(command_str)
        print(f"Command Sent: {command_str}")
    except serial.SerialException as e:
        print(f"Failed to send command: {e}")

def forward(pwm):
    """Send forward command with PWM value."""
    send_command('F', pwm)

def stop():
    """Send stop command."""
    send_command('SS')  # Send stop command without PWM value

def check_for_exit():
    """Check if user input is available and handle it."""
    if select.select([sys.stdin], [], [], 0.0)[0]:
        user_input = sys.stdin.readline().strip().lower()
        if user_input == 'q':
            return True
    return False

def pwm_cycle():
    """Gradually increase PWM value from 0 to 255 and print it."""
    try:
        for pwm in range(0, 256):
            if check_for_exit():  # Check if 'q' is pressed
                print("Stopping...")
                stop()  # Send stop command before exiting
                break
            forward(pwm)  # Send PWM value for forward direction
            print(f"Current PWM: {pwm}")
            time.sleep(0.5)  # Delay between PWM steps
    except KeyboardInterrupt:
        print("Program interrupted by user.")
        stop()  # Ensure stop command is sent if interrupted

def main():
    print("Starting PWM cycle. Enter 'q' to stop.")
    pwm_cycle()
    ser.close()  # Close the serial connection when done

if __name__ == "__main__":
    main()
