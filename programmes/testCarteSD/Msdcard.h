/* 
 * File:   Msdcard.h
 * Author: philippe
 *
 * Created on 4 septembre 2021, 21:48
 */

#ifndef MSDCARD_H
#define MSDCARD_H

#include "Arduino.h"
#include "SPI.h"
#include "SD.h"
#include "FS.h"


class Msdcard {
public:
    Msdcard(uint8_t sckPin,uint8_t misoPin,uint8_t mosiPin,uint8_t ssPin);
    Msdcard(const Msdcard& orig);
    virtual ~Msdcard();
    
    bool begin();
    void appendFile(fs::FS &fs, const char * path, const char * message);
    void writeFile(fs::FS &fs, const char * path, const char * message);
    
private:
    
    uint8_t SD_CS;

};

#endif /* MSDCARD_H */

