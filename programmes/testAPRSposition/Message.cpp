/* 
 * File:   Message.cpp
 * Author: philippe & Anthony (Touchard Le Mans)
 * 
 * Created on 8 août 2021, 11:47
 * brief  Classe pour envoyer des messages aprs
 * 
 */

#include "Message.h"

Message::Message(String _addressee, String _text, String _message_No) {
    
    char adr[10];
    _addressee.toCharArray(adr, 10);          // les 9 premiers caratères du String
    sprintf (addressee, "%-9s", adr);         // On complète avec du blanc 
    _text.toCharArray(text, 68);              // Les 67 premiers caratères du text
    _message_No.toCharArray(message_No, 6);   // Le numero de message
}

Message::Message(const Message& orig) {
}

Message::~Message() {
}

char* Message::getPduAprs() {
    
    if(message_No[0] == '\0')
        snprintf(pdu, sizeof (pdu), ":%s:%s", addressee, text);
    else
        snprintf(pdu, sizeof (pdu), ":%s:%s{%s", addressee, text, message_No);
    return pdu;
}

