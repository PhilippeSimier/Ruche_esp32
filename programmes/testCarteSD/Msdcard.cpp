/* 
 * File:   Msdcard.cpp
 * Author: Anthony Le Cren
 * 
 * Created on 4 septembre 2021, 21:48
 * manque la gestion des retours d'erreurs dans la plupart des méthodes
 * Attention :
 * Avec l'affectation des broches standard de la liaison SPI de l'esp32 (carte ruche)
 * Msdcard cartesd(18, 19, 23, 5); //SCK,MISO,MOSI,ss
 * SPI.begin() et SD.begin() suffit 
 * pour une affection non standard de la liaison SPI (carte ballon)
 * SPI.begin(14, 2, 15, 13); //SCK,MISO,MOSI,ss
 * il faut utiliser préciser la vitesse du bus SPI et le chip select
 * SD.begin(SD_CS, SPI, 40000000, "/sd")
 */

#include "Msdcard.h"
#include "Arduino.h"

Msdcard::Msdcard(uint8_t sckPin, uint8_t misoPin, uint8_t mosiPin, uint8_t ssPin) {
    SD_CS = ssPin;
    SPI.begin(sckPin, misoPin, mosiPin, ssPin); //SCK,MISO,MOSI,ss     
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

void Msdcard::listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if (!root) {
        Serial.println("Failed to open directory");
        return;
    }
    if (!root.isDirectory()) {
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if (levels) {
                listDir(fs, file.name(), levels - 1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void Msdcard::createDir(fs::FS &fs, const char * path) {
    Serial.printf("Creating Dir: %s\n", path);
    if (fs.mkdir(path)) {
        Serial.println("Dir created");
    } else {
        Serial.println("mkdir failed");
    }
}

void Msdcard::removeDir(fs::FS &fs, const char * path) {
    Serial.printf("Removing Dir: %s\n", path);
    if (fs.rmdir(path)) {
        Serial.println("Dir removed");
    } else {
        Serial.println("rmdir failed");
    }
}

void Msdcard::readFile(fs::FS &fs, const char * path) {
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if (!file) {
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while (file.available()) {
        Serial.write(file.read());
    }
    file.close();
}

void Msdcard::renameFile(fs::FS &fs, const char * path1, const char * path2) {
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("File renamed");
    } else {
        Serial.println("Rename failed");
    }
}

void Msdcard::deleteFile(fs::FS &fs, const char * path) {
    Serial.printf("Deleting file: %s\n", path);
    if (fs.remove(path)) {
        Serial.println("File deleted");
    } else {
        Serial.println("Delete failed");
    }
}

void Msdcard::testFileIO(fs::FS &fs, const char * path) {
    File file = fs.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if (file) {
        len = file.size();
        size_t flen = len;
        start = millis();
        while (len) {
            size_t toRead = len;
            if (toRead > 512) {
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("%u bytes read for %u ms\n", flen, end);
        file.close();
    } else {
        Serial.println("Failed to open file for reading");
    }


    file = fs.open(path, FILE_WRITE);
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }

    size_t i;
    start = millis();
    for (i = 0; i < 2048; i++) {
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
    file.close();
}


