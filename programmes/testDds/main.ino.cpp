/*
   tests unitairs de la classe Dds 
   DAC sur GPIO25 (génération d'une sinusoide sur cette sortie)
   
   
 */

#include <Arduino.h>
#include "Dds.h"

#define SAMPLING_FREQUENCY 25000    //fréquence d'échantillonage
#define MARK 1200.0                 //fréquence mark
#define SHIFT 1000.0                //fréquence de shift pour calculer la fréquence space (space=mark+shift)
#define DAC_CHANNEL DAC_CHANNEL_1   //numéro du dac
#define SYNC GPIO_NUM_2             //gpio pour sync led et oscillo

#if ((10000000/SAMPLING_FREQUENCY)%10>0)
#error "Fréquence d'échantillonage incompatible avec la période du timer"
#endif

Dds leDds;

void setup() {
    Serial.begin(115200);
    leDds.begin(SAMPLING_FREQUENCY, MARK, SHIFT, DAC_CHANNEL, SYNC);
}

void loop() {
    char c;
    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case '0': leDds.stop(); //stop le dac
                Serial.println("stop");
                break;
            case '1': leDds.enableMark(); //sortie dds à 1200 hz
                Serial.println("Mark");
                break;
            case '2': leDds.enableSpace(); //sortie dds à 2200 hz
                Serial.println("Space");
                break;
            case '3': leDds.setFrequency(500); //change la fréquence du dds
                Serial.println("Fréquence 500");
                break;
            case '4': leDds.setFrequency(1000); //test le changement de phase 
                Serial.println("phase");
                for (int n = 0; n < 1000; n++) {
                    leDds.setPhase(0);
                    delay(10);
                    leDds.setPhase(180);
                    delay(10);
                }
                break;
        }
    }
}


