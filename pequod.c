/*
 * pequod.c
 *
 *  Created on: Feb. 24, 2022
 *      Author: Alex Steele
 */

#include <msp430.h>

#include "pequod.h"



void configure_clock() {
    BCSCTL1 = CALBC1_1MHZ; // Set range
    DCOCTL = CALDCO_1MHZ;
    BCSCTL2 &= ˜(DIVS_3); // SMCLK = DCO = 1MHz
}


void configure_uart() {
    P1SEL = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2; // Use SMCLK
    UCA0BR0 = 104; // Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
    UCA0BR1 = 0; // Set baud rate to 9600 with 1MHz clock
    UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
    UCA0CTL1 &= ˜UCSWRST; // Initialize USCI state machine
}


void send_byte(unsigned char data) {
    while (! (IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
    UCA0TXBUF = data; // Write new data
}


void send_long(unsigned long data) {
    unsigned char TXBytes[4];
    // Break data into its constituent bytes.
    for (unsigned int i = 0; i < 4; i++) {
        TXBytes[3 - i] = (unsigned char) (data >> 8 * i);
    }
    // Send the bytes of data in big-endian order.
    for (unsigned int i = 0; i < 4; i++) {
        send_byte(TXBytes[i]);
    }
}
