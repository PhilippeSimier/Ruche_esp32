/* 
 * File:   main.ino.cpp
 * Author: philippe SIMIER
 * 
 * Filtrage numérique 
 * simulaltion d'un filtre du second ordre
 *  
 * Created on 16 octobre 2021, 17:11
 */



#include <driver/adc.h>
#include <driver/dac.h>
#include <Arduino.h>
#include "Filter.h"

Filter leFiltre(5000, ADC1_CHANNEL_6, DAC_CHANNEL_1);


void setup() {

    Serial.begin(115200);
    
    leFiltre.setLPFOrdre1(100);
    leFiltre.begin();
    
}

void loop() {   
}

