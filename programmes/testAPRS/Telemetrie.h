/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Telemetrie.h
 * Author: philippe
 *
 * Created on 15 août 2021, 11:48
 */

#ifndef TELEMETRIE_H
#define TELEMETRIE_H

#include <stdint.h>


class Telemetrie {
public:

    Telemetrie();
    Telemetrie(const Telemetrie& orig);
    virtual ~Telemetrie();

        
    char* getPduAprs();
    void setValue(const int field, const char _value);
    void setDigital(const int bit, const bool value);
    void setComment(String _comment);
    
private:
    
    char* value;
    char* digital;
    char* comment;
    int sequenceNo;
    
    char pdu[255];

};

#endif /* TELEMETRIE_H */

