#include <Arduino.h>
#include "Position.h"

Position p1(47.890242, 0.276770, '>', "Ballon");  

void setup() {
  Serial.begin(115200);
  Serial.println("Test APRS position");
  
  
}

void loop() {
    Serial.println(p1.getPduAprs());
    delay(1000);
}
