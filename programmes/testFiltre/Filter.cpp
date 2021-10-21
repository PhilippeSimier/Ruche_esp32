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
n(0) {
    anchor = this;
    
    a[0] = 1.0;
    a[1] = 0.0;
    a[2] = 0.0;
    b[1] = 0.0;
    b[2] = 0.0;

}

Filter::Filter(const Filter& orig) {
}

Filter::~Filter() {
}

void Filter::begin() {

    dac_output_enable(dacChannel);

    adc1_config_width(ADC_WIDTH_BIT_12); // Configuration de la résolution
    adc1_config_channel_atten(adc1Channel, ADC_ATTEN_DB_11); // Configuration de l'atténuation tension d'entrée /4

    timer = timerBegin(0, 80, true); // Configuration du timer
    timerAttachInterrupt(timer, Filter::marshall, true); // Attache une fonction au timer
    timerAlarmWrite(timer, 1000000 / splFreq, true); // Configuration de la fréquence d'échantillonage
    timerAlarmEnable(timer); // Lancement du timer

}

void Filter::marshall() {
    anchor->interuption();
}

void IRAM_ATTR Filter::interuption() {

    xthal_set_cpenable(1); // enable FPU
    xthal_save_cp0(cp0_regs); // Save FPU registers

    x[n] = adc1_get_raw(adc1Channel); // Lecture de la valeur sur adc1

    // Calcul de l'équation de récurrence filtre IIR
    y[n] = b[0] * x[ n];
    y[n] += b[1] * x[(n - 1) & MASQUE_TAMPON];
    y[n] += b[2] * x[(n - 2) & MASQUE_TAMPON];
    y[n] -= a[1] * y[(n - 1) & MASQUE_TAMPON];
    y[n] -= a[2] * y[(n - 2) & MASQUE_TAMPON];


    dac_output_voltage(dacChannel, y[n] / 16); //envoi de la valeur entière vers le dac
    n = (n + 1) & MASQUE_TAMPON; // incrémentation de n

    xthal_restore_cp0(cp0_regs); // Restore FPU  
    xthal_set_cpenable(0); // and turn it back off
}

/**
 * @brief méthode pour calculer les coefficients 
 * d'un filtre passe bas du premier ordre
 *
 * @param fc la fréquence de coupure en Hz
 */
void Filter::setLPFOrdre1(float fc) {


    float A = splFreq / (M_PI * fc);

    b[0] = 1 / (1 + A);
    b[1] = b[0];
    b[2] = .0;

    a[1] = (1 -A) / (1 + A);
    a[2] = .0;
}

/**
 * Methode pour obtenir l'équation de récurrence sous forme litérale
 * @param client le flux de sortie
 */
void Filter::printEquaReccurence(Stream* client) {

    client->print("Yn = ");
    if (std::fpclassify(b[0]) != FP_ZERO) {
        client->printf("%.4f", b[0]);
        client->print(" Xn ");
    }
    if (std::fpclassify(b[1]) != FP_ZERO) {
        client->print(" + ");
        client->printf("%.4f", b[1]);
        client->print(" Xn_1 ");
    }
    if (std::fpclassify(b[2]) != FP_ZERO) {
        client->print(" + ");
        client->printf("%.4f", b[2]);
        client->print(" Xn_2 ");
    }
    if (std::fpclassify(a[1]) != FP_ZERO) {
        client->print(" + ");
        client->printf("%.4f", a[1]);
        client->print(" Yn_1 ");
    }
    if (std::fpclassify(a[2]) != FP_ZERO) {
        client->print(" + ");
        client->printf("%.4f", a[2]);
        client->println(" Yn_2");
    }
    client->println(" ");
}

/**
 * Methode pour fixer les coefficients de l'équation de réccurence 
 * @param _a le tableau des coefficients a
 * @param _b le tableau des coefficients b
 */
void Filter::setEquaReccurence(float _a[3],float _b[3]){
   for(int i = 0; i<3; i++){
       a[i] = _a[i];
       b[i] = _b[i];
   } 
}

Filter* Filter::anchor = NULL;





