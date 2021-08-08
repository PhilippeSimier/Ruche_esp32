#include <Arduino.h>
#include "Fsk.h"
#include "Ax25.h"
#include "Position.h"
#include "Message.h"

#define BITRATE 1200

Fsk leFsk(1200, 1000);
Ax25 ax25(leFsk);

Position p1(48.010524, 0.205744, '>', "test unitaire p1"); 
Position p2(48.010524, 0.205744, '>', "test unitaire p2");
Message  m1("Anthony",  "test unitaire m1"); 
Message  m2("Philippe", "test unitaire m2", "0001");

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
  delay(10000);
  ax25.txMessage(m1.getPduAprs());
  delay(10000);
  ax25.txMessage(m2.getPduAprs());
}

void loop() {
    
}
