/*
   tests unitairs de la classe Rtty45
 * la classe Fsk hérite de Dds 
   DAC sur GPIO25 (génération d'une sinusoide sur cette sortie)
   
   
 */

#include <Arduino.h>
#include "Rtty.h"


Rtty* leRtty;

void setup() {
    Serial.begin(115200);
    leRtty = new Rtty(1000, 170, 50);

}

void loop() {
    char c = 0;
    char message[] = "Bonjour le monde....\n";
    char car;
    
    if (Serial.available()) {
        c = Serial.read();
        switch (c) {

            case '1':
                Serial.println("test methode txByte(22)");

                leRtty->txByte(31); //  Letter mode enable
                leRtty->txByte(4); //  space
                leRtty->txByte(4); //  space
                leRtty->txByte(4); //  space
                leRtty->txByte(16); //  T
                leRtty->txByte(1); //  E
                leRtty->txByte(5); //  S
                leRtty->txByte(16); //  T
                leRtty->txByte(8); //  CR
                leRtty->txByte(2); //  LF
                leRtty->stop();
                break;
                
            case '2':
                Serial.println("test methode tx(\"Bonjour le monde....\")");
                
                leRtty->tx(message);
                break;
                
            case '3':
                Serial.println("test message au clavier (echap pour quitter)");
                car = '\0';
                leRtty->txByte(31); //  Letter mode enable
                do {
                    if (Serial.available()) {
                        car = Serial.read();
                        leRtty->txChar(car);
                    }
                } while (car != 27 && car != 3);
                break;
        }
    }
}


