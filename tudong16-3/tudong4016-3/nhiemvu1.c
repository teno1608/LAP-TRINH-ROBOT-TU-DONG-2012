
///// NHIEM VU 1

void nhiemvu1()
{
disable_interrupts(int_timer1);
while (ctc1==1) { dc1t(350); }
resetdc1();
beep(1,100);
while (ctc2==1) { dc2t(350); }
resetdc2();
beep(1,100);
qei_set_count(0);
En2=0;
vantay1=vantay2=vancanh1=vanleo=vancanh2=vanduoi=1;
enable_interrupts(int_timer1);
clear_interrupt(int_timer1);
set_timer1(3035);
Ti1=0;
}