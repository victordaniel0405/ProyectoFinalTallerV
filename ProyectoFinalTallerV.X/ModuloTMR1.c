/*
 * File:   ModuloTMR1.c
 * Author: Victor Muñoz
 *
 * Created on 7 de noviembre de 2016, 07:27 PM
 */


#include <xc.h>
#include <stdbool.h>
#include "ModuloTMR1.h"

void configuracionTMR1(void) {
    on1 = false;
    // Configuracion TMR1
    T1CONbits.RD16 = 1;   // Se configura el TMR1 de 16 bits
    T1CONbits.T1CKPS = 1; // Se establece el preescaler de 1:2
    T1CONbits.TMR1CS = 0; // Se asigna la señal del TMR1: interna Fosc/4
    T1CONbits.T1OSCEN = 0; // Se deshabilita el oscilador del TMR1
    T1CONbits.TMR1ON = 1; // Se enciende el TMR1
    
    PIR1bits.TMR1IF = 0; // Se baja la bandera del TMR1
    IPR1bits.TMR1IP = 1; // Prioridad alta para el TMR1
    PIE1bits.TMR1IE = 1; // Se activa la interrucion debida al overflow del TMR1

    TMR1 = 60536; // Semilla para 18 milisegundos
}

void isrTMR1(void) {
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1 = 0;   // 15 segundos
        on1 = true;
        LATCbits.LC2 ? TMR1 = 18036 : 63036; // Duty 1seg
        //LATCbits.LC2 ? TMR1 = 20536 : 60536; //Duty 2seg
        //LATCbits.LC2 ? TMR1 = 21786 : 59286; //Duty 2.5seg
        LATCbits.LC2 = ~LATCbits.LC2;
        return;
    }
}
