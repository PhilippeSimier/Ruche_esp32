/** 
 @file ModemSigfox.h
 @autho GUITTON Baptiste
 @brief Déclaration de la classe ModemSigfox
 @date 21/05/2021
 @details  Classe modélisant l'utilisation de Sigfox
 */


#ifndef MODEMSIGFOX_H
#define MODEMSIGFOX_H
#include "Sigfox.h"
#include "constante.h"

//typedef struct {
//    unsigned short masse;
//    short temperature;
//    unsigned short pression;
//    unsigned short eclairement;
//    short pointDeRosee;
//    unsigned char humidite;
//    char typeTrame = 1;
//} trameMesure;

//struct mesureBatterie {
//    float tensionBatterie;
//    float puissanceBatterie;
//    int tauxDeChargeBatterie;
//    float chargeBatterie;
//    float intensiteBatterie;
//    
//};
//struct mesure{
//    float temperature;
//    float humidite;
//    float pression;
//    float eclairement;
//
//};

//typedef struct {
//    short tension;
//    short courant;
//    short puissance;
//    short charge;
//    short nu;
//    unsigned char tauxDeCharge;
//    char typeTrame = 02;
//} trameBatterie;

class ModemSigfox : public Sigfox {
public:

    ModemSigfox();
    void ForgerTrameMesure(mesure lesMesures, float masse);
    void ForgerTrameBatterie(mesureBatterie lesMesuresBatterie);
    virtual ~ModemSigfox();
private:
    trameMesure laTrameMesure;
    trameBatterie laTrameBatterie;

};

#endif /* MODEMSIGFOX_H */

