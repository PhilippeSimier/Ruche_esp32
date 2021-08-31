/* 
 * File:   Telemetry.cpp
 * Author: philippe
 * 
 * Created on 16 août 2021, 22:07
 */

#include <stddef.h>
#include <pgmspace.h>
#include <WString.h>
#include <Print.h>
#include "Telemetry.h"

Telemetry::Telemetry(String _callsign) :
sequenceNo(0) {
    for (int i = 0; i < 5; i++) {
        value[i] = 0;
        strlcpy(name[i], "", 8);
        strlcpy(unit[i], "", 8);
        equation[i][0] = 0;
        equation[i][1] = 1;
        equation[i][2] = 0;
    }
    for (int i = 0; i < 8; i++) {
        digital[i] = '0';
    }
    digital[8] = '\0';
    _callsign.toCharArray(callsign, 9);
}

Telemetry::Telemetry(const Telemetry& orig) {
}

Telemetry::~Telemetry() {
}

void Telemetry::setValue(int field, const char _value) {
    if (field < 6)
        value[field - 1] = _value;

}

void Telemetry::setName(const int field, const char* _name) {
    if (field < 6)
        strlcpy(name[field - 1], _name, 8);
}

void Telemetry::setUnit(const int field, const char* _name) {
    if (field < 6)
        strlcpy(unit[field - 1], _name, 8);
}

void Telemetry::setDigital(const int bit, const bool _value) {
    if (bit < 8) {
        if (_value)
            digital[7 - bit] = '1';
        else
            digital[7 - bit] = '0';
    }
}

void Telemetry::setComment(String _comment) {
    _comment.toCharArray(comment, 100);
}

void Telemetry::setEqn(const int field, const double a, const double b, const double c) {
    if (field < 6) {
        equation[field -1][0] = a;
        equation[field -1][1] = b;
        equation[field -1][2] = c;
    }
}

char* Telemetry::getValuePduAprs() {

    snprintf(pdu, sizeof (pdu), "T#%03u,%03u,%03u,%03u,%03u,%03u,%s", sequenceNo, value[0], value[1], value[2], value[3], value[4], digital);
    sequenceNo++;
    if (sequenceNo == 999)
        sequenceNo = 0;

    return pdu;
}

char* Telemetry::getNamePduAprs() {

    snprintf(pdu, sizeof (pdu), ":%-9s:PARM.%s,%s,%s,%s,%s,B1,B2,B3,B4,B5,B6,B7,B8", callsign, name[0], name[1], name[2], name[3], name[4]);
    return pdu;
}

char* Telemetry::getUnitPduAprs() {

    snprintf(pdu, sizeof (pdu), ":%-9s:UNIT.%s,%s,%s,%s,%s,B1,B2,B3,B4,B5,B6,B7,B8", callsign, unit[0], unit[1], unit[2], unit[3], unit[4]);
    return pdu;
}

char* Telemetry::getEqnsPduAprs() {
    
    
    
    for(int i=0; i<5; i++){
       snprintf(sEqns[i], sizeof(sEqns[i]), "%g,%g,%g", equation[i][0], equation[i][1], equation[i][2]); 
    }
    
    snprintf(pdu, sizeof (pdu), ":%-9s:EQNS.%s,%s,%s,%s,%s", callsign, sEqns[0], sEqns[1], sEqns[2], sEqns[3],sEqns[4]);
    return pdu;
}


