/* 
 * File:   ModuloADC.h
 * Author: Victor Muñoz
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MODULO_ADC_H
#define	MODULO_ADC_H

#include <xc.h> 
#include <stdbool.h>

volatile bool tareaADC = false;
volatile short adcValue;

void configuracionADC(void);
void iniciarConversion(void);
void isrADC(void);


#endif	/* MODULO_ADC_H */

