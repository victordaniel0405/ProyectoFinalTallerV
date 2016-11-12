/* 
 * File:   ModuloTMR1
 * Author: Victor Muñoz
 * Comments:
 * Revision history: 
 */
  
#ifndef MODULO_TMR1_H
#define	MODULO_TMR1_H

#include <xc.h>  
#include <stdbool.h>

volatile bool on1;
int contadorLED;

void configuracionTMR1(void);
void tareaTMR1(void);
void isrTMR1(void);


#endif	/* MODULO_TMR1_H */

