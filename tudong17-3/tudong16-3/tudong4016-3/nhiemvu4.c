
///// NHIEM VU 4

void nhiemvu4()
{
beep(4,100);
//disable_interrupts(int_timer1);
resetdc1();
resetdc2();
chonct=1;

while (cten==1) {delay_ms(50);};
vanleo=0;
vanduoi=0;
delay_ms(2000);
vanleo=1;
delay_ms(2000);
vanleo=0;
delay_ms(2000);
vanleo=1; 
delay_ms(2000);
vanleo=0;
delay_ms(2000);
vanleo=1;
delay_ms(2000);
vanleo=0;
delay_ms(2000);
vanleo=1;
delay_ms(2000);
vanleo=0;
delay_ms(2000);
vanleo=1;
delay_ms(2000);

enable_interrupts(int_timer0);
clear_interrupt(int_timer0);

xungservo=10;
}
