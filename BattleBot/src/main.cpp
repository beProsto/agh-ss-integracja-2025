#include <BluetoothSerial.h>

#include "./servomotor.h"
#include "./motor.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
  #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#if !defined(CONFIG_BT_SPP_ENABLED)
  #error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif
 
const char *pin = "4321"; 
String device_name = "GiantPPBot";
BluetoothSerial SerialBT;

#define HBRIDGE_BACKWARD_PIN 34
#define HBRIDGE_FORWARD_PIN 35

HBridge h_bridge{};

void setup() {
  new(&h_bridge) HBridge(HBRIDGE_BACKWARD_PIN, HBRIDGE_FORWARD_PIN);
  Serial.begin(115200);
  SerialBT.begin(device_name); 
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  SerialBT.setPin(pin);
  Serial.println("Using PIN");
}
 
void loop() {
  delay(20);
  
  if(!SerialBT.available())
    return;
  
  const int btbyte = SerialBT.read();
  if (btbyte == 0) return;
  
  switch(btbyte){
    case 'q': 
      h_bridge.run(true, -1);
      break;
    case 'w': 
      h_bridge.run(false, -1);
      break;
    case 'a':
    case 's':
      h_bridge.stop();
      break;
  }    

  Serial.println("BT input: " + String(btbyte));
}
