
///// DEFINE CAC DONG CO

#bit br1=porte.2
#bit br2=porte.1
#bit trisbr1 = trise.2
#bit trisbr2 = trise.1
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
   setup_timer_2(T2_DIV_BY_4,250,1);      //401 us overflow, 401 us interrupt
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (x);
}

void dc1n(INT16 x)
{
   trispwm1 = trisdir1 = trisbr1 = 0;
   dir1 = 0;
   br1 = 0;
   setup_timer_2(T2_DIV_BY_4,250,1);      //401 us overflow, 401 us interrupt
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (x);
}

void resetdc1()
{
   trispwm1 = trisdir1 = trisbr1 = 0;
   setup_timer_2(T2_DIV_BY_4,250,1);      //401 us overflow, 401 us interrupt
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (0);
   br1 = 1;
   dir1 = 0;
}

void dc2n(INT16 x)
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   dir2 = 1;
   br2 = 0;
   setup_timer_2(T2_DIV_BY_4,250,1);      //401 us overflow, 401 us interrupt
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (x);
}

void dc2t(INT16 x)
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   br2 = 0;
   dir2 = 0;
   setup_timer_2(T2_DIV_BY_4,250,1);      //401 us overflow, 401 us interrupt
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (x);
}

void resetdc2()
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   br2 = 1;
   dir2 = 0;
   setup_timer_2(T2_DIV_BY_4,250,1);      //401 us overflow, 401 us interrupt
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (0);
}


#bit pwm3 = portd.6
#bit dir3 = portd.5
#bit trispwm3 = trisd.6
#bit trisdir3 = trisd.5

