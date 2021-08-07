/* 
 * File:   Position.cpp
 * Author: philippe
 * 
 * Created on 7 août 2021, 08:00
 */

#include "Position.h"

Position::Position(const double _latitude, const double _longitude, const char _symbole, String _comment) :
latitude(_latitude),
longitude(_longitude),
symbole(_symbole)       
{
    _comment.toCharArray(comment,43);
}

Position::Position(const Position& orig) {
}

Position::~Position() {
}

char* Position::getPduAprs() {


    latitude_to_str();
    longitude_to_str();

    snprintf(pdu, sizeof (pdu), "!%s/%s%c%s", slat, slong, symbole, comment);
    return pdu;
}

void Position::latitude_to_str() {
    char hemi; // Hemisphere: N or S
    int ideg; // whole number of degrees
    double dmin; // Minutes after removing degrees
    char smin[6]; // Decimal Minutes in format mm.mm 

    if (latitude < 0) {
        latitude = (-latitude);
        hemi = 'S';
    } else {
        hemi = 'N';
    }

    ideg = (int) latitude;
    dmin = (latitude - ideg) * 60.;

    snprintf(smin, sizeof (smin), "%02.2f", dmin);
    /* Due to roundoff, 59.99 could come out as "60.00" */
    if (smin[0] == '6') {
        smin[0] = '0';
        ideg++;
    }

    snprintf(slat, sizeof (slat), "%02d%s%c", ideg, smin, hemi);
}

void Position::longitude_to_str() {
    char    hemi;      // Hemisphere: W or E
    int     ideg;      // whole number of degrees. 
    double  dmin;      // Minutes after removing degrees. */
    char    smin[7];   // Minutes in format mmm.mm */

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

