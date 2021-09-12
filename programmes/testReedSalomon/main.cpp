/* 
 * File:   main.cpp
 * Author: ale
 *
 * Created on 8 septembre 2021, 13:30
 */


#include "Rs.h"

using namespace std;


int main(int argc, char** argv) {

    Rs leRs;
    //préload sans bit stuffing avec fcs    
    uint8_t preload[] = {0x8C,0x62,0xB4,0x9A,0x9A,0x40,0x64,0x8C,0x62,0xB4,0x9A,0x9A,
    0x40,0x6A,0xAE,0x92,0x88,0x8A,0x62,0x40,0x62,0xAE,0x92,0x88,0x8A,0x64,0x40,
    0x65,0x3,0xF0,0x21,0x34,0x37,0x35,0x33,0x2E,0x34,0x31,0x4E,0x2F,0x30,0x30,
    0x30,0x31,0x36,0x2E,0x36,0x31,0x45,0x3E,0x74,0x65,0x73,0x74,0x65,0xE2};
    
    printf("Affiche toute les trames possible à partir du payload\n");

    for (int i = 100 + CTAG_MIN; i <= 100 + CTAG_MAX; i++) {
        leRs.fx25_print_all_frame(0, preload, (int) sizeof (preload), i);
    }
    
    
    
    uint8_t radio[268];
    int radioLen;
    
    leRs.fx25Generate (preload, (int) sizeof (preload),radio,&radioLen, 1);

    printf("Bilan de la trame FX.25 : %d data bytes\n", radioLen);
    leRs.fx_hex_dump(radio,radioLen);
    
    return 0;
}


        