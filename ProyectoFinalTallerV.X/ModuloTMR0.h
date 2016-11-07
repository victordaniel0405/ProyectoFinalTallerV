/* 
 * File:   ModuloTMR0.h
 * Author: Victor Muñoz
 * Comments:
 * Revision history: 
 */

#ifndef MODULO_TMR0_H
#define MODULO_TMR0_H

#include <xc.h> 
#include <stdbool.h>

volatile bool on0;

void configuracionTMR0(void);
void encendidoTMR0(void);
void isrTMR0(void);


#endif	/* MODULO_TMR0_H */

