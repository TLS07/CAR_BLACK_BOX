#include"main.h"
/*
 SW1=>increase value
 Sw2=>change cursor
 SW4=>save and exit
 SW5=>exit without saving*/
#define DEC_TO_BCD(x)   (((x / 10) << 4) | (x % 10))
#define BCD_TO_DEC(x)   (((x >> 4) * 10) + (x & 0x0F))

void set_time(void)
{
    unsigned char clock_reg[3];
    unsigned char hh,mm,ss;
    unsigned char field=0;
    unsigned char key;
    unsigned short blink=0;
    
    get_time(clock_reg);
    
    hh=BCD_TO_DEC(clock_reg[0]);
    mm=BCD_TO_DEC(clock_reg[1]);
    ss=BCD_TO_DEC(clock_reg[2]);
    
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    clcd_print("HH:MM:SS", LINE1(4));
    
    while(1)
    {
        key=read_digital_keypad(STATE);
        
        if (key == SW1)   // Increment
        {
            if (field == 0 )
                hh=(hh+1)%24;
            else if (field == 1 ) 
                mm=(mm+1)%60;
            else if (field == 2) 
                ss=(ss+1)%60;
        }
        else if(key==SW2)
        {
            field = (field + 1) % 3;
        }
        else if (key == SW4)  // Save & Exit
        {
            write_ds1307(HOUR_ADDR, DEC_TO_BCD(hh));
            write_ds1307(MIN_ADDR,  DEC_TO_BCD(mm));
            write_ds1307(SEC_ADDR,  DEC_TO_BCD(ss));
            clcd_print("saving.....", LINE1(0));
            __delay_ms(3000);
            break;
        }
        else if(key==SW5)
        {
            clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            clcd_print("exiting....", LINE1(0));
             __delay_ms(3000);
            return;
        }
        blink++;
        if (blink >= 10)
         blink = 0;

            /* HH */
        if (field == 0 && blink < 5)
        {
            clcd_putch(' ', LINE2(4));
            clcd_putch(' ', LINE2(5));
        }
        else
        {
            clcd_putch((hh / 10) + '0', LINE2(4));
            clcd_putch((hh % 10) + '0', LINE2(5));
        }

        clcd_putch(':', LINE2(6));

        /* MM */
        if (field == 1 && blink < 5)
        {
            clcd_putch(' ', LINE2(7));
            clcd_putch(' ', LINE2(8));
        }
        else
        {
            clcd_putch((mm / 10) + '0', LINE2(7));
            clcd_putch((mm % 10) + '0', LINE2(8));
        }

        clcd_putch(':', LINE2(9));

        /* SS */
        if (field == 2 && blink < 5)
        {
            clcd_putch(' ', LINE2(10));
            clcd_putch(' ', LINE2(11));
        }
        else
        {
            clcd_putch((ss / 10) + '0', LINE2(10));
            clcd_putch((ss % 10) + '0', LINE2(11));
        }

        

    }
        clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
}