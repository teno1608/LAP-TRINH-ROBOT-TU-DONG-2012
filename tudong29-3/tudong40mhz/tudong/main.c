#include <main.h>

void main()
{
	setup_timer_2(T2_DIV_BY_16,250,1);		//401 us overflow, 401 us interrupt

	setup_ccp1(CCP_PWM);
	set_pwm1_duty((int16)1001);

	while(TRUE)
	{
		//TODO: User Code
	}

}
