#include <BluetoothSerial.h>
 
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif
 
const char *pin = "4321"; 
String device_name = "GiantPPBot";
BluetoothSerial SerialBT;
 
void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name); 
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  SerialBT.setPin(pin);
  Serial.println("Using PIN");
}
 
void loop() {
  // if (Serial.available()) {
  //   SerialBT.write(Serial.read());
  // }
  delay(20);
  
  if (!SerialBT.available()) return;
  
  const int btbyte = SerialBT.read();
  if (btbyte == 0) return;

  // if (btbyte == 'q') {}

  Serial.write(btbyte);
}