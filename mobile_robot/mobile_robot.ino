#include <Arduino.h>
#include "ultrasonic.h"
#include "serialcommand.h"


byte x = 200;
uint8_t motorpin[4] = {11, 10, 9, 6};
void setup()
{
  sensor.init(16, 17);
  syscommand.init(motorpin);
  Serial.begin(9600);
}
void loop()
{
  syscommand.receive_data();
  syscommand.operation();
}
