
///// NHIEM VU 2

void nhiemvu2()
{


delay_ms(1000);
beep(2,100);

while(cten==1){}
delay_ms(100);

if(cten==0) { vanduoi=0; }
delay_ms(100);

while(cten==0) {}

delay_ms(2000);

while(cten==1) {}

if(cten==0) { vanduoi=1; }

demct=200;
enable_interrupts(int_timer5);

}


