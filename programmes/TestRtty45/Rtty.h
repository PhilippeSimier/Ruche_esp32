/* 
 * File:   Rtty.h
 * Author: philippe
 *
 * Created on 26 juillet 2021, 11:27
 */

#ifndef RTTY_H
#define RTTY_H
#include "Fsk.h"

enum etatRtty
{
  LETTERS,
  FIGURES
};


class Rtty {
public:
    Rtty(stopBits _nbStopBits = BITS_2);
    Rtty(const Rtty& orig);
    virtual ~Rtty();
    
    void txByte(char car);
    void tx(char message[]);
    void stop();
    
private:
    Fsk* leFsk;
    stopBits nbStopBits;   //Nb de bit de stops
    
};

#endif /* RTTY_H */

