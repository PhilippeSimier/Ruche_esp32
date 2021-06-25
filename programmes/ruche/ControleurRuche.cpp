/**
 * @file ControleurRuche.cpp
 * @brief Implémentation de la classe ControleurRuche
 * @author GUITTON Baptiste
 * @date 04/05/2021
 * @details Classe principal du projet , permet la création des différent objets
 * 
 */
#include "ControleurRuche.h"
/**
 * @brief ControleurRuche::ControleurRuche
 * @details création de tout les objets et lecture de l'EEPROM
 */
ControleurRuche::ControleurRuche() {


    lesMesuresC.temperature = 0;
    lesMesuresC.humidite = 0;
    lesMesuresC.pression = 0;
    lesMesuresC.eclairement = 0;
    unEnvironnement = new Environnement(false, BME280I2C::I2CAddr_0x77);
    laBalance = new Balance();
    laBatterie = new Batterie();
    leMenu = new Menu();
    leModemSigfox = new ModemSigfox();
    leModemSigfox->begin();
    choixTrame = true;

    laBalance->ConfiguerOffset(EEPROM.readDouble(0)); // lire le coef offset à l'adresse 0 et configuration de offset
    laBalance->ConfiguerScale(EEPROM.readDouble(10)); // lire le coef scale à l'adresse 10 et configuration de scale
    
}

ControleurRuche::ControleurRuche(const ControleurRuche& orig) {
}

ControleurRuche::~ControleurRuche() {
}
/**
 * @brief ControleurRuche::RecupererDonnees
 * @detail cette fonction permet la recupération de toute les données relative à la classe Environnement et Balance
 */
void ControleurRuche::RecupererDonnees() {

    lesMesuresC = unEnvironnement->ObtenirMesures();
    masse = laBalance->Peser();
    Serial.print("Temp: ");
    Serial.print(lesMesuresC.temperature);
    Serial.println("°C\t");
    Serial.print("Humidity: ");
    Serial.print(lesMesuresC.humidite);
    Serial.println("% RH\t");
    Serial.print("Pressure: ");
    Serial.print(lesMesuresC.pression);
    Serial.println("hPa\t");
    Serial.print("eclairement: ");
    Serial.print(lesMesuresC.eclairement);
    Serial.println("lux\t");
    Serial.print(masse);
    Serial.println("kg\t");

    

}
/**
 * @brief ControleurRuche::RecupererDonneesBatterie
 * @detail cette fonction permet la recupération de toute les données relative à la classe Batterie
 */
void ControleurRuche::RecupererDonneesBatterie() {
    lesMesuresBatterie = laBatterie->CalculerCaracteristiques();
    Serial.print("Tension:       ");
    Serial.print(lesMesuresBatterie.tensionBatterie);
    Serial.println(" V");
    Serial.print("Courant:       ");
    Serial.print(lesMesuresBatterie.intensiteBatterie);
    Serial.println(" mA");
    Serial.print("Puissance:     ");
    Serial.print(lesMesuresBatterie.puissanceBatterie);
    Serial.println(" mW");
    Serial.print("Charge:        ");
    Serial.print(lesMesuresBatterie.chargeBatterie);
    Serial.println(" Ah");
    Serial.print("Taux de Charge:  ");
    Serial.print(lesMesuresBatterie.tauxDeChargeBatterie);
    Serial.println("%");
    Serial.println("");
    
}
/**
 * @brief ControleurRuche::Ordonnancer
 * @detail cette fonction permet d'alterner en la récupération des mesures et la récupération des données de la batterie
 */
void ControleurRuche::Ordonnancer() {
    if (choixTrame == true) {
        RecupererDonnees();
        leModemSigfox->ForgerTrameMesure(lesMesuresC, masse);
        choixTrame = false;

    } else {
        RecupererDonneesBatterie();
        leModemSigfox->ForgerTrameBatterie(lesMesuresBatterie);
        choixTrame = true;
   }
}
/**
 * @brief ControleurRuche::Retour
 * @detail cette fonction permet de retourner au menu précédent ou de quitter le Menu
 */
void ControleurRuche::Retour() {
    int choix;
    leMenu->AfficherMenu();
    while (!Serial.available());


    choix = Serial.read();
    GestionMenu(choix);

}
/**
 * @brief ControleurRuche::GestionMenu
 * @detail cette fonction permet d'interpréter le choix de l'utilisateur dans le menu principal
 */
void ControleurRuche::GestionMenu(int _choix) {


    switch (_choix) {
        case '1':
            leMenu->AfficherMenuBatterie();
            GestionMenuBatterie();

            break;
        case '2':
            leMenu->AfficherMenuBalance();
            GestionMenuBalance();
            break;
        case '3':
            leMenu->AfficherMenuSysteme();
            GestionMenuSysteme();

    }

}
/**
 * @brief ControleurRuche::GestionMenuSysteme
 * @detail cette fonction permet d'interpréter le choix de l'utilisateur dans le menu Systeme
 */
