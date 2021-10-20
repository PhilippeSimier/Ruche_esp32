/* 
 * File:   main.ino.cpp
 * Author: philippe SIMIER
 * 
 * Filtrage numérique 
 * 
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

    leFiltre.setLPFOrdre1(500);
    leFiltre.printEquaReccurence(&Serial);
    leFiltre.begin();

}

void loop() {
    char c = 0;
    // Coefficient pour un filtre du second ordre  m = 0.1
    float a[3] = {0.084971 , 0.16994 , 0.084971};
    float b[3] = {0.0      , 1.55193 ,-0.89181};
    
    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case '1':
                Serial.println("F coupure 100Hz");
                leFiltre.setLPFOrdre1(100);
                break;

            case '2':
                Serial.println("F coupure 200Hz");
                leFiltre.setLPFOrdre1(200);
                break;

            case '5':
                Serial.println("F coupure 500Hz");
                leFiltre.setLPFOrdre1(500);
                break;
                
            case '6':
                Serial.println("Filtre du second ordre m = 0.1");
                
                leFiltre.setEquaReccurence(a,b);
                break;
                
            case 'e':
                leFiltre.printEquaReccurence(&Serial);
                break;
        }
    }
}

