#include <main.h>

void main()
{
	setup_timer_2(T2_DIV_BY_4,249,1);		//200 us overflow, 200 us interrupt

	setup_ccp1(CCP_PWM);
	set_pwm1_duty((int16)997);

	while(TRUE)
	{
		//TODO: User Code
	}

}
