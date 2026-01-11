#include "main.h"

/*
 SW1 => scroll up
 SW2 => scroll down
 SW5 => go back
*/
extern unsigned int address;

void view_log(void)
{
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    char line1[17];
    char line2[17];

    unsigned char key;
    unsigned char log_index = 0;
    unsigned char total_log;
    unsigned int eep_addr;

    total_log = address / 10; // each log occupies 10 bytes

    if (total_log == 0)
    {
        clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
        clcd_print("No Logs Found", LINE1(0));
        __delay_ms(1500);
        return;
    }

    while (1)
    {
        // -------- LINE 1 --------
        eep_addr = log_index * 10;

        line1[0] = (log_index+1) + '0';
        line1[1] = ' ';

        line1[2] = read_external_eeprom(eep_addr++);
        line1[3] = read_external_eeprom(eep_addr++);
        line1[4] = ':';
        line1[5] = read_external_eeprom(eep_addr++);
        line1[6] = read_external_eeprom(eep_addr++);
        line1[7] = ':';
        line1[8] = read_external_eeprom(eep_addr++);
        line1[9] = read_external_eeprom(eep_addr++);
        line1[10] = ' ';
        line1[11] = read_external_eeprom(eep_addr++);
        line1[12] = read_external_eeprom(eep_addr++);
        line1[13] = ' ';
        line1[14] = read_external_eeprom(eep_addr++);
        line1[15] = read_external_eeprom(eep_addr++);
        line1[16] = '\0';

        // -------- LINE 2 --------
        if (log_index + 1 < total_log)
        {
            eep_addr = (log_index + 1) * 10;

            line2[0] = (log_index + 2) + '0';
            line2[1] = ' ';
            line2[2] = read_external_eeprom(eep_addr++);
            line2[3] = read_external_eeprom(eep_addr++);
            line2[4] = ':';
            line2[5] = read_external_eeprom(eep_addr++);
            line2[6] = read_external_eeprom(eep_addr++);
            line2[7] = ':';
            line2[8] = read_external_eeprom(eep_addr++);
            line2[9] = read_external_eeprom(eep_addr++);
            line2[10] = ' ';
            line2[11] = read_external_eeprom(eep_addr++);
            line2[12] = read_external_eeprom(eep_addr++);
            line2[13] = ' ';
            line2[14] = read_external_eeprom(eep_addr++);
            line2[15] = read_external_eeprom(eep_addr++);
            line2[16] = '\0';
        }
        else
        {
            for (int i = 0; i < 16; i++) line2[i] = ' ';
            line2[16] = '\0';
        }

        // -------- UPDATE LCD --------
        clcd_print(line1, LINE1(0));
        clcd_print(line2, LINE2(0));

        // -------- READ KEYS --------
        key = read_digital_keypad(STATE);

        if (key == SW1 && log_index > 0)
        {
            log_index--; // scroll up
        }
        else if (key == SW2 && log_index < total_log - 1)
        {
            log_index++; // scroll down
        }
        else if (key == SW5)
        {
            clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            return; // go back to menu
        }

    }
}

void clear_log(void)
{
    //reset address to zero
    address=0;
    
    //print log cleared
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    clcd_print("Logs Cleared", LINE1(0));
    __delay_ms(3000);
}
