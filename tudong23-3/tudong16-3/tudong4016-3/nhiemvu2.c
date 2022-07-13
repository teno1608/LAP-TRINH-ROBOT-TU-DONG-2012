
///// NHIEM VU 2

void nhiemvu2()
{
disable_interrupts(int_timer1);
disable_interrupts(int_timer5);

beep(2,100);
chonct=0;
while(cten==1){delay_ms(50);}

if(cten==0)
   {
   delay_ms(20);
   if(cten==0)
      {
      vanduoi=0;
      }
   }
while(cten==0) {delay_ms(50);}

while(cten==1) {delay_ms(50);}
if(cten==0)
   {
   delay_ms(20);
   if(cten==0)
      {
      vanduoi=0;
      }
   }
   
enable_interrupts(int_timer5);
clear_interrupt(int_timer5);
set_timer5(59286);
}
