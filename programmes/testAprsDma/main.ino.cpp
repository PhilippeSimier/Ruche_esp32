/*
 Utilisation de l'interface i2s dans l'ESP32 avec une tache
 
 */


#include "Ax25.h"

Ax25 leAx25;
char srcCallsign[]  = "F1ZMM-5";
char dstCallsign[]  = "F1ZMM-2";
char path1[]        = "WIDE1-1";
char path2[]        = "WIDE2-2";

void setup() {
    Serial.begin(115200);
    leAx25.begin(srcCallsign, dstCallsign, path1, path2);

}

void loop() {

    char c;
    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case 'f': 
                leAx25.txMessage("!4753.41N/00016.61E>test");
                leAx25.debug();
                break;
        }
    }
}