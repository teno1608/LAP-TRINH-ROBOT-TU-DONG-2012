///// RESETALL

void resetall()
{
disable_interrupts(int_timer1);
disable_interrupts(int_timer5);
chonct=0;
Ti1=0;
Ti2=0;
//while (ctc1==1) { dc1t(370); }
//resetdc1();
dc1t(1000);
//beep(1,100);
while (ctc2==1) { dc2t(370); }
resetdc2();
beep(1,100);
qei_set_count(0);
En2=0;
setvt1=0;
setvt2=0;
vantay1=vantay2=vancanh1=vanleo=vancanh2=vanduoi=1;

enable_interrupts(int_timer5);
clear_interrupt(int_timer5);
set_timer5(59286);
}

