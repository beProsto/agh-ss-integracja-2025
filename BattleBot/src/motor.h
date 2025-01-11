#include <arduino/Arduino.h>

class HBridge
{
  byte forward_pin;
  byte backward_pin; 
  public:
    HBridge(uint8_t driverPin1, uint8_t driverPin2);
    void run(bool, byte) const;
    void stop(byte brake) const;
    
};


HBridge::HBridge(byte _backward_pin, byte _forward_pin)
:backward_pin(_backward_pin), forward_pin(_forward_pin)
{
  pinMode(forward_pin, OUTPUT);
  pinMode(_forward_pin, OUTPUT);
  analogWrite(forward_pin, 0);
  analogWrite(_forward_pin, 0);
}

void HBridge::run(bool direction, byte speed) const
{
  if (direction) {
    analogWrite(backward_pin, 0);
    analogWrite(forward_pin, speed);
  } else {
    analogWrite(forward_pin, 0);
    analogWrite(backward_pin, speed);
  }
}

void HBridge::stop(byte brake=0) const
{
  this->run(0,0);
}
