#include <thutd.h>
#include <PIC16F887_registers.h>
#define LCD_RS_PIN      PIN_E0                                 
#define LCD_RW_PIN      PIN_E1    
#define LCD_ENABLE_PIN  PIN_E2                                                              
#define LCD_DATA4       PIN_D0                                 
#define LCD_DATA5       PIN_D1                                  
#define LCD_DATA6       PIN_D2                                   
#define LCD_DATA7       PIN_D3
#include <lcd.c>

void setbamxung()
   {
   setup_timer_2 (T2_DIV_BY_16, 155, 1);
   setup_ccp1 (CCP_PWM);
   setup_ccp2 (CCP_PWM);
   set_pwm1_duty (0);
   set_pwm2_duty (0);
   delay_ms (10);
   }

void lcd_putnum(int32 so,INT8 x,int8 y)
{
   INT32 a, b, c, d, e;
   a = so / 10000;
   b = (so - 10000 * a) / 1000;
   c = (so - 10000 * a - 1000 * b) / 100;
   d = (so - 10000 * a - 1000 * b - 100 * c) / 10;
   e = so - 10000 * a - 1000 * b - 100 * c - 10 * d;
   lcd_gotoxy (x, y) ;
   lcd_putc (a + 48) ;
   lcd_putc (b + 48) ;
   lcd_putc (c + 48) ;
   lcd_putc (d + 48) ;
   lcd_putc (e + 48) ;
}

#bit Din = mcu_PORTC.7// dây 1 màu nâu (chan DI)
#bit Dout = mcu_PORTC.6 // dây 2 màu cam (chan DO)
#bit CLK = mcu_PORTC.5// dây 7 xanh da tr?i (chan CLK)
#bit CS = mcu_PORTC.4 // dây 6 màu vàng (chan CS)

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
   mcu_portc = 0xff;
   mcu_trisc = 0b10000000;
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

   
#bit pwm1 = mcu_portb.0
#bit dir1 = mcu_portb.1
#bit pwm2 = mcu_portb.2
#bit dir2 = mcu_portb.3
#bit van5 = mcu_portb.4
#bit van6 = mcu_portb.5
#bit van7 = mcu_portb.6
#bit van8 = mcu_portb.7

void main()
{
   mcu_portb = 0x00;
   mcu_trisb = 0x00;
   lcd_init ();
   WHILE (true)
   {  
      doctaypes () ;
      pwm1=pwm2=dir1=dir2=0;
      IF (nut1 == 0) {pwm1 = 1; dir1 = 1; lcd_putc ('\f'); lcd_gotoxy (0, 0); lcd_putc ("dc1thuan"); }
      IF (nut2 == 0) {pwm1 = 1; dir1 = 0; lcd_putc ('\f'); lcd_gotoxy (0, 0); lcd_putc ("dc1nguoc"); }
      IF (nut3 == 0) {pwm2 = 1; dir2 = 1; lcd_putc ('\f'); lcd_gotoxy (0, 0); lcd_putc ("dc2thuan"); }
      IF (nut4 == 0) {pwm2 = 1; dir2 = 0; lcd_putc ('\f'); lcd_gotoxy (0, 0); lcd_putc ("dc2nguoc"); }
      delay_ms(50);
      lcd_putc ('\f') ;
      //van1 = 0; lcd_putc ('\f'); lcd_gotoxy (0, 0); lcd_putc ("van1_set") ;
      //IF (nut1 == 0) {van1 = 0; lcd_putc ('\f'); lcd_gotoxy (0, 0); lcd_putc ("van1_set"); } else van1 = 1;
      //IF (nut2 == 0) {van2 = 0; lcd_putc ('\f'); lcd_gotoxy (0, 0); lcd_putc ("van2_set"); } else van2 = 1;
      //IF (nut3 == 0) {van3 = 0; lcd_putc ('\f'); lcd_gotoxy (0, 0); lcd_putc ("van3_set"); } else van3 = 1;
      //IF (nut4 == 0) {van4 = 0; lcd_putc ('\f'); lcd_gotoxy (0, 0); lcd_putc ("van4_set"); } else van4 = 1;
      //delay_ms (100) ;
      //van1 = 1; lcd_putc ('\f') ;
      //delay_ms (100) ;
   }
}

