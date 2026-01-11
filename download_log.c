
#include"main.h"
extern unsigned int address;
void download_log(void)
{
    unsigned char total_log=0;
    unsigned char eeprom_addr=0;
    unsigned char i,j;
    
   
    total_log=address/10;
    if(total_log==0)
    {
        uart_tx_string("-------NO DATA LOGS FOUND-------\r\n");
        return;
    }
    uart_tx_string("-----------DATA LOG---------\r\n");
    uart_tx_string("\r\n");
    uart_tx_string("NO.   TIME     EVENT  SPEED\r\n");
    uart_tx_string("----------------------------\r\n");
    for(i=0;i<total_log;i++)
    {
        //serial no
        uart_tx_char('0' + (i + 1));
        uart_tx_string(".  ");
        
        /* hh */
        uart_tx_char(read_external_eeprom(eeprom_addr++));
        uart_tx_char(read_external_eeprom(eeprom_addr++));
        uart_tx_char(':');
        
        /* mm */
        uart_tx_char(read_external_eeprom(eeprom_addr++));
        uart_tx_char(read_external_eeprom(eeprom_addr++));
        uart_tx_char(':');
        
        /* ss */
        uart_tx_char(read_external_eeprom(eeprom_addr++));
        uart_tx_char(read_external_eeprom(eeprom_addr++));
        uart_tx_string("   ");
                
         /* Event */
        uart_tx_char(read_external_eeprom(eeprom_addr++));
        uart_tx_char(read_external_eeprom(eeprom_addr++));
        uart_tx_string("      ");

        /* Speed */
        uart_tx_char(read_external_eeprom(eeprom_addr++));
        uart_tx_char(read_external_eeprom(eeprom_addr++));

        uart_tx_string("\r\n");

    }
     clcd_print(" Logs Downloaded", LINE1(0));
     __delay_ms(3000);
     return;
}