/* 
 * File:   Rtty.cpp
 * Author: Anthony & philippe S(Touchard Washington)
 * 
 * Created on 26 juillet 2021, 11:27
 */

#include "Rtty.h"

/**
 * @brief Constructeur Rtty par défaut
 *        Mark 1000Hz, Carrier shift 170Hz, Baud rate 45.5, Stop bits 2 
 * @param _nbStopBits
 */
Rtty::Rtty(stopBits _nbStopBits) :
leFsk(new Fsk(1000, 170, 45.5)),
nbStopBits(_nbStopBits) {
    leFsk->begin();
    figlett = LETTERS;
}

/**
 * @brief Constructeur avec paramètres 
 * @param mkFreq   Marc Fréquency 
 * @param shift    Carrier Shift
 * @param br       Baud rate (45 45.45 50) 
 * @param _nbStopBits Stop bits (1 1.5 2)
 */
Rtty::Rtty(float mkFreq, float shift, float br, stopBits _nbStopBits) :
leFsk(new Fsk(mkFreq, shift, br)),
nbStopBits(_nbStopBits) {
    leFsk->begin();
    figlett = LETTERS; // RTTY Baudot signs/letters toggle
}

Rtty::Rtty(const Rtty& orig) {
}

Rtty::~Rtty() {
    delete leFsk;
}

/**
   @brief Rtty::tx(char * stringRtty)

   @details envoie l'octet codé en rtty
   @param   caractère (contient le bit de start et les 2 bits de stop) 5+1+2=8 bits
   A changer dans une future version !!
 */

void Rtty::txByte(char car) {
    
    bool val;
    car = car << 1; //ajout du bit de start
    for (int b = 0; b < 6; b++) // LSB first
    {
        val = bitRead(car, b); // Read 1 bit
        leFsk->sendBit(val);
    }
    leFsk->sendStopBit(nbStopBits);
}



/**
 * @brief Rtty::tx(char message[])
 * @param stringRtty
 */

void Rtty::tx(char message[]) {
    leFsk->start();
    
    Rtty::txByte(0);   // 0 pour reveiller le récepteur
    Rtty::txByte(31);  // Passage en mode lettre
    figlett = LETTERS;
    
    for (int i = 0; message[i] != '\0'; i++) {
        txChar(message[i]);
    }
    leFsk->stop();    
}

/**
 * @brief méthode pour encoder le caractère en baudot 
 *        et l'envoyer 
 * @param x
 */
void Rtty::txChar(char x) {
    //  Tableau d'encodage                     sp  !   "   #  $  %   &   '   (   )  *  +  ,   -  .   /   0   1   2   3   4   5   6  7   8  9   :   ;   <  =  >  ?   @  A  B   C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   T   U   V  W   X   Y   Z
    const static char TableRtty[59] PROGMEM = {4, 13, 17, 20, 9, 0, 26, 11, 15, 18, 0, 0, 12, 3, 28, 29, 22, 23, 19, 1, 10, 16, 21, 7, 6, 24, 14, 30, 0, 0, 0, 25, 0, 3, 25, 14, 9, 1, 13, 26, 20, 6, 11, 15, 18, 28, 12, 24, 22, 23, 10, 5, 16, 7, 30, 19, 29, 21, 17};

    char car = toupper(x);
    switch (car) {
        case '\n':
            Rtty::txByte(8);
            break;

        case '\r':
            Rtty::txByte(2);
            break;
            
        case ' ':
            Rtty::txByte(4);
            figlett = LETTERS;
            break;    
 
        default:
            if (car >= ' ' && car <= 'Z') // is alphanumeric char
            {
                car = car - ' '; //substract space char
                if (car > 32) {
                    if (figlett == FIGURES) {
                        figlett = LETTERS; // toggle form signs to letters table
                        Rtty::txByte(31);
                    }
                } else {
                    if (figlett == LETTERS) {
                        figlett = FIGURES; // toggle form letters to signs table
                        Rtty::txByte(27);
                    }
                }

                Rtty::txByte(pgm_read_word(&TableRtty[int(car)])); // Send the 5 bits word
            }
    }

}