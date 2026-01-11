/*
 * File:   dashboard.c
 * Author: 25014
 *
 * Created on 31 December, 2025
 */
#include <xc.h>
#include "main.h"
extern char time[9];
unsigned char clock_reg[3], speed[3] = {0};
char  *event[ ] = { "ON",  "GN", "G1", "G2", "G3", "G4", "GR", "C "};
int pos = 0;
unsigned int adc_val;
unsigned int address=0;
unsigned char prev_pos=0;
extern unsigned char login_index;
extern unsigned char login_delay = 0;
extern unsigned char user_pass[5];
extern unsigned char pass[5];
extern unsigned char attempts_left = 3;
extern unsigned int lock_timer ;
extern unsigned char lock_flag ;
unsigned char attempt_s[2];


void dashboard(unsigned char key) {
    
        clcd_print(" TIME     EV  SP", LINE1(0));
        
        // display time
        get_time(clock_reg);
        display_time(clock_reg);
        
        // event display ( Gear pos and speed )
        if (key==SW1)
        { 
            pos=7;
        }
        else if(key==SW2)
        {
            if(pos==7)
            {
                pos=1;
            }
            else if(pos<6)
            {
                pos++;
            }
        }
        else if(key==SW3)
        {
            if(pos==7)
            {
                pos=1;
            }
            else if(pos>1)
            {
                pos--;
            }
        }
        
        clcd_print(event[pos],LINE2(10));
        
        adc_val=read_adc(0)/10.23;//(0-99)
                
        speed[0]=(adc_val/10)+'0';
        speed[1]=(adc_val%10)+'0';
        speed[2]='\0';
        
        clcd_print(speed,LINE2(14));
        
        //to store events into eeprom
        if(prev_pos!=pos)
        {
            store_event();
            prev_pos=pos;
        }
 
}

void store_event(void)
{
    //to fetch time
    for(char i=0;i<8;i++)
    {
        if(i==2||i==5)
        {
            continue;
        }
        else
        {
            write_external_eeprom(address++,time[i]);
        }
    }
    //store event
    write_external_eeprom(address++,event[pos][0]);
    write_external_eeprom(address++,event[pos][1]);
    
    // storing speed
    write_external_eeprom(address++,speed[0]);
    write_external_eeprom(address++,speed[1]);
    
    if(address>99)
    {
        address=0;
    }
    
}

int my_strcmp(unsigned char *str1,unsigned char *str2)
{
    while(*str1!='\0'&& *str2!='\0')
    {
        if(*str1!=*str2)
        {
            return (*str1-*str2);
        }
        str1++;
        str2++;
    }
    return (*str1-*str2);
    
}

void login_screen(unsigned char *oper)
{
    unsigned char key;
    
    if(lock_flag)
    {
//        clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
        clcd_print("  User Blocked", LINE1(0));
        clcd_print("  Wait 30 Sec's", LINE2(0));

        __delay_ms(1000);
        lock_timer++;

        if (lock_timer >= 30)
        {
            lock_timer = 0;
            lock_flag = 0;
            attempts_left = 3;
            login_index = 0;
            
            clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            clcd_print("Enter Password", LINE1(0));
        }
        return;
    }
    clcd_print("Enter Password", LINE1(0));
    key = read_digital_keypad(STATE);
    if(*oper==1)
    {
    if (login_index < 4)
    {
        // blinking cursor
        if (login_delay < 5)
            clcd_putch('_', LINE2(login_index+4));
        else if (login_delay < 10)
            clcd_putch(' ', LINE2(login_index+4));
        else
            login_delay = 0;

        login_delay++;
        
    

        if (key == SW1)
        {
            user_pass[login_index] = '0';
            clcd_putch('*', LINE2(login_index+4));
            login_index++;
        }
        else if (key == SW2)
        {
            user_pass[login_index] = '1';
            clcd_putch('*', LINE2(login_index+4));
            login_index++;
        }
    }
    else
    {
        user_pass[4] = '\0';

        if (my_strcmp(user_pass,pass) == 0)
        {
            clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            clcd_print("Login Success", LINE1(0));
            __delay_ms(1000);

            *oper = 2;   // go to menu
        }
        else
        {
            attempts_left--;
            attempt_s[0]=attempts_left+'0';
            attempt_s[1]='\0';
            clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            clcd_print("Wrong Password", LINE1(0));
            clcd_print("Attempts left:",LINE2(0));
            clcd_print(attempt_s,LINE2(14));
            
            __delay_ms(1000);
            
            if(attempts_left==0)
            {
                lock_flag = 1;
                lock_timer = 0;
                clcd_write(CLEAR_DISP_SCREEN, INST_MODE);  
                return;
            }

            clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            clcd_print("Enter Password", LINE1(0));

            login_index = 0;  // reset for retry
        }
      }
    }
    
}






