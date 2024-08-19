import cv2 as cv
import numpy as np

cap = cv.VideoCapture(0)

def nothing(x):
    pass

cv.namedWindow('Color Tracker')
cv.createTrackbar("lower hue", "Color Tracker", 0, 255, nothing)
cv.createTrackbar("lower saturation", "Color Tracker", 0, 255, nothing)
cv.createTrackbar("lower value", "Color Tracker", 0, 255, nothing)

cv.createTrackbar("upper hue", "Color Tracker", 0, 255, nothing)
cv.createTrackbar("upper saturation", "Color Tracker", 0, 255, nothing)
cv.createTrackbar("upper value", "Color Tracker", 0, 255, nothing)


while True:
    #frame = cv.imread('finger_point.jpg')
    _, frame = cap.read()
    hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)

    l_h = cv.getTrackbarPos("lower hue", "Color Tracker")
    l_s = cv.getTrackbarPos("lower saturation", "Color Tracker")
    l_v = cv.getTrackbarPos("lower value", "Color Tracker")

    u_h = cv.getTrackbarPos("upper hue", "Color Tracker")
    u_s = cv.getTrackbarPos("upper saturation", "Color Tracker")
    u_v = cv.getTrackbarPos("upper value", "Color Tracker")

    l_b = np.array([l_h, l_s, l_v])
    u_b = np.array([u_h, u_s, u_v])

    mask = cv.inRange(hsv, l_b, u_b)
    res = cv.bitwise_and(frame, frame, mask=mask)

    #cv.imshow("frame", frame)
    #cv.imshow("hsv", hsv)
    cv.imshow("mask", mask)
    cv.imshow("result", res)

    if cv.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv.destroyAllWindows()