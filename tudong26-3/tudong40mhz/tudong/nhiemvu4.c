
///// NHIEM VU 4
int8 deml=0;
void nhiemvu4()
{
disable_interrupts(int_timer5);
disable_interrupts(int_timer1);
demct=0; 
delay_ms(1000);
beep(4,100);
trispwm3=trisdir3=0;
pwm3=dir3=1;
while (cten==1) {}
delay_ms(100);

dclep=1;
enable_interrupts(int_timer0);
vanduoi=0;
while (ctld==1)
   {
   dir3=0;
   xungleo=75;
   }
xungleo=200;
beep(1,100);
while (ctlt==1)
   {
   dir3=1;
   xungleo=50;
   }
xungleo=200;
beep(1,100);
while (ctld==1)
   {
   dir3=0;
   xungleo=50;
   }
xungleo=200;
beep(1,100);
while (ctlt==1)
   {
   dir3=1;
   xungleo=50;
   }
xungleo=200;
beep(1,100);
while (ctld==1)
   {
   dir3=0;
   xungleo=50;
   }
xungleo=200;
beep(1,100);
while (ctlt==1)
   {
   dir3=1;
   xungleo=50;
   }
xungleo=200;
beep(1,100);
while (ctld==1)
   {
   dir3=0;
   xungleo=50;
   }
xungleo=200;
beep(1,100);
while (ctlt==1)
   {
   dir3=1;
   xungleo=50;
   }
xungleo=200;
beep(1,100);
while (ctld==1)
   {
   dir3=0;
   xungleo=50;
   }
xungleo=200;
beep(1,100);
while (ctlt==1)
   {
   dir3=1;
   xungleo=50;
   }
xungleo=200;
beep(1,100);

vanduoi=1;
beep(1,100);
pwm3=1;
dclep=0;
xungleo=10;
beep(3,100);
while (cten==1) { }
disable_interrupts(int_timer0);



//while (ctlt==1) { beep(1,100); } //dc1n(600);



}

