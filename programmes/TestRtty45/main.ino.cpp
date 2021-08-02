/*
   tests unitairs de la classe Rtty
 * la classe Fsk hérite de Dds 
   DAC sur GPIO25 (génération d'une sinusoide sur cette sortie)
   
   
 */

#include <Arduino.h>
#include "Rtty.h"


Rtty* leRtty45;


void setup() {
    Serial.begin(115200);
    leRtty45 = new Rtty(1000, 170, 45);
    

}

void loop() {
    char c = 0;
    char message[] = "Test RTTY a 45 Bauds....\n";
    char car;
    
    if (Serial.available()) {
        c = Serial.read();
        switch (c) {                
            case '1':
                
                Serial.println("test methode tx(\"Test RTTY a 45 Bauds....\")");
               
                leRtty45->tx(message);
                break;
                
               
        }
    }
}


