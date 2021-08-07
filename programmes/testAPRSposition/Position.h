/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Position.h
 * Author: philippe
 *
 * Created on 7 août 2021, 08:00
 */

#ifndef POSITION_H
#define POSITION_H

#include <WString.h>


class Position {
public:
    
    Position(const double _latitude, const double _longitude, const char _symbole= '>', String _comment = "");
    Position(const Position& orig);
    virtual ~Position();
    
    char* getPduAprs();
    char* getCompressedPduAprs();
    void setLatitude(const double _latitude);
    void setLongitude(const double _longitude);
    void setComment(String _comment);
    
    
private:
    double  latitude;
    double  longitude;
    char    symbole;
    char    comment[44];
    
    char  pdu[100];
    
    void latitude_to_str();
    char slat[9];
    
    void longitude_to_str();
    char slong[10];
    
    void latitude_to_comp_str();
    char clon[5];
    
    void longitude_to_comp_str();
    char clat[5];
    

};

#endif /* POSITION_H */

