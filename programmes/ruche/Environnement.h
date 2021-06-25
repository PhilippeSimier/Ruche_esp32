/** 
 @file Environnement.h
 @autho GUITTON Baptiste
 @brief Déclaration de la classe Environnement
 @date 26/03/2021
 @details  Classe modélisant la gestion des capteurs
 */
#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include<Arduino.h>
#include<Wire.h>
#include<BME280I2C.h>
#include <BH1750.h>
#include "constante.h"

class Environnement {
public:
    Environnement(bool _debug=false,BME280I2C::I2CAddr adresse=BME280I2C::I2CAddr_0x77);
//    Environnement(const Environnement& orig);
    virtual ~Environnement();
    mesure ObtenirMesures();


private:
    bool debug;
    BH1750 *leBh1750;
    BME280 *leBme280;
   
    mesure lesMesures;


};

#endif /* ENVIRONNEMENT_H */

