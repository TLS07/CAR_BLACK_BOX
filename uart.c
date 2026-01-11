#include"main.h"
void init_uart(void)
{
    /*
     baurd rate=9600
     Tx=>C6
     Rx=>C7
     */
    
    TRISC6=0;  //TX output
    TRISC7=1;  //RX input

    SYNC=0;    //asysnchornus
    BRGH =1;   //high speed
    SPBRG=129; // for 9600 baurd rate
    
    TX9=0;     //8 bit transmisson
    SPEN=1;    //enable transmitter
    TXEN=1;    //transmit enable
}

void uart_tx_char(unsigned char byte)
{
    while(TXIF!=1);   //wait till TXREG is empty
    TXREG=byte;       // load data
}
void uart_tx_string(unsigned char *s)
{
    while(*s!='\0')     //till end of string
    {
        uart_tx_char(*s++);
    }
}