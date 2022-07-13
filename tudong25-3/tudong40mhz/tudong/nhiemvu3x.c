///// NHIEM VU 3X

void nhiemvu3x()
{
signed int16 temp1, temp2;
disable_interrupts(int_timer5);
demct=0; 
delay_ms(2000);
beep(3,100);
setup_timer_2 (t2_div_by_1, 249, 1);
setup_ccp1 (ccp_pwm);
setup_ccp2 (ccp_pwm);
enable_interrupts(int_timer1);
vantay1=vantay2=vancanh1=vancanh2=vanduoi=1;
vancanh1=vancanh2=0;
setvt1=280;
setvt2=230;
vantay1=vantay2=0;

while (ctsel==1) {}

if (ctsel==0) { vantay2=1; beep(1,100); }
disable_interrupts(int_timer1);
resetdc1();
resetdc2();

while (cten==1) {}

if (cten==0) { dc2n(700); }

while (ctt1==1) { if ( En2>285 ) {resetdc2(); beep(10,100);} }

if (ctt1==0) {vantay1=1; resetdc2(); beep(1,100); }

delay_ms(1000);
temp2=En2;
vantay2=0;
enable_interrupts(int_timer1);
setvt2=temp2;
setvt1=250;
while ( qei_get_count() >252) {}

setvt1=50;
setvt2=0;
while ( qei_get_count() >50) {}

disable_interrupts(int_timer1);
resetdc1();
resetdc2();
dc1t(700);
while (ctt2==1) { if ( qei_get_count() <-5 ) {resetdc1(); beep(10,100);} }

if (ctt2==0) {vantay2=1;resetdc1(); beep(1,100); }

delay_ms(1000);
temp1=qei_get_count();
vantay1=0;
enable_interrupts(int_timer1);
setvt1=temp1;
setvt2=30;
while (En2 <30) {}

setvt1=280;
setvt2=250;

while (En2<250) {}
disable_interrupts(int_timer1);
resetdc1();
resetdc2();
dc2n(700);

while (ctt1==1) { if ( En2>295 ) {resetdc2(); beep(10,100);}}

if (ctt1==0) {vantay1=1;resetdc2(); beep(1,100); } 

delay_ms(1000);
temp2=En2;
vantay2=0;
enable_interrupts(int_timer1);
setvt2=temp2;
setvt1=240;
while ( qei_get_count() > 242) {}
disable_interrupts(int_timer1);
resetdc1();
resetdc2();

while (cten==1) {}

}