void ControleurRuche::GestionMenuSysteme() {
    String nom = "Ruche de Beaufay";
    int choix;
    int choix2;
    do{
    while (!Serial.available());


    choix = Serial.read();
    switch (choix) {
        case '1':
            Serial.println();
            Serial.print("Entrez le nouveau nom du système : ");
            while (!Serial.available());
            nom = Serial.readString();
            Serial.println("\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n");
            leMenu->AfficherMenuSysteme();
            break;
        case '2':
            Serial.println();
            Serial.println("Configuration : \n");
            Serial.print("Nom du système : ");
            Serial.println(nom);
            Serial.print("Capacité de la Batterie : ");
            Serial.println(laBatterie->DonnerCapacite());
            Serial.print("Offset de la Balance : ");
            Serial.println(laBalance->ObtenirOffset());
            Serial.print("Scale de la Balance : ");
            Serial.println(laBalance->ObtenirScale());
            delay(2000);
            leMenu->AfficherMenuSysteme();
            break;
        case '3':
            Serial.println();
            Serial.println("Voulez vous supprimer toutes les données de l'ESP32 ? (1 = Oui / 2 = Non) : ");
            do{
            while (!Serial.available());
            choix2 = Serial.read();
            }while (choix2 < '1' || choix2 > '2');
            if(choix2 == '1'){
                for (int i = 0; i < 512; i++) {
                EEPROM.write(i, 0);
                }
                EEPROM.end();
                Serial.println("Appuyez sur le bouton EN de l'esp32 pour relancer le programme.");
                while(1==1){}
  }
            leMenu->AfficherMenuSysteme();
    }
    }while(choix != '4');
    leMenu->AfficherMenu();
}
/**
 * @brief ControleurRuche::GestionMenuBatterie
 * @detail cette fonction permet d'interpréter le choix de l'utilisateur dans le menu Batterie
 */
void ControleurRuche::GestionMenuBatterie() {
    int choix;
    float capacite;
    do {
        do {
            while (!Serial.available());
            choix = Serial.read();
        } while (choix < '1' || choix > '2');
        switch (choix) {
            case '1':
                Serial.println("\n \n");
                Serial.print(" La capacité est de : ");
                Serial.print(laBatterie->DonnerCapacite());
                Serial.println("\n \n");
                Serial.print(" Entrez la nouvelle capacité : ");
                do {
                    while (!Serial.available());
                    capacite = Serial.parseFloat();
                    laBatterie->ConfigurerCapacite(capacite);
                    Serial.print(capacite);
                } while (capacite < 1 );
                leMenu->AfficherMenuBatterie();
        }
    } while (choix != '2');
    leMenu->AfficherMenu();
}
/**
 * @brief ControleurRuche::GestionMenuBalance
 * @detail cette fonction permet d'interpréter le choix de l'utilisateur dans le menu Balance
 */
void ControleurRuche::GestionMenuBalance() {
    float poidEtalon;
    int choix;

    laBalance->ConfiguerOffset(EEPROM.readDouble(0)); // lire le coef offset à l'adresse 0 et configuration de offset
    laBalance->ConfiguerScale(EEPROM.readDouble(10));
    do {
        while (!Serial.available());
        choix = Serial.read();
        switch (choix) {
            case '1': // l'utilisateur à choisi l'option Tarer
                Serial.println("Vider le plateau et appuyer sur une touche pour tarer ");
                while (!Serial.available());
                while (Serial.available()) Serial.read();
                laBalance->TarerLaBalance();
                // Serial.println(laBalance.ObtenirOffset()); affichage de coef offset
                Serial.println("Tarage effectué: \t\t");
                EEPROM.writeDouble(0, laBalance->ObtenirOffset()); // sauvegarder le coef offset à l'adresse 0
                EEPROM.commit();
                Serial.print("Masse = ");
                Serial.println(laBalance->Peser());
                break;
            case '2': // l'utilisateur à choisi l'option Tarer
                if (laBalance->TarageEffectuer()) {
                    Serial.println("Poser la masse étalon puis donnez sa valeur en gramme (ex:400g= 400) et appuyez sur entrer ");
                    while (!Serial.available());

                    while (Serial.available() == 0) {
                    }
                    poidEtalon = Serial.parseFloat();


                    while (!Serial.available());
                    while (Serial.available()) Serial.read();
                    Serial.println(poidEtalon); // affiche 4 si l'ont tape 4
                    laBalance->EtalonnerLaBalance(poidEtalon);
                    Serial.println(laBalance->ObtenirScale());
                    EEPROM.writeDouble(10, laBalance->ObtenirScale()); // sauvegarder le coef scale à l'adresse 10
                    EEPROM.commit();
                } else {
                    Serial.println("Vous devez tarer la balance avant de faire un étalonnage ");
                }
                break;
            case '3':
                Serial.print("Masse = ");
                Serial.println(laBalance->Peser()); // appel de la fonction peser qui renvoit la masse mesurée


        }
        leMenu->AfficherMenuBalance();
    } while (choix != '4');
    leMenu->AfficherMenu();

}