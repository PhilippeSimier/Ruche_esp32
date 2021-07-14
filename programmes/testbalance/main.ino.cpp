/* 
 * File:   main.ino.cpp
 * Author: psimier
 *
 * Created on 28 juin 2021, 14:12
 */

#include "balance.h"
#include "scan.h"


Balance *laBalance;
char unite[10] = {0};

void afficherMenu() {
    Serial.println(" Menu Balance, que souhaitez-vous faire ?");
    Serial.println("\n 1- Configurer l'unité ");
    Serial.println(" 2- Tarer la balance ");
    Serial.println(" 3- Etalonner la balance ");
    Serial.println(" 4- Enregistrer les coefficients ");
    Serial.println(" 5- Afficher les coefficients ");
    Serial.println(" 6- Peser ");
    Serial.println(" ?- Menu Balance ");
}

void setup() {
    int choix = 0;
    float poids_connu = 0.0;
    laBalance = new Balance(13, 15);

    Serial.begin(115200);
    afficherMenu();

    do {
        while (!Serial.available());
        choix = Serial.read();

        switch (choix) {

            case '1':
                Serial.println("\rDonnez l'unité du poids ");
                Scan::lireTabChar(unite, 10);
                laBalance->fixerUnite(unite);
                break;

            case '2':
                Serial.println("\rVider le plateau et appuyer sur Entrée pour tarer ");
                Scan::confirmer();
                Serial.printf("offset : %ld\r", laBalance->tarerLaBalance());
                break;

            case '3':
                Serial.println("\rDonner la valeur du poids connu ");
                poids_connu = Scan::lireFloat();
                Serial.println("\rPoser le poids connu et  appuyer sur Entrée ");
                Scan::confirmer();
                Serial.printf("Poids connu : %.3f\r", poids_connu);               
                Serial.printf("scale : %.3f\r", laBalance->etalonnerLaBalance(poids_connu));
                break;

            case '4':
                if (laBalance->ecrireCoefficients()) {
                    Serial.println("\rCommit EEPROM effectué avec succes");
                }
                break;

            case '5':
                Serial.println('\r');
                laBalance->afficherCoefficients();
                break;
                
            case '?': 
                afficherMenu();

        }

    } while (choix != '6');
    Serial.println(" ");
}

void loop() {

    Serial.printf("%.2f %s \t%.2f\r", laBalance->peser(), laBalance->obtenirUnite(), laBalance->obtenirVariance());
    delay(100);

}