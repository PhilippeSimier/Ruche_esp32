/* 
 * File:   Filter.h
 * Author: philippe
 *
 * Created on 17 octobre 2021, 09:02
 * 
 *  ADC1 channel 6 is GPIO34
 * 
 */

#ifndef FILTER_H
#define FILTER_H

#include <Arduino.h>
#include <driver/adc.h>
#include <driver/dac.h>

#define SAMPLING_FREQUENCY 25000    //fréquence d'échantillonage en Hz

class Filter {
public:
    Filter(float _splFreq = SAMPLING_FREQUENCY,
            adc1_channel_t _adc1Channel = ADC1_CHANNEL_6,
            dac_channel_t _dacChannel = DAC_CHANNEL_1
            );

    Filter(const Filter& orig);
    virtual ~Filter();

    void begin();

private:
    hw_timer_t * timer;
    void IRAM_ATTR interuption();
    static void marshall();
    static Filter* anchor;

    int splFreq; // Fréquence d'échantillonage   
    adc1_channel_t adc1Channel;
    dac_channel_t dacChannel;
    int accum;

};

#endif /* FILTER_H */

