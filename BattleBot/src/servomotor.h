#pragma once
#include <Arduino.h>
#include <Servo.h>

class ServoMotor
{
    Servo servo;
    public:
        ServoMotor(int servoPin);
        ~ServoMotor();

        void setDegrees(int degrees);
};

ServoMotor::ServoMotor(int servoPin)
{
    pinMode(servoPin, OUTPUT);
    servo.attach(servoPin);
}

ServoMotor::~ServoMotor()
{
}

void ServoMotor::setDegrees(int degrees) 
{
    servo.write(degrees);
}
