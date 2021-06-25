/** 
 @file ControleurRuche.h
 @autho GUITTON Baptiste
 @brief Déclaration de la classe ControleurRuche
 @date 04/05/2021
 @details Classe principale du projet Ruche
 */
#ifndef CONTROLEURRUCHE_H
#define CONTROLEURRUCHE_H
#include "Balance.h"
#include "Environnement.h"
#include "constante.h"
#include "Menu.h"
#include "Batterie.h"
#include "ModemSigfox.h"





class ControleurRuche {
public:
    ControleurRuche();
    ControleurRuche(const ControleurRuche& orig);
    virtual ~ControleurRuche();
    void Ordonnancer();
    void RecupererDonnees();
    void RecupererDonneesBatterie();
    void AfficherConfig();
    void ConfiguerNom();
    void CommandeSaisie();
    void Retour();
    void ConfiguerBatterie();

    void GestionMenu(int _choix);
    void GestionMenuSysteme();
    void GestionMenuBatterie();
    void GestionMenuBalance();
     Menu *leMenu;
 

private:
    mesure lesMesuresC;
    mesureBatterie lesMesuresBatterie;
    float masse;
    float tension;
    float intensite;
    float tauxDeCharge;
    float charge;
    bool choixTrame;
    Balance *laBalance;
    Environnement *unEnvironnement;
    Batterie *laBatterie;
    ModemSigfox *leModemSigfox;
    

};



#endif /* CONTROLEURRUCHE_H */