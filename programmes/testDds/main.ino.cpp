/*
   tests unitairs de la classe Dds et Fsk
 * la classe Fsk hérite de Dds 
   DAC sur GPIO25 (génération d'une sinusoide sur cette sortie)
   
   
 */

#include <Arduino.h>
#include "Fsk.h"


Fsk leFsk;

void setup() {
    Serial.begin(115200);
    leFsk.begin();
}

void loop() {
    char c=0;
    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case '0': leFsk.stop(); //stop le dac
                Serial.println("stop");
                break;
            case '1': leFsk.enableMark(); //sortie dds à 1200 hz
                Serial.println("Mark");
                break;
            case '2': leFsk.enableSpace(); //sortie dds à 2200 hz
                Serial.println("Space");
                break;
            case '3': leFsk.setFrequency(500); //change la fréquence du dds
                Serial.println("Fréquence 500");
                break;
            case '4': 
                Serial.println("setbit à 300 bauds");
                leFsk.setBitRate(300);
                for (int n = 0; n < 1000; n++) {
                    leFsk.sendBit(0);
                    leFsk.sendBit(1);
                    leFsk.sendBitOff();
                }
                break;
        }
    }
}


