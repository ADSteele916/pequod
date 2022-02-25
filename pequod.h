/*
 * pequod.h
 *
 *  Created on: Feb. 24, 2022
 *      Author: Alex Steele
 */

#ifndef PEQUOD_H_
#define PEQUOD_H_

void configure_clock();

void configure_uart();

void send_byte(unsigned char data);

void send_long(unsigned long data);

#endif /* PEQUOD_H_ */
