/* 
 * File:   Dds.h
 * Author: Anthony (f4goh@orange.fr)
 *
 * Created on 23 juillet 2021, 11:35
 */

#ifndef DDS_H
#define DDS_H
#include <Arduino.h>
#include <driver/dac.h>

class Dds {
public:
    Dds();
    Dds(const Dds& orig);
    virtual ~Dds();

    void begin(float splFreq, float mkFreq, float shFreq, dac_channel_t dac, gpio_num_t sLed);
    void setFrequency(float freq);
    void stop();
    void setPhase(int ph);
    void enableMark();
    void enableSpace();

private:
    hw_timer_t * timer;
    void IRAM_ATTR interuption();
    static void marshall();
    uint32_t computeDdsWord(float freq);

    static Dds* anchor;
    gpio_num_t syncLed;
    dac_channel_t dacChannel;
    int samplingFrequency;
    uint32_t ddsMark;
    uint32_t ddsSpace;
    volatile uint32_t ddsAccu; //accumulateur du dds
    volatile uint32_t ddsWord; //mot de consigne image de la fréquence
    volatile int phase;
};

#endif /* DDS_H */

