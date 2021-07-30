/*
   tests unitairs de la classe Psk
 * la classe Psk hérite de Dds 
   DAC sur GPIO25 (génération d'une sinusoide sur cette sortie)
   
   
 */

#include <Arduino.h>
#include "Psk.h"


Psk lePsk(992,31);

void setup() {
    Serial.begin(115200);
    lePsk.begin();
    lePsk.stop();
    Serial.println("Test PSK");
    
}

void loop() {
    char c = 0;
    int i;

    if (Serial.available()) {
        c = Serial.read();
        switch (c) {

            case '1':
                Serial.println("test méthode Psk::sendBitPhase");
                delay(5000);
                lePsk.setFrequency(992);
                for (i = 0; i < 10; i++) {
                    lePsk.sendBitPhase(0);
                    lePsk.sendBitPhase(180);
                }
                lePsk.stop();


                break;

            case '2':
                Serial.println("test methode tx(\"Bonjour le monde....\")");


                break;




        }
    }
}

