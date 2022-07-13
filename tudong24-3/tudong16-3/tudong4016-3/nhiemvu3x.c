///// NHIEM VU 3X

void nhiemvu3x()
{
disable_interrupts(int_timer5);

demct=0; 
delay_ms(2000);
beep(3,100);

setup_timer_2 (t2_div_by_1, 249, 1);
setup_ccp1 (ccp_pwm);
setup_ccp2 (ccp_pwm);
enable_interrupts(int_timer1);
qei_set_count(0);
En2=0;
Ti1=0;
Ti2=0;
setvt1=0;
setvt2=0;
vantay1=vantay2=vancanh1=vancanh2=vanduoi=1;
vancanh1=vancanh2=0;
setvt1=280;
setvt2=250;
vantay1=vantay2=0;

while (ctsel==1) {delay_ms(50);}

if (ctsel==0) { vantay2=1; beep(1,100); }

while (cten==1) {delay_ms(50);}

if (cten==0) { dc2n(700); }

while (ctt1==1) {delay_ms(50);}

if (ctt1==0) {vantay1=1; resetdc2(); }

delay_ms(1000);

vantay2=0;

setvt1=250;
delay_ms(1500);

setvt1=0;
setvt2=0;
while (ctt2==1) {delay_ms(50);}

if (ctt2==0) {vantay2=1; beep(1,100); }
delay_ms(2000);
vantay1=0;
setvt2=30;
delay_ms(1500);
setvt1=280;
setvt2=280;

while (ctt1==1) {delay_ms(50);}
if (ctt1==0) {vantay1=1; beep(1,100); } 
delay_ms(2000);

vantay2=0;
setvt1=240;
delay_ms(4000);
disable_interrupts(int_timer1);
resetdc1();
resetdc2();
while(cten==1) {delay_ms(50);}
*/
disable_interrupts(int_timer1);

}
