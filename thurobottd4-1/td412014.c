#include <18F4431.h>
#include <PIC18F4431_registers.h>
#fuses hs,nobrownout,nowdt,protect,put,nolvp,nodebug
#use delay(clock=20000000)

///////////////////////////////////////////////////
#define LCD_RS_PIN      PIN_B5                             
#define LCD_RW_PIN      PIN_B6   
#define LCD_ENABLE_PIN  PIN_B7                                                              
#define LCD_DATA4       PIN_D0                                 
#define LCD_DATA5       PIN_D1                                  
#define LCD_DATA6       PIN_D2                                   
#define LCD_DATA7       PIN_D3
#include <lcd.c>

void lcd_putnum(int32 so,INT8 x,int8 y)
{
   INT32 a, b, c, d, e;
   a = so / 10000;
   b = (so - 10000 * a) / 1000;
   c = (so - 10000 * a - 1000 * b) / 100;
   d = (so - 10000 * a - 1000 * b - 100 * c) / 10;
   e = so - 10000 * a - 1000 * b - 100 * c - 10 * d;
   lcd_gotoxy (x, y);
   lcd_putc (a + 48);
   lcd_putc (b + 48);
   lcd_putc (c + 48);
   lcd_putc (d + 48);
   lcd_putc (e + 48);
}

///////////////////////////////////////////////
#bit trisDin = trisc.7
#bit trisDout = trisc.6
#bit trisCLK = trisc.5
#bit trisCS = trisc.4
#bit Din = PORTc.7// dây 1 màu nâu (chan DI)
#bit Dout = PORTc.6 // dây 2 màu cam (chan DO)
#bit CLK = PORTc.5// dây 7 xanh da tr?i (chan CLK)
#bit CS = PORTc.4 // dây 6 màu vàng (chan CS)

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

void doctayPES()
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

///////////////////////////////////////////////
#bit vant=portd.7
#bit vanp=portd.6
#bit van3=portd.5
#bit van4=portd.4
#bit trisvant=trisd.7
#bit trisvanp=trisd.6
#bit trisvan3=trisd.5
#bit trisvan4=trisd.4
#bit br1=porta.4
#bit br2=porta.5
#bit trisbr1 = trisa.4
#bit trisbr2 = trisa.5
#bit dir1=portc.3
#bit dir2=portc.0
#bit trisdir1 = trisc.3
#bit trisdir2 = trisc.0
#bit pwm1=portc.2
#bit pwm2=portc.1
#bit trispwm1 = trisc.2
#bit trispwm2 = trisc.1

void dcpt(INT16 x)
{
   trispwm1 = trisdir1 = trisbr1 = 0;
   dir1 = 1;
   br1 = 0;
   setup_timer_2 (t2_div_by_4, 255, 1);
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (x);
}

void dcpn(INT16 x)
{
   trispwm1 = trisdir1 = trisbr1 = 0;
   dir1 = 0;
   br1 = 0;
   setup_timer_2 (t2_div_by_4, 255, 1);
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (x);
}

void resetdcp()
{
   trispwm1 = trisdir1 = trisbr1 = 0;
   setup_timer_2 (t2_div_by_4, 255, 1);
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (0);
   br1 = 1;
   dir1 = 0;
}

void dctt(SIGNED INT16 x)
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   dir2 = 1;
   br2 = 0;
   setup_timer_2 (t2_div_by_4, 255, 1);
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (x);
}

void dctn(SIGNED INT16 x)
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   br2 = 0;
   dir2 = 0;
   setup_timer_2 (t2_div_by_4, 255, 1);
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (x);
}

void resetdct()
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   br2 = 1;
   dir2 = 0;
   setup_timer_2 (t2_div_by_4, 255, 1);
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (0);
}

///////////////////////////////////////////
#bit ctp1=portb.0
#bit ctp2=portb.1
#bit ctt1=portb.2
#bit ctt2=portb.3
#bit trisctp1=trisb.0
#bit trisctp2=trisb.1
#bit trisctt1=trisb.2
#bit trisctt2=trisb.3

int16 i;

