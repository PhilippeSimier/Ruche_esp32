/*
 Utilisation de l'interface i2s dans l'ESP32 avec une tache
 Inter-IC Sound, Integrated Interchip Sound, ou IIS

https://docs.espressif.com/projects/esp-idf/en/v3.3/api-reference/peripherals/i2s.html#_CPPv414i2s_dac_mode_t

  I2S_DAC_CHANNEL_RIGHT_EN : gpio 25
  I2S_DAC_CHANNEL_LEFT_EN  : gpio 26
  I2S_DAC_CHANNEL_BOTH_EN : les deux (pour du stéréo)
 */


#include "DdsI2s.h"

DdsI2s leDds(100); //init du bitrate

QueueHandle_t DdsI2s::queueDds = xQueueCreate(64, sizeof (ddsConfig_t)); //comment déplacer cette ligne dans la classe ?

void setup() {
    Serial.begin(115200); //au cas ou    
    leDds.begin();

}

void loop() {
    // delay(1); //indispensable sinon le watchdog provoque un reset
    char c;
    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case 's': leDds.stop();
                break;
            case 'a': leDds.start();
                break;
            case 'b': for (int n = 0; n < 200; n++) {
                    leDds.setFrequency(1000);
                    leDds.sendBit();
                    leDds.off();
                    leDds.sendBit();
                    leDds.off();
                }
                break;
            case '2': leDds.updateSampleRate(200);
                break;
            case '4': leDds.updateSampleRate(400);
                break;
            case 'f': leDds.setFrequency(1000);
                leDds.start();
                break;
            case 'g': leDds.setFrequency(2000);
                leDds.start();
                break;
        }
    }
}