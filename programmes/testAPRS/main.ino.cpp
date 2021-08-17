#include <Arduino.h>
#include "Fsk.h"
#include "Ax25.h"
#include "Position.h"
#include "Message.h"
#include "Weather.h"
#include "Telemetry.h"

#define BITRATE 1200

Fsk leFsk(1200, 1000);
Ax25 ax25(leFsk);

Position p1(48.010524, 0.205744, "test unitaire p1");            // icon car
Position p2(48.010237, 0.206267, "test unitaire p2", '/', '[');  // icon Human
Weather  w3(47.816326, 0.113171);                                // a Weather station
Message  m1("Anthony", "test unitaire m1");
Message  m2("Philippe", "test unitaire m2", "0001");
Telemetry t1("F1ZMM-5");

 
void setup() {
    Serial.begin(115200);
    Serial.println("Test APRS position");

    leFsk.begin();
    char srcCallsign[] = "F1ZMM-5";
    char dstCallsign[] = "F1ZMM-2";
    char path1[]       = "WIDE1-1";
    char path2[]       = "WIDE2-2";
    ax25.begin(BITRATE, srcCallsign, dstCallsign, path1, path2);
    
    t1.setName(1, "tension");   t1.setUnit(1, "V");  t1.setEqn(1, 0, 0.1, 0);
    t1.setName(2, "courant");   t1.setUnit(2, "mA");
    t1.setName(3, "puiss");     t1.setUnit(3, "mW");
    t1.setName(4, "charge");    t1.setUnit(4, "mAh");
    t1.setName(5, "Taux");      t1.setUnit(5, "%");
    
}

void loop() {
    char c;
    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case '1':
                Serial.println("Position p2 trame normale sans altitude");
                ax25.txMessage(p1.getPduAprs());
                ax25.debug();
                break;
            case '2':
                Serial.println("Position p2 trame compressée avec altitude");
                p2.setAltitude(80);
                ax25.txMessage(p2.getPduAprs(true));
                ax25.debug();
                break;    
            case '3':
                Serial.println("Message sans numero");
                ax25.txMessage(m1.getPduAprs());
                ax25.debug();
                break;
            case '4':
                Serial.println("Message avec numero");
                ax25.txMessage(m2.getPduAprs());
                ax25.debug();
                break;
            case '5':
                Serial.println("Test weather report");
                w3.setWind(90);          // Direction du vent 
                w3.setSpeed(2.5);        // Vitesse moyenne du vent en m/s
                //w3.setGust(5.1);         // Vitesse en rafale en m/s
                w3.setTemp(25.5);        // Température en degré celsius
                w3.setRain(0);           // Pluie en mm/1h
                w3.setRain24(0);         // Pluie en mm/24h
                w3.setRainMid(0);        // Pluie en mm/depuit minuit
                w3.setHumidity(49);      // Hmidité relative en %
                w3.setPressure(1024.5);  // Pression barométrique en hPa
                
                ax25.txMessage(w3.getPduAprs());
                ax25.debug();
                break;
                
            case '6':
                Serial.println("test télémétrie");
                t1.setValue(1, 127);
                t1.setValue(2, 255);
                t1.setDigital(4,true);
                t1.setDigital(3,true);
                ax25.txMessage(t1.getValuePduAprs());
                ax25.debug();
                break;
                
            case '7':
                Serial.println("test télémétrie MetaData");
                ax25.txMessage(t1.getUnitPduAprs());
                ax25.debug();
                delay(1000);
                ax25.txMessage(t1.getNamePduAprs());
                ax25.debug();
                delay(1000);
                ax25.txMessage(t1.getEqnsPduAprs());
                ax25.debug();
                break;
                
        }
    }
}
