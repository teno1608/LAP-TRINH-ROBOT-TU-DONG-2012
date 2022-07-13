
///// NHIEM VU 3

void nhiemvu3()
{
disable_interrupts(int_timer5);
beep(3,100);
enable_interrupts(int_timer1);
chonct=0;
qei_set_count(0);
En2=0;
Ti1=0;
Ti2=0;
setvt1=0;
setvt2=0;
vantay1=vantay2=vancanh1=vancanh2=vanduoi=1;
vancanh1=vancanh2=0;
setvt1=260;
setvt2=260;
vantay1=vantay2=0;






disable_interrupts(int_timer1);
enable_interrupts(int_timer5);
clear_interrupt(int_timer5);
set_timer5(59286);
}
