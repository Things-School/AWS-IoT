#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "secrets.h"

WiFiClientSecure wifi = WiFiClientSecure();
PubSubClient AWSIoTCore(wifi);

void setup() {
  Serial.begin(9600);
  connectWiFi();
  connectAWS();
  AWSIoTCore.publish("esp32pub","Hello from ESP32!");
}

void loop() {
  AWSIoTCore.loop();
}

void connectWiFi()
{
  // Set WiFi to station/client mode and connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFi_SSID, WiFi_Password);

  // Display the status of WiFi connection
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to ");
  Serial.println(WiFi_SSID);

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  wifi.setCACert(Amazon_Root_CA);
  wifi.setCertificate(Device_Cert);
  wifi.setPrivateKey(Device_PrivateKey);
}

void connectAWS()
{
  // Connect to the AWSIoTCore broker on the AWS endpoint we defined earlier
  AWSIoTCore.setServer(AWS_IoT_Endpoint, AWS_IoT_Endpoint_Port);

  // Create a message handler
  AWSIoTCore.setCallback(messageHandler);
  
  
  Serial.print("Connecting to AWS IoT Core");
  while (!AWSIoTCore.connect(ThingName)) {
    Serial.print(".");
    delay(500);
  }

  if(!AWSIoTCore.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }

  Serial.println("Connected to AWS IoT Core!");

  //AWSIoTCore.subscribe("esp32sub");
}

void messageHandler(char* topic, byte* payload, unsigned int length) {
  /*
  Serial.println("Message Received!");
  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  //payload[length] = '\0';
  Serial.println((char *)payload);
  */
}
