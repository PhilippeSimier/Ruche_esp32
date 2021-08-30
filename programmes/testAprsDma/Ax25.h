/* 
 * File:   Ax25.h
 * Author: Anthony le Cren & philippe SIMIER
 *
 * Created on 30 août 2021, 09:51
 */

#ifndef AX25_H
#define AX25_H

#include <Arduino.h>
#include "DdsI2s.h"

#define AX25_HEADER_SIZE 30    //longueur de l'entete pour 4 callsign (fixe)
#define AX25_CONTROL     0x03  //APRS-UI frame
#define AX25_PROTOCOL    0xF0  //Protocol Identifier
#define AX25_MAX_LENGTH  512

class Ax25 {
public:
    Ax25();
    Ax25(const Ax25& orig);
    virtual ~Ax25();
    
    void begin(char *sourceCallsign ,
               char *destinationCallsign ,
               char *path1 ,
               char *path2);
    
    void txMessage(char *bufMsg);
    void debug();
    
private:
    uint8_t* addCallsign(uint8_t *buf, char *callsign);
    uint16_t  crcCcittUpdate(uint16_t crc, uint8_t data);
    void      calculateCRC();
    
    uint8_t* buffer;
    int      frameLength;  //longeur de la trame à envoyer
    attenuation_t attenuation;
    
    DdsI2s  *leDdsI2s;

};

#endif /* AX25_H */

