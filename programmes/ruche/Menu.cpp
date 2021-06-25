/**
 * @file Menu.cpp
 * @brief Implémentation de la classe Menu
 * @author GUITTON Baptiste
 * @date 06/05/2021
 * @details Classe qui permet l'affichage des différent menu
 * 
 */
#include "Menu.h"
/**
 * @brief Menu::Menu
 * @details Constructeur de la classe Menu
 */
Menu::Menu() {
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
}
/**
 * @brief Menu::AfficherMenu
 * @details Affiche le menu principal
 */
void Menu::AfficherMenu() {
    Serial.println("\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n");
    Serial.println("\n Faites votre choix :");
    Serial.println("\n 1- Configurer la Batterie");
    Serial.println("\n 2- Configurer la Balance");
    Serial.println("\n 3- Configurer le menu système");
    Serial.println("\n 4- Quitter le mode configuration\n");
}
/**
 * @brief Menu::AfficherMenuBatterie
 * @details Affiche le menu de la Batterie
 */
void Menu::AfficherMenuBatterie() {

    Serial.println("\n \n \n");
    Serial.println("\n Menu Batterie, que souhaitez-vous faire ? \n");
    Serial.println("\n 1- Configurer la capacité de la Batterie \n");
    Serial.println("\n 2- Retourner en arrière\n");
}
/**
 * @brief Menu::AfficherMenuBalance
 * @details Affiche le menu de la Balance
 */
void Menu::AfficherMenuBalance() {

    Serial.println(" Menu Balance, que souhaitez-vous faire ?");
    Serial.println("\n 1- Tarer la balance ");
    Serial.println("\n 2- Etalonner la balance ");
    Serial.println("\n 3- Peser ");
    Serial.println("\n 4- Retourner en arrière\n");
}
/**
 * @brief Menu::AfficherMenuSysteme
 * @details Affiche le menu du systeme
 */
void Menu::AfficherMenuSysteme() {
    Serial.println("\n \n \n Menu Système, que souhaitez-vous faire ?");
    Serial.println("\n 1- Configurer le nom ");
    Serial.println("\n 2- Afficher la configuration ");
    Serial.println("\n 3- Remettre à zéro l'ESP32 ");
    Serial.println("\n 4- Retour en arrière \n");
}