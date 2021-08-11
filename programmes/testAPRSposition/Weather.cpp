/* 
 * File:   Weather.cpp
 * Author: philippe
 * 
 * Created on 11 août 2021, 15:40
 */


#include <Print.h>

#include "Weather.h"

Weather::Weather(const double _latitude, const double _longitude) :
Position(_latitude, _longitude, "", '/', '_'),
wind(-1),
speed(NAN),
gust(NAN),
temp(NAN),
rain(NAN),
rain24(NAN),
rainMidnight(NAN),
humidity(NAN),
pressure(NAN) {
}

Weather::~Weather() {
}

void Weather::setTemp(double _temp) {
    temp = _temp * 9 / 5 + 32; // °F = °C x 9/5 + 32
}

void Weather::setHumidity(double _humidity){
    humidity = _humidity;
}

void Weather::setPressure(double _pressure){
    pressure = _pressure * 10;
}

char* Weather::getPduAprs() {

    char data[100];
    char stemp[5]     = "t...";
    char shumidity[4] = "h..";
    char spressure[7] = "b.....";

    if (!isnan(temp))     snprintf(stemp,     sizeof (stemp),     "t%03.0f", temp);
    if (!isnan(humidity)) snprintf(shumidity, sizeof (shumidity), "h%02.0f", humidity);
    if (!isnan(pressure)) snprintf(spressure, sizeof (spressure), "b%05.0f", pressure);
    snprintf(data, sizeof (data), ".../...g...%sr...p...P...%s%s", stemp, shumidity, spressure);

    latitude_to_str();
    longitude_to_str();
    snprintf(pdu, sizeof (pdu), "!%s%c%s%c%s", slat, symboleTable, slong, symbole, data);

    return pdu;
}

