/* 
 * File:   balance.h
 * Author: psimier
 *
 * Created on 28 juin 2021, 14:16
 */

#ifndef BALANCE_H
#define BALANCE_H

#define TAILLEMAX 9
#define EEPROM_SIZE 512

#include "HX711.h"
#include <EEPROM.h>

class Balance {
public:
    Balance(int _dout = 26, int _sck = 25, int _gain = 64, int _adrEEPROM = 0 );
    Balance(const Balance& orig);
    virtual ~Balance();
    
    void  tarerLaBalance();
    float etalonnerLaBalance(float poidsEtalon);
    float obtenirScale();
    float obtenirOffset();
    void  configuerOffset(float _offset);
    void  configuerScale(float _scale);
    float peser();
    float obtenirVariance();    
    bool  tarageEffectuer();
    void  afficherCoefficients();
    
private:

    HX711 leHX711;
    bool tarage;
    float offset;
    float scale;
    int adrOffsetEeprom;
    int adrScaleEeprom;
    int adrTarageEffectue;
    float tab[TAILLEMAX];
    float calculerMoyenne();
};

#endif /* BALANCE_H */

