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

#define SAMPLING_FREQUENCY 25000    //fréquence d'échantillonage
#define DAC_CHANNEL DAC_CHANNEL_1   //numéro du dac
#define SYNC GPIO_NUM_2             //gpio pour sync led et oscillo

#if ((10000000/SAMPLING_FREQUENCY)%10>0)
#error "Fréquence d'échantillonage incompatible avec la période du timer"
#endif

class Dds {
public:
    Dds(float _splFreq = SAMPLING_FREQUENCY,  
        dac_channel_t _dacChannel = DAC_CHANNEL_1, 
        gpio_num_t _syncLed = GPIO_NUM_2);
    
    Dds(const Dds& orig);
    virtual ~Dds();

    void begin();
    
    void setFrequency(float freq);
    void stop();
    void setPhase(int ph);


private:
    hw_timer_t * timer;
    void IRAM_ATTR interuption();
    static void marshall();
    

    static Dds* anchor;
    gpio_num_t syncLed;
    dac_channel_t dacChannel;
    volatile uint32_t accumulateur;        // Accumulateur de phase
    
protected:
    uint32_t computeIncrementPhase(float freq);
    
    volatile uint32_t incrementPhase;      // Increment de phase courant
    volatile uint32_t dephase;             // Valeur du déphasage de la porteuse  
    volatile uint32_t compteur;            // Compteur d'échantillons
    int splFreq;                           // Fréquence d'échantillonage
};

#endif /* DDS_H */

