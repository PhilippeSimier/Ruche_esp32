/* test dela classe Ax25
   Author: Anthony
   Envoi d'une trame APRS de test
   L'APRS © est un protocole de Bob Bruninga WB4APR
*/



#include "Fsk.h"
#include "Ax25.h"


#define SOURCE_CALLSIGN "F1ZMM-1"
#define DESTINATON_CALLSIGN "F1ZMM-2"
#define PATH1 "WIDE1-1"
#define PATH2 "WIDE2-2"
#define APRS1 "/115570h4800.00N/00012.21E>73Touchard"
#define APRS2 "/124200z4759.20N/00012.00E_.../...g...t072r...p...P...h45b10158ALEC"
#define APRS3 "!4800.00N/00012.21E>Test position Temps reel"
#define BITRATE 1200


Fsk leFsk(1200, 1000);
Ax25 ax25(leFsk);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  leFsk.begin();
  char srcCallsign[] = SOURCE_CALLSIGN;
  char dstCallsign[] = DESTINATON_CALLSIGN;
  char path1[] = PATH1;
  char path2[] = PATH2;
  ax25.begin(BITRATE, srcCallsign, dstCallsign, path1, path2);
}

void loop() {
  char c = 0;
  char aprs1[] = APRS1;
  char aprs2[] = APRS2;
  char aprs3[] = APRS3;
  if (Serial.available() > 0) {
    c = Serial.read();
    switch (c) {
      case '1': ax25.txMessage(aprs1);
        ax25.debug();
        Serial.println("Trame envoyée");
        break;

      case '2': ax25.txMessage(aprs2);
        ax25.debug();
        Serial.println("Trame envoyée");
        break;
        
      case '3': ax25.txMessage(aprs3);
        ax25.debug();
        Serial.println("Trame envoyée");
        break;  
    }
  }
}