/*
 Utilisation de l'interface i2s dans l'ESP32 avec une tache
 */


#include "Fx25.h"
#include "Position.h"

Fx25* fx25;

Position p2(48.010237, 0.206267, "test unitaire p2", '/', '['); // icon Human

void setup() {
    Serial.begin(115200);
    fx25 = new Fx25();
    char srcCallsign[] = "F1ZMM-5";
    char dstCallsign[] = "F1ZMM-2";
    char path1[] = "WIDE1-1";
    char path2[] = "WIDE2-2";
    fx25->begin(srcCallsign, dstCallsign, path1, path2);
    fx25->setFec(true);  // La trame Ax25 est encapsulée dans une trame Fec

}

void loop() {

    char c;
    char trameAPRS[] = "!4753.41N/00016.61E>test";
    
    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case 'f':
                
                fx25->txMessage(trameAPRS);                
                break;
                
            case 'p':
                
                Serial.println("Position p2 trame compressée avec altitude");
                p2.setAltitude(80);
                fx25->txMessage(p2.getPduAprs(true));
                break;
        }
    }
}