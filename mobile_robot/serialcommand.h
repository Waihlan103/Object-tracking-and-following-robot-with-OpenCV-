#ifndef _SERIALCOMMAND_H
#define _SERIALCOMMAND_H
#include "motorcontrol.h"
#include "ultrasonic.h"
class serialcommand : public motorcontrol
{
private:
    char _serial_read = '\n';

public:
    serialcommand(int speed);
    void init(uint8_t *pin);
    uint8_t receive_data();
    void operation();
    void moveforward(int speed);
    void movebackward(int speed);
    void moveleft(int speed);
    void moveright(int speed);
    ~serialcommand();
};
extern serialcommand syscommand;
#endif