/* 
 * File:   main.ino.cpp
 * Author: philippe SIMIER
 * 
 * Filtrage numérique 
 * simulaltion d'un filtre du second ordre
 * Voir document sur https://www.f-legrand.fr/scidoc/docimg/sciphys/arduino/filtrage/filtrage.html
 * 
 * Created on 16 octobre 2021, 17:11
 */



#include <driver/adc.h>
#include <driver/dac.h>
#include <Arduino.h>
#include "Filter.h"

//Filter leFiltre;

#define TAILLE_TAMPON 0b00001000     // supérieure à max(na,nb) ici 8
#define MASQUE_TAMPON 0b00000111     // TAILLE_TAMPON-1

uint8_t nb = 2; // nombre de coefficients b
float b[2];     // tableau des coefficients b
uint8_t na = 2; // nombre de coefficients a
float a[2];     // tableau des coefficients a

int16_t x[TAILLE_TAMPON] = {0}; // tampon pour les x_n
int16_t y[TAILLE_TAMPON] = {0}; // tampon pour les y_n

uint8_t j = 0;                 // indice pour les tampons
uint8_t i = 0;
float accum;

void setup() {

    Serial.begin(115200);
    
    dac_output_enable(DAC_CHANNEL_1);
    
    adc1_config_width(ADC_WIDTH_BIT_9);                         // Résolution 9 bits
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11); // Atténuation 11 dB

    // Filtre passe bas du second ordre 
    b[0] = 0.084971;
    b[1] = 0.16994;
    b[2] = 0.084971;
    a[1] = -1.55193;
    a[2] = 0.89181;
    
    //leFiltre.begin();
    
}

void loop() {

    x[j] = adc1_get_raw(ADC1_CHANNEL_6) / 2; // Lecture de l'entrée analogique

    accum = 0;
    i = j;
    for (int k = 0; k < nb; k++) {
        accum += x[i] * b[k];
        i = (i - 1) & MASQUE_TAMPON;
    }
    
    i = (j - 1) & MASQUE_TAMPON;
    for (int k = 1; k < na; k++) {
        accum -= y[i] * a[k];
        i = (i - 1) & MASQUE_TAMPON;
    }
    
    y[j] = accum;
    j = (j + 1) & MASQUE_TAMPON;

    dac_output_voltage(DAC_CHANNEL_1, accum); // Ecriture de la sortie ananlogique

}

