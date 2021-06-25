/**
 * @file Environnement.cpp
 * @brief Implémentation de la classe Environnement
 * @author GUITTON Baptiste
 * @date 26/03/2021
 * @details Classe récupérant les informations relatif aux capteurs d'éclairement,pression,humidité,température
 * 
 */

#include "Environnement.h"
/**
 * @brief Environnement::Environnement
 * @details Initialisation des capteurs BME280 et BH1750
 */
Environnement::Environnement(bool _debug,BME280I2C::I2CAddr adresse)
: debug(_debug) {
    
    BME280I2C::Settings settings(
            BME280::OSR_X1,
            BME280::OSR_X1,
            BME280::OSR_X1,
            BME280::Mode_Forced,
            BME280::StandbyTime_1000ms,
            BME280::Filter_Off,
            BME280::SpiEnable_False,
            BME280I2C::I2CAddr_0x77 // 0x77 I2C address pour BME 280 Adafruit.
            );
    settings.bme280Addr=adresse;
    lesMesures.temperature = 0;
    lesMesures.humidite = 0;
    lesMesures.pression = 0;
    lesMesures.eclairement = 0;
    leBme280 = new BME280I2C(settings);
    leBh1750 = new BH1750();

    leBh1750->begin();

    leBme280->begin();
    if (debug) {
        Serial.println("Debug");
    }
   
}

/**
 * @brief Environnement::~Environnement
 * @details destructeur de la classe Environnement
 */
Environnement::~Environnement() {
    delete leBh1750;
    delete leBme280;
}
/**
 * @brief Environnement::ObtenirMesures
 * @details Cette fonction permet d'intéroger les capteurs et de remplire une stucture
 * @return retourne la stucture avec les nouvelles données
 */
mesure Environnement::ObtenirMesures() {
    float temp(NAN), hum(NAN), pres(NAN), ecl(NAN);
    leBme280->read(pres, temp, hum, BME280::TempUnit_Celsius, BME280::PresUnit_hPa);
    lesMesures.temperature = temp;
    lesMesures.humidite = hum;
    lesMesures.pression = pres;
    lesMesures.eclairement = leBh1750->readLightLevel();
    return lesMesures;
}

