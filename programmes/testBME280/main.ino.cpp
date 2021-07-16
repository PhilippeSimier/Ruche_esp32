#include <Arduino.h>
#include <Wire.h>
#include <BME280.h>
#include <BME280I2C.h>
#define SERIAL_BAUD 115200

BME280I2C::Settings parametrage(
        BME280::OSR_X1,
        BME280::OSR_X1,
        BME280::OSR_X1,
        BME280::Mode_Forced,
        BME280::StandbyTime_1000ms,
        BME280::Filter_Off,
        BME280::SpiEnable_False,
        BME280I2C::I2CAddr_0x77 // I2C address 77 pour BME 280 Adafruit.
        );

BME280I2C bme(parametrage);


void printBME280Data(Stream* client);
int erreur = 0;
int nb = 0;

void setup() {
    Serial.begin(SERIAL_BAUD);
    while (!Serial) {
    }

    Wire.begin();
    
    size_t clock = Wire.getClock();
    Serial.print("clock : ");
    Serial.println(clock);

    while (!bme.begin()) {
        Serial.println("Could not find BME280 sensor!");
        delay(1000);
    }

    switch (bme.chipModel()) {
        case BME280::ChipModel_BME280:
            Serial.println("Found BME280 sensor! Success.");
            break;
        case BME280::ChipModel_BMP280:
            Serial.println("Found BMP280 sensor! No Humidity available.");
            break;
        default:
            Serial.println("Found UNKNOWN sensor! Error!");
    }
 }

void loop() {
    printBME280Data(&Serial);
    delay(100);
}

void printBME280Data(Stream* client) {
    float temp(NAN), hum(NAN), pres(NAN);

    BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
    BME280::PresUnit presUnit(BME280::PresUnit_hPa);

    bme.read(pres, temp, hum, tempUnit, presUnit);
    if (temp > 50 || temp < 0) ++erreur;
    nb++;
    client->print("Temp: ");
    client->print(temp);
    client->print(" °C");
    client->print("\tHum: ");
    client->print(hum);
    client->print(" %");
    client->print("\tPres: ");
    client->print(pres);
    client->print(" hPa\t");
    client->print(nb);
    client->print("\t");
    client->println(erreur);
}