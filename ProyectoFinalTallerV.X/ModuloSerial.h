/* 
 * File:   ModuloSerial.h
 * Author: Victor Muñoz
 * Comments:
 * Revision history: 
 */
  
#ifndef MODULO_SERIAL_H
#define	MODULO_SERIAL_H

#include <xc.h>  

void configuracionPuertoSerial(void);
void sendChar(char dataToSend);
void sendStringChar(char* stringToSend);

#endif	/* MODULO_SERIAL_H */

