/*
 * File:   menu.c
 * Author: Srinath
 */

#include <xc.h>
#include "main.h"

#define TOTAL_MENU_ITEMS 6

// Menu strings
static const char *menu[TOTAL_MENU_ITEMS] =
{
    "View Log",
    "Clear Log",
    "Download Log",
    "Set Timer",
    "Change Password",
    "Exit"
};

/*
 * Function: menu_screen
 * Returns : menu serial number (1 to 6)
 */
unsigned char menu_screen(void)
{
    unsigned char key;
    unsigned char index = 0;     // selected menu index
    unsigned char start = 0;     // first visible item
    unsigned char prev_start=0xff;

    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);

    while (1)
    {
        if(start!=prev_start)
        {
        clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
        // Display two menu items
        clcd_putch('*', LINE1(0));
        clcd_print(menu[start], LINE1(2));

        clcd_putch(' ', LINE2(0));
        clcd_print(menu[start + 1], LINE2(2));
        prev_start=start;
        }

        // Place star correctly
        if (index == start)
        {
            clcd_putch('*', LINE1(0));
            clcd_putch(' ', LINE2(0));
        }
        else
        {
            clcd_putch(' ', LINE1(0));
            clcd_putch('*', LINE2(0));
        }

        key = read_digital_keypad(STATE);

        // Scroll UP
        if (key == SW1)
        {
            if (index > 0)
            {
                index--;
                if (index < start)
                    start--;
            }
        }

        // Scroll DOWN
        else if (key == SW2)
        {
            if (index < TOTAL_MENU_ITEMS - 1)
            {
                index++;
                if (index > start + 1)
                    start++;
            }
        }

        // ENTER
        else if (key == SW4)
        {
            clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            return (index + 1);   // RETURN MENU NUMBER
        }

       
    }
}
