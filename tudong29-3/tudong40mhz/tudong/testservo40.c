#include <18F4431.h>
#include <PIC18F4431_registers.h>
#FUSES h4
#FUSES NOWDT,PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT
#use delay(crystal=40000000)



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
      output_high(pin_c7);
      }
   if (demservo >=xungservo) output_low(pin_c7);
      
   } 


///// CHUONG TRINH LOA TIN HIEU
#bit trisloa = trisd.7
#bit loa = portd.7
void beep(int8 solan,int8 time)
{
int8 i;
for (i=0; i<solan; i++)
   {
   trisloa = 0;
   loa = 0;
   delay_ms(30);
   loa = 1;
   delay_ms(time-30);
   }
}

void main()
{
   enable_interrupts(int_timer0);
  
   
   enable_interrupts(GLOBAL);
  
   clear_interrupt(int_timer0);

   
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_4|RTCC_8_bit);      //102 us overflow, 0.4us
   set_timer0(5);

   while(TRUE)
   {
      //TODO: User Code
      xungservo=10;
      delay_ms(3000);
      beep(1,100);
      xungservo=15;
      delay_ms(3000);
      beep(1,100);
      xungservo=20;
      delay_ms(3000);
      beep(1,100);
   }

}
