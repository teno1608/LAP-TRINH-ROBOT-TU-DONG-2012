
///// NHIEM VU 3
int8 inv3=0; 
void nhiemvu3()
{

delay_ms(1000);
beep(3,100);
setup_timer_2(T2_DIV_BY_4,250,1);      //401 us overflow, 401 us interrupt
setup_ccp1 (ccp_pwm);
setup_ccp2 (ccp_pwm);

vantay1=vantay2=vancanh1=vancanh2=vanduoi=1;
vancanh1=vancanh2=0;

chonpid=2;
setvt2=280;
enable_interrupts(int_timer1);
while (En2<280) {}

chonpid=1;
setvt1=235;
while (qei_get_count() <235) {}

vantay1=vantay2=0;

while (ctsel==1) {}
if (ctsel==0) { vantay1=1; beep(1,100); }
while (cten==1) {}
/*
chonpid=1; 
if (cten==0) { setvt1=270; }
while (qei_get_count() <270) {};
*/
chonpid=0;

dc1n(600);
for ( inv3=0; inv3 < 6 ; inv3++)
{
while (ctt2==1) { dc1n(600);} //if ( qei_get_count()>285 ) {resetdc1(); beep(10,100);} }
if (ctt2==0) {vantay2=1; resetdc1();  }
delay_ms(100);
if (ctt2==1) {vantay2=0; dc1t(300); delay_ms(400); dc1n(600); }
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
while ( En2 >10) {}
chonpid=0;

dc2t(600);
for (inv3=0; inv3 < 6; inv3++)
   {
   while (ctt1==1) { dc2t(600);} //if ( En2 <-5 ) {resetdc2(); beep(10,100);} }
   if (ctt1==0) {vantay1=1;resetdc2();  }
   delay_ms(100);
   if (ctt1==1) {vantay1=0; dc2n(300); delay_ms(400); dc2t(600); }
   }
vantay1=1;resetdc2(); 


delay_ms(1000);
vantay2=0;
chonpid=1;
setvt1=30;
enable_interrupts(int_timer1);
while (qei_get_count() < 30) {}

setvt1=270;
setvt2=275;
chonpid=3;
while (qei_get_count() < 270) {}
chonpid=0;
dc1n(600);
for ( inv3=0; inv3 < 6 ; inv3++)
{
while (ctt2==1) {dc1n(600);} // if ( qei_get_count() >285 ) {resetdc1(); beep(10,100);} }
if (ctt2==0) {vantay2=1; resetdc1();  }
delay_ms(100);
if (ctt2==1) {vantay2=0; dc1t(300); delay_ms(400); resetdc1(); dc1n(600); }
}
vantay2=1; resetdc1();

delay_ms(1000);
vantay2=0;
chonpid=2;
setvt2=0;
enable_interrupts(int_timer1);

vancanh2=1;
while ( En2 > 240) {}
chonpid=0;
vancanh2=0;

while (cten==1) {}

while (ctsel==1) {}

 vantay1=0; delay_ms(500);
 
while (ctsel==1) {}
 resetvan(); 
 
demct=200;
enable_interrupts(int_timer5);

}



/*

void nhiemvu3xdg()
{
delay_ms(1000);
beep(3,100);

vantay1=vantay2=vancanh1=vancanh2=vanduoi=1;
vancanh1=vancanh2=0;
vantay1=vantay2=0;
En2=0;
qei_set_count(0);

while( En2< 235) dc2n(500);  
resetdc2();
while (En2> 235) dc2t(250);
resetdc2();

while( qei_get_count() < 280) dc1n(500);  
resetdc1();
while (qei_get_count() > 280) dc1t(250);
resetdc1();

while (ctsel==1) {}

vantay2=1; beep(1,100); 

while (cten==1) {}

while( En2< 270) dc2n(370); 

while (ctt1==1) { dc2n(600); }
vantay1=0; 
resetdc2();
delay_ms(200);
if (ctt1==1) { vantay1=0; }   
while (ctt1==1) { dc2n(600); }
vantay1=0; 
resetdc2();
delay_ms(200);





}


*/

