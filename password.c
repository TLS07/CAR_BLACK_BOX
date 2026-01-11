
#include"main.h"
/*
 SW1=>'0'
 SW2=>'1'*/

void change_password(char *main_pwd)
{
    unsigned char new_pwd[5] = "____";
    unsigned char confirm_pwd[5] = "____";
    unsigned char field = 0;
    unsigned char stage = 0;      // 0 = new, 1 = confirm
    unsigned char key;
    unsigned short blink = 0;
    unsigned char i;
    unsigned char bit;

    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    clcd_print("NEW PASSWORD", LINE1(2));

    while (1)
    {
        key = read_digital_keypad(STATE);

        /* Exit without saving */
        if (key == SW4)
            return;

        /* Blink timing */
        blink++;
        if (blink >= 10)
            blink = 0;

        /* ---------- INPUT HANDLING ---------- */
        if (key == SW1 || key == SW2)
        {
            if(key==SW1)
            {
                bit='0';
            }
            else if(key==SW2)
            {
                bit='1';
            }

            if (stage == 0)
                new_pwd[field] = bit;
            else
                confirm_pwd[field] = bit;

            field++;   //  move cursor

            if (field >= 4)
            {
                if (stage == 0)
                {
                    stage = 1;
                    field = 0;
                    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
                    clcd_print("RE-ENTER PWD", LINE1(2));
                }
                else
                {
                    /* Compare passwords */
                    if (my_strcmp(new_pwd, confirm_pwd) == 0)
                    {
                        for( i=0;i<4;i++)
                        {
                            main_pwd[i]=new_pwd[i];
                        }
                        main_pwd[4]='\0';
                        
                        clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
                        clcd_print("NEW PASSWORD ", LINE1(2));
                        clcd_print("    SET", LINE2(2));
                        __delay_ms(3000);
                        return;
                    }
                    else
                    {
                        clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
                        clcd_print("MISMATCH", LINE1(4));
                        __delay_ms(3000);

                        for (i = 0; i < 4; i++)
                        {
                            new_pwd[i] = '_';
                            confirm_pwd[i] = '_';
                        }
                        new_pwd[4]='\0';
                        confirm_pwd[4]='\0';

                        field = 0;
                        stage = 0;

                        clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
                        clcd_print("NEW PASSWORD", LINE1(2));
                    }
                }
            }
        }

        /* ---------- DISPLAY ---------- */
        unsigned char cursor = (field < 4) ? field : 3;
        for (i = 0; i < 4; i++)
        {
            char ch;

            if (stage == 0)
                ch = new_pwd[i];
            else
                ch = confirm_pwd[i];

            if (i == cursor && blink < 5)
                clcd_putch(' ', LINE2(6 + i));
            else
            {
                if (ch == '_')  //text not entered 
                    clcd_putch('_', LINE2(6 + i));
                else            //text entered
                    clcd_putch('*', LINE2(6 + i));
                
            }
                
        }
    }
}
