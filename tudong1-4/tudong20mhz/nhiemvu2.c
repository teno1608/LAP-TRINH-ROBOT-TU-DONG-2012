
///// NHIEM VU 2

void nhiemvu2()
{

delay_ms(1000);
beep(2,100);

while(cten==0){}
delay_ms(1000);

vanduoi=0; 
delay_ms(500);

while(cten==1) {}

delay_ms(1000);

vanduoi=1; 

demct=200;
enable_interrupts(int_timer5);

}



