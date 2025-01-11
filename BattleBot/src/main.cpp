#include <WiFi.h>
#include <WebSocketsServer.h>

// Static IP configuration
IPAddress local_IP(192, 168, 1, 1);  // Set your desired static IP address
IPAddress gateway(192, 168, 1, 254); // Set gateway IP
IPAddress subnet(255, 255, 255, 0);  // Set subnet mask

// WebSocket server on port 81
WebSocketsServer webSocket = WebSocketsServer(81);

// PWM
const int MOTOR_PIN_A = 12; // Motor 1 on pin 12
const int MOTOR_PIN_B = 13; // Motor 2 on pin 13

const int PWM_CHANNEL_A = 0;    
const int PWM_CHANNEL_B = 1;    
const int PWM_FREQ = 500;     
const int PWM_RESOLUTION = 8;
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 
const int HALF_DUTY_CYCLE = MAX_DUTY_CYCLE / 2;


void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);

void setup()
{
    ledcSetup(PWM_CHANNEL_A, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(PWM_CHANNEL_B, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(MOTOR_PIN_A, PWM_CHANNEL_A);
    ledcAttachPin(MOTOR_PIN_B, PWM_CHANNEL_B);


  Serial.begin(115200);
  WiFi.softAPConfig(local_IP, gateway, subnet);

  // Set SSID and password (Make sure password is at least 8 characters)
  const char *ssid = "ESP32_SoftAP"; // CHANGE ME!
  const char *password = "yourpassword"; // Ensure this password is at least 8 characters

  if (WiFi.softAP(ssid, password))
  {
    Serial.println("SoftAP Started");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP()); // Print SoftAP IP
  }
  else
  {
    Serial.println("Failed to start SoftAP");
  }

  // Start WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent); // Define the WebSocket event handler

  // Wait for a connection
  Serial.println("Waiting for WebSocket connections...");
}

void loop()
{
  // Handle WebSocket events
  webSocket.loop();
}

// WebSocket URL: ws://192.168.1.1:81
//  WebSocket event handler
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
  String receivedString;

  switch (type)
  {
  case WStype_DISCONNECTED:
    Serial.printf("Client %u disconnected!\n", num);
    break;
  case WStype_CONNECTED:
  {
    IPAddress ip = webSocket.remoteIP(num);
    Serial.printf("Client %u connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
  }
  break;
  case WStype_TEXT:
    Serial.printf("Received: %s\n", payload);

    receivedString = String((char *)payload);

    if (receivedString == "left") {
      Serial.println("Handling LEFT");
      ledcWrite(PWM_CHANNEL_A, 0);
      ledcWrite(PWM_CHANNEL_B, MAX_DUTY_CYCLE);
    } else if (receivedString == "right") {
      Serial.println("Handling RIGHT");
      ledcWrite(PWM_CHANNEL_A, MAX_DUTY_CYCLE);
      ledcWrite(PWM_CHANNEL_B, 0);
    } else if (receivedString == "back") {
      Serial.println("Handling BACK");
      ledcWrite(PWM_CHANNEL_A, 0);
      ledcWrite(PWM_CHANNEL_B, 0);
    } else {
      Serial.println("Unknown command received.");
    }

    webSocket.sendTXT(num, payload, length);
    break;
  default:
    break;
  }
}
