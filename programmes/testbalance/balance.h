/* 
 * File:   balance.h
 * Author: psimier
 *
 * Created on 28 juin 2021, 14:16
 */

#ifndef BALANCE_H
#define BALANCE_H

#define TAILLEMAX 9
#define EEPROM_SIZE 64

#include "HX711.h"
#include <EEPROM.h>

class Balance {
public:
    Balance(int _dout = 13, int _sck = 15, int _gain = 64, int _adrEEPROM = 0 );
    Balance(const Balance& orig);
    virtual ~Balance();
    
    long  tarerLaBalance();
    float etalonnerLaBalance(float poidsEtalon);
    float obtenirScale();
    long  obtenirOffset();
    void  configuerOffset(long _offset);
    void  configuerScale(float _scale);
    float peser();
    float obtenirVariance();    
    bool  tarageEffectue();
    void  afficherCoefficients();
    bool  ecrireCoefficients();
    void  fixerUnite(char* _unite);
    char*  obtenirUnite();
    
private:

    HX711 leHX711;
    bool tarage;
    long offset;
    float scale;
    int adrOffsetEeprom;
    int adrScaleEeprom;
    int adrTarageEffectue;
    int adrUnite;
    float tab[TAILLEMAX];
    float calculerMoyenne();
    char unite[10];
};

#endif /* BALANCE_H */

