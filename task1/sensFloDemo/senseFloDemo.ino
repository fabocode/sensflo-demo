#include <WiFi.h>
#include "secrets.h"
#include "OTAWiFiUpdater.h"

uint32_t previousMillis = 0;
const uint32_t LEDInterval = 100;
const uint32_t RebootTimeout = 5000;
const uint32_t ConnectionInterval = 500;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);

  const uint32_t StartAttemptTime = millis();
  const uint32_t ConnectionTimeout = 20000; // 20 seconds timeout

  Serial.print("Connecting to WiFi");

  // Wait for connection with a timeout
  while (WiFi.status() != WL_CONNECTED && (millis() - StartAttemptTime < ConnectionTimeout)) {
    Serial.print(".");
    delay(ConnectionInterval);
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nConnection Failed! Rebooting...");
    delay(RebootTimeout);
    ESP.restart();
  }

  Serial.println("\nConnected to WiFi");

  initOTA(PASSWORD);
}

void loop() {
  // Handle OTA updates
  ArduinoOTA.handle();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Attempting to reconnect...");
    WiFi.disconnect();
    WiFi.begin(SSID, PASSWORD);
  }

  // Non-blocking LED blink using millis()
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= LEDInterval) {
    previousMillis = currentMillis;
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}
