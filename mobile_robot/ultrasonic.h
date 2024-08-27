#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H
#include <Arduino.h>
class ultrasonic
{
private:
    uint8_t _trigPin = 0;
    uint8_t _echoPin = 0;
    uint8_t _distance = 0;
public:
    ultrasonic();
    void init(uint8_t trigPin, uint8_t echoPin);
    uint8_t getDistance();
    ~ultrasonic();
};

extern ultrasonic sensor;

#endif