/* 
 * File:   Psk.cpp
 * Author: philippe S
 * 
 * Created on 29 juillet 2021, 09:18
 */

#include "Psk.h"

Psk::Psk(float _freq, float br) :
Dds(),
freq(_freq),
phaseActuelle(0) {
    
    setBitRate(br);

}

Psk::Psk(const Psk& orig) {
}

Psk::~Psk() {
}

void Psk::setBitRate(float br) {
    nbEchPerBit = round(splFreq / br);
}

void Psk::sendBitPhase(int _phase) {
    compteur = 0;

    if (phaseActuelle != _phase) { // si la phaseActuelle est différente
        Dds::setAttenuation(dB_24); // attenution de l'amplitude 6dB 
        while (compteur < (nbEchPerBit / 16)); // pendant 1/16 de période

        phaseActuelle = _phase;
        Dds::setPhase(phaseActuelle); // Changement de phase

        while (compteur < (2 * nbEchPerBit / 16));
        Dds::setAttenuation(dB_O);
    }

    while (compteur < nbEchPerBit);
}

void Psk::idle(int nb) {
    int phase = 0;
    setFrequency(freq);
    for (int n = 0; n < nb; n++) {
        if (phase == 0) phase = 180;
        else phase = 0;

        Dds::compteur = 0;
        Dds::setPhase(phase); // Changement de phase
        while (Dds::compteur < Psk::nbEchPerBit);
    }
}

void Psk::tx(char* message, modesPsk_t modePsk) {

    const static int varicode[2][128] PROGMEM = {
        { 2732,2924,2996,3548,2988,3452,3004,3060,3068,956,116,3516,2932,124,3540,3756,3036,3028,3764,3772,3436,3500,3508,3420,3564,
          3572,3804,3412,3444,3820,3052,3580,4,2044,1404,2004,1900,2900,2796,1532,1004,988,1468,1916,468,212,348,1724,732,756,948,1020,
          1500,1388,1452,1716,1708,1756,980,1780,1972,340,1884,2748,2804,500,940,692,724,476,876,1012,1364,508,2036,1524,860,748,884,
          684,852,1908,700,444,436,1372,1748,1396,1492,1516,2740,2012,1980,2028,2812,1460,2940,44,380,188,180,12,244,364,172,52,1964,
          764,108,236,60,28,252,1788,84,92,20,220,492,428,892,372,1876,2780,1772,2772,2908,3796},
        { 11,11,11,11,11,11,11,11,11,9,6,11,11,6,11,11,11,11,11,11,11,11,11,11,11,
          11,11,11,11,11,11,11,2,10,10,10,10,11,11,10,9,9,10,10,8,7,8,10,9,9,9,9,
          10,10,10,10,10,10,9,10,10,8,10,11,11,8,9,9,9,8,9,9,10,8,10,10,9,9,9,9,9,
          10,9,8,8,10,10,10,10,10,11,10,10,10,11,10,11,5,8,7,7,3,7,8,7,5,10,9,6,7,
           5,4,7,10,6,6,4,7,8,8,9,8,10,11,10,11,11,11}
    };

    const static int QpskConvol[32] PROGMEM = {180, 90, -90, 0, -90, 0, 180, 90, 0, -90, 90, 180, 90, 180, 0, -90, 90, 180, 0,
        -90, 0, -90, 90, 180, -90, 0, 180, 90, 180, 90, -90, 0};



    int phase = 0;
    int shreg = 0; // Shift register qpsk
    byte nb_bits, val;
    int c, d, e;
    Dds::setFrequency(freq);  // start Dds
    idle(50);
    for (int i = 0; message[i] != '\0'; i++) {
        c = message[i];
        e = int(pgm_read_word(&varicode[0][c])); // Get PSK varicode & spacing
        nb_bits = int(pgm_read_word(&varicode[1][c])); // Get PSK varicode length
        for (int b = nb_bits; b >= 0; b--) //send car in psk
        {
            val = bitRead(e, b); //look varicode

            if (modePsk == BPSK) // BPSK mode
            {
                if (val == 0) {
                    if (phase == 0) phase = 180;
                    else phase = 0; //swapp phase 0/180°
                }
            } else if (modePsk == QPSK) { // QPSK mode
                shreg = (shreg << 1) | val; // Loading shift register with next bit
                d = (int) int(pgm_read_word(&QpskConvol[shreg & 31])); // Get the phase shift from convolution code of 5 bits in shit register
                phase = (phase + d) % 360; // Phase shifting
            }

            Dds::compteur = 0;
            Dds::setPhase(phase); // Changement de phase
            while (Dds::compteur < Psk::nbEchPerBit);
        }        
    }
    Dds::stop();  // stop Dds
}

