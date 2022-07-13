
///// NHIEM VU 4

void nhiemvu4()
{
disable_interrupts(int_timer1);
disable_interrupts(int_timer5);
beep(4,100);
resetdc1();
resetdc2();
chonct=0;

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
