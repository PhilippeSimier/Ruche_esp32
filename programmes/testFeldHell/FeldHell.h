/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FeldHell.h
 * Author: philippe
 *
 * Created on 3 août 2021, 09:35
 */

#ifndef FELDHELL_H
#define FELDHELL_H
#include "Fsk.h"

class FeldHell {
    
public:
    FeldHell(float _frequency = 800, float _br = 122.5);
    FeldHell(const FeldHell& orig);
    virtual ~FeldHell();
    
    void tx(char * message);
    
private:
    Fsk* leFsk;
    float frequency;
    float br;
};

#endif /* FELDHELL_H */

