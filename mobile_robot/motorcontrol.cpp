#include "motorcontrol.h"

motorcontrol::motorcontrol(int motorspeed) : _motorspeed(motorspeed)
{
    setspeed(_motorspeed);
    stop();
}
void motorcontrol::init(uint8_t *pin)
{
    for (size_t i = 0; i < 4; i++)
    {
        _pin[i] = pin[i];
        pinMode(_pin[i], OUTPUT);
        digitalWrite(_pin[i], LOW);
    }

    return;
}
void motorcontrol::forward()
{
    stop();
    analogWrite(_pin[0], _motorspeed);
    analogWrite(_pin[2], _motorspeed);
    return;
}
void motorcontrol::backward()
{
    stop();
    analogWrite(_pin[1], _motorspeed);
    analogWrite(_pin[3], _motorspeed);
    return;
}
void motorcontrol::turnright()
{
    stop();
    analogWrite(_pin[0], _motorspeed);
    analogWrite(_pin[3], _motorspeed);
    return;
}
void motorcontrol::turnleft()
{
    stop();
    analogWrite(_pin[2], _motorspeed);
    analogWrite(_pin[1], _motorspeed);
    return;
}
void motorcontrol::stop()
{
    for (size_t i = 0; i < 4; i++)
    {
        analogWrite(_pin[i], 0);
        digitalWrite(_pin[i], LOW);
    }
    return;
}
void motorcontrol::motorcontrol::setspeed(int motorspeed)
{
    _motorspeed = motorspeed;
    return;
}
motorcontrol::~motorcontrol()
{
}