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

enum modesPsk_t
{
  BPSK,
  QPSK
};

#include <Arduino.h>
#include "Dds.h"

class Psk : public Dds
{
public:
    Psk(float _freq = PSK_FREQ, float br = PSK_RATE, modesPsk_t _mode = BPSK);
    Psk(const Psk& orig);
    virtual ~Psk();
    
    void setBitRate(float br);
    void idle(int nb);
    void tx(char* c);
    
private:
    int nbEchPerBit;    //nombre d'échantillons pour un bit en accord avec le bit rate
    modesPsk_t mode;
    int freq;
};

#endif /* PSK_H */

