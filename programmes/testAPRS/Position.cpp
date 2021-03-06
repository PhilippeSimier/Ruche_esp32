/* 
 * File:   Position.cpp
 * Author: philippe & Anthony 
 * 
 * Created on 7 août 2021, 08:00
 */

#include "Position.h"

Position::Position(const double _latitude, const double _longitude, String _comment, const char _symboleTable, const char _symbole) :
latitude(_latitude),
longitude(_longitude),
alt(0),
comment(_comment),        
symboleTable(_symboleTable),
symbole(_symbole) {
    
}

Position::Position(const Position& orig) {
}

Position::~Position() {
}

void Position::setLatitude(const double _latitude) {
    latitude = _latitude;
}

void Position::setLongitude(const double _longitude) {
    longitude = _longitude;
}

void Position::setComment(String _comment) {
    comment = _comment;
}

void Position::setAltitude(const double _alt) {
    alt = (int)(3.2809 * _alt);
}
/**
 * @brief Fabrique le PDU APRS position 
 *        si compressed est true la position est compressée (base91)
 * @param bool compressed indique si la position doit être compressée
 * @return char* Le pdu APRS position 
 */
char* Position::getPduAprs(bool compressed) {
    char com[43];
    char scom[33];
    char salt[10];
    
    if (alt != 0){
        snprintf(salt, sizeof (salt), "/A=%06d", alt);
        comment.toCharArray(scom, 33);
        snprintf(com, sizeof(com), "%s %s", salt, scom);
    }else{
        comment.toCharArray(com, 43);
    }
    
    if (compressed) {

        latitude_to_comp_str();
        longitude_to_comp_str();

        snprintf(pdu, sizeof (pdu), "!%c%s%s%c  T%s", symboleTable, slat, slong, symbole, com);
    }
    else {

        latitude_to_str();
        longitude_to_str();

        snprintf(pdu, sizeof (pdu), "!%s%c%s%c%s", slat, symboleTable, slong, symbole, com);
    }
    return pdu;
}

void Position::latitude_to_str() {
    char hemi; // Hemisphere: N or S
    int ideg; // whole number of degrees
    double dmin; // Minutes after removing degrees
    char smin[8]; // Decimal Minutes in format mm.mm 

    if (latitude < 0) {
        latitude = (-latitude);
        hemi = 'S';
    } else {
        hemi = 'N';
    }

    ideg = (int) latitude;
    dmin = (latitude - ideg) * 60.;

    snprintf(smin, sizeof (smin), "%05.2f", dmin);
    /* Due to roundoff, 59.99 could come out as "60.00" */
    if (smin[0] == '6') {
        smin[0] = '0';
        ideg++;
    }

    snprintf(slat, sizeof (slat), "%02d%s%c", ideg, smin, hemi);
}

void Position::longitude_to_str() {
    char hemi; // Hemisphere: W or E
    int ideg; // whole number of degrees. 
    double dmin; // Minutes after removing degrees. */
    char smin[8]; // Minutes in format mmm.mm */

    if (longitude < 0) {
        longitude = (-longitude);
        hemi = 'W';
    } else {
        hemi = 'E';
    }

    ideg = (int) longitude;
    dmin = (longitude - ideg) * 60.;

    snprintf(smin, sizeof (smin), "%05.2f", dmin);
    /* Due to roundoff, 59.9999 could come out as "60.00" */
    if (smin[0] == '6') {
        smin[0] = '0';
        ideg++;
    }

    snprintf(slong, sizeof (slong), "%03d%s%c", ideg, smin, hemi);
}

void Position::latitude_to_comp_str() {

    int y;
    y = (int) round(380926. * (90. - latitude));
    convBase91(y, slat);
}

void Position::longitude_to_comp_str() {

    int x;
    x = (int) round(190463. * (180. + longitude));
    convBase91(x, slong);
}

void Position::convBase91(int x, char* base91) {

    int c[4];

    for (int i = 3; i >= 0; i--) {
        base91[i] = (x % 91) + 33;
        x /= 91;
    }
    base91[4] = '\0';
}