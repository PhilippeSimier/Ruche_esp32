/* 
 * File:   main.ino.cpp
 * Author: ale & philippe
 *
 * Created on 14 septembre 2021, 11:45
 */
#include "Arduino.h"
#include "Rs.h"

int LED = 02;
Rs leRs;

uint8_t preload[] = {0x8C, 0x62, 0xB4, 0x9A, 0x9A, 0x40, 0x64, 0x8C, 0x62, 0xB4, 0x9A, 0x9A,
    0x40, 0x6A, 0xAE, 0x92, 0x88, 0x8A, 0x62, 0x40, 0x62, 0xAE, 0x92, 0x88, 0x8A, 0x64, 0x40,
    0x65, 0x3, 0xF0, 0x21, 0x34, 0x37, 0x35, 0x33, 0x2E, 0x34, 0x31, 0x4E, 0x2F, 0x30, 0x30,
    0x30, 0x31, 0x36, 0x2E, 0x36, 0x31, 0x45, 0x3E, 0x74, 0x65, 0x73, 0x74, 0x65, 0xE2};

void setup() {
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    
    printf("Affiche toute les trames possible à partir du payload\n");

    for (int i = 100 + CTAG_MIN; i <= 100 + CTAG_MAX; i++) {
        leRs.fx25_print_all_frame(0, preload, (int) sizeof (preload), i);
    }
    
    uint8_t radio[268];
    int radioLen;
    
    leRs.fx25Generate (preload, (int) sizeof (preload),radio,&radioLen, 1);

    printf("Bilan de la trame FX.25 : %d data bytes\n", radioLen);
    leRs.fx_hex_dump(radio,radioLen);
}

void loop() {
    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
    delay(200); // wait for a second
    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
    delay(1000); // wait for a second
}
