


void resetvan()
{
disable_interrupts(int_timer5);
demct=0; 
delay_ms(2000);
beep(1,100);
chonct=0;
Ti1=0;
Ti2=0;
vantay1=vantay2=vancanh1=vancanh2=0;
delay_ms(2000);
while (ctc1==1) { dc1t(370); }
resetdc1();
beep(1,100);
while (ctc2==1) { dc2t(400); }
resetdc2();
beep(1,100);
qei_set_count(0);
En2=0;
setvt1=0;
setvt2=0;
vantay1=vantay2=vancanh1=vancanh2=vanduoi=1;

}

