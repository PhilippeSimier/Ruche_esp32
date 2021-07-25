/* 
 * File:   Fsk.h
 * Author: philippe
 *
 * Created on 25 juillet 2021, 10:20
 */

#ifndef FSK_H
#define FSK_H
#include "Dds.h"

enum stopBits {
  BIT_1,
  BIT_1_5,
  BITS_2
};

class Fsk : public Dds 
{
public:
    Fsk();
    Fsk(const Fsk& orig);
    virtual ~Fsk();
    
    void sendBit(bool value);
    void setBitRate(float br); 
    void sendStopBit(stopBits nStop);
    void sendBitOff();
    
private:
    int nbEchPerBit;    //nombre d'échantillons pour un bit en accord avec le bit rate
};

#endif /* FSK_H */

