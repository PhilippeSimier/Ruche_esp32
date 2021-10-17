/* 
 * File:   Filter.cpp
 * Author: philippe SIMIER SNIR Touchard Washington
 * 
 * doc : https://microcontrollerslab.com/adc-esp32-measuring-voltage-example/
 * 
 * Created on 17 octobre 2021, 09:02
 */

#include "Filter.h"
/*
 * ADC_CHANNEL_6 --> GPIO34
 */
Filter::Filter(float _splFreq,
            adc1_channel_t _adc1Channel,
            dac_channel_t _dacChannel
            ):
splFreq(_splFreq),
adc1Channel(_adc1Channel),
dacChannel(_dacChannel),
timer(NULL) 
{
    anchor = this;
}

Filter::Filter(const Filter& orig) {
}

Filter::~Filter() {
}

void Filter::begin() {

    dac_output_enable(dacChannel);
    
    adc1_config_width(ADC_WIDTH_BIT_9);   // Configuration de la résolution
    adc1_config_channel_atten(adc1Channel, ADC_ATTEN_DB_11);   // Configuration de l'atténuation
    
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, Filter::marshall, true);
    timerAlarmWrite(timer, 1000000 / splFreq, true);
    timerAlarmEnable(timer);

    

}

void Filter::marshall() {
    anchor->interuption();
}

void IRAM_ATTR Filter::interuption() {
    
    accum = adc1_get_raw(adc1Channel);   // Lecture de la valeur sur adc1
    accum = accum/2;
    dac_output_voltage(dacChannel, accum); //envoi de la valeur vers le dac    
}

Filter* Filter::anchor = NULL;





