/* 
 * File:   Compteur.h
 * Author: philippe
 *
 * Created on 18 juillet 2021, 17:47
 */

#ifndef COMPTEUR_H
#define COMPTEUR_H
#include <Arduino.h>

class Compteur {
    
public:
    Compteur();
    Compteur(const Compteur& orig);
    virtual ~Compteur();
    void begin(byte sensPin);
    int getValue();

private:
    
    void  IRAM_ATTR interuption();
    
    static void marshall();
    static Compteur* anchor;
    
    int lastMillis;
    volatile int nb;
    
};



#endif /* COMPTEUR_H */

