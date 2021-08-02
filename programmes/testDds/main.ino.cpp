/*
   tests unitairs de la classe Dds et Fsk
 * la classe Fsk hérite de Dds 
   DAC sur GPIO25 (génération d'une sinusoide sur cette sortie)
   
   
 */

#include <Arduino.h>
#include "Fsk.h"


Fsk leFsk(1200,1000,300);  // Mark, shift, baudRate

void setup() {
    Serial.begin(115200);
    leFsk.begin();
    leFsk.start();
}

void loop() {
    char c=0;
    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case '0': leFsk.stop(); //stop le dac
                Serial.println("stop");
                break;
            case '1': leFsk.setFrequency(1200); //sortie dds à 1200 hz
                Serial.println("Mark 1200");
                break;
            case '2': leFsk.setFrequency(2200); //sortie dds à 2200 hz
                Serial.println("Space 2200");
                break;
            case '3': leFsk.setFrequency(500); //change la fréquence du dds
                Serial.println("Fréquence 500");
                break;
            case '4': leFsk.setAttenuation(dB_6); //change l'amplitude attenuation 6dB
                Serial.println("Attenution de l'amplitude 6dB");
                break;    
            case '5': leFsk.setAttenuation(dB_12); //change l'amplitude attenuation 12dB
                Serial.println("Attenution de l'amplitude 12dB");
                break;   
            case '6': leFsk.setAttenuation(dB_18); //change l'amplitude attenuation 18dB
                Serial.println("Attenution de l'amplitude 18dB");
                break;     
            case '7': leFsk.setAttenuation(dB_24); //change l'amplitude attenuation 24dB
                Serial.println("Attenution de l'amplitude 24dB");
                break;        
            case '8': 
                Serial.println("setbit à 300 bauds");
                leFsk.setBitRate(300);
                for (int n = 0; n < 450; n++) {  // Trame de 01 (900 bits) durée 3s
                    leFsk.sendBit(0);
                    leFsk.sendBit(1);
                }
                leFsk.stop();
                break;
            case '9': 
                Serial.println("setbit à 45.5 bauds 1000 Hz 1170 Hz");
                leFsk.setBitRate(45.5);
                leFsk.setMarkFrequence(1000);
                leFsk.setSpaceFrequence(1170);
                for (int n = 0; n < 90; n++) {    // Trame de 01 (180 bits) durée 4s
                    leFsk.sendBit(0);
                    leFsk.sendBit(1);
                    //leFsk.sendBitOff();
                }
                leFsk.stop();
                break;    
        }
    }
}


