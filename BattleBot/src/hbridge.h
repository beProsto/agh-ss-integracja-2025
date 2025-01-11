#pragma once
#include <Arduino.h>

class HBridge
{
  uint8_t forward_pin;
  uint8_t backward_pin; 
  public:
    HBridge(){}
    HBridge(uint8_t driverPin1, uint8_t driverPin2);
    void run(bool, uint8_t) const;
    void stop() const;
    void break_now() const;
    // void break() const;
};


HBridge::HBridge(uint8_t _backward_pin, uint8_t _forward_pin)
:backward_pin(_backward_pin), forward_pin(_forward_pin)
{
  pinMode(forward_pin, OUTPUT);
  pinMode(backward_pin, OUTPUT);
  analogWrite(forward_pin, 0);
  analogWrite(backward_pin, 0);
}

void HBridge::run(bool direction, uint8_t speed) const
{
  if (direction) {
    analogWrite(backward_pin, 0);
    analogWrite(forward_pin, speed);
  } else {
    analogWrite(forward_pin, 0);
    analogWrite(backward_pin, speed);
  }
}

void HBridge::stop() const
{
  this->run(0,0);
}

void HBridge::break_now() const{
  this->run(-1,-1);
}
