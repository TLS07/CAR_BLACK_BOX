/*
 * File:   main.c
 * Author: 25014
 *
 * Created on 31 December, 2025
 */

#pragma config WDTE = OFF

#include <xc.h>
#include "main.h"
char *gear[]={"GN","GR","G1","G2","G3","G4"};
unsigned char pass[5]="1100";
unsigned char user_pass[5];
unsigned char login_index = 0;
unsigned char login_delay = 0;
unsigned char attempts = 3;
unsigned char attempts_left = 3;
unsigned int lock_timer = 0;
unsigned char lock_flag = 0;
unsigned char menu_option=0;


void init_config()
{
    init_adc();
    init_clcd();
    init_digital_keypad();
    init_i2c(100000); 
    init_ds1307();
    init_uart();
    
}

void main(void) {
    init_config();
    
    unsigned char key, operation = 0;
    
    while(1)
    {
      
        key = read_digital_keypad(STATE);
        
        if(key == SW4)
        {
            operation = 1;
            clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            
        }
       
        if(operation == 0)
        {
            dashboard(key);
        }
        else if(operation == 1)
        {
            // login screen
            login_screen(&operation);


        }
        else if(operation == 2)
        {
            // menu part
            menu_option=menu_screen();
            
            switch(menu_option)
            {
                case 1: view_log();break;
                case 2: clear_log(); break;
                case 3: download_log(); break;
                case 4: set_time(); break;
                case 5: change_password(pass); break;
                case 6:  
                       operation=0;
                       clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
                       break;
                
                
            }
        }
           
    }
}
