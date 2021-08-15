/* 
 * File:   Telemetrie.cpp
 * Author: philippe
 * 
 * Created on 15 août 2021, 11:48
 */

#include <stddef.h>
#include <pgmspace.h>

#include "Telemetrie.h"

Telemetrie::Telemetrie() :
value(new char[5]),
digital(new char[9]),
comment(new char[101]),
sequenceNo(0) {
    for (int i = 0; i < 5; i++) {
        value[i] = 0;
    }
    for (int i = 0; i < 8; i++) {
        digital[i] = '0';
    }
    digital[8] = '\0';
}

Telemetrie::Telemetrie(const Telemetrie& orig) {
}

Telemetrie::~Telemetrie() {
    delete value;
    delete digital;
    delete comment;
}

void Telemetrie::setValue(int field, const char _value) {
    if (field < 5)
        value[field - 1] = _value;

}

void Telemetrie::setDigital(const int bit, const bool _value) {
    if (bit < 8){
        if (_value)
            digital[7-bit] = '1';
        else
            digital[7-bit] = '0';
    }
}

void Telemetrie::setComment(String _comment) {
    _comment.toCharArray(comment, 100);
}

char* Telemetrie::getPduAprs() {
    
    snprintf(pdu,   sizeof (pdu), "T#%03u,%03u,%03u,%03u,%03u,%03u,%s", sequenceNo, value[0], value[1], value[2], value[3], value[4], digital);
    sequenceNo++;
    if (sequenceNo == 999)
        sequenceNo = 0;

    return pdu;
}



