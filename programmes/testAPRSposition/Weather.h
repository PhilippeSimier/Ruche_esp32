/* 
 * File:   Weather.h
 * Author: philippe
 *
 * Created on 11 août 2021, 15:40
 */

#ifndef WEATHER_H
#define WEATHER_H
#include "Position.h"
#include <cmath>   // pour avoir NAN

class Weather : public Position {

    public:
    Weather(const double _latitude, 
            const double _longitude );
    

    virtual ~Weather();
    
    void setTemp(double _temp);
    void setHumidity(double _humidity);
    void setPressure(double _pressure);
    char* getPduAprs();

    private:
    int     wind;         // direction du vent
    double  speed;        // vitesse du vent
    double  gust;         // Pointe de vitesse
    double  temp;         // température en °F
    double  rain;         // Pluie en mm
    double  rain24;       // Pluie sur 24h
    double  rainMidnight; // Pluie depuis minuit
    double  humidity;     // Humidité en %
    double  pressure;     // Pression barométrique    
        

};

#endif /* WEATHER_H */

