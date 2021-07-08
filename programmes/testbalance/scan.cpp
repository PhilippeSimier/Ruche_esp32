#include "scan.h"

float Scan::lireFloat() {
    float valeur = 0.0;
    Serial.setTimeout(10000);
    while (Serial.available() == 0) {
    }
    valeur = Serial.parseFloat();
    char Byte = Serial.read();

    return valeur;
}

int Scan::lireInt() {
    int valeur = 0;
    Serial.setTimeout(10000);
    while (Serial.available() == 0) {
    }
    valeur = Serial.parseInt();
    char Byte = Serial.read();

    return valeur;
}

String Scan::lireString() {

    String message = "";
    char rc;
    boolean fin = false;

    while (fin == false) {
        while (Serial.available() > 0) {
            rc = Serial.read();
            if (rc != '\r' && rc != '\n') {
                message += rc;
            } else {
                fin = true;
            }
        }
    }
    return message;
}

void Scan::confirmer() {
    char rc = '\0';
    while (!Serial.available());
    do {
        rc = Serial.read();
    } while (rc != '\r' && rc != '\n');
}

void Scan::lireTabChar(char* buffer, int lenght){
    int i = 0;
    boolean fin = false;
    char rc = '\0';
    
    Serial.setTimeout(10000);
    while (fin == false && i < (lenght-1)) {
        while (Serial.available() > 0) {
            rc = Serial.read();
            if (rc != '\r' && rc != '\n') {
                buffer[i++] = rc;
            } else {
                fin = true;               
            }
        }
    }
    buffer[i] = '\0';
}

