/* 
 * File:   Psk.cpp
 * Author: philippe S
 * 
 * Created on 29 juillet 2021, 09:18
 */

#include "Psk.h"

Psk::Psk(float freq, float br):
Dds(),
phase(0)        
{
    setFrequency(freq);
    setBitRate(br);
    
}

Psk::Psk(const Psk& orig) {
}

Psk::~Psk() {
}

void Psk::setBitRate(float br){
    nbEchPerBit = round(splFreq / br);
}

void Psk::sendBitPhase(int _phase){
    compteur = 0;
    if (phase != _phase){   // si la phase est différente
       Dds::setAttenuation(dB_6);   // attenution de l'amplitude 6dB 
       while (compteur < (nbEchPerBit/8));   // pendant 1/16 de période
       Dds::setAttenuation(dB_18);          
       while (compteur < (nbEchPerBit/4));
       phase = _phase;
       Dds::setPhase(phase);      // Changement de phase
       while (compteur < (3 * nbEchPerBit/8));
       Dds::setAttenuation(dB_6);
       while (compteur < (2 * nbEchPerBit/4));
       Dds::setAttenuation(dB_O);
    }
    while (compteur < nbEchPerBit);    
}