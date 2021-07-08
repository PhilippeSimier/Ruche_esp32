/* 
 * File:   main.ino.cpp
 * Author: psimier
 *
 * Created on 28 juin 2021, 14:12
 */

#include "balance.h"
#include "scan.h"


Balance *laBalance;
char unite[10] = {};

void setup() {
    int choix = 0;
    float poids_connu = 0.0;   
    laBalance = new Balance(13,15);
    
    Serial.begin(115200);
    
    
    
    Serial.println(" Menu Balance, que souhaitez-vous faire ?");
    Serial.println("\n 1- Tarer la balance ");
    Serial.println(" 2- Etalonner la balance ");
    Serial.println(" 3- Afficher les coefficients ");
    Serial.println(" 4- Peser ");
    Serial.println(" 5- Configurer l'unité ");
    Serial.println(" 6- Enregistrer les coefficients ");

    do {
        while (Serial.available() == 0) {}
        choix = Serial.read();

        switch (choix) {
            case '1':
                Serial.println("\rVider le plateau et appuyer sur entrer pour tarer ");
                Scan::confirmer();
                laBalance->tarerLaBalance();
                Serial.print("offset : ");
                Serial.println(laBalance->obtenirOffset());
                break;

            case '2':
                Serial.println("\rDonnez la valeur du poids connu ");
                
                poids_connu = Scan::lireFloat();
                Serial.println("\rPosez le poids connu et  appuyez sur entrer ");
                Scan::confirmer();
                Serial.print("Poids connu : ");
                Serial.println(poids_connu);
                laBalance->etalonnerLaBalance(poids_connu);
                Serial.print("scale : ");
                Serial.println(laBalance->obtenirScale());
                break;

            case '3':
                laBalance->afficherCoefficients();
                break;
                
            case '5':
                Serial.println("\rDonnez l'unité du poids ");
                Scan::lireTabChar(unite,10);
                laBalance->fixerUnite(unite);
                break; 
                
            case '6':
                if (laBalance->ecrireCoefficients()) {
                    Serial.println("Commit EEPROM effectué avec succes");
                }
                break;    
        }

    } while (choix != '4');
}

void loop() {
    Serial.print(laBalance->peser());
    Serial.print(" ");
    Serial.print(laBalance->obtenirUnite());
    Serial.print("\t");
    Serial.println(laBalance->obtenirVariance());
    delay(200);

}