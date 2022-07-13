#include <18F4431.h>
#include <PIC18F4431_registers.h>
#include <stdlib.h>
#include <stdio.h>
#FUSES NOWDT, H4,PUT, NOPROTECT, NODEBUG, BROWNOUT, NOLVP, NOCPD, NOWRT
#use delay(clock=40000000)
#use fast_io(a)
#use fast_io(d)
#use fast_io(c)
#use fast_io(e)


///////////////////////////////////////////////////
#bit br1=portd.4
#bit br2=portd.5
#bit trisbr1 = trisd.4
#bit trisbr2 = trisd.5
#bit dir1=portc.3
#bit dir2=portc.0
#bit trisdir1 = trisc.3
#bit trisdir2 = trisc.0
#bit pwm1=portc.2
#bit pwm2=portc.1
#bit trispwm1 = trisc.2
#bit trispwm2 = trisc.1

void dc1t(INT16 x)
{
   trispwm1 = trisdir1 = trisbr1 = 0;
   dir1 = 1;
   br1 = 0;
   setup_timer_2 (t2_div_by_1, 249, 1);
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (x);
}

void dc1n(INT16 x)
{
   trispwm1 = trisdir1 = trisbr1 = 0;
   dir1 = 0;
   br1 = 0;
   setup_timer_2 (t2_div_by_1, 249, 1);
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (x);
}

void resetdc1()
{
   trispwm1 = trisdir1 = trisbr1 = 0;
   setup_timer_2 (t2_div_by_1, 249, 1);
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (0);
   br1 = 1;
   dir1 = 0;
}

void dc2n(INT16 x)
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   dir2 = 1;
   br2 = 0;
   setup_timer_2 (t2_div_by_1, 249, 1);
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (x);
}

void dc2t(INT16 x)
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   br2 = 0;
   dir2 = 0;
   setup_timer_2 (t2_div_by_1, 249, 1);
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (x);
}

void resetdc2()
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   br2 = 1;
   dir2 = 0;
   setup_timer_2 (t2_div_by_1, 249, 1);
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (0);
}

///// CHUONG TRINH LOA TIN HIEU
#bit trisloa = trisd.7
#bit loa = portd.7
void beep()
{
trisloa = 0;
loa = 0;
delay_ms(30);
loa = 1;
delay_ms(70);
}

///////////////////////////////////////////////
#bit trisDin = trisd.2
#bit trisDout = trisd.1
#bit trisCLK = trisd.3
#bit trisCS = trisd.0
#bit Din = PORTd.2// dây 1 màu nâu (chan DI)
#bit Dout = PORTd.1 // dây 2 màu cam (chan DO)
#bit CLK = PORTd.3// dây 7 xanh da tr?i (chan CLK)
#bit CS = PORTd.0 // dây 6 màu vàng (chan CS)

unsigned CHAR rbyte,analog,pes4,pes5,adcrlp,adcudp,adcrlt,adcudt;
unsigned CHAR select,start,len,xuong,trai,phai,trai0,phai0,trai1,phai1,trai2,phai2,nut1,nut2,nut3,nut4;

void access(UNSIGNED char wbyte)
{
   UNSIGNED char j = 0;
   rbyte = 0;
   CLK = 1;
   FOR (j = 0; j < 8; j++)
   {
      IF (bit_test (wbyte, j) == 1) Dout = 1; else Dout = 0;
      delay_us (10);
      CLK = 0;
      delay_us (10);

      IF (Din == 1)
      {
         IF (j == 0) rbyte = 1;
         IF (j == 1) rbyte = rbyte + 2;
         IF (j == 2) rbyte = rbyte + 4;
         IF (j == 3) rbyte = rbyte + 8;
         IF (j == 4) rbyte = rbyte + 16;
         IF (j == 5) rbyte = rbyte + 32;
         IF (j == 6) rbyte = rbyte + 64;
         IF (j == 7) rbyte = rbyte + 128;
      }

      CLK = 1;
   }
}

