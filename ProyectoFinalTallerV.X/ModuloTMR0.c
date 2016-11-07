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

void configuracionTMR0(void) {
    // Configuracion TMR0
    on0 = false;            // Variable para el TMR0
    
    T0CONbits.T08BIT = 0;   // Se configura el TMR0 de 16 bits
    T0CONbits.T0CS = 0;     // Se asigna la señal principal : Fcy
    T0CONbits.PSA = 0;      // Se asigna el preescaler del TMRO
    T0CONbits.T0PS = 6;     // Se establece el preescaler en 1:128

    INTCONbits.TMR0IF = 0;  // Se baja la bandera del TMR0
    INTCON2bits.TMR0IP = 1; // Prioridad alta para el TMR0
    INTCONbits.TMR0IE = 1;  // Se activa la interrucion debida al overflow del TMRO  

    TMR0 = 26473;           // Semilla para 1 segundo
}

void isrTMR0(void) {
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        TMR0 = 26473;
        on0 = true;
        return;
    }
}

/*
void encendidoTMR0(void) {

}
*/

/*
void iniciarLedEstado(void) {
    TRISCbits.RC4 = 0; // Se define el pin del Led
    LED_ESTADO = 0; // Se inicia el con el led apagado
}*/
