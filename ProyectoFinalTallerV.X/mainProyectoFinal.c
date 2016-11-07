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
#include "ModuloMux.h"
#include "ModuloTMR0.h"
#include "ModuloADC.h"

short sensorsData[5];
char iSensor;

void main(void) {

    iSensor = 0; // Se inicia el valor del indice del vector sensorsData en 0
    
    configuracionMux();
    configuracionTMR0();
    configuracionADC();

    RCONbits.IPEN = 1; // Activamos el modelo de Prioridades en las interrupciones
    INTCONbits.PEIE = 1; // Activamos las interrupciones generadas por los perifericos
    INTCONbits.GIE = 1; // Activamos las interrupciones

    while (1) {
        NOP();
        if (on0) {
            muxSelect(iSensor);             // Se selecciona el canal
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

void interrupt low_priority ISR_bajaPrioridad(void) {
    /* Aca van TODO el manejo de las intr de baja prioridad */


}

void interrupt high_priority ISR_altaPrioridad(void) {
    /* Aca van TODO el manejo de las intr de alta prioridad */
    isrADC();
    isrTMR0();
}