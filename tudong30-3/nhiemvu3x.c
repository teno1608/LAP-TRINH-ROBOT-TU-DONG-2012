
///// NHIEM VU 3X

int8 inv3x=0;
void nhiemvu3x()
{
delay_ms(1000);
beep(3,100);
setup_timer_2(T2_DIV_BY_16,250,1);      //401 us overflow, 401 us interrupt
setup_ccp1 (ccp_pwm);
setup_ccp2 (ccp_pwm);

vantay1=vantay2=vancanh1=vancanh2=vanduoi=1;
vancanh1=vancanh2=0;

chonpid=2;
setvt2=230;
enable_interrupts(int_timer1);
while (En2<230) {}

chonpid=1;
setvt1=280;
while (qei_get_count() <280) {}

vantay1=vantay2=0;

while (ctsel==1) {}

vantay2=1; beep(1,100); 

while (cten==1) {}
chonpid=2; 
setvt2=270;
while (En2 <270) {};
chonpid=0;
delay_ms(100);

dc2n(600);
for ( inv3x=0; inv3x < 6 ; inv3x++)
{
while (ctt1==1) {} ///*if ( En2>285 ) {resetdc2(); beep(10,100);}*/}
if (ctt1==0) {vantay1=1; resetdc2(); }
delay_ms(100);
if (ctt1==1) {vantay1=0; dc2t(300); delay_ms(400);resetdc2(); dc2n(600); }
}
vantay1=1; resetdc2();

delay_ms(1000);
vantay2=0;
chonpid=1;
setvt1=0;
enable_interrupts(int_timer1);
while ( qei_get_count() >220) {}

setvt1=10;
setvt2=0;
chonpid=3;
while ( qei_get_count() >10) {}
chonpid=0;
delay_ms(100);
dc1t(600);
for (inv3x=0; inv3x <6; inv3x++)
   {
   while (ctt2==1) {} ///* if ( qei_get_count() <-5 ) {resetdc1(); beep(10,100);} */}
   if (ctt2==0) {vantay2=1;resetdc1(); }
   delay_ms(100);
   if (ctt2==1) {vantay2=0; dc1n(300); delay_ms(400);resetdc1(); dc1t(600); }
   }
vantay2=1;resetdc1(); 


delay_ms(1000);
vantay1=0;
chonpid=2;
setvt2=280;
enable_interrupts(int_timer1);
while (En2 < 50) {}
setvt1=280;
setvt2=270;
chonpid=3;
while (En2<270) {}
chonpid=0;
delay_ms(100);
dc2n(600);
for ( inv3x=0; inv3x < 6 ; inv3x++)
{
while (ctt1==1) {} ///*if ( En2>285 ) {resetdc2(); beep(10,100);}*/ }
if (ctt1==0) {vantay1=1; resetdc2(); beep(1,100); }
delay_ms(30);
if (ctt1==1) {vantay1=0; dc2t(300); delay_ms(400);resetdc2(); dc2n(600); }
}
vantay1=1; resetdc2();


delay_ms(1000);
vantay2=0;
chonpid=1;
setvt1=240;
enable_interrupts(int_timer1);
while ( qei_get_count() > 240) {}
chonpid=0;

while (cten==1) {}

while (ctsel==1) {}

vantay1=0; delay_ms(500); 

while (ctsel==1) {}

resetvan();

demct=200;
enable_interrupts(int_timer5);

}
/*
void nhiemvu3xdan()
{
delay_ms(1000);
beep(3,100);
setup_timer_2(T2_DIV_BY_16,250,1);      //401 us overflow, 401 us interrupt
setup_ccp1 (ccp_pwm);
setup_ccp2 (ccp_pwm);

vantay1=vantay2=vancanh1=vancanh2=vanduoi=1;
vancanh1=vancanh2=0;

chonpid=2;
setvt2=280;
enable_interrupts(int_timer1);
while (En2<280) {}

chonpid=1;
setvt1=280;
while (qei_get_count() <280) {}

chonpid=0;
vantay1=vantay2=0;

while (ctsel==1) {}

vantay1=1;
vantay2=1; beep(1,100); 

while (cten==1) {}

while (ctsel==1) {}
while (cten==1) {}

}

*/
