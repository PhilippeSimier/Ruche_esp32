/* 
 * File:   main.ino.cpp
 * Author: philippe
 *
 * Created on 12 juillet 2021, 11:05
 */

#include "sigfox.h"
#include "trame.h"
#define LED 2   //The ESP32 has an internal blue LED at D2 (GPIO 02)


Sigfox mySigfox(16, 17, 2, false);
trameMesure laTrame;

void setup() {

    Serial.begin(115200);
    Serial.println("Programme test Sigfox");

    pinMode(LED, OUTPUT);
    mySigfox.begin();
    
    Serial.printf("Test : %s\r", mySigfox.tester());
    Serial.printf("ID : %s\r", mySigfox.obtenirID());
    Serial.print("PAC : ");
    Serial.println(mySigfox.obtenirPAC());
    Serial.printf("Fréquence d'émission : %.2f Mhz\r", mySigfox.obtenirFreqEmi());
    Serial.printf("Fréquence de réception : %.2f Mhz\r", mySigfox.obtenirFreqRec());
    
    float V0, V1;
    mySigfox.obtenirTension(V0,V1);
    Serial.printf("Tension d'alimentation : %.2f V\r", V0);
    Serial.printf("Tension d'émission : %.2f V\r", V1);
    
    laTrame.type = 1;
    laTrame.humidite = 55;
    laTrame.poids = 1024;
    laTrame.temperature = 234;
    
    bool status = mySigfox.envoyer(&laTrame, sizeof(laTrame));
    if (status){
        Serial.println("trame envoyée avec succès");
    }
    
}

void loop() {
    
    

}

