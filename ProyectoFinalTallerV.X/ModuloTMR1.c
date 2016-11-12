/*
 * File:   ModuloTMR1.c
 * Author: Victor Muñoz
 *
 * Created on 7 de noviembre de 2016, 07:27 PM
 */


#include <xc.h>
#include <stdbool.h>
#include "ModuloTMR1.h"
#include "ModuloMux.h"
#include "ModuloADC.h"

extern char iSensor;

void configuracionTMR1(void) {
    on1 = false;
    TRISAbits.RA1 = 0; // LED de estado
    LATAbits.LA1 = 1; // Comienza encendido

    // Configuracion TMR1
    T1CONbits.RD16 = 1; // Se configura el TMR1 de 16 bits
    T1CONbits.T1CKPS = 3; // Se establece el preescaler de 1:8
    T1CONbits.TMR1CS = 0; // Se asigna la señal del TMR1: interna Fosc/4
    T1CONbits.T1OSCEN = 0; // Se deshabilita el oscilador del TMR1
    T1CONbits.TMR1ON = 1; // Se enciende el TMR1

    PIR1bits.TMR1IF = 0; // Se baja la bandera del TMR1
    IPR1bits.TMR1IP = 1; // Prioridad alta para el TMR1
    PIE1bits.TMR1IE = 1; // Se activa la interrucion debida al overflow del TMR1

    TMR1 = 3036; // Semilla para 0.1 segundos
}

void tareaTMR1(void) {
    if (on1) {
        contadorLED++;
        if (contadorLED == 10) {
            LATAbits.LA1 = ~LATAbits.LA1;
            contadorLED = 0;
        }
        muxSelect(iSensor); // Se selecciona el canal
        iniciarConversion(); // Se realiza la conversión            
        on1 = false;
    }
}

void isrTMR1(void) {
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1 = 3036; // 0.1 segundos
        on1 = true;
        return;
    }
}
