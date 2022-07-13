
///// NHIEM VU 4

void nhiemvu4()
{
while (ctc1==1) { dc1t(350); }
resetdc1();
while (ctc2==1) { dc2t(350); }
resetdc2();
qei_set_count(0);

En2=0;
vantay1=vantay2=vancanh1=vanleo=vancanh2=vanduoi=1;
delay_ms(1000);
vanleo=0;
delay_ms(1000);
vanleo=1;
delay_ms(1000);
vanleo=0;
delay_ms(1000);
vanleo=1;

}
