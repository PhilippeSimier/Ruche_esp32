/** 
 @file constante.h
 @autho GUITTON Baptiste
 @brief Déclaration du document contenant toute les définition du projet
 @date 06/05/2021
 */
#ifndef CONSTANTE_H
#define CONSTANTE_H
#define EEPROM_SIZE 512
#define LOADCELL_DOUT_PIN = 26;
#define LOADCELL_SCK_PIN = 25;
#define SERIAL_BAUD 115200

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  120        /* Time ESP32 will go to sleep (in seconds) */

typedef struct {
    float temperature;
    float humidite;
    float pression;
    float eclairement;

} mesure;

typedef struct {
    unsigned short masse;
    short temperature;
    unsigned short pression;
    unsigned short eclairement;
    short pointDeRosee;
    unsigned char humidite;
    char typeTrame = 1;
} trameMesure;

typedef struct {
    float tensionBatterie;
    float puissanceBatterie;
    int tauxDeChargeBatterie;
    float chargeBatterie;
    float intensiteBatterie;
} mesureBatterie;


typedef struct {
    short tension;
    short courant;
    short puissance;
    short charge;
    short nu;
    unsigned char tauxDeCharge;
    char typeTrame = 02;
} trameBatterie;

#endif /* CONSTANTE_H */

