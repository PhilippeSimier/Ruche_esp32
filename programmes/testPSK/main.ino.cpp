/*
   tests unitairs de la classe Psk
 * la classe Psk hérite de Dds 
   
   
   
 */

#include <Arduino.h>
#include "Psk.h"


Psk lePsk(1000, 31.25);
  

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
    char message[] = "Bonjour test unitaire pour PSK31\r";
    
    if (Serial.available()) {
        c = Serial.read();
        switch (c) {

            case '1':
                Serial.println("test méthode Psk::send Idle");
                
                lePsk.setFrequency(1000);
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
                        lePsk.setFrequency(1000);
                        message[0] = car;
                        lePsk.tx(message,BPSK);
                        
                    }
                } while (car != 27 && car != 3);
                break;
                
            case '3':
                Serial.println("Pas d'attenuation");
                Serial.println(message);
                lePsk.setAttenuation(dB_O);
                lePsk.setFrequency(1000);               
                lePsk.tx(message, BPSK);
                break;
                
            case '4':
                Serial.println("attenuation 18 dB");
                Serial.println(message);
                lePsk.setAttenuation(dB_18);
                lePsk.setFrequency(1000);               
                lePsk.tx(message, BPSK);
                break; 
                
            case '5':
                Serial.println("attenuation 24 dB");
                Serial.println(message);
                lePsk.setAttenuation(dB_24);
                lePsk.setFrequency(1000);               
                lePsk.tx(message, BPSK);
                break;    
        }
    }
}

