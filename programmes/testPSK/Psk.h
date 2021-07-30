/* 
 * File:   Psk.h
 * Author: Philippe & Anthony
 *
 * Created on 29 juillet 2021, 09:18
 * la classe Psk herite de Dds
 */

#ifndef PSK_H
#define PSK_H

#define PSK_FREQ 800
#define PSK_RATE 31

#include "Dds.h"

class Psk : public Dds
{
public:
    Psk(float freq = PSK_FREQ, float br = PSK_RATE);
    Psk(const Psk& orig);
    virtual ~Psk();
    
    void setBitRate(float br);
    void sendBitPhase(int phase);
    
private:
    int nbEchPerBit;    //nombre d'échantillons pour un bit en accord avec le bit rate
    int phase;          // la phase courante
};

#endif /* PSK_H */

