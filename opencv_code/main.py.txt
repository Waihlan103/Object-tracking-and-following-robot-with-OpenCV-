import cv2 as cv
import numpy as np
import time
import serial

# Set up serial communication
arduino = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(2)  # Wait for the connection to establish

KNOWN_WIDTH = 5.4
FOCAL_LENGTH = 392

def centriod(roi):
    M = cv.moments(roi)
    if M["m00"] != 0:
        center_x = int(M["m10"] / M["m00"])
        center_y = int(M["m01"] / M["m00"])
        cv.circle(frame, (center_x, center_y), 5, (0, 0, 255), -1)
        return center_x, center_y

def forward():
    arduino.write(b'F9')
    cv.putText(frame, "Move Forward", (450, 40), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 3)
    
def backward():
    arduino.write(b'B9')
    cv.putText(frame, "Move Backward", (450, 40), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 3)

def left():
    arduino.write(b'Ld')
    cv.putText(frame, "Turn Left", (450, 40), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 3)
    
def right():
    arduino.write(b'Rd')
    cv.putText(frame, "Turn Right", (450, 40), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 3)
    
def stop():
    arduino.write(b'SS')
    cv.putText(frame, "Stop", (450, 40), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 3)

def calculate_distance(focal_length, known_width, pixel_width):
    dist = (known_width * focal_length) / pixel_width
    return dist

def detect_object(image):
    color_lower = np.array([51, 175, 62])  # example: lower bound for green color
    color_upper = np.array([78, 255, 202])  # example: upper bound for green color
    
    hsv = cv.cvtColor(image, cv.COLOR_BGR2HSV) #convert BGR to HSV
    blurred = cv.GaussianBlur(hsv, (5, 5), 0) #GaussianBLur
    mask = cv.inRange(blurred, color_lower, color_upper) #Mask the image
    contours, _ = cv.findContours(mask, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE) #drawContours
    
    if contours:
        c = max(contours, key = cv.contourArea) #maximum area
        
        epsilon = 0.03 * cv.arcLength(c, True) #find epsilon
        approx = cv.approxPolyDP(c, epsilon, True) #approx PolyDP Method          
        return approx
    
cap = cv.VideoCapture(0)
time.sleep(2)

while(cap.isOpened()):
    ret, frame = cap.read()
    if not ret or frame is None:
        print("No frame captured, stopping robot...")
        stop()
        #cap.release()
        #cv.destoryAllWindows()
        break
    
    approx_value = detect_object(frame)
    if approx_value is None:
        print("No frame captured, stopping robot...")
        stop()
        cap.release()
        cv.destoryAllWindows()
        break
    
    else:
        if len(approx_value) > 8:
            shape = "circle"
            cx, cy = centriod(approx_value)
            cv.putText(frame, shape, (cx, cy), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 3)
            stop()
                
        elif len(approx_value) == 4:
            shape = "Rectangle"
            cx, cy = centriod(approx_value)
            print(f"Point of X-coordinate is {cx} and Point of Y-coordinate is {cy}")
            cv.putText(frame, shape, (cx, cy), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 3)
            x, y, w, h = cv.boundingRect(approx_value)
            cv.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 3)
        
            distance = calculate_distance(FOCAL_LENGTH, KNOWN_WIDTH, w)
            
            cv.putText(frame, f"Distance: {distance:.2f} cm", (10, 30), cv.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)
            # Get image dimensions
            height, width = frame.shape[:2]

            # Define the ROI boundaries (1/3 to 2/3 of the frame)
            x_start = width // 3
            x_end = 2 * width // 3
                
            # Crop the ROI
            center_roi = frame[:,x_start:x_end]
            if cx < frame.shape[1] // 3:
                left()
                if x_start <= cx < x_end:
                    stop()
                    #time.sleep(0.5)

            elif cx > 2 * frame.shape[1] // 3:
                right()
                if x_start <= cx < x_end:
                    stop()
                    #time.sleep(0.5)
                
            else:
                if distance > 25:
                    forward()
                elif distance <= 25 and distance > 20:
                    stop()
                else:
                    backward()
                
            cv.imshow("frame", frame)
            if cv.waitKey(1) & 0xFF == ord('q'):
                break

arduino.close()
cap.release()
cv.destroyAllWindows()


