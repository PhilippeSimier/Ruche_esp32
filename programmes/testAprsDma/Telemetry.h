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

#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>


class Telemetry {
public:

    Telemetry(String _callsign);
    Telemetry(const Telemetry& orig);
    virtual ~Telemetry();

        
    char* getValuePduAprs();
    char* getUnitPduAprs();
    char* getNamePduAprs();
    char* getEqnsPduAprs();
    
    void setValue(const int field, const char _value);
    void setName(const int field, const char* _name);
    void setUnit(const int field, const char* _name);
    void setEqn(const int field, const double a, const double b, const double c);
    
    void setDigital(const int bit, const bool value);
    void setComment(String _comment);
    
private:
    
    char value[5];
    char name[5][8];
    char unit[5][8];
    double equation[5][3];
    char   sEqns[5][50];
    
    char digital[9];
    char comment[101];
    int sequenceNo;
    char callsign[8];
    
    char pdu[512];

};

#endif /* TELEMETRY_H */

