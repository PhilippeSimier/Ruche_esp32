/*
   tests unitairs de la classe Psk
 * la classe Psk hérite de Dds 
    
 */

#include <Arduino.h>
#include "Psk.h"


Psk lePsk(1000, 31.25, QPSK);    // fréquence de la porteuse 1000Hz débit de symboles 31.25 Bauds (31.25 * 32 = 1000 Hz)
  

void setup() {
    Serial.begin(115200);
    lePsk.begin();
    lePsk.stop();
    Serial.println("Test PSK");
    
}

void loop() {
    char car = 0;
    char c = 0;
    int i;
    char message[] = "Bonjour test unitaire pour QPSK31\r";
    
    if (Serial.available()) {
        c = Serial.read();
        switch (c) {

            case '1':
                Serial.println("test méthode Psk::send Idle");
                lePsk.start();
                lePsk.idle(31);
                lePsk.stop();
                break;

            case '2':
                message[1] = '\0';
                Serial.println("test message au clavier (echap pour quitter)");
                car = '\0';
                
                do {
                    if (Serial.available()) {
                        car = Serial.read();
                        message[0] = car;
                        lePsk.tx(message);
                        
                    }
                } while (car != 27 && car != 3);
                break;
                
            case '3':
                Serial.println("Pas d'attenuation 0 dB");
                Serial.println(message);
                lePsk.setAttenuation(dB_0);               
                lePsk.tx(message);
                break;
                
            case '4':
                Serial.println("attenuation 18 dB");
                Serial.println(message);
                lePsk.setAttenuation(dB_18);               
                lePsk.tx(message);
                break; 
                
            case '5':
                Serial.println("attenuation 24 dB");
                Serial.println(message);
                lePsk.setAttenuation(dB_24);
                lePsk.tx(message);
                break;    
        }
    }
}

