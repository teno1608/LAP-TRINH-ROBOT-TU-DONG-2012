
///// NHIEM VU 4


void nhiemvu4()
{

int8 inv4;
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
   xungleo=80;
   
   } 
dir3=1;
xungleo=0;
beep(1,100);

for (inv4=0; inv4 < 3; inv4++)    /// 4 lan la ok
 {
   while (ctlt==1)
      {
      dir3=1;
      xungleo=80;
      }
   dir3=0;   
   xungleo=0;
   beep(1,100);

   while (ctld==1)
      {
      dir3=0;
      xungleo=85;
      }
   dir3=1;   
   xungleo=0;
   beep(1,100);
 }
 
 //delay_ms(1000);
 /////////////////////delay nga robot
 while (ctlt==1)
      {
      dir3=1;
      xungleo=80;
      }
   dir3=0;   
   xungleo=0;
   beep(1,100);

   while (ctld==1)
      {
      dir3=0;
      xungleo=85;
      }
   dir3=1;   
   xungleo=0;
   beep(1,100);
 
 

while (ctlt==1)
      {
      dir3=1;
      xungleo=80;
      }
   dir3=0;   
   xungleo=0;
   beep(1,100);
   
while (ctlt==0)
   {
   dir3=0; 
   xungleo=60;
   }
   xungleo=0;
   beep(1,100);
 
vanduoi=1;
pwm3=1;
dir3=1;
dclep=0;
xungleo=10;
while (cten==1) { }
disable_interrupts(int_timer0);

demct=200;
enable_interrupts(int_timer5);
}


