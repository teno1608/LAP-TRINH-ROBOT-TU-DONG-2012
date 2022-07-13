#include <18F4431.h>
#include <PIC18F4431_registers.h>
#include <stdlib.h>
#include <stdio.h>
#FUSES NOWDT, H4,PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT, ssp_rd
#use delay(clock=40000000)
#use spi(MASTER ,FORCE_HW, BITS=16)
#use fast_io(a)
#use fast_io(d)
#use fast_io(c)
#use fast_io(e)

#bit ss1 = PORTD.0

///// DEFINE CAC DONG CO
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

///// DEFINE VAN
#bit vantay1=porte.1
#bit vantay2=porte.0
#bit vancanh1=porta.2    
#bit vancanh2=porta.0    
#bit vanleo=porta.1
#bit vanduoi=porta.5

///// DEFINE CONG TAC HANH TRINH
#bit ctc1=portb.0
#bit ctt1=portb.1
#bit ctc2=portb.2
#bit ctt2=portb.3
#bit ctsel=portb.7
#bit cten=portb.6

///// CHUONG TRINH LOA TIN HIEU
#bit trisloa = trisd.7
#bit loa = portd.7
void beep(int8 solan,int8 time)
{
int8 i;
for (i=0; i<solan; i++)
   {
   trisloa = 0;
   loa = 0;
   delay_ms(30);
   loa = 1;
   delay_ms(time-30);
   }
}

///// QEI MEM
#define ChanelA PIN_C4
#define ChanelB PIN_C5

signed int16 En1, En2;

#INT_EXT1
void  EXT1_L2H_isr(void) 
{
INTEDG1^=1;
if (INTEDG1)
   {
   if (input(ChanelB)) {En2++;} 
   else {En2--;}
   }
else 
   { 
   if (input(ChanelB)) {En2--;}
   else {En2++;}
   }
}

#int_EXT2
void  EXT2_isr(void) 
{
INTEDG2^=1;
if (INTEDG2)
   {
   if (input(ChanelA)) {En2--;} 
   else {En2++;}
   }
else 
   { 
   if (input(ChanelA)) {En2++;}
   else {En2--;}
   }
}

///// NGAT TIMER1
#int_timer1
void ngat_timer1(void) 
{
      En1=qei_get_count();
 
}

///// CHUONG TRINH DOC PES
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

///// KHAI BAO BIEN
int8 i;

void main()
{
   i=0;
   trisa=0b00011000;
   trisb=0b11111111;
   port_b_pullups(0xff);
   trisc=0b00110000;
   trisd=0b00000100;
   trise=0b00000000;
   br1=br2=1;
   vantay1=vantay2=vancanh1=vanleo=vancanh2=vanduoi=1;
   
   enable_interrupts(INT_EXT1);
   enable_interrupts(INT_EXT2);
   enable_interrupts(int_timer1);
   enable_interrupts(GLOBAL);
   ext_int_edge(1,L_to_H);
   ext_int_edge(2,L_to_H);
   clear_interrupt(INT_EXT1);
   clear_interrupt(INT_EXT2);
   clear_interrupt(int_timer1);
   setup_qei(qei_mode_x4,qei_filter_enable_qea|qei_filter_enable_qeb|qei_filter_div_2,65535);
   qei_set_count(0);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);      //52.4 ms overflow, 0.8us
   set_timer1(3035);
   setup_spi(SPI_MASTER|SPI_L_TO_H|SPI_CLK_DIV_16);
   ss1=1;
   
   beep(2,100);
     
   En1=0; 
   En2=0;

   dir1=0;
   pwm1=0;
   dir2=0;
   pwm2=0;
while(true)
   {
   ss1=0;
   delay_us(15);
   spi_xfer(50);
   ss1=1;
   delay_ms(5);
   ss1=0;
   delay_us(15);
   spi_xfer(50);
   ss1=1;
   delay_ms(1000);
   ss1=0;
   delay_us(15);
   spi_xfer(90);
   ss1=1;
   delay_ms(5);
   ss1=0;
   delay_us(15);
   spi_xfer(90);
   ss1=1;
   
   } 
  

}
