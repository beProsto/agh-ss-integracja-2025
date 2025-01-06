#include <WiFi.h>
#include <WebSocketsServer.h>

// Static IP configuration
IPAddress local_IP(192, 168, 1, 1);  // Set your desired static IP address
IPAddress gateway(192, 168, 1, 254); // Set gateway IP
IPAddress subnet(255, 255, 255, 0);  // Set subnet mask

// WebSocket server on port 81
WebSocketsServer webSocket = WebSocketsServer(81);

// Forward declaration of the webSocketEvent function
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);

void setup()
{
  // Start the serial communication
  Serial.begin(115200);

  // Set up SoftAP with static IP
  WiFi.softAPConfig(local_IP, gateway, subnet);

  // Set SSID and password (Make sure password is at least 8 characters)
  const char *ssid = "ESP32_SoftAP";
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
    // Respond to the client (example: send back the received message)
    webSocket.sendTXT(num, payload, length);
    break;
  default:
    break;
  }
}
