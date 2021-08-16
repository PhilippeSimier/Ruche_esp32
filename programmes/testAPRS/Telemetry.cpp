/* 
 * File:   Telemetry.cpp
 * Author: philippe
 * 
 * Created on 16 août 2021, 22:07
 */

#include <stddef.h>
#include <pgmspace.h>
#include "Telemetry.h"

Telemetry::Telemetry(char* _callsign):
sequenceNo(0) 
{
    for (int i = 0; i < 5; i++) {
        value[i] = 0;
        strcpy(name[i], "");
        strcpy(unit[i], "");
    }
    for (int i = 0; i < 8; i++) {
        digital[i] = '0';
    }
    digital[8] = '\0';
    strcpy(callsign, _callsign);
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
        strcpy(name[field - 1] , _name);
}

void Telemetry::setUnit(const int field, const char* _name) {
    if (field < 6)
        strcpy(unit[field - 1] , _name);
}

void Telemetry::setDigital(const int bit, const bool _value) {
    if (bit < 8){
        if (_value)
            digital[7-bit] = '1';
        else
            digital[7-bit] = '0';
    }
}

void Telemetry::setComment(String _comment) {
    _comment.toCharArray(comment, 100);
}

char* Telemetry::getValuePduAprs() {
    
    snprintf(pdu, sizeof(pdu), "T#%03u,%03u,%03u,%03u,%03u,%03u,%s", sequenceNo, value[0], value[1], value[2], value[3], value[4], digital);
    sequenceNo++;
    if (sequenceNo == 999)
        sequenceNo = 0;

    return pdu;
}

char* Telemetry::getNamePduAprs() {
    
    snprintf(pdu, sizeof(pdu),":%-9s:PARM.%s,%s,%s,%s,%s,B1,B2,B3,B4,B5,B6,B7,B8", callsign, name[0], name[1], name[2], name[3], name[4]);
    return pdu;
}

char* Telemetry::getUnitPduAprs() {
    
    snprintf(pdu, sizeof(pdu),":%-9s:UNIT.%s,%s,%s,%s,%s,B1,B2,B3,B4,B5,B6,B7,B8", callsign, unit[0], unit[1], unit[2], unit[3], unit[4]);
    return pdu;
}


