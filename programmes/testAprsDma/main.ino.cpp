/*
 Utilisation de l'interface i2s dans l'ESP32 avec une tache
 */


#include "Ax25.h"
#include "Position.h"

Ax25* ax25;

Position p2(48.010237, 0.206267, "test unitaire p2", '/', '['); // icon Human

void setup() {
    Serial.begin(115200);
    ax25 = new Ax25();
    char srcCallsign[] = "F1ZMM-5";
    char dstCallsign[] = "F1ZMM-2";
    char path1[] = "WIDE1-1";
    char path2[] = "WIDE2-2";
    ax25->begin(srcCallsign, dstCallsign, path1, path2);
    ax25->setFec(true);  // La trame Ax25 est encapsulée dans une trame Fec

}

void loop() {

    char c;
    char trameAPRS[] = "!4753.41N/00016.61E>test";
    
    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case 'f':
                
                ax25->txMessage(trameAPRS);                
                break;
                
            case 'p':
                
                Serial.println("Position p2 trame compressée avec altitude");
                p2.setAltitude(80);
                ax25->txMessage(p2.getPduAprs(true));
                break;
        }
    }
}