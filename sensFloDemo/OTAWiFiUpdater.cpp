#include "OTAWiFiUpdater.h"
#include <WiFi.h>

static void otaStart() {
    String type;

    if(ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
    } else {
        type = "filesystem";
    }

    Serial.println("Start updating " + type);
}

static void otaEnd() {
    Serial.println("\nUpdate Complete!");
}

static void otaProgress(uint16_t progress, uint16_t total) {
    Serial.printf("Progress: %u%%\r", (progress * 100 / total));
}

static void otaError(ota_error_t err) {
    Serial.printf("Error[%u]: ", err);
    if(err == OTA_AUTH_ERROR) {
        Serial.println("Auth Failed");
    } else if(err == OTA_BEGIN_ERROR) {
        Serial.println("Begin Failed");
    } else if(err == OTA_CONNECT_ERROR) {
        Serial.println("Connect Failed");
    } else if(err == OTA_RECEIVE_ERROR) {
        Serial.println("Receive Failed");
    } else if(err == OTA_END_ERROR) {
        Serial.println("End Failed");
    }
}

void initOTA(const char* PASSWORD) {
    ArduinoOTA.onStart(otaStart);
    ArduinoOTA.onEnd(otaEnd);
    ArduinoOTA.onProgress(otaProgress);
    ArduinoOTA.onError(otaError);

    ArduinoOTA.setPassword(PASSWORD);

    ArduinoOTA.begin();

    Serial.println("OTA Initialized");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}
