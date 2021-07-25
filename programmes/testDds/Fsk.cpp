/* 
 * File:   Fsk.cpp
 * Author: Anthony & Philippe (Touchard Washington)
 * 
 * Created on 25 juillet 2021, 10:20
 */

#include "Fsk.h"

Fsk::Fsk() :
Dds(),
nbEchPerBit(splFreq) // Un baud 
{
   
}

Fsk::Fsk(const Fsk& orig) {
}

Fsk::~Fsk() {
}

void Fsk::sendBit(bool value) {
    compteur = 0;
    if (value) 
        enableMark();
    else 
        enableSpace();
    while (compteur < nbEchPerBit);
}

/**
   @brief Fsk::setBitRate(float br)

   @details calcul le bitrate du signal à transmettre en accord avec la féquence d'achantillonage
   @param   float  bitrate 
 */

void Fsk::setBitRate(float br) {
    nbEchPerBit = round(splFreq / br);
}

/**
   @brief Fsk::sendStopBit(stopBits nStop)
   @details envoi d'un bit ou plusieurs bits de stop en accord avec le calcul du bit rate et nbEchPerBit
   @param stopBits nombre de bits de stop
*/

void Fsk::sendStopBit(stopBits nStop){
  int nbIrq;  
  switch (nStop) {
    case BIT_1: nbIrq = nbEchPerBit;
      break;
    case BIT_1_5: nbIrq = nbEchPerBit + (nbEchPerBit / 2);
      break;
    case BITS_2: nbIrq = nbEchPerBit * 2;
      break;
  }
  enableSpace();
  compteur = 0;
  while (compteur < nbIrq);
}


/**
   @brief Fsk::sendBitOff()
   @details envoi d'un bit en accord avec le calcul du bit rate nbEchPerBit            
   @param  aucun la sortie du dds ne génère aucune sinudoide meme si l'interruption Timer est toujours en fonctionement
           Méthode pour la génération d'un signal tout ou rien OOK (On Off Keying)
*/
void Fsk::sendBitOff(){
    stop();
    compteur = 0;
    while (compteur < nbEchPerBit);
}