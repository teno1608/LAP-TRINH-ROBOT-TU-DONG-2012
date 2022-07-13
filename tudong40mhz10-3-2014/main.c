#include <main.h>


void main()
{

setup_timer_2(T2_DIV_BY_4,124,1);		//50.0 us overflow, 50.0 us interrupt
   setup_ccp1(CCP_PWM);
   set_pwm1_duty(1023);


}
