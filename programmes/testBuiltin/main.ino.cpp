/* 
 * File:   main.ino.cpp
 * Author: philippe
 *
 * Created on 14 septembre 2021, 11:45
 */
#include "Arduino.h"

int LED = 02;

void setup() {
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    int nb = 0;
    assert(nb = __builtin_popcountll(0X1F));
    Serial.print(" nb = ");
    Serial.println(nb);

}

void loop() {
    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
    delay(200); // wait for a second
    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
    delay(1000); // wait for a second
}
