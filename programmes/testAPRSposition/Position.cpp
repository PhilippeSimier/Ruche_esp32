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
    
    snprintf(pdu, sizeof (pdu), "!/%s%s%c  T%s", clat, clon, symbole, comment);
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

    int y, y0, y1, y2, y3;

    y = (int) round(380926. * (90. - latitude));

    y0 = y / (91 * 91 * 91);
    y -= y0 * (91 * 91 * 91);

    y1 = y / (91 * 91);
    y -= y1 * (91 * 91);

    y2 = y / (91);
    y -= y2 * (91);

    y3 = y;

    clat[0] = y0 + 33;
    clat[1] = y1 + 33;
    clat[2] = y2 + 33;
    clat[3] = y3 + 33;
    clat[4] = '\0';
}

void Position::longitude_to_comp_str() {

    int x, x0, x1, x2, x3;

    x = (int) round(190463. * (180. + longitude));

    x0 = x / (91 * 91 * 91);
    x -= x0 * (91 * 91 * 91);

    x1 = x / (91 * 91);
    x -= x1 * (91 * 91);

    x2 = x / (91);
    x -= x2 * (91);

    x3 = x;

    clon[0] = x0 + 33;
    clon[1] = x1 + 33;
    clon[2] = x2 + 33;
    clon[3] = x3 + 33;
    clon[4] = '\0';
}

