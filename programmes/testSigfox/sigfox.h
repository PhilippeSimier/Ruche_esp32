/* 
 * File:   sigfox.h
 * Author: philippe
 *
 * Created on 12 juillet 2021, 11:12
 * @details Assure la communication avec le transmetteur sigfox BRKWS01
 * @version    v1.0 - First release
 */

#ifndef SIGFOX_H
#define SIGFOX_H

#include "Arduino.h"
#include <HardwareSerial.h>

class Sigfox {
public:

    Sigfox(uint8_t _rx = 16, uint8_t _tx = 17, uint8_t _uart = 2, bool _debug = false);
    virtual ~Sigfox();

    String tester();
    void begin();

    String obtenirID();
    String obtenirPAC();
    float  obtenirTemp();
    float  obtenirFreqEmi();
    float  obtenirFreqRec();
    void   obtenirTension(float &tension0, float &tension1);

    bool envoyer(const void* data, uint8_t size);

private:
    uint8_t rx, tx;
    bool debug;
    
    HardwareSerial *serialSig;
    
    String obtenirData();

};



#endif /* SIGFOX_H */

