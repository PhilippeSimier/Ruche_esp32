/* 
 * File:   main.ino.cpp
 * Author: philippe S (SNIR Touchard)
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
    
    
    laTrame.field1 = 4413;  // Masse
    laTrame.field2 = 3579;  // Température
    laTrame.field3 = 10142; // Pression
    laTrame.field5 = 7944;  // Eclairement
    laTrame.field6 = 2234;  // Point de rosée
    laTrame.field4 = 46;    // Humidité
    
    
    bool status = mySigfox.envoyer(&laTrame, sizeof(laTrame));
    if (status){
        Serial.println("trame envoyée avec succès");
    }
    
}

void loop() {
    
    

}

