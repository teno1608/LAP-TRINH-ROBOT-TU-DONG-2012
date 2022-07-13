#include <18F4431.h>
#include <PIC18F4431_registers.h>
#include <stdlib.h>
#include <stdio.h>
#FUSES HS,NOWDT,NOLVP
#use delay(clock=20000000)
#use fast_io(a)
#use fast_io(d)
#use fast_io(c)
#use fast_io(e)

#define LCD_RS_PIN      PIN_B0                                 
#define LCD_RW_PIN      PIN_B1    
#define LCD_ENABLE_PIN  PIN_B2                                                              
#define LCD_DATA4       PIN_B4                                 
#define LCD_DATA5       PIN_B5                                  
#define LCD_DATA6       PIN_B6                                   
#define LCD_DATA7       PIN_B7
#include <lcd.c>
void lcd_putnum(int16 so,INT8 x,int8 y)
{
   INT32 a, b, c, d, e;
   a = so / 10000;
   b = (so - 10000 * a) / 1000;
   c = (so - 10000 * a - 1000 * b) / 100;
   d = (so - 10000 * a - 1000 * b - 100 * c) / 10;
   e = so - 10000 * a - 1000 * b - 100 * c - 10 * d;
   lcd_gotoxy (x, y);
   lcd_putc (a + 48);
   lcd_putc (b + 48);
   lcd_putc (c + 48);
   lcd_putc (d + 48);
   lcd_putc (e + 48);
}
 
#define ChanelA PIN_C4
#define ChanelB PIN_C5

signed int16 En2;

#INT_EXT1
void  EXT1_L2H_isr(void) 
{
INTEDG1^=1;
if (INTEDG1)
   {
   if (input(ChanelB)) {En2++;} 
   else {En2--;}
   }
else 
   { 
   if (input(ChanelB)) {En2--;}
   else {En2++;}
   }
}

#int_EXT2
void  EXT2_isr(void) 
{
INTEDG2^=1;
if (INTEDG2)
   {
   if (input(ChanelA)) {En2--;} 
   else {En2++;}
   }
else 
   { 
   if (input(ChanelA)) {En2++;}
   else {En2--;}
   }
}


void main()
{
   trisc=0xff;
   lcd_init();
   lcd_putc ("Ready.........");
   delay_ms(1000);
   lcd_putc ('\f');
   
   enable_interrupts(INT_EXT1);
   enable_interrupts(INT_EXT2);
   enable_interrupts(GLOBAL);
   ext_int_edge(1,L_to_H);
   ext_int_edge(2,L_to_H);
  
   En2=0;
   while(true)
      {
      printf(LCD_PUTC, "\fEn_count=%5Ld",En2);
      delay_ms(200);
//      lcd_putnum(En2,0,1);
      }

}
