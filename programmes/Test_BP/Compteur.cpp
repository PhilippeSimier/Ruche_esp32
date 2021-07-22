/* 
 * File:   Compteur.cpp
 * Author: philippe
 * 
 * Created on 18 juillet 2021, 17:47
 */

#include "Compteur.h"

Compteur::Compteur() :
lastMillis(0),
nb(0)     
{
    anchor = this;
}

Compteur::Compteur(const Compteur& orig) {
}

Compteur::~Compteur() {
}

void Compteur::begin(byte sensePin) {
    attachInterrupt(sensePin, Compteur::marshall, FALLING);

}

void Compteur::marshall() {
    anchor->interuption();
}

void IRAM_ATTR Compteur::interuption() {
    if (millis() - this->lastMillis > 200) { //Software anti-rebond

        ets_printf("triggered\r\n");
        this->nb++;
    }
    this->lastMillis = millis();
}

int Compteur::getValue() {
    return this->nb;
}

Compteur* Compteur::anchor = NULL;