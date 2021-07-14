/* 
 * File:   balance.cpp
 * Author: psimier
 * 
 * Created on 28 juin 2021, 14:16
 */

#include "balance.h"

Balance::Balance(int _dout, int _sck, int _gain, int _adrEEPROM) {
    if (!EEPROM.begin(EEPROM_SIZE)) {
        Serial.println("Échec de l'initialisation de l'EEPROM");
        Serial.println("Redémarrage... ");
        delay(10000);
        ESP.restart();
    }
    adrOffsetEeprom = _adrEEPROM;
    adrScaleEeprom = _adrEEPROM + sizeof (offset);
    adrTarageEffectue = adrScaleEeprom + sizeof (scale);
    adrUnite = adrTarageEffectue + sizeof (tarage);

    leHX711.begin(_dout, _sck, _gain);

    tarage = EEPROM.readBool(adrTarageEffectue);
    offset = EEPROM.readLong(adrOffsetEeprom);
    leHX711.set_offset(offset);
    scale = EEPROM.readFloat(adrScaleEeprom);
    leHX711.set_scale(scale);
    for (int i = 0; i < 10; i++) {
        unite[i] = EEPROM.readChar(adrUnite + i);
    }
    
}

Balance::Balance(const Balance& orig) {
}

Balance::~Balance() {

}

/**
 * @brief Balance::peser
 * @detail Permet d'obtenir la valeur du poids en unité de mesure (médiane de la série)
 * @return float la valeur du poids
 */
float Balance::peser() {

    float tmp;

    for (int i = 0; i < TAILLEMAX; i++) {
        tab[i] = leHX711.get_units();
    }

    for (int i = 0; i < TAILLEMAX - 1; i++)
        for (int j = i + 1; j < TAILLEMAX; j++)
            if (tab[i] < tab[j]) {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[i] = tmp;
            }

    return tab[TAILLEMAX / 2];
}

/**
 * @brief  Méthode pour obtenir la variance de la dernière série
 * @return  float la variance
 */
float Balance::obtenirVariance() {

    float moyenne = calculerMoyenne();
    float k = 0;
    for (unsigned int i = 0; i < TAILLEMAX; i++)
        k += (tab[i] - moyenne)*(tab[i] - moyenne);
    return 1000 * k / (float) TAILLEMAX;
}

/**
 * @brief  Méthode pour calculer la moyenne de la dernière série
 * @return la moyenne de la dernière série
 */
float Balance::calculerMoyenne() {

    float k = 0;
    for (unsigned int i = 0; i < TAILLEMAX; i++) {
        k = k + tab[i];
    }

    k = k / TAILLEMAX;
    return k;
}

/**
 * @brief Balance::tarerLaBalance
 * @detail cette fonction permet de tarer la balance et de sauvegarder le coefficient offset
 */
long Balance::tarerLaBalance() {


    leHX711.tare();
    tarage = true;
    offset = leHX711.get_offset();
    return offset;

}

/**
 * @brief Balance::EtalonnerLaBalance
 * @detail cette fonction permet d'étalonner la balance et de sauvegarder le coefficient scale
 * @param poidEtalon
 * @return le coefficient scale
 */
float Balance::etalonnerLaBalance(float poidsEtalon) {

    scale = (leHX711.read_average(10) - leHX711.get_offset()) / poidsEtalon;

    leHX711.set_scale(scale);
    scale = leHX711.get_scale();
    return scale;
}

/**
 * @brief Balance::TarageEffectuer
 * @detail vérification si le tarage à été effectuer avant l'étalonnage
 * @return retourne l'état d'une variable boolean
 */
bool Balance::tarageEffectue() {
    return tarage;
}

/**
 * @brief Balance::ObtenirOffset
 * @detail récuperation du coefficient offset
 * @return retourne le  coefficient offset
 */
long Balance::obtenirOffset() {
    return leHX711.get_offset();
}

/**
 * @brief Balance::ObtenirScale
 * @detail récuperation du coefficient scale
 * @return retourne le  coefficient scale
 */
float Balance::obtenirScale() {
    return leHX711.get_scale();
}

/**
 * @brief Balance::ConfiguerOffset
 * @detail permet de configurer le coefficient offset, utilisé après la lecture de l'EEPROM
 * @param _offset
 */
void Balance::configuerOffset(long _offset) {

    leHX711.set_offset(_offset);
}

/**
 * @brief Balance::ConfiguerScale
 * @detail permet de configurer le coefficient scale, utilisé après la lecture de l'EEPROM
 * @param _scale
 */
void Balance::configuerScale(float _scale) {
    leHX711.set_scale(_scale);
}

/**
 * @brief Balance::afficherCoefficients
 * @detail Affiche les coefficients enregistrés en EEPROM
 */

void Balance::afficherCoefficients() {
    Serial.print("tarage effectué : ");
    Serial.println(EEPROM.readBool(adrTarageEffectue));
    Serial.print("offset : ");
    Serial.println(EEPROM.readLong(adrOffsetEeprom));
    Serial.print("scale : ");
    Serial.println(EEPROM.readFloat(adrScaleEeprom));
    Serial.print("unité : ");

    for (int i = 0; i < 10; i++) {
        byte readValue = EEPROM.readChar(adrUnite + i);
        if (readValue == 0) {
            break;
        }
        char readValueChar = char(readValue);
        Serial.print(readValueChar);
    }
    Serial.println(' ');
}

bool Balance::ecrireCoefficients() {

    EEPROM.writeLong(adrOffsetEeprom, offset);
    EEPROM.writeFloat(adrScaleEeprom, scale);
    EEPROM.writeBool(adrTarageEffectue, true);

    for (int i = 0; i < 10; i++) {
        EEPROM.writeChar(adrUnite + i, unite[i]);
    }
    return EEPROM.commit();
}

/**
 * @brief Balance::fixerUnite
 * @detail Enregistre l'unité de mesure utilisée
 * @param _unite
 */
void Balance::fixerUnite(char* _unite) {

    for (int i = 0; i < 10; i++) {
        unite[i] = _unite[i];
        EEPROM.writeChar(adrUnite + i, unite[i]);
    }
    EEPROM.commit();
}

char* Balance::obtenirUnite() {
    return unite;
}



