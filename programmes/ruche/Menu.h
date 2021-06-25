/** 
 @file Menu.h
 @autho GUITTON Baptiste
 @brief Déclaration de la classe Menu
 @date 06/05/2021
 @details  Classe modélisant la gestion de l'affichage des menu
 */
#ifndef MENU_H
#define MENU_H

class Menu {
public:
    Menu();
    Menu(const Menu& orig);
    virtual ~Menu();
//private:
    void AfficherMenu();
    void AfficherMenuBatterie();
    void AfficherMenuBalance();
    void AfficherMenuSysteme();

};

#endif /* MENU_H */

