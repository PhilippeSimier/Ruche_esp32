/**
 * @file Batterie.cpp
 * @brief Déclaration de la classe Batterie
 * @version 2.0
 * @author Quentin BRAULT
 * @date 28/05/2021
 * 
 */

#include <Adafruit_INA219.h>
#include <EEPROM.h>
#include "constante.h"

#ifndef BATTERIE_H
#define BATTERIE_H

#define EEPROM_SIZE 512

/** Structure regroupant les caractéristiques de la batterie*/


class Batterie : public Adafruit_INA219 {
public:
    Batterie();
    Batterie(const Batterie& orig);
    virtual ~Batterie();

    void ConfigurerCapacite(float nouvCapacite);
    int DonnerCapacite();
    mesureBatterie CalculerCaracteristiques();
private:
    /** Valeur pour calculer la charge de la batterie*/
    float ancienneIntensite;
    /** Valeur pour calculer la charge de la batterie*/
    float ancienneCharge;
    /** Valeur dela capacité de la batterie*/
    float capacite;

    float intensite;

    int loop;
    mesureBatterie lesMesuresB;

    Adafruit_INA219 *ina219;

};

#endif /* BATTERIE_H */

