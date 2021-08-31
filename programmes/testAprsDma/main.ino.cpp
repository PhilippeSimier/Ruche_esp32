/*
 Utilisation de l'interface i2s dans l'ESP32 avec une tache
 
 */


#include "Ax25.h"
#include "Position.h"
#include "DRA818.h"

#define DRA_TYPE DRA818_VHF  // or DRA818_UHF
#define TX_RX_FREQUENCY 144.800

Ax25 ax25;
DRA818 dra;

Position p2(48.010237, 0.206267, "test unitaire p2", '/', '['); // icon Human

void setup() {
    Serial.begin(115200);

    char srcCallsign[] = "F1ZMM-5";
    char dstCallsign[] = "F1ZMM-2";
    char path1[] = "WIDE1-1";
    char path2[] = "WIDE2-2";
    ax25.begin(srcCallsign, dstCallsign, path1, path2);

    uint8_t ret;
    //modelDra, freq_rx, freq_tx, squelch, vol, ctcss_rx, ctcss_tx, bandwidth, pre, high, low

    ret = dra.configure(DRA_TYPE, TX_RX_FREQUENCY, TX_RX_FREQUENCY, 4, 8, 0, 0, DRA818_12K5, true, true, true);
    if (!ret) {
        Serial.println("\nError while configuring DRA818");
    } else {
        Serial.println("DRA818 configuration finished");
    }
}

void loop() {

    char c;
    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case 'f':
                ax25.txMessage("!4753.41N/00016.61E>test");
                ax25.debug();
                break;
            case 'p':
                Serial.println("Position p2 trame compressée avec altitude");
                p2.setAltitude(80);
                ax25.txMessage(p2.getPduAprs(true));
                ax25.debug();
                break;
        }
    }
}