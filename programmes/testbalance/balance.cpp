/* 
 * File:   balance.cpp
 * Author: psimier
 * 
 * Created on 28 juin 2021, 14:16
 */

#include "balance.h"


Balance::Balance(int dout, int sck, int gain, int _adrOffsetEeprom,int _adrScaleEeprom):
    adrOffsetEeprom(_adrOffsetEeprom),
    adrScaleEeprom(_adrScaleEeprom)
{
    EEPROM.begin(EEPROM_SIZE);
    tarage = false;
    leHX711.begin(dout, sck, gain);
    
    offset = EEPROM.readDouble(adrOffsetEeprom);
    leHX711.set_offset(offset);
    scale = EEPROM.readDouble(adrScaleEeprom);
    leHX711.set_scale(scale);
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
        tab[i] = leHX711.get_units(1);
        delay(20);
    }

    for (int i = 0; i < TAILLEMAX - 1; i++) 
        for (int j = i+1; j < TAILLEMAX; j++) 
            if (tab[i] < tab[j]) {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[i] = tmp;
            }
        
    return tab[TAILLEMAX/2];
}

 
/**
 * @brief  Méthode pour obtenir la variance de la dernière série
 * @return  float la variance
 */
float Balance::obtenirVariance(){
    
    float moyenne = calculerMoyenne();
    float k = 0;
    for(unsigned int i=0 ; i<TAILLEMAX ; i++)
        k += (tab[i]-moyenne)*(tab[i]-moyenne);
    return 1000 * k/(float)TAILLEMAX;
}

/**
 * @brief  Méthode pour calculer la moyenne de la dernière série
 * @return la moyenne de la dernière série
 */
float Balance::calculerMoyenne(){
    
    float k=0;
    for(unsigned int i=0 ; i<TAILLEMAX ; i++)
    {
        k = k + tab[i];
    }

    k = k/TAILLEMAX;
    return k;
}

/**
 * @brief Balance::tarerLaBalance
 * @detail cette fonction permet de tarer la balance et de sauvegarder le coefficient offset
 */
void Balance::tarerLaBalance() {


    leHX711.tare();
    tarage = true;
    offset = leHX711.get_offset();
    EEPROM.writeDouble(adrOffsetEeprom, offset);
    EEPROM.commit();
    }

/**
 * @brief Balance::EtalonnerLaBalance
 * @detail cette fonction permet d'étalonner la balance et de sauvegarder le coefficient scale
 * @param poidEtalon
 * @return le coefficient scale
 */
float Balance::etalonnerLaBalance(float poidEtalon) {

    float scale = (leHX711.read_average(10) - leHX711.get_offset()) / (poidEtalon);

    leHX711.set_scale(scale);
    scale = leHX711.get_scale();
    EEPROM.writeDouble(adrScaleEeprom, scale); 
    EEPROM.commit();
    return scale;
}

/**
 * @brief Balance::TarageEffectuer
 * @detail vérification si le tarage à été effectuer avant l'étalonnage
 * @return retourne l'état d'une variable boolean
 */
bool Balance::tarageEffectuer() {
    return tarage;
}
/**
 * @brief Balance::ObtenirOffset
 * @detail récuperation du coefficient offset
 * @return retourne le  coefficient offset
 */
float Balance::obtenirOffset() {
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
void Balance::configuerOffset(float _offset) {
     
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



