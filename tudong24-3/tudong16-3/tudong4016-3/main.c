#include <18F4431.h>
#include <PIC18F4431_registers.h>
#include <stdlib.h>
#FUSES HS,NOWDT,NOLVP,LPOL_HIGH
#use delay(clock=20000000)
#use fast_io(a)
#use fast_io(d)
#use fast_io(c)
#use fast_io(e)

int16 i;
void main()
{
setup_power_pwm(pwm_clock_div_4|pwm_free_run,1,0,625,0,1,0);
setup_power_pwm_pins(1,1,1,1);
set_power_pwm_override(7, false, 0);
while (true)
{
for (i=0; i<2200; i++)
   {
   set_power_pwm6_duty(i);
   delay_ms(2);
   }
}


}
