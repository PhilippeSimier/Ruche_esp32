/*
   Bridge Série pour modem SigFox 
 * Projet Ruche connectée
*/
#include <HardwareSerial.h>
#define LED 2   //The ESP32 has an internal blue LED at D2 (GPIO 02)


HardwareSerial serialSigfox(2);


void setup() {
  Serial.begin(115200);
  serialSigfox.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("Sigfox Serial Bridge");
  
  pinMode(LED, OUTPUT);
}



void loop() {
  
  char car;
  
  if (Serial.available() > 0) {
    car = Serial.read();
    serialSigfox.write(car);
    digitalWrite(LED, true); 
  }

  if (serialSigfox.available() > 0) {
    car = serialSigfox.read();
    Serial.write(car);
    digitalWrite(LED, false);
  }
  
}
