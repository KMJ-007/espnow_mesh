
#include <ESP8266WiFi.h>
#include <espnow.h>

// Replace with master ESP32 MAC Address
uint8_t broadcastAddress[] = {0x30, 0xAE, 0xA4, 0x32, 0x87, 0x58};

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len) {
    Serial.print("Received data from: ");
    Serial.print(mac[0], HEX);
    Serial.print(":");
    Serial.print(mac[1], HEX);
    Serial.print(":");
    Serial.print(mac[2], HEX);
    Serial.print(":");  
    Serial.print(mac[3], HEX);
    Serial.print(":");
    Serial.print(mac[4], HEX);
    Serial.print(":");
    Serial.println(mac[5], HEX);
    int rssi = WiFi.RSSI();
    int distance = calculateDistance(rssi);
    Serial.print("RSSI: ");
    Serial.print(rssi);
    Serial.print(" dBm, Distance: ");
    Serial.print(distance);
    Serial.println(" meters");
    Serial.print("Data: ");
    Serial.write(data, len);
    Serial.println();
  });
}

int calculateDistance(int rssi) {
  int txPower = -50; // transmit power in dBm
  int n = 2; // path loss exponent
  return round(pow(10, (txPower - rssi) / (10 * n)));
}

void loop() {
  
}

