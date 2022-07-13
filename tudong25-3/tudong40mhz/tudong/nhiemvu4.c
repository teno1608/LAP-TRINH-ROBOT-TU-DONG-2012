
///// NHIEM VU 4
int8 deml=0;
void nhiemvu4()
{
disable_interrupts(int_timer5);
demct=0; 
delay_ms(1000);
beep(4,100);
trispwm3=trisdir3=0;
pwm3=dir3=1;
enable_interrupts(int_timer0);
delay_ms(100);
dir3=1;
xungleo=190;
delay_ms(3000);
beep(1,100);
xungleo=190;
dir3=0;
delay_ms(3000);
beep(1,100);
xungleo=200;
dir3=1;
while (cten==1) {}
//while (ctlt==1) { beep(1,100); } //dc1n(600);



}

