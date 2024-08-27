#ifndef _MOTORCONTROL_H
#define _MOTORCONTROL_H
#include "notation.h"
#include <Arduino.h>

class motorcontrol
{
private:
    uint8_t _pin[4]= {0, 0, 0, 0};
    int _motorspeed = 0;

public:
    motorcontrol(int motorspeed);
    void init(uint8_t *pin);
    void setspeed(int motorspeed);
    void forward();
    void backward();
    void turnleft();
    void turnright();
    void stop();
    ~motorcontrol();
};
extern motorcontrol sys;
#endif