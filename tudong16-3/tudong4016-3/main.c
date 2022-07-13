#include <18F4431.h>
#include <PIC18F4431_registers.h>
#FUSES HS,NOWDT,NOLVP
#use delay(clock=20000000)

///// NGAT TIMER0
char demservo, xungservo;
#int_timer0
void ngat_timer0(void) 
   {
   set_timer0(5);
   demservo++;
   if (demservo>=200)
      {
      demservo=0;
      output_high(pin_d7);
      }
   if (demservo >=xungservo) output_low(pin_d7);
      
   }
   
   
void main()
{
trisd=0x00;
portd=0x00;
enable_interrupts(int_timer0);
clear_interrupt(int_timer0);
enable_interrupts(global);
setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2|RTCC_8_bit);      //102 us overflow
set_timer0(5);
while(true)
   {
   xungservo=10;
   delay_ms(2000);
   xungservo=15;
   delay_ms(2000);
   xungservo=20;
   delay_ms(2000);
   }
}
