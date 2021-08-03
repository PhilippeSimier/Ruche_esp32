#include <Arduino.h>
#include "FeldHell.h"

FeldHell* leFeldHell;

void setup() {
    Serial.begin(115200);
    Serial.println("Programme test FeldHell");
    leFeldHell = new FeldHell();
}

void loop() {
    
    char message[] = "Test Feld Hell....\r";
    char c;
    if (Serial.available()) {
        c = Serial.read();
        switch (c) {                
            case '1':
                
                Serial.println("test méthode tx(\"Test LeFeldHell->tx\")");
               
                leFeldHell->tx(message);
                break;
                
               
        }
    }
}
    


