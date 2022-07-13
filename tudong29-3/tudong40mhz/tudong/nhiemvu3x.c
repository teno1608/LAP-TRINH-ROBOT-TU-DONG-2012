
///// NHIEM VU 3X

void nhiemvu3x()
{
int8 inv3x=0;

disable_interrupts(int_timer5);
disable_interrupts(int_timer0);

delay_ms(1000);
beep(3,100);
setup_timer_2(T2_DIV_BY_16,250,1);      //401 us overflow, 401 us interrupt
setup_ccp1 (ccp_pwm);
setup_ccp2 (ccp_pwm);

vantay1=vantay2=vancanh1=vancanh2=vanduoi=1;
vancanh1=vancanh2=0;

chonpid=3;
enable_interrupts(int_timer1);

setvt2=240;
setvt1=280;

vantay1=vantay2=0;

while (ctsel==1) {}

vantay2=1; beep(1,100); 

while (cten==1) {}
chonpid=2; 
setvt2=270;
while (En2 <270) {};
chonpid=0;

dc2n(700);
for ( inv3x=0; inv3x < 4 ; inv3x++)
{
while (ctt1==1) { /*if ( En2>285 ) {resetdc2(); beep(10,100);}*/ }
if (ctt1==0) {vantay1=1; resetdc2(); beep(1,100); }
delay_ms(30);
if (ctt1==1) {vantay1=0; dc2t(500); delay_ms(800); dc2n(900); }
}
vantay1=1; resetdc2();


delay_ms(1000);
vantay2=0;
chonpid=1;
setvt1=250;
enable_interrupts(int_timer1);
while ( qei_get_count() >250) {}

setvt1=10;
setvt2=0;
chonpid=3;
while ( qei_get_count() >10) {}
chonpid=0;

dc1t(700);
for (inv3x=0; inv3x <4; inv3x++)
   {
   while (ctt2==1) {/* if ( qei_get_count() <-5 ) {resetdc1(); beep(10,100);} */}
   if (ctt2==0) {vantay2=1;resetdc1(); beep(1,100); }
   delay_ms(30);
   if (ctt2==1) {vantay2=0; dc1n(500); delay_ms(800); dc1t(900); }
   }
vantay2=1;resetdc1(); 


delay_ms(1000);
vantay1=0;
chonpid=2;
setvt2=30;
enable_interrupts(int_timer1);
while (En2 < 30) {}
setvt1=280;
setvt2=270;
chonpid=3;
while (En2<270) {}
chonpid=0;

dc2n(700);
for ( inv3x=0; inv3x < 4 ; inv3x++)
{
while (ctt1==1) { /*if ( En2>285 ) {resetdc2(); beep(10,100);}*/ }
if (ctt1==0) {vantay1=1; resetdc2(); beep(1,100); }
delay_ms(30);
if (ctt1==1) {vantay1=0; dc2t(500); delay_ms(800); dc2n(900); }
}
vantay1=1; resetdc2();


delay_ms(1000);
vantay2=0;
chonpid=1;
setvt1=250;
enable_interrupts(int_timer1);
while ( qei_get_count() > 250) {}
chonpid=0;

while (cten==1) {}

while (ctsel==1) {}

if (ctsel==0) { vantay1=0; delay_ms(400); }
while (ctsel==1) {}
if (ctsel==0) { delay_ms(400);  resetvan(); }

demct=200;
enable_interrupts(int_timer5);

}

