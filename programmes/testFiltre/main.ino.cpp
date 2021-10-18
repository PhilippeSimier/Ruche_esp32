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

#define TAILLE_TAMPON 16     // supérieure a la taille du tableau des coefficients ici 16
#define MASQUE_TAMPON 15     // TAILLE_TAMPON-1

float a[2];     // tableau des coefficients a
float b[2];     // tableau des coefficients b


float x[TAILLE_TAMPON] = {0}; // tampon pour les x_n
float y[TAILLE_TAMPON] = {0}; // tampon pour les y_n


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
    
    float accum;
    static uint8_t n = 0;
    
    x[n] = adc1_get_raw(ADC1_CHANNEL_6); // Lecture de l'entrée analogique
    
    // Calcul de l'équation de récurrence
    accum  = b[0] * x[ n    & MASQUE_TAMPON];
    accum += b[1] * x[(n-1) & MASQUE_TAMPON];
    accum += b[2] * x[(n-2) & MASQUE_TAMPON];
    accum -= a[1] * y[(n-1) & MASQUE_TAMPON];
    accum -= a[2] * y[(n-2) & MASQUE_TAMPON];  
    y[n] = accum;
    
    dac_output_voltage(DAC_CHANNEL_1, y[n] / 2); // Ecriture de la sortie analogique
    n = (n + 1) & MASQUE_TAMPON;
}

