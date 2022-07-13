#include <testservo.h>

///// NGAT TIMER0
volatile int8 demservo, xungleo=0;
#int_timer0
void ngat_timer0(void) 
   {
   set_timer0(5);
   demservo++;
   if (demservo>=200)
      {
      demservo=0;
      output_high(pin_d1);
      }
   if (demservo >=xungleo) output_low(pin_d1);
   }
     

void main()
{
   enable_interrupts(int_timer0);
   
   enable_interrupts(GLOBAL);
 
   clear_interrupt(int_timer0);
   
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2|RTCC_8_bit);      //102 us overflow
   set_timer0(5);

   while(TRUE)
   {
      //TODO: User Code
      xungleo=10;
      delay_ms(3000);
      xungleo=15;
      delay_ms(3000);
      xungleo=20;
      delay_ms(3000);
   }

}
