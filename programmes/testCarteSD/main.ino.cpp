/* 
 * File:   main.ino.cpp
 * Author: Anthony le Cren
 *
 * Created on 4 septembre 2021, 09:01
 */

#include "Msdcard.h"

Msdcard cartesd(18, 19, 23, 5); //SCK,MISO,MOSI,ss

void setup() {

    Serial.begin(115200);
    bool erreur;
    erreur = cartesd.begin();
    if (erreur == false) {
        
        cartesd.writeFile(SD, "/hello.txt", "Hello ");
        cartesd.appendFile(SD, "/hello.txt", "World!\n");
    }
}

void loop() {


}

