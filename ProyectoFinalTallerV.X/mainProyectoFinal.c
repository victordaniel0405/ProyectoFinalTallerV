/*
 * File:   mainProyectoFinal.c
 * Author: Victor Muñoz
 *
 * Created on 7 de noviembre de 2016, 01:24 PM
 */

#include <xc.h>
#include <stdbool.h>
#include "HAL.h"
#include "ConfigurationBits.h"
#include "ModuloTMR0.h"
#include "ModuloADC.h"

void muxSelect(int input);
short sensorsData[5];
char iSensor;

void main(void) {

    // Selectores para el Mux 8 - 1
    TRISCbits.RC3 = 0;
    TRISCbits.RC4 = 0;
    TRISCbits.RC5 = 0;

    // Se inician los selectores en el primer canal
    MuxA = 0;
    MuxB = 0;
    MuxC = 0;

    iSensor = 0; // Se inicia el valor del indice del vector sensorsData en 0

    configuracionTMR0();
    configuracionADC();

    RCONbits.IPEN = 1; // Activamos el modelo de Prioridades en las interrupciones
    INTCONbits.PEIE = 1; // Activamos las interrupciones generadas por los perifericos
    INTCONbits.GIE = 1; // Activamos las interrupciones

    while (1) {
        NOP();
        if (on0) {
            muxSelect(iSensor); // Se selecciona el canal
            iniciarConversion();            // Se realiza la conversión
            
            on0 = false; 
        }
        if (tareaADC){
            sensorsData[iSensor] = adcValue;            // Se guarda el valor en el vector
            iSensor = (iSensor < 4) ? iSensor + 1 : 0;  // Se aumenta el contador
            
            tareaADC = false;
        }

    }
    return;
}

void muxSelect(int input) {
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

void interrupt low_priority ISR_bajaPrioridad(void) {
    /* Aca van TODO el manejo de las intr de baja prioridad */


}

void interrupt high_priority ISR_altaPrioridad(void) {
    /* Aca van TODO el manejo de las intr de alta prioridad */
    isrADC();
    isrTMR0();
}