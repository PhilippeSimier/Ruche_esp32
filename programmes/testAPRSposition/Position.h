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
    
    Position(const double _latitude, 
             const double _longitude, 
             String _comment = "", 
             const char _symboleTable = '/',
             const char _symbole= '>'
             );
    
    Position(const Position& orig);
    virtual ~Position();
    
    char* getPduAprs(bool compressed = false);
    void setLatitude(const double _latitude);
    void setLongitude(const double _longitude);
    void setComment(String _comment);
    
    
private:
    double  latitude;   
    double  longitude;
    char    comment[44];
    char    symboleTable;
    char    symbole;
    
    
    char  pdu[100];
    
    void latitude_to_str();
    void latitude_to_comp_str();
    char slat[9];
    
    void longitude_to_str();
    void longitude_to_comp_str();
    char slong[10];
    
    void convBase91(int x, char* base91);
    
};

#endif /* POSITION_H */

