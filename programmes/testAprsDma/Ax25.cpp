/* 
 * File:   Ax25.cpp
 * Author: Anthony le Cren & philippe SIMIER
 * 
 * Created on 30 août 2021, 09:51
 */

#include "Ax25.h"

Ax25::Ax25():
attenuation(dB_0)
{
    buffer = new uint8_t[AX25_MAX_LENGTH];
    leDdsI2s = new DdsI2s();
    leDdsI2s->begin();

}

Ax25::Ax25(const Ax25& orig) {
}

Ax25::~Ax25() {
    delete buffer;
    delete leDdsI2s;
}

void Ax25::txMessage(char *bufMsg) {

    int bufLen = strlen(bufMsg);
    memcpy(buffer + AX25_HEADER_SIZE, bufMsg, bufLen);
    frameLength = AX25_HEADER_SIZE + bufLen;
    calculateCRC();

    frame_t frame;

    frame.attenuation = attenuation;
    frame.nBytes = frameLength;
    memcpy(frame.data, buffer, frameLength);

    xQueueSend(leDdsI2s->queueDds, &frame, portMAX_DELAY);
}

/**
   @brief   Ax25::begin()
   @details Permet de créer l'entête de la trame Ax25
   @param   *sourceCallsign         indicatif de la source 
            *destinationCallsign    indicatif du destinataire
            *path1 chemin1
            *path2 chemin2
 */
void Ax25::begin(char *sourceCallsign, char *destinationCallsign, char *path1, char *path2) {
    uint8_t *ptr = buffer;

    ptr = addCallsign(buffer, destinationCallsign); // ajoute la destination dans l'header AX25
    ptr = addCallsign(ptr, sourceCallsign); // puis le sourceCallsign 
    ptr = addCallsign(ptr, path1); // le premier chemin
    ptr = addCallsign(ptr, path2); // le second  chemin
    ptr[-1] |= 1; // Marqueur fin de l'entete sur le dernier ssid

    *(ptr++) = AX25_CONTROL; //ajout ctrl + protocol
    *(ptr++) = AX25_PROTOCOL;
}



/**
   @brief   Ax25::addCallsign(uint8_t *buf, char *callsign)
   @details Ajoute un callSign (addresse) dans l'entête de la trame
   @param   *buf pointeur dans le buffer pour le positionnement du callsign
            *callsign pointeur de la chaine callsign
   @return  le pointeur courant ds le buffer pour le prochain ajout
 */

uint8_t* Ax25::addCallsign(uint8_t *buf, char *callsign) {
    char ssid;
    char i;
    for (i = 0; i < 6; i++) {
        if (*callsign && *callsign != '-') *(buf++) = *(callsign++) << 1;
        else *(buf++) = ' ' << 1;
    }

    if (*callsign == '-') ssid = atoi(callsign + 1);
    else ssid = 0;

    *(buf++) = ('0' + ssid) << 1;
    return (buf);
}


/**
   @brief Ax25::calculateCRC()
   @details calcule le crc16 de la trame complete et ajoute le crc en fin de trame en utilisant les fonctions intégrées de la rom dans l'ESP32
 * https://github.com/espressif/esp-idf/blob/master/components/esp_rom/include/esp32/rom/crc.h
*/ 

void Ax25::calculateCRC() {
    uint16_t crc;
    uint8_t *s;
    s=buffer+ frameLength;
    crc = crc16_le(0, buffer, frameLength);
    *(s++) = crc & 0xFF;
    *(s++) = crc >> 8;
    frameLength += 2;
}



/**
   @brief Ax25::debug()
   @details permet d'afficher la trame fabriquée par la classe Ax25 !!
 */

void Ax25::debug() {
    int n;
    Serial.print("longueur de la trame : ");
    Serial.print(frameLength);
    Serial.println(" Octets");
    for (n = 0; n < AX25_HEADER_SIZE - 2; n++) {
        Serial.print(buffer[n], HEX);
        Serial.print(",");

    }
    Serial.print("\n\rHeader : ");
    for (n = 0;  n < AX25_HEADER_SIZE - 2; n++) {       
        Serial.print((char) (buffer[n] >> 1));
    }
    Serial.print("\n\rPDU APRS : ");
    for (n = AX25_HEADER_SIZE; n < frameLength - 2; n++) {
        Serial.print((char) buffer[n]);
    }
    Serial.print("\n\rCRC : ");
    Serial.print(buffer[frameLength - 2], HEX);
    Serial.print(',');
    Serial.println(buffer[frameLength - 1], HEX);
}


