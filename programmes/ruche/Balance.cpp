/**
 * @file balance.cpp
 * @brief Implémentation de la classe Balance
 * @author GUITTON Baptiste
 * @date 22/03/2021
 * @details Classe récupérant les informations et le paramatrage relatif à la balance
 * 
 */


#include "Balance.h"
#define TAILLEMAX 11
/**
 * @brief Balance::Balance
 * @param dout
 * @param sck
 * @param gain
 * @detail Constructeur de la classe Balance , permet l'initialisation du capteur HX711
 */
Balance::Balance(int dout, int sck, int gain) {
    tarage = false;

    leHX711 = new HX711();
    leHX711->begin(dout, sck, gain);
}

Balance::Balance(const Balance& orig) {
}

Balance::~Balance() {
    delete leHX711;
}
/**
 * @brief Balance::Peser
 * @detail cette fonction permet d'intéroger le capteurs 11 fois , de trier les données de de retourné la mediane
 * @return poids en kilogramme
 */
float Balance::Peser() {


    float tab[TAILLEMAX];
    float reserve;
    for (int i = 0; i < TAILLEMAX; i++) {
        tab[i] = (leHX711->get_units(1));
    }

    for (int n = 0; n < TAILLEMAX; n++) {
        for (int p = 0; p < TAILLEMAX; p++) {
            if (tab[n] < tab[p]) {
                reserve = tab[n];
                tab[n] = tab[p];
                tab[p] = reserve;
            }
        }
    }

    return tab[5] / 1000;
}
/**
 * @brief Balance::TarerLaBalance
 * @detail cette fonction permet de tarer la balance et de sauvegarder le coefficient offset
 */
void Balance::TarerLaBalance() {


    leHX711->tare();
    tarage = true;
    offset = leHX711->get_offset();
    }
/**
 * @brief Balance::EtalonnerLaBalance
 * @detail cette fonction permet d'étalonner la balance et de sauvegarder le coefficient scale
 * @param poidEtalon
 * @return le coefficient scale
 */
float Balance::EtalonnerLaBalance(float poidEtalon) {

    float scale = (leHX711->read_average(10) - leHX711->get_offset()) / (poidEtalon);

    leHX711->set_scale(scale);
    scale = leHX711->get_scale();
    //Serial.println(leHX711->get_offset());

    return leHX711->get_scale();
}
/**
 * @brief Balance::TarageEffectuer
 * @detail vérification si le tarage à été effectuer avant l'étalonnage
 * @return retourne l'état d'une variable boolean
 */
bool Balance::TarageEffectuer() {
    return tarage;
}
/**
 * @brief Balance::ObtenirOffset
 * @detail récuperation du coefficient offset
 * @return retourne le  coefficient offset
 */
float Balance::ObtenirOffset() {
    return leHX711->get_offset();
}
/**
 * @brief Balance::ObtenirScale
 * @detail récuperation du coefficient scale
 * @return retourne le  coefficient scale
 */
float Balance::ObtenirScale() { 
    return leHX711->get_scale();
}
/**
 * @brief Balance::ConfiguerOffset
 * @detail permet de configurer le coefficient offset, utilisé après la lecture de l'EEPROM
 * @param _offset
 */
void Balance::ConfiguerOffset(float _offset) {
    //Serial.print(" offset fonction config: ");
    //Serial.println(_offset);


    leHX711->set_offset(_offset);
}
/**
 * @brief Balance::ConfiguerScale
 * @detail permet de configurer le coefficient scale, utilisé après la lecture de l'EEPROM
 * @param _scale
 */
void Balance::ConfiguerScale(float _scale) {
    //Serial.print(" scale fonction config: ");
    //Serial.println(_scale);

    leHX711->set_scale(_scale);
}