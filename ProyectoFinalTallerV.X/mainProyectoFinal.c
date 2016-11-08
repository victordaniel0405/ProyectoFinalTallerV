/*
 * File:   mainProyectoFinal.c
 * Author: Victor Muñoz
 *
 * Created on 7 de noviembre de 2016, 01:24 PM
 */

#include <xc.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "HAL.h"
#include "ConfigurationBits.h"
#include "ModuloMux.h"
#include "ModuloTMR0.h"
#include "ModuloTMR1.h"
#include "ModuloADC.h"
#include "ModuloPWM.h"
#include "ModuloSerial.h"

char bufferTransmision[64];

short sensorsData[5];
char iSensor;

void main(void) {

    // Configuramos el pin RC2 como un "pwm" controlado por TMR1
    TRISCbits.RC2 = 0;  // Se configura el pin como salida
    LATCbits.LC2 = 1;   // Se inicia el pin apagado
    
    iSensor = 0; // Se inicia el valor del indice del vector sensorsData en 0
    
    configuracionMux();
    configuracionTMR0();
    configuracionTMR1();
    configuracionADC();
    configuracionPuertoSerial();    // Solo se encuentra activa la transmisión

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
            sprintf(bufferTransmision,"Dato Sensor #%u = %u \r\n",iSensor+1,adcValue);
            //sendStringChar(bufferTransmision);
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
    isrTMR1();
    isrADC();
    isrTMR0();
}