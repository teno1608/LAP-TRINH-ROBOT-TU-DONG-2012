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

#bit Din = PORTB.3// dây 1 màu nâu (chan DI)
#bit Dout = PORTB.1 // dây 2 màu cam (chan DO)
#bit CLK = PORTB.2// dây 7 xanh da tr?i (chan CLK)
#bit CS = PORTB.0 // dây 6 màu vàng (chan CS)

unsigned CHAR rbyte,analog,pes4,pes5,adcrlp,adcudp,adcrlt,adcudt;
unsigned CHAR select,start,len,xuong,trai,phai,trai0,phai0,trai1,phai1,trai2,phai2,nut1,nut2,nut3,nut4;

void access(UNSIGNED char wbyte)
  {
   UNSIGNED char j = 0;
   rbyte = 0;
   CLK = 1;
   FOR (j = 0; j < 8; j++)
   {
      IF (bit_test (wbyte, j) == 1) Dout=1; else Dout = 0;
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

void doctayPES()
   {
   portb = 0xff;
   trisb = 0b10000000;
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
   delay_ms(20);
   loa = 1;
   delay_ms(time-20);
   }
}   

void main()
{
WHILE (true)
   {
      doctayPES ();
     
      IF (len == 0) {beep(1,100); }
      IF (xuong == 0) {beep(1,100); }
      IF (trai == 0) {beep(1,100); }
      IF (phai == 0) {beep(1,100); }
      IF (select == 0) {beep(1,100); }
      IF (start == 0) {beep(1,100);}
      
   }

}
