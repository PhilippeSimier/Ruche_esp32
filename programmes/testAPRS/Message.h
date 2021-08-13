/* 
 * File:   Message.h
 * Author: philippe & Anthony (Touchard Le Mans)
 *
 * Created on 8 août 2021, 11:47
 */

#ifndef MESSAGE_H
#define MESSAGE_H
#include <Arduino.h>

class Message {
public:
    
    Message(String _addressee, String _text, String _message_No = "" );
    Message(const Message& orig);
    virtual ~Message();
    
    char* getPduAprs();
    
private:
    char addressee[10];
    char text[68];
    char message_No[6];
    
    char pdu[85];
};

#endif /* MESSAGE_H */

