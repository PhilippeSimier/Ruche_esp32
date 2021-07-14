#include "scan.h"

float Scan::lireFloat() {
    float valeur = 0.0;
    Serial.setTimeout(10000);
    while (!Serial.available());
    valeur = Serial.parseFloat();
    char Byte = Serial.read();

    return valeur;
}

int Scan::lireInt() {
    int valeur = 0;
    Serial.setTimeout(10000);
    while (!Serial.available());
    valeur = Serial.parseInt();
    char Byte = Serial.read();

    return valeur;
}

String Scan::lireString() {

    String message = "";
    char rc = '\0';

    while (!Serial.available());
    while (rc != '\r') {
        if (Serial.available()) {
            rc = Serial.read();
            if (rc != '\r' && rc != '\n') {
                message += rc;
            }
        }
    }

    return message;
}

void Scan::confirmer() {
    char rc = '\0';
    while (!Serial.available());
    do {
        if (Serial.available())
            rc = Serial.read();
    } while (rc != '\r');
}

void Scan::lireTabChar(char* buffer, int lenght) {
    int i = 0;
    char rc = '\0';

    Serial.setTimeout(10000);
    while (rc != '\r' && i < (lenght - 1)) {
        if (Serial.available()) {
            rc = Serial.read();
            if (rc != '\r' && rc != '\n') {
                buffer[i++] = rc;
            } 
        }
    }
    buffer[i] = '\0';
}

