/*
 * File:   ModuloADC.c
 * Author: Victor Muñoz
 *
 * Created on 7 de noviembre de 2016, 03:55 PM
 */


#include <xc.h>
#include "ModuloADC.h"

char i;

void configuracionADC(void){
    tareaADC = false;
    TRISAbits.TRISA0 = 1;   // Se configura el pin AN0 como una entrada
    
    ADCON0bits.ADCS = 2;    // Configuramos el Tad como 32 Tosc
    ADCON1bits.ADCS2 = 0;   // Configuramos el Tad como 32 Tosc
    //ADCON0bits.ADCS = 3;  // Configuracion del Reloj interno RC - modo Sleep
    //ADCON1bits.ADCS2 = 1; // Configuracion del Reloj interno RC - modo Sleep
    ADCON1bits.ADFM = 1;    // Configuramos con justificacion a la derecha (numeros enteros).
    ADCON1bits.PCFG = 14;   // Se configura el pin AN0 como análogo, todos los demas como digitales.

    IPR1bits.ADIP = 1; // Alta prioridad
    PIR1bits.ADIF = 0; // Bajamos la bandera
    PIE1bits.ADIE = 1; // Activamos la interrupcion
    
}


void iniciarConversion(void){
    NOP();
    ADCON0bits.ADON = 1; // Inicial a carga el C_hold
    // Esperar la carga del capacitor... hay que calcular
    for(i = 0; i < 7; i++){
        NOP();
    }
    NOP();
    ADCON0bits.GO = 1;
}

void isrADC(void){
    if(PIE1bits.ADIE && PIR1bits.ADIF){
        adcValue = ADRES;       // Se guarda el valor analogo 
        tareaADC =  true;   
        PIR1bits.ADIF = 0;      // Se baja la bandera de la interrupcion
        ADCON0bits.ADON = 0;    // Se apaga la carga el C_hold
        return;
    }
}
