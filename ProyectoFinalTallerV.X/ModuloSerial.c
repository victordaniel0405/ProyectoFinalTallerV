/*
 * File:   ModuloSerial.c
 * Author: Victor Muñoz
 *
 * Created on 7 de noviembre de 2016, 07:12 PM
 */


#include <xc.h>
#include "ModuloSerial.h"

void configuracionPuertoSerial(void) {
    //Comunicacion Serial
    TRISCbits.TRISC7 = 1; // Para la comunicacion serial
    TRISCbits.TRISC6 = 0; // para la comunicacion serial
    /* Configuracion del puerto Serial*/
    TXSTAbits.BRGH = 1; // Alta velocidad
    TXSTAbits.TXEN = 1; // Activamos el modulo de transmision
    TXSTAbits.SYNC = 0; // Modo asincrono
    TXSTAbits.TX9 = 0;  // Transmision de datos a 8 bit

    RCSTAbits.RX9 = 0;  // Recepcion de datos de 8 bit
    RCSTAbits.CREN = 1; // Modo continuo activado
    RCSTAbits.SPEN = 1; // Activamos el puerto serial

    SPBRG = 64;         // Para transmitir a 19200bps

    //IPR1bits.RCIP = 1; // Configuramos la interrupcion por recepcion como alta prioridad
    //PIR1bits.RCIF = 0; // Bajamos la bandera por recepcion
    //PIE1bits.RCIE = 1; // Activamos la bandera de la interrupcion por recepcion

    IPR1bits.TXIP = 0; // Configuramos la interrupcion por transmision como baja prioridad
    //PIR1bits.TXIF = 0; // Bajamos la bandera por recepcion
    PIE1bits.TXIE = 0; // Activamos la bandera de la interrupcion por recepcion

    /* Final de la config del puerto serial*/
}

void sendChar(char dataToSend) {
    while (TXSTAbits.TRMT == 0) {
        NOP();
    }
    TXREG = dataToSend;
}

void sendStringChar(char* stringToSend){
    while (*stringToSend != '\0') {
        sendChar(*stringToSend);
        stringToSend++;
    }
}

/*void isrRecepcion(void) {
    if (PIE1bits.RCIE && PIR1bits.RCIF) {
        bufferRecepcion = RCREG; // Leemos el RCREG -> bajamos la bandera de la interrupcion
        return;
    }
}*/

