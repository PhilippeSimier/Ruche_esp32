/** 
 @file Balance.h
 @autho GUITTON Baptiste
 @brief Déclaration de la classe Balance
 @date 22/03/2021
 @details Classe modélisant la gestion de la balance
 */
#ifndef BALANCE_H
#define BALANCE_H
#include "HX711.h"
#include<Arduino.h>
#include <soc/rtc.h>
#include <EEPROM.h>
class Balance {
public:
    Balance(int dout = 26, int sck = 25, int gain = 64);
    Balance(const Balance& orig);
    virtual ~Balance();
    void TarerLaBalance();
    float EtalonnerLaBalance(float poidEtalon);
    float ObtenirScale();
    float ObtenirOffset();
    void ConfiguerOffset(float _offset);
    void ConfiguerScale(float _scale);
    float Peser();
    bool TarageEffectuer();
  
private:

    HX711 *leHX711;
    bool tarage;
    float masse;
    float offset;
    float scale;
    int dout;
    int sck;


};

#endif /* BALANCE_H */

#include <EEPROM.h>
#include "HX711.h"