/**
 * @file Batterie.cpp
 * @brief Implémentation de la classe Batterie
 * @version 2.0
 * @author Quentin BRAULT
 * @date 28/05/2021
 * @details Classe récupérant les informations et effectuant les calculs relatif à la batterie
 * 
 */

#include "Batterie.h"

/**
 * @brief Batterie::Batterie
 * @details Initialisation du capteur INA219
 */
Batterie::Batterie() :
ancienneIntensite(0),
capacite(10),
ancienneCharge(10),
intensite(0),
loop(0) {

    ina219 = new Adafruit_INA219();

    EEPROM.begin(EEPROM_SIZE);
    EEPROM.get(70, loop);


    ina219->begin();
}

Batterie::Batterie(const Batterie& orig) {
}

Batterie::~Batterie() {
    delete ina219;
}

/**
 * @brief Batterie::ConfigurerCapacite
 * @details Change la valeur de la capacité de la batterie par la valeur de la capacité de la nouvelle batterie
 * @param nouvCapacite la valeur de la capacité de la nouvelle batterie
 */
void Batterie::ConfigurerCapacite(float nouvCapacite) {
    capacite = nouvCapacite;
    ancienneCharge = nouvCapacite;
    ancienneIntensite = 0;

    EEPROM.writeFloat(20, capacite);
    EEPROM.commit();
    EEPROM.writeFloat(40, ancienneCharge);
    EEPROM.commit();
    EEPROM.writeFloat(50, ancienneIntensite);
    EEPROM.commit();
}

/**
 * @brief Batterie::DonnerCapacite
 * @details Retourne la valeur de la capacité de la batterie.
 * @return Valeur de la capacité de la batterie
 */
int Batterie::DonnerCapacite() {
    return capacite;
}

/**
 * @brief Batterie::CalculerCaracteristiques
 * @details Calcule et récupère toutes les caractréristiques nécessaire de la batterie
 * @return Structure regroupant toutes les données
 */
mesureBatterie Batterie::CalculerCaracteristiques() {
    if (loop == 1) {

        capacite = EEPROM.readFloat(20);
        Serial.println(capacite);
        lesMesuresB.chargeBatterie = EEPROM.readFloat(30); //chargeBatterie
        Serial.println(lesMesuresB.chargeBatterie);
        ancienneCharge = EEPROM.readFloat(40); //ancienneCharge
        Serial.println(ancienneCharge);
        ancienneIntensite = EEPROM.readFloat(50); //ancienneIntensite
        Serial.println(ancienneIntensite);
        lesMesuresB.tauxDeChargeBatterie = EEPROM.readFloat(60); //lesMesuresB.tauxDeChargeBatterie
        Serial.println(lesMesuresB.tauxDeChargeBatterie);
    }

    loop = 1;
    EEPROM.writeInt(70, loop);
    EEPROM.commit();

    lesMesuresB.tensionBatterie = ina219->getBusVoltage_V();
    lesMesuresB.intensiteBatterie = ina219->getCurrent_mA();
    lesMesuresB.puissanceBatterie = ina219->getPower_mW();


    /**Calcul Charge de la batterie*/
    lesMesuresB.chargeBatterie = ancienneCharge + ((ancienneIntensite + lesMesuresB.intensiteBatterie / 1000) / 2) * 0.00277778;
  
    /**Si la charge de la batterie excéde la capacité ou est en dessous de 0, corrige le problème*/
    if (lesMesuresB.chargeBatterie > capacite) {
        lesMesuresB.chargeBatterie = capacite;

    } else if (lesMesuresB.chargeBatterie < 0) {
        lesMesuresB.chargeBatterie = 0;
    }


    ancienneCharge = lesMesuresB.chargeBatterie;

    ancienneIntensite = lesMesuresB.intensiteBatterie / 1000;


    /**Calcul SoC Batterie*/
    lesMesuresB.tauxDeChargeBatterie = (lesMesuresB.chargeBatterie / capacite)*100;

    EEPROM.writeFloat(20, capacite);
    EEPROM.commit();
    EEPROM.writeFloat(30, lesMesuresB.chargeBatterie);
    EEPROM.commit();
    EEPROM.writeFloat(40, ancienneCharge);
    EEPROM.commit();
    EEPROM.writeFloat(50, ancienneIntensite);
    EEPROM.commit();
    EEPROM.writeFloat(60, lesMesuresB.tauxDeChargeBatterie);
    EEPROM.commit();


    return lesMesuresB;
}