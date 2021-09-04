/* 
 * File:   Msdcard.cpp
 * Author: philippe
 * 
 * Created on 4 septembre 2021, 21:48
 */

#include "Msdcard.h"
#include "Arduino.h"

Msdcard::Msdcard(uint8_t sckPin, uint8_t misoPin, uint8_t mosiPin, uint8_t ssPin) {
    SD_CS = ssPin;
    SPI.begin(sckPin, misoPin, mosiPin, ssPin); //SCK,MISO,MOSI,ss
    //SPI.begin(); 
    delay(10);
}


Msdcard::Msdcard(const Msdcard& orig) {
}

Msdcard::~Msdcard() {
}



bool Msdcard::begin() {
    bool erreur = false;

    //if (!SD.begin(SD_CS, SPI, 40000000, "/sd")) {
    if (!SD.begin()) {
        Serial.println("Card Mount Failed");
        erreur = true;
    } else {
        uint8_t cardType = SD.cardType();
        if (cardType == CARD_NONE) {
            Serial.println("No SD card attached");
            erreur = true;
        } else {
            Serial.print("SD Card Type: ");
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
        uint64_t cardSize = SD.cardSize() / (1024 * 1024);
        Serial.printf("SD Card Size: %lluMB\n", cardSize);
    }
}

void Msdcard::writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void Msdcard::appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

