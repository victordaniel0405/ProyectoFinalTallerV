/*
 * File:   ModuloTMR0.c
 * Author: Victor Muñoz
 *
 * Created on 7 de noviembre de 2016, 03:32 PM
 */


#include <xc.h>
#include <stdbool.h>
#include "HAL.h"
#include "ModuloTMR0.h"


extern char tiempoAlto;

void configuracionTMR0(void) {
    on0 = false; // Variable para el TMR0
    contadorPWM = 0; // Se inicia el contador del PWM
    
    // Configuración del pin PWM
    TRISBbits.TRISB0 = 0; // Se configura el pin como salida
    LATBbits.LATB0 = 1; // Se inicia el pin encendido
    
    // Configuracion TMR0
    T0CONbits.T08BIT = 1; // Se configura el TMR0 de 8 bits
    T0CONbits.T0CS = 0; // Se asigna la señal principal : Fcy
    T0CONbits.PSA = 0; // Se asigna el preescaler del TMRO
    T0CONbits.T0PS = 6; // Se establece el preescaler en 1:128

    INTCONbits.TMR0IF = 0; // Se baja la bandera del TMR0
    INTCON2bits.TMR0IP = 1; // Prioridad alta para el TMR0
    INTCONbits.TMR0IE = 1; // Se activa la interrucion debida al overflow del TMRO  

    TMR0 = 252; // Semilla para  0.1 milisegundos
}

void tareaTMR0(void) {
    if (on0) {
        contadorPWM++;
        if (contadorPWM == tiempoAlto) {    // Se completa el ciclo de trabajo
            LATBbits.LATB0 = 0;
        }
        if (contadorPWM == 100) {   // Se completa el periodo
            LATBbits.LATB0 = 1;
            contadorPWM = 0;
        }
        on0 = false;
    }
}

void isrTMR0(void) {
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        on0 = true;
        TMR0 = 252;
        return;
    }
}