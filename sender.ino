 
#include <esp_now.h>
#include <WiFi.h>

// Replace with your slave MAC Address
uint8_t broadcastAddress[] = {0x84, 0x0D, 0x8E, 0x82, 0xF3, 0xEC};

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  String data = "Hello Karan from ESP32";
  const uint8_t* dataToSend = (const uint8_t*) data.c_str();
  int dataLength = data.length() + 1;
  esp_err_t result = esp_now_send(broadcastAddress, dataToSend, dataLength);
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
  delay(5000);
}

