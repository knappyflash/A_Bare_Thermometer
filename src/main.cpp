#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <FS.h>
#include <FFat.h>

#include <MyWifi.cpp>

#define SD_CS 5

void setup() {
    Serial.begin(115200);

    delay(5000);

    if (!SD.begin(SD_CS)) {
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE) {
        Serial.println("No SD card attached");
        return;
    }
    Serial.println("SD Card Type: ");
    if (cardType == CARD_MMC) {
        Serial.println("MMC");
    } else if (cardType == CARD_SD) {
        Serial.println("SDSC");
    } else if (cardType == CARD_SDHC) {
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }
}

void loop() {
    Serial.println(SD.usedBytes());
    Serial.println(SD.totalBytes());
    Serial.println("");
    delay(5000);
}