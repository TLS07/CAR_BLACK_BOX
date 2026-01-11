/* 
 * File:   main.h
 * Author: 25014
 *
 * Created on 26 November, 2025, 5:53 PM
 */

#ifndef MAIN_H
#define	MAIN_H
#include "adc.h"
#include "digital_keypad.h"
#include "clcd.h"
#include "i2c.h"
#include "ds1307.h"
#include "external_eeprom.h"
#include <xc.h>
#include "uart.h"
void dashboard(unsigned char key);
void store_event(void);
void login_screen(unsigned char *oper);
unsigned char menu_screen(void);
void view_log(void);
void clear_log(void);
void set_time(void);
int my_strcmp(unsigned char *str1,unsigned char *str2);
void change_password(char *main_pwd);
void download_log(void);

#endif	/* MAIN_H */

