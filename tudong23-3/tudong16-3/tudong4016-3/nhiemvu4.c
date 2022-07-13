
///// NHIEM VU 4
int8 deml=0;
void nhiemvu4()
{
disable_interrupts(int_timer1);
disable_interrupts(int_timer5);
beep(4,100);

chonct=0;

while (ctlt==1) { beep(1,100); } //dc1n(600);

//dc1t(1000);

deml=0;
while (cten==1) {}
while (deml<5) 
   {  
   while (ctld==1) { } //dc1t(300);
   while (ctlt==1) { } //dc1n(300);
   deml++;
   
   }
   
//dc1t(1000);

enable_interrupts(int_timer0);
clear_interrupt(int_timer0);

xungservo=10;
}
