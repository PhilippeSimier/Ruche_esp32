/* 
 * File:   Position.cpp
 * Author: philippe & Anthony 
 * 
 * Created on 7 août 2021, 08:00
 */

#include "Position.h"

Position::Position(const double _latitude, const double _longitude, const char _symbole, String _comment) :
latitude(_latitude),
longitude(_longitude),
symbole(_symbole) {
    _comment.toCharArray(comment, 43);
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
    _comment.toCharArray(comment, 43);
}

char* Position::getPduAprs() {

    latitude_to_str();
    longitude_to_str();

    snprintf(pdu, sizeof (pdu), "!%s/%s%c%s", slat, slong, symbole, comment);
    return pdu;
}

char* Position::getCompressedPduAprs() {
    
    latitude_to_comp_str();
    longitude_to_comp_str();
    
    snprintf(pdu, sizeof (pdu), "!/%s%s%c  T%s", slat, slong, symbole, comment);
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
    convBase91(y,slat);
}

void Position::longitude_to_comp_str() {

    int x;
    x = (int) round(190463. * (180. + longitude));
    convBase91(x,slong);
}

void Position::convBase91(int x, char* base91){
    
    int c[4];
    
    c[0] = x / (91 * 91 * 91);
    x -= c[0] * (91 * 91 * 91);

    c[1] = x / (91 * 91);
    x -= c[1] * (91 * 91);

    c[2] = x / (91);
    x -= c[2] * (91);

    c[3] = x;

    base91[0] = c[0] + 33;
    base91[1] = c[1] + 33;
    base91[2] = c[2] + 33;
    base91[3] = c[3] + 33;
    base91[4] = '\0';
}

