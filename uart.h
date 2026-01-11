#ifndef UART_H
#define UART_H
/* uart baurd rate 9600
 TX=>rc6*/
void init_uart(void);
void uart_tx_char(unsigned char byte);
void uart_tx_string(unsigned char *s);

#endif