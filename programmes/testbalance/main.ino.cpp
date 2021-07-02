/* 
 * File:   main.ino.cpp
 * Author: psimier
 *
 * Created on 28 juin 2021, 14:12
 */

#include "balance.h"

Balance *laBalance;


void setup() {
    int choix = 0;
    float poids_connu = 5000.0;
    laBalance = new Balance();
    Serial.begin(115200);
    
    
    Serial.println("Test de la balance");

    Serial.println(" Menu Balance, que souhaitez-vous faire ?");
    Serial.println("\n 1- Tarer la balance ");
    Serial.println(" 2- Etalonner la balance ");
    Serial.println(" 3- Afficher les coefficients ");
    Serial.println(" 4- Peser ");

    do {
        while (Serial.available() == 0) {
        }
        choix = Serial.read();

        switch (choix) {
            case '1':
                Serial.println("Vider le plateau et appuyer sur une touche pour tarer ");
                while (!Serial.available());
                while (Serial.available())
                    Serial.read();
                laBalance->tarerLaBalance();
                Serial.print("offset : ");
                Serial.println(laBalance->obtenirOffset());
                break;

            case '2':
                Serial.println("Posez le poids connu 5000g et  appuyez sur entrer ");
                
                while (!Serial.available());
                while (Serial.available()) Serial.read();
                Serial.println(poids_connu);
                laBalance->etalonnerLaBalance(poids_connu);
                Serial.print("scale : ");
                Serial.println(laBalance->obtenirScale());
                break;

            case '3':
                laBalance->afficherCoefficients();
                break;
        }

    } while (choix != '4');
}

void loop() {
    Serial.print(laBalance->peser());
    Serial.print(" g\t");
    Serial.println(laBalance->obtenirVariance());
    delay(1000);

}