void doctaypes()
{
   Din = Dout = CLK = CS = 1;
   trisDin = 1;
   trisDout = trisCLK = trisCS = 0;
   cs = 0;
   access (0x01);
   access (0x42);
   analog = rbyte;
   access (0x00);
   access (0x00);
   pes4 = rbyte;
   access (0x00);
   pes5 = rbyte;
   access (0x00);
   adcrlp = rbyte;
   access (0x00);
   adcudp = rbyte;
   access (0x00);
   adcrlt = rbyte;
   access (0x00);
   adcudt = rbyte;
   cs = 1;
   select = pes4&0x01;
   trai0 = (pes4&0x02) / 2;
   phai0 = (pes4&0x04) / 4;
   start = (pes4&0x08) / 8;
   len = (pes4&0x10) / 16;
   phai = (pes4&0x20) / 32;
   xuong = (pes4&0x40) / 64;
   trai = (pes4&0x80) / 128;
   trai2 = (pes5&0x01);
   phai2 = (pes5&0x02) / 2;
   trai1 = (pes5&0x04) / 4;
   phai1 = (pes5&0x08) / 8;
   nut1 = (pes5&0x10) / 16;
   nut2 = (pes5&0x20) / 32;
   nut3 = (pes5&0x40) / 64;
   nut4 = (pes5&0x80) / 128;
}

///define van/////////////////////////////
#bit vantay1=porte.1
#bit vantay2=porte.0
#bit van3=porta.2
#bit vanleo4=porta.1
#bit van5=porta.0
#bit vanduoi6=porta.5
///define ctht////////////////////////
#bit ctc1=portb.0
#bit ctt1=portb.1
#bit ctc2=portb.2
#bit ctt2=portb.3
#bit ctsel=portb.7
#bit cten=portb.6

int8 i;
void main()
{
beep();
i=0;
trisa=0b00000000;
trisb=0b11111111;
port_b_pullups(0xff);
trisc=0b00000000;
trisd=0b00000100;
trise=0b00000000;
br1=br2=1;
van1=van2=van3=van4=van5=van6=1;
/*
while(true)
   {
   doctaypes();
   if (len==0) { beep(); van1=van1^1; delay_ms(200); }
   if (phai==0) { beep(); van2=van2^1; delay_ms(200); }
   if (xuong==0) { beep(); van3=van3^1; delay_ms(200); }
   if (trai==0) { beep(); van4=van4^1; delay_ms(200); }
   if (nut1==0) { beep(); van5=van5^1; delay_ms(200); }
   if (nut2==0) { beep(); van6=van6^1; delay_ms(200); }
   }
*/
/*
while (true)
   {
   if (ctc1==0) { beep(); while (ctc1==0){}; }
   if (ctt1==0) { beep(); beep(); while (ctt1==0){};  }
   if (ctc2==0) { beep(); beep(); beep(); while (ctc2==0){}; }
   if (ctt2==0) { beep(); beep(); beep(); beep(); while (ctt2==0){}; }
   if (ctsel==0) { beep(); beep(); beep(); beep(); beep(); while (ctsel==0){}; }
   if (cten==0) { beep(); beep(); beep(); beep(); beep(); beep(); while (cten==0){}; }
   }
*/


dir1=0;
pwm1=0;
dir2=0;
pwm2=0;
while(true)
   {
   doctayPES();
   if (nut1==0) { beep(); van1=van1^1; delay_ms(200); }
   if (nut2==0) { beep(); van2=van2^1; delay_ms(200); }
   if (nut3==0) { beep(); van5=van5^1; delay_ms(200); }
   if (nut4==0) { beep(); van3=van3^1; delay_ms(200); }
   
   if (len==0) 
      {
      beep();
      i=1;
      len=1;
      while(i==1) 
         {
         dc2t(400);
         doctayPES();
         if(len==1) i=0;
         }
      resetdc2();
      delay_ms(100);
      }
   if (xuong==0) 
      {
      beep();
      i=1; 
      xuong=1;
      while(i==1) 
         {
         dc2n(400);
         doctayPES();
         if(xuong==1) i=0;
         }
      resetdc2();
      delay_ms(100);
      }
      
      
      ////////////////////////////////
      if (trai==0) 
      {
      beep();
      i=1;
      trai=1;
      while(i==1) 
         {
         dc1t(400);
         doctayPES();
         if(trai==1) i=0;
         }
      resetdc1();
      delay_ms(100);
      }
   if (phai==0) 
      {
      beep();
      i=1; 
      phai=1;
      while(i==1) 
         {
         dc1n(400);
         doctayPES();
         if(phai==1) i=0;
         }
      resetdc1();
      delay_ms(100);
      }
   
   }
}
