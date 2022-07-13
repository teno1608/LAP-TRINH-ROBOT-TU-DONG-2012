#include <18F4431.h>
#include <PIC18F4431_registers.h>
#include <stdlib.h>
#FUSES HS,NOWDT,NOLVP
#use delay(clock=20000000)
#use fast_io(a)
#use fast_io(d)
#use fast_io(c)
#use fast_io(e)

#define LCD_RS_PIN      PIN_D5                                 
#define LCD_RW_PIN      PIN_D6    
#define LCD_ENABLE_PIN  PIN_D7                                                              
#define LCD_DATA4       PIN_B0                                 
#define LCD_DATA5       PIN_B1                                  
#define LCD_DATA6       PIN_B2                                   
#define LCD_DATA7       PIN_B3
#include <lcd.c>
void lcd_putnum(int32 so,INT8 x,int8 y)
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

#bit br1=porte.1
#bit br2=porte.0
#bit trisbr1 = trise.1
#bit trisbr2 = trise.0
#bit dir1=portc.3
#bit dir2=portc.0
#bit trisdir1 = trisc.3
#bit trisdir2 = trisc.0
#bit pwm1=portc.2
#bit pwm2=portc.1
#bit trispwm1 = trisc.2
#bit trispwm2 = trisc.1

void dc1t(INT16 x)
{
   trispwm1 = trisdir1 = trisbr1 = 0;
   dir1 = 1;
   br1 = 0;
   setup_timer_2 (t2_div_by_1, 249, 1);
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (x);
}

void dc1n(INT16 x)
{
   trispwm1 = trisdir1 = trisbr1 = 0;
   dir1 = 0;
   br1 = 0;
   setup_timer_2 (t2_div_by_1, 249, 1);
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (x);
}

void resetdc1()
{
   trispwm1 = trisdir1 = trisbr1 = 0;
   setup_timer_2 (t2_div_by_1, 249, 1);
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (0);
   br1 = 1;
   dir1 = 0;
}

void dc2t(INT16 x)
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   dir2 = 1;
   br2 = 0;
   setup_timer_2 (t2_div_by_1, 249, 1);
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (x);
}

void dc2n(INT16 x)
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   br2 = 0;
   dir2 = 0;
   setup_timer_2 (t2_div_by_1, 249, 1);
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (x);
}

void resetdc2()
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   br2 = 1;
   dir2 = 0;
   setup_timer_2 (t2_div_by_1, 249, 1);
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (0);
}

int16 i;
///////////////////////////////////////////
void main()
{
/*
lcd_init();
lcd_putc ("Ready.........");
delay_ms(1000);
lcd_putc ('\f');

setup_timer_2(T2_DIV_BY_1,249,1);      //50.0 us overflow, 50.0 us interrupt
setup_ccp1(CCP_PWM);
setup_ccp2(CCP_PWM);
set_pwm1_duty(0);      ///// Max 1000
set_pwm2_duty(0);

resetdc1();
resetdc2();
*/
trisb=0x00;
trisc=0x00;
trise=0x00;
portb=0xff;
portc=0x00;
porte=0xff;
while(true)
{

for (i=0; i<9; i++)
   {
   portb=0b11111110; 
   delay_ms(500);
   portb=0b11111101; 
   delay_ms(500);
   portb=0b11111011; 
   delay_ms(500);
   portb=0b11110111; 
   delay_ms(500);
   portb=0b11101111; 
   delay_ms(500);
   portb=0b11011111; 
   delay_ms(500);
   portb=0b10111111; 
   delay_ms(500);
   portb=0b01111111; 
   delay_ms(500);
   
   }

/*
for (i=0; i<900; i++)
   {
   dc2t(i);
   delay_ms(10);
   }
resetdc2();
delay_ms(2000);
for (i=0; i<900; i++)
   {
   dc2n(i);
   delay_ms(10);
   }
resetdc2();
delay_ms(2000);   
*/
}

}
