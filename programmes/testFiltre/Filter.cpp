/* 
 * File:   Filter.cpp
 * Author: philippe SIMIER SNIR Touchard Washington
 * 
 * Brief: Cette classe implémente un filtre IIR
 * le code utilise la transformée bilinéaire pour synthétiser un filtre passe-bas 
 * Reste à faire le filtre passe bande et le filtre passe haut
 * 
 * doc : http://www.iowahills.com/4IIRFilterPage.html
 *       https://cpge.frama.io/fiches-cpge/Python/80-Filtrage/
 * 
 * Created on 17 octobre 2021, 09:02
 */

#include "Filter.h"

Filter::Filter(float _splFreq,
        adc1_channel_t _adc1Channel,
        dac_channel_t _dacChannel
        ) :
splFreq(_splFreq),
adc1Channel(_adc1Channel),
dacChannel(_dacChannel),
timer(NULL),
n(0)
{
    anchor = this;
    // Second ordre m = 0.1
    a[0] = 0.084971;
    a[1] = 0.16994;
    a[2] = 0.084971;
    b[1] = 1.55193;
    b[2] = -0.89181; 
    
}

Filter::Filter(const Filter& orig) {
}

Filter::~Filter() {
}

void Filter::begin() {

    dac_output_enable(dacChannel);

    adc1_config_width(ADC_WIDTH_BIT_12); // Configuration de la résolution
    adc1_config_channel_atten(adc1Channel, ADC_ATTEN_DB_11); // Configuration de l'atténuation tension d'entrée /4

    timer = timerBegin(0, 80, true);  // Configuration du timer
    timerAttachInterrupt(timer, Filter::marshall, true);  // Attache une fonction au timer
    timerAlarmWrite(timer, 1000000 / splFreq, true);   // Configuration de la fréquence d'échantillonage
    timerAlarmEnable(timer);  // Lancement du timer

}

void Filter::marshall() {
    anchor->interuption();
}

void IRAM_ATTR Filter::interuption() {
   
    xthal_set_cpenable(1);      // enable FPU
    xthal_save_cp0(cp0_regs);   // Save FPU registers

    x[n] = adc1_get_raw(adc1Channel); // Lecture de la valeur sur adc1

    // Calcul de l'équation de récurrence filtre IIR
    y[n]  = a[0] * x[ n];
    y[n] += a[1] * x[(n-1) & MASQUE_TAMPON];
    y[n] += a[2] * x[(n-2) & MASQUE_TAMPON];
    y[n] += b[1] * y[(n-1) & MASQUE_TAMPON];
    y[n] += b[2] * y[(n-2) & MASQUE_TAMPON];
  
        
    dac_output_voltage(dacChannel, y[n] / 16); //envoi de la valeur entière vers le dac
    n = (n + 1) & MASQUE_TAMPON;              // incrémentation de n
    
    xthal_restore_cp0(cp0_regs);    // Restore FPU  
    xthal_set_cpenable(0);          // and turn it back off
}

/**
 * @brief méthode pour calculer les coefficients 
 * pour un filtre passe bas du premier ordre
 *
 * @param fc la fréquence de coupure en Hz
 */
void Filter::setLPFOrdre1(float fc){
    
   
    float A = splFreq / (M_PI * fc);
    
    a[0] = 1/(1+A);
    a[1] = a[0];
    a[2] = 0;
    
    b[1] = (A-1)/(A+1);
    b[2] = 0;   
}

Filter* Filter::anchor = NULL;





