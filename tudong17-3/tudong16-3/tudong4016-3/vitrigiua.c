
void vitrigiua()
{
disable_interrupts(int_timer1);
dc1n(320);
dc2n(320);
delay_ms(500);
resetdc1();
resetdc2();
qei_set_count(0);
En2=0;
vantay1=vantay2=vancanh1=vanleo=vancanh2=vanduoi=1;
enable_interrupts(int_timer1);
clear_interrupt(int_timer1);
set_timer1(3035);

}
