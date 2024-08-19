import cv2 as cv
import numpy as np
import time

# Known distance from the camera to the object (in cm)
KNOWN_DISTANCE = 20.0

# Known object width (in cm)
KNOWN_WIDTH = 5.4


# Capture a reference image of the object at the known distance
#ret, ref_image = cap.read()

def find_focal_length(known_distance, known_width, ref_pixel_width):
    focal_length = ref_pixel_width * known_distance / known_width
    return focal_length

def detect_object(image):
    color_lower = np.array([51, 175, 62])  # example: lower bound for blue color
    color_upper = np.array([78, 255, 202])  # example: upper bound for blue color
    hsv = cv.cvtColor(image, cv.COLOR_BGR2HSV)
    blurred = cv.GaussianBlur(hsv, (5, 5), 0)
    mask = cv.inRange(blurred, color_lower, color_upper)
    contours, _ = cv.findContours(mask, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
    if contours:
        c = max(contours, key=cv.contourArea)
        x, y, w, h = cv.boundingRect(c)
        cv.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 3)

        return w


cap = cv.VideoCapture(0)

capture_duration = 2
start_time = time.time()
while(int(time.time() - start_time) < capture_duration):
    _, ref_frame = cap.read()

ref_pixel_width = detect_object(ref_frame)

print("reference pixel width : ", ref_pixel_width)
focal_length = find_focal_length(KNOWN_DISTANCE, KNOWN_WIDTH, ref_pixel_width)

print("focal_length : ", focal_length)

