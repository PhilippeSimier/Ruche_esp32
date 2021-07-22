/* 
 * File:   main.ino.cpp
 * Author: psimier
 *
 * Created on 28 juin 2021, 14:12
 */

#include "balance.h"
#include "scan.h"


Balance *laBalance = NULL;
char unite[10] = {0};

void afficherMenu() {
    Scan::effacer();
    Serial.println(" Menu Balance, que souhaitez-vous faire ?");
    Serial.println("\n 1- Configurer l'unité ");
    Serial.println(" 2- Tarer la balance ");
    Serial.println(" 3- Etalonner la balance ");
    Serial.println(" 4- Enregistrer les coefficients ");
    Serial.println(" 5- Afficher les coefficients ");
    Serial.println(" 6- Peser ");
    Serial.println(" ?- Menu Balance\r\n");
    Scan::afficherPrompt("Balance");
}

void setup() {
    int choix = 0;
    float poids_connu = 0.0;
    if (laBalance == NULL)
        laBalance = new Balance(13, 15);
    Serial.begin(115200);


    do {
        afficherMenu();
        while (!Serial.available());
        choix = Serial.read();

        switch (choix) {

            case '1':
                Scan::effacer();
                Serial.println("\rDonnez l'unité du poids ");
                Scan::lireTabChar(unite, 10);
                laBalance->fixerUnite(unite);

                break;

            case '2':
                Scan::effacer();
                Serial.println("Vider le plateau et appuyer sur Entrée pour tarer ");
                Scan::confirmer();
                Serial.printf("offset : %ld\r\n", laBalance->tarerLaBalance());
                Scan::confirmer();
                break;

            case '3':
                Scan::effacer();
                Serial.println("Donner la valeur du poids connu ");
                poids_connu = Scan::lireFloat();
                Serial.println("\r\nPoser le poids connu et  appuyer sur Entrée ");
                Scan::confirmer();
                Serial.printf("Poids connu : %.3f\r\n", poids_connu);
                Serial.printf("scale : %.3f\r\n", laBalance->etalonnerLaBalance(poids_connu));
                Scan::confirmer();
                break;

            case '4':
                Scan::effacer();
                if (laBalance->ecrireCoefficients()) {
                    Serial.println("Commit EEPROM effectué avec succes");
                }
                Scan::confirmer();
                break;

            case '5':
                Scan::effacer();
                laBalance->afficherCoefficients();
                Scan::confirmer();
                break;

            case '?':
            case 3:    

                afficherMenu();

        }

    } while (choix != '6');

    Scan::effacer();
    Serial.printf("Ctrl-C pour quitter\r\n");
}

void loop() {
    int car;

    Serial.printf("%.2f %s \t%.2f\r\n", laBalance->peser(), laBalance->obtenirUnite(), laBalance->obtenirVariance());
    delay(1000);
    
    if (Serial.available()) {
        car = Serial.read();
        if (car == 27 || car == 3)
            setup();
    }

}