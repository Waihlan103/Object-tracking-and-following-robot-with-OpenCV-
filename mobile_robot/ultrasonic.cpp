#include "ultrasonic.h"
ultrasonic sensor;
ultrasonic::ultrasonic(/* args */)
{
}
void ultrasonic::init(uint8_t trigPin, uint8_t echoPin)
{
    _trigPin = trigPin;
    _echoPin = echoPin;
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
    Serial.begin(115200);
    return;
}
uint8_t ultrasonic::getDistance()
{
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);

    // Set the trigPin HIGH for 10 microseconds
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    // Read the echoPin, pulseIn() returns the duration (microseconds) of the pulse
    long duration = pulseIn(_echoPin, HIGH);

    // Calculate the distance in centimeters
    _distance = duration * 0.034 / 2;

    // Print the distance to the Serial Monitor
    // Serial.print("Distance: ");
    // Serial.print(distance);
    // Serial.println(" cm");

    return _distance;
}
ultrasonic::~ultrasonic()
{
}