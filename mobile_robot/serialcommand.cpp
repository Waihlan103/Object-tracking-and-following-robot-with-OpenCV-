#include "serialcommand.h"
serialcommand syscommand(0);
serialcommand::serialcommand(int speed) : motorcontrol(speed)
{
}
void serialcommand::init(uint8_t *pin)
{
    motorcontrol::init(pin);
}
uint8_t serialcommand::receive_data()
{
    uint8_t distance = 0;
    while (Serial.available() == 0);
    // {
    //     distance = sensor.getDistance();
    //     if (distance != 0){
    //         Serial.println(distance);
    //     }
    //     if (distance > 0 && distance < 20 ){
    //         setspeed(100);
    //         backward();
    //     }
    //     else{
    //         setspeed(0);
    //         stop();
    //     }
        
    // }
    _serial_read = Serial.read();
    return _serial_read;
}
void serialcommand::operation()
{
    while (Serial.available() == 0);
    switch (_serial_read)
    {
    case 'F':
        moveforward(Serial.read());
        break;
    case 'B':
        movebackward(Serial.read());
        break;
    case 'L':
        moveleft(Serial.read());
        break;
    case 'R':
        moveright(Serial.read());
        break;
    case 'S':
        Serial.read();
        stop();
        break;
    case 'U':
        Serial.read();
        Serial.write(sensor.getDistance());
    default:
        Serial.read();
        break;
    }
    return;
}
void serialcommand::moveforward(int speed)
{
    setspeed(speed);
    forward();
    // delay(distance);
}
void serialcommand::movebackward(int speed)
{
    setspeed(speed);
    backward();
    // delay(distance);
}
void serialcommand::moveleft(int speed)
{
    setspeed(speed);
    turnleft();
    // delay(distance);
}
void serialcommand::moveright(int speed)
{
    setspeed(speed);
    turnright();
    // delay(distance);
}
serialcommand::~serialcommand()
{
}