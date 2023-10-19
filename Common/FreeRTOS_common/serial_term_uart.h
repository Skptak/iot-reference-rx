/*
 * rskrx65n_uart.h
 * --> serial_term_uart.h
 *
 *  Created on: Feb 8, 2018
 *      Author: godocha01
 */

#ifndef VENDOR_CODE_RSKRX65N_UART_H_
#define VENDOR_CODE_RSKRX65N_UART_H_

void uart_config(void);
void uart_string_printf(char * pString);
void mbedtls_string_printf(void * ssl, int level, const char * file, int line, const char * str);

#endif /* VENDOR_CODE_RSKRX65N_UART_H_ */
