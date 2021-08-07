#include <Arduino.h>
#include "Fsk.h"
#include "Ax25.h"
#include "Position.h"

#define BITRATE 1200

Fsk leFsk(1200, 1000);
Ax25 ax25(leFsk);

Position p1(48.010524, 0.205744, '>', "test unitaire p1"); 
Position p2(48.010524, 0.205744, '>', "test unitaire p2");

void setup() {
  Serial.begin(115200);
  Serial.println("Test APRS position");
  
  leFsk.begin();
  char srcCallsign[] = "F1ZMM-5";
  char dstCallsign[] = "F1ZMM-2";
  char path1[] = "WIDE1-1";
  char path2[] = "WIDE2-2";
  ax25.begin(BITRATE, srcCallsign, dstCallsign, path1, path2);
  ax25.txMessage(p2.getCompressedPduAprs());
  ax25.debug();
  Serial.println("Trame position envoyée");
  
  
}

void loop() {
    
}