//////////////////////////////////////////////
void main()
{
   lcd_init ();
   lcd_putc (" NQ Fairy...");
   delay_ms (500);
   lcd_putc ('\f');
   PORT_B_PULLUPS(0xff);
   WHILE (true)
   {
      start=1;
      while(start==1) {doctayPES (); lcd_gotoxy(0,1); lcd_putc (" Ready1..."); };
      lcd_putc ('\f');
      if (start==0) {trisctp1=1; while(ctp1==1){dcpn(400); }; resetdcp(); start=1; delay_ms(500); };//vi tri dau dcp
     
      while(start==1) {doctayPES (); lcd_gotoxy(0,1); lcd_putc (" Ready2..."); };
      lcd_putc ('\f');
      if (start==0) {trisctt2=1; while(ctt2==1) {dctn(400); }; resetdct(); start=1; delay_ms(500); };//vi tri dau dct
      
      while(start==1) {doctayPES (); lcd_gotoxy(0,1); lcd_putc (" Ready3..."); };
      lcd_putc ('\f');
      if (start==0) {trisvant=0; vant=0; start=1; delay_ms(500);};//mo van trai
      
      while(start==1) {doctayPES (); lcd_gotoxy(0,1); lcd_putc (" Ready4..."); };
      lcd_putc ('\f');
      if (start==0) {trisvant=0; vant=1; start=1; delay_ms(500);};//dong van trai
      
      while(start==1) {doctayPES (); lcd_gotoxy(0,1); lcd_putc (" Ready5..."); };
      lcd_putc ('\f');
      if (start==0) {trisvanp=0; vanp=0; start=1; delay_ms(500);};//mo van phai
      
      while(start==1) {doctayPES (); lcd_gotoxy(0,1); lcd_putc (" Ready6..."); };
      lcd_putc ('\f');
      if (start==0) {trisctt1=1; while(ctt1==1) {dctt(400);} resetdct(); start=1; delay_ms(500); };//quay dct >ct1
      
      while(start==1) {doctayPES (); lcd_gotoxy(0,1); lcd_putc (" Ready7..."); };
      lcd_putc ('\f');
      if (start==0) {trisvanp=0; vanp=1; start=1; delay_ms(500);};//dong van phai
      
      while(start==1) {doctayPES (); lcd_gotoxy(0,1); lcd_putc (" Ready8..."); };
      lcd_putc ('\f');
      if (start==0) {trisvant=0; vant=0; start=1; delay_ms(500);};//mo van trai
      
      while(start==1) {doctayPES (); lcd_gotoxy(0,1); lcd_putc (" Ready9..."); };
      lcd_putc ('\f');
      if (start==0) { for (i=0; i<50000; i++) {dcpt(400);}; resetdcp(); start=1; delay_ms(500); };//quay dcp ra giua
      
      while(start==1) {doctayPES (); lcd_gotoxy(0,1); lcd_putc (" Ready10..."); };
      lcd_putc ('\f');
      if (start==0) {trisctt2=1; while(ctt2==1) {dctn(400); }; resetdct(); start=1; delay_ms(500); };//quay dct >ct2
      
      while(start==1) {doctayPES (); lcd_gotoxy(0,1); lcd_putc (" Ready11..."); };
      lcd_putc ('\f');
      if (start==0) {trisctp2=1; while(ctp2==1) {dcpt(400); }; resetdcp(); start=1; delay_ms(500); };//quay dcp >ct2
      
      while(start==1) {doctayPES (); lcd_gotoxy(0,1); lcd_putc (" Ready12..."); };
      lcd_putc ('\f');
      if (start==0) {trisvant=0; vant=1; start=1; delay_ms(500);};//dong van trai
      
      
      /*
      lcd_putnum (adcudp, 0, 0);
      lcd_putnum (adcrlp, 8, 0);
      lcd_putnum (adcudt, 0, 1);
      lcd_putnum (adcrlt, 8, 1);
      IF (len == 0){lcd_putc ('\f'); lcd_putc ("len"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (xuong == 0){lcd_putc ('\f'); lcd_putc ("xuong"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (trai == 0){lcd_putc ('\f'); lcd_putc ("trai"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (phai == 0){lcd_putc ('\f'); lcd_putc ("phai"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (select == 0){lcd_putc ('\f'); lcd_putc ("select"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (start == 0){lcd_putc ('\f'); lcd_putc ("start"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (nut1 == 0){lcd_putc ('\f'); lcd_putc ("nut1"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (nut2 == 0){lcd_putc ('\f'); lcd_putc ("nut2"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (nut3 == 0){lcd_putc ('\f'); lcd_putc ("nut3"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (nut4 == 0){lcd_putc ('\f'); lcd_putc ("nut4"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (trai0 == 0){lcd_putc ('\f'); lcd_putc ("trai0"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (trai1 == 0){lcd_putc ('\f'); lcd_putc ("trai1"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (trai2 == 0){lcd_putc ('\f'); lcd_putc ("trai2"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (phai0 == 0){lcd_putc ('\f'); lcd_putc ("phai0"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (phai1 == 0){lcd_putc ('\f'); lcd_putc ("phai1"); delay_ms (500) ; lcd_putc ('\f') ; }
      IF (phai2 == 0){lcd_putc ('\f'); lcd_putc ("phai2"); delay_ms (500) ; lcd_putc ('\f') ; }
      */
      
   }
}

