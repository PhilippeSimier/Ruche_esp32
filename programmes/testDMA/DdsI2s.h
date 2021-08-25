/* 
 * File:   DdsI2s.h
 * Author: Anthony Le Cren
 *
 * Created on 18 août 2021, 17:33
 */

#ifndef DDSI2S_H
#define DDSI2S_H

#include <Arduino.h>
#include <driver/i2s.h>
#include <driver/dac.h>


#define DAC_CHANNEL DAC_CHANNEL_1   //numéro du dac
#define SYNC GPIO_NUM_2             //gpio pour led
#define NUM_SAMPLES 32
#define MIN_SAMPLING_FREQUENCY 20000

typedef enum {
    dB_0 = 0x0, /* 1/1 Default value */
    dB_6 = 0x1, /* 1/2 */
    dB_12 = 0x2, /* 1/4 */
    dB_18 = 0x3, /* 1/8 */
    dB_24 = 0x4, /* 1/16 */
} attenuation_t;


//structure de contôle du DDS utilisé dans la file pour la tache

typedef struct {
    uint32_t dephase;
    int attenuation;
    uint32_t incrementPhase;
    uint16_t nBuffer;
} ddsConfig_t;

class DdsI2s {
public:
    DdsI2s(float _bitRate = 100,
            dac_channel_t _dacChannel = DAC_CHANNEL_1,
            gpio_num_t _syncLed = GPIO_NUM_2);

    DdsI2s(const DdsI2s& orig);
    virtual ~DdsI2s();

    void begin();
    void setFrequency(float freq);
    void stop();
    void start();
    void off();
    void setPhase(int ph);
    void setAttenuation(int _attenuation);
    void sendBit();
    void updateSampleRate(float br);
    
    
private:
    void configureI2s();
    boolean isInteger(float num);
    void computeSampleRate(float br);
    TaskHandle_t TaskHandle_Dac;
    static void dma(void *pvParameter);
    int splFreq; // Fréquence d'échantillonage
    gpio_num_t syncLed;
    dac_channel_t dacChannel;

protected:
    uint32_t computeIncrementPhase(float freq);
    ddsConfig_t ddsConfig;
    float bitRate;
    static QueueHandle_t queueDds;
    

};

#endif /* DDSI2S_H */

