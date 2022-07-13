
///// RESET TAT CA
int8 ire=0;

void resetvan()
{

disable_interrupts(int_timer1);
disable_interrupts(int_timer0);

delay_ms(200);
beep(1,100);

for (ire=0; ire<50; ire++)
   {
   if (ctsel==0) {vancanh1=vancanh2=0; delay_ms(1000); vantay1=vantay2=0; ire=100; }
   delay_ms(10);
   }
delay_ms(500);   
while (ctc1==1) { dc1t(470); }
resetdc1();
while (ctc2==1) { dc2t(550); }
resetdc2();
beep(1,100);
vantay1=vantay2=vancanh1=vancanh2=vanduoi=1;

trispwm3=trisdir3=0;
pwm3=dir3=1;
enable_interrupts(int_timer0);
dclep=1;
while (ctlt==1)
   {
   dir3=1;
   xungleo=30;
   }
   xungleo=0;  
   delay_ms(300);
while (ctlt==0)
   {
   dir3=0; 
   xungleo=60;
   }
   xungleo=0;
   beep(1,100);   
disable_interrupts(int_timer0);
pwm3=1;
dir3=1;
beep(1,100);

qei_set_count(0);
En2=0;
Ti1=0;
Ti2=0;
setvt1=0;
setvt2=0;
chonpid=4;

demct=200;
enable_interrupts(int_timer5);

}




