import cv2 as cv
import numpy as np

def centriod(roi):
    M = cv.moments(roi)
    if M["m00"] != 0:
        center_x = int(M["m10"] / M["m00"])
        center_y = int(M["m01"] / M["m00"])
        cv.circle(frame, (center_x, center_y), 5, (0, 0, 255), -1)
        return center_x, center_y

cap = cv.VideoCapture(0)

while True:
    _, frame = cap.read()
    color_lower = np.array([51, 175, 62])  # example: lower bound for blue color
    color_upper = np.array([78, 255, 202])  # example: upper bound for blue color
    hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
    blurred = cv.GaussianBlur(hsv, (5, 5), 0)
    mask = cv.inRange(blurred, color_lower, color_upper)
    contours, _ = cv.findContours(mask, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
    
    if contours:
        c = max(contours, key = cv.contourArea)
        
        epsilon = 0.03 * cv.arcLength(c, True)
        approx = cv.approxPolyDP(c, epsilon, True)
                                
        if len(approx) == 3:
            print("It is triangle")
        elif len(approx) == 4:
            shape = "Rectangle"
            cx, cy = centriod(approx)
            cv.putText(frame, shape, (cx, cy), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 3)
            x, y, w, h = cv.boundingRect(approx)
            cv.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 3)

        else:
            shape = "circle"
            cx, cy = centriod(approx)
            cv.putText(frame, shape, (cx, cy), cv.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 3)
                
    cv.imshow("Frame", frame)
    
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
    
cap.release()
cv.destoryAllWindows()
    