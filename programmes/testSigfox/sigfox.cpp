/* 
 * File:   sigfox.cpp
 * Author: philippe S
 *
 * Created on 12 juillet 2021, 11:12
 * @details Assure la communication avec le réseau Sigfox avec les commandes AT
 * 
 */

#include "sigfox.h"

/**
 * @brief  le constructeur de la classe Sigfox
 * @param _rx  Le n° de la broche esp32 pour la réception 
 * @param _tx  le n° de la borche esp32 pour l'emission
 * @param _uart  le n° de l'uart (par défaut 2)
 * @param _debug true pour le mode debug
 */

Sigfox::Sigfox(uint8_t _rx, uint8_t _tx, uint8_t _uart, bool _debug) :
rx(_rx),
tx(_tx),
debug(_debug),
serialSig(new HardwareSerial(_uart)) {

}

Sigfox::~Sigfox() {
    delete serialSig;
}

// Lecture des datas reçus sur la liaison série HardwareSerial 

String Sigfox::obtenirData(void) {
    String data = "";
    char input;
    bool fin = false;


    while (!serialSig->available()) {
        delay(100);
    }

    while (serialSig->available() && !fin) {
        input = serialSig->read();
        fin = (input == '\n');
        if ((input != 0x0A) && (input != 0x0D)) { //0x0A Line feed | 0x0D Carriage return
            data += input;
        }
        delay(10);
    }
    return data;
}

// Initialise la liaison avec le transmetteur Sigfox

void Sigfox::begin() {

    serialSig->begin(9600, SERIAL_8N1, rx, tx);

    if (debug) {
        delay(100);
        tester();
        delay(100);
        obtenirID();
        delay(100);
        obtenirPAC();
    }
}

//Méthode pour obtenir l'identifiant Sigfox

String Sigfox::obtenirID() {
    serialSig->print("AT$I=10\r");
    String id = obtenirData();

    if (debug) {
        Serial.printf("ID: %s\r", id);
    }

    return id;
}

/*
  Méthode pour obtenir le PAC number du transmetteur Sigfox
  @return un string contenant le PAC number
 */

String Sigfox::obtenirPAC() {
    serialSig->print("AT$I=11\r");
    String pac = obtenirData();

    if (debug) {
        Serial.print("PAC : ");
        Serial.println(pac);
    }

    return pac;
}

//Méthode pour obtenir la température du module

float Sigfox::obtenirTemp(void) {
    serialSig->print("AT$T?\r");
    float tempVal = obtenirData().toFloat() / 10.0;

    if (debug) {
        Serial.printf("Module temperature : %.2f\r", tempVal);

    }

    return tempVal;
}

/*
  Méthode pour obtenir la fréquence d'émission en MHz
  @return un float la frequence d'émission
 */
float Sigfox::obtenirFreqEmi() {
    serialSig->print("AT$IF?\r");
    float freqEmi = obtenirData().toFloat() / 1e6;
    return freqEmi;
}

/*
  Méthode pour obtenir la fréquence de reception en MHz
  @return un float la frequence de reception
 */
float Sigfox::obtenirFreqRec(void) {
    serialSig->print("AT$DR?\r");
    float freqRec = obtenirData().toFloat() / 1e6;
    return freqRec;
}

/**
 * 
 * @param tension0 current voltage
 * @param tension1 voltage measured during the last transmission in V.
 */
void Sigfox::obtenirTension(float &tension0, float &tension1) {
    serialSig->print("AT$V?\r");
    tension0 = obtenirData().toFloat() / 1e3;
    tension1 = obtenirData().toFloat() / 1e3;

}

/** Méthode pour tester le composant 
 *  la commande AT renvoie OK
 */

String Sigfox::tester() {
    serialSig->print("AT\r");
    String status = obtenirData();

    if (debug) {
        Serial.printf("Status : %s\r", status);

    }

    return status;
}

/**
 * Méthode pour envoyer des data
 * data un tableau de 12 octets au maximum
 * size le nombre d'octet à envoyer
 * retourne vrai si le message a été envoyé avec success
 */
bool Sigfox::envoyer(const void* data, uint8_t size) {
    String status = "";
    char output;

    uint8_t* bytes = (uint8_t*) data;

    serialSig->print("AT$SF=");
    if (debug) {
        Serial.print("Byte : ");
    }
    for (uint8_t i = 0; i < size; ++i) {
        serialSig->print(bytes[i] < 16 ? "0" : "");
        serialSig->print(bytes[i], HEX);

        if (debug) {
            Serial.print(bytes[i] < 16 ? "0" : "");
            Serial.print(bytes[i], HEX);
        }
    }
    if (debug) {
        Serial.println(" ");
    }
    serialSig->print("\r");

    String res = obtenirData();

    bool val = (res.indexOf("OK") >= 0);

    if (debug) {
        Serial.print("Status : ");
        Serial.println(res);
    }
    return val;
}