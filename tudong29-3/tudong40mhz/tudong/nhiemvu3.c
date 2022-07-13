
///// NHIEM VU 3X

void nhiemvu3xnew()
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





///// NHIEM VU 3
/*
void nhiemvu3()
{
int8 inv3=0; 
disable_interrupts(int_timer5);
disable_interrupts(int_timer0);
demct=0; 
delay_ms(1000);
beep(3,100);
setup_timer_2(T2_DIV_BY_16,250,1);      //401 us overflow, 401 us interrupt
setup_ccp1 (ccp_pwm);
setup_ccp2 (ccp_pwm);

vantay1=vantay2=vancanh1=vancanh2=vanduoi=1;
vancanh1=vancanh2=0;

chonpid=3;
enable_interrupts(int_timer1);
setvt2=280;
setvt1=220;
vantay1=vantay2=0;

while (ctsel==1) {}
if (ctsel==0) { vantay2=1; beep(1,100); }
while (cten==1) {}
chonpid=1; 
if (cten==0) { setvt1=270; }
while (qei_get_count() <270) {};
chonpid=0;

dc1n(700);
for ( inv3=0; inv3 < 4 ; inv3++)
{
while (ctt2==1) { if ( qei_get_count()>285 ) {resetdc1(); beep(10,100);} }
if (ctt2==0) {vantay2=1; resetdc1(); beep(1,100); }
if (ctt2==1) {vantay2=0; dc1t(500); delay_ms(800); dc1n(900); }
}
vantay2=1; resetdc1();


delay_ms(1000);
vantay1=0;
chonpid=2;
setvt2=250;
enable_interrupts(int_timer1);
while ( En2 >250) {}

setvt2=10;
setvt1=0;
chonpid=3;
while ( En2 >11) {}
chonpid=0;

dc2t(700);
for (inv3=0; inv3 < 4; inv3++)
   {
   while (ctt1==1) { if ( En2 <-5 ) {resetdc2(); beep(10,100);} }
   if (ctt1==0) {vantay1=1;resetdc2(); beep(1,100); }
   if (ctt1==1) {vantay1=0; dc2n(500); delay_ms(800); dc2t(900); }
   }
vantay1=1;resetdc1(); 


delay_ms(1000);
vantay2=0;
chonpid=1;
setvt1=30;
enable_interrupts(int_timer1);
while (qei_get_count() < 30) {}

setvt1=270;
setvt2=280;
chonpid=3;
while (qei_get_count() < 270) {}
chonpid=0;

dc1n(700);
for ( inv3=0; inv3 < 4 ; inv3++)
{
while (ctt1==1) { if ( qei_get_count() >285 ) {resetdc1(); beep(10,100);} }
if (ctt1==0) {vantay2=1; resetdc1(); beep(1,100); }
if (ctt1==1) {vantay2=0; dc1t(500); delay_ms(1000); dc1n(900); }
}
vantay2=1; resetdc2();


delay_ms(1000);
vantay2=0;
chonpid=2;
setvt2=220;
enable_interrupts(int_timer1);
while ( En2 > 220) {}
chonpid=0;

while (cten==1) {}
if (cten==0) {delay_ms(100);}
while (cten==1) {}
while (ctsel==1) {}

if (ctsel==0) { vantay1=0; delay_ms(400); }
while (ctsel==1) {}
if (ctsel==0) { delay_ms(400);  resetvan(); }

enable_interrupts(int_timer5);

}
*/
