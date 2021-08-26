/*
 Utilisation de l'interface i2s dans l'ESP32 avec une tache
 

 */


#include "DdsI2s.h"

DdsI2s leDds(600); //init du bitrate

 
void setup() {
    Serial.begin(115200);  
    leDds.begin();

}

void loop() {
    
    char c;
    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case 's': leDds.stop();
                break;
            case 'a': leDds.start();
                break;
            case 'b': for (int n = 0; n < 200; n++) {
                    leDds.setFrequency(1000);
                    leDds.sendBit();
                    leDds.off();
                    leDds.sendBit();
                    leDds.off();
                }
                break;
            case '2': leDds.updateSampleRate(200);
                break;
            case '4': leDds.updateSampleRate(400);
                break;
            case 'f': leDds.setFrequency(1000);
                leDds.start();
                break;
            case 'g': leDds.setFrequency(2000);
                leDds.start();
                break;
        }
    }
}