/*
 * File:   ModuloMux.c
 * Author: Victor Muñoz
 *
 * Created on 7 de noviembre de 2016, 04:31 PM
 */


#include <xc.h>
#include "HAL.h"
#include "ModuloMux.h"

void configuracionMux(void){
    // Selectores para el Mux 8 - 1
    TRISCbits.RC3 = 0;
    TRISCbits.RC4 = 0;
    TRISCbits.RC5 = 0;

    // Se inician los selectores en el primer canal
    MuxA = 0;
    MuxB = 0;
    MuxC = 0;
}

void muxSelect(int input){
    switch (input) {
        case 0:
            MuxA = 0;
            MuxB = 0;
            MuxC = 0;
            break;
        case 1:
            MuxA = 1;
            MuxB = 0;
            MuxC = 0;
            break;
        case 2:
            MuxA = 0;
            MuxB = 1;
            MuxC = 0;
            break;
        case 3:
            MuxA = 1;
            MuxB = 1;
            MuxC = 0;
            break;
        case 4:
            MuxA = 0;
            MuxB = 0;
            MuxC = 1;
            break;
        default:
            break;
    }
}