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
    // Coefficients pour un filtre du second ordre  m = 0.1
    float a1[3] = {0.0      , -1.55193 , 0.89181};
    float b1[3] = {0.084971 ,  0.16994 , 0.084971};
    
    // Coefficients pour un filtre du premier ordre  fc=50
    float a2[3] = {1.0      , -0.9390625, 0.0};
    float b2[3] = {0.030468 , 0.030468 , 0.0};
    
    // Coefficient pour un filtre 2 pôles Chebyshev
    float a3[3] = {1.0      , -1.916900, +0.92043911};
    float b3[3] = {0.000884 , 0.001769 , 0.000884};
    
    
    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case '0':
                Serial.println("Filtre PB premier ordre fc = 50hz");
                
                leFiltre.setEquaReccurence(a2,b2);
                leFiltre.printEquaReccurence(&Serial);
                break;
            
            case '1':
                Serial.println("F coupure 100Hz");
                leFiltre.setLPFOrdre1(100);
                leFiltre.printEquaReccurence(&Serial);
                break;

            case '2':
                Serial.println("F coupure 200Hz");
                leFiltre.setLPFOrdre1(200);
                leFiltre.printEquaReccurence(&Serial);
                break;

            case '5':
                Serial.println("F coupure 500Hz");
                leFiltre.setLPFOrdre1(500);
                leFiltre.printEquaReccurence(&Serial);
                break;
                
            case '6':
                Serial.println("Filtre du second ordre m = 0.1");
                
                leFiltre.setEquaReccurence(a1,b1);
                leFiltre.printEquaReccurence(&Serial);
                break;
                
            case '7':
                Serial.println("Filtre 2 pôles Chebyshev fc = 50hz");
                
                leFiltre.setEquaReccurence(a3,b3);
                leFiltre.printEquaReccurence(&Serial);
                break;    
                
            case 'e':
                leFiltre.printEquaReccurence(&Serial);
                break;
        }
    }
}

