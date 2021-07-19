/* 
 * File:   main.ino.cpp
 * Author: philippe
 *
 * Created on 17 juillet 2021, 16:59
 * brief:  Programme pour tester le BP (GPIO34) avec une interuption
 * doc https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html
 */

#include <Arduino.h>
#include "Compteur.h"


Compteur leCompteur;


void setup() {
    pinMode(34, INPUT);  //This pin doesn't have internal pull-ups or pull-down resistors.
    pinMode(2, OUTPUT);
    Serial.begin(115200);
    Serial.println("Test BP");

    digitalWrite(2, 1);
    
    leCompteur.begin(34);
}

void loop() {
    printf("compteur : %d\r\n", leCompteur.getValue());
    delay(10000);
}
