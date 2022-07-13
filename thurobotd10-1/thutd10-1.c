#include <18F4431.h>
#include <PIC18F4431_registers.h>
#fuses hs,nobrownout,nowdt,protect,put,nolvp,nodebug
#use delay(clock=20000000)

///////////////////////////////////////////////////
#define LCD_RS_PIN      PIN_b7                            
#define LCD_RW_PIN      PIN_b6   
#define LCD_ENABLE_PIN  PIN_b5                                                              
#define LCD_DATA4       PIN_d0                                 
#define LCD_DATA5       PIN_d1                                  
#define LCD_DATA6       PIN_d2                                   
#define LCD_DATA7       PIN_d3
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

/////////////////////////////////////////////////
#bit triskenhAt=trisc.4
#bit kenhAt=portc.4
#bit triskenhBt=trisc.6
#bit kenhBt=portc.6

signed INT16 endatap=0, endatapn=0; 
#INT_ext1

void ngatngoai1()
{
   
   triskenhBt = 1;
   IF (kenhBt == 0) endatap++; else endatapn++;
}

/////////////////////////////////////////////////
#bit triskenhAp=trisc.5
#bit kenhAp=portc.5
#bit triskenhBp=trisc.7
#bit kenhBp=portc.7

signed INT16 endatat=0, endatatn=0;

#INT_ext2

void ngatngoai2()
{
   
   triskenhBp = 1;
   IF (kenhBp == 0) endatat++; else endatatn++;
}

//////////////////////////////////////////////////
void setint()
{
   enable_interrupts (global);
   enable_interrupts (INT_ext1_h2l);
   enable_interrupts (INT_ext2_h2l);
}

///////////////////////////////////////////////
#bit trisDin = trisb.0
#bit trisDout = trisb.1
#bit trisCLK = trisb.2
#bit trisCS = trisb.3
#bit Din = PORTb.0// dây 1 màu nâu (chan DI)
#bit Dout = PORTb.1 // dây 2 màu cam (chan DO)
#bit CLK = PORTb.2// dây 7 xanh da tr?i (chan CLK)
#bit CS = PORTb.3 // dây 6 màu vàng (chan CS)

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
#bit vant=porta.2
#bit vanp=porta.3
#bit van3=porta.1
#bit van4=porta.0
#bit trisvant=trisa.2
#bit trisvanp=trisa.3
#bit trisvan3=trisa.1
#bit trisvan4=trisa.0
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
#bit ctp=portd.6
#bit ctt=portd.7
#bit trisctp=trisd.6
#bit trisctt=trisd.7

#bit tayt=portd.5
#bit tayp=portd.4
#bit tristayt=trisd.5
#bit tristayp=trisd.4


//////////////////////////////////////////////
void main()
{
   lcd_init ();
   lcd_putc ("Ready...");
   delay_ms (500);
   lcd_putc ('\f');
   PORT_B_PULLUPS (0xff);
   setint ();

   WHILE (true)
   {
      
      start = 1;
      WHILE (start == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready1..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      lcd_putc ('\f');
      if (start == 0){trisctp = 1; ctp = 1; WHILE (ctp == 1){dcpn (600); }; resetdcp () ; start = 1; delay_ms (500); };
      //WHILE (start == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready2..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      //lcd_putc ('\f');
      delay_ms(1000);
      if (start == 0){trisctt = 1; ctt = 1; WHILE (ctt == 1) {dctt (600); }; resetdct(); start = 1; endatatn = 0; delay_ms (500) ; };
      //WHILE (start == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready3..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      //lcd_putc ('\f');
      delay_ms(1000);
      if (start == 0){endatatn = 0; WHILE (endatatn <30) {dctn (600); }; resetdct (); start = 1; delay_ms (500); };
      //WHILE (start == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready4..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      //lcd_putc ('\f');
      delay_ms(1000);
      IF (start == 0){trisvant = 0; vant = 0; start = 1; delay_ms (500); }; //mo van trai
      WHILE (start == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready5..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      lcd_putc ('\f');
      
      IF (start == 0){trisvant = 0; vant = 1; start = 1; delay_ms (500); }; //dong van trai
      WHILE (start == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready6..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      lcd_putc ('\f');
      IF (start == 0){trisvanp = 0; vanp = 0; start = 1; delay_ms (500); }; //mo van phai
      //WHILE (start == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready7..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      //lcd_putc ('\f');
      delay_ms(1000);
      IF (start == 0){ tristayp=1; tayp=1; endatat=0; while (tayp==1) {dctt(600); if (endatat>60) {resetdct(); while (true) {}; };}; resetdct(); start=1; trisvanp = 0; vanp = 1; start = 1; delay_ms (500); }; //dong van phai
      //WHILE (start == 1){doctayPES (); lcd_gotoxy (0,1); lcd_putc (" Ready8..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      //lcd_putc ('\f');
      delay_ms(1000);
      IF (start == 0){trisvant = 0; vant = 0; start = 1; delay_ms (500); }; //mo van trai
      //WHILE (start == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready9..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      //lcd_putc ('\f');
      delay_ms(1000);
      IF (start == 0){ endatap=0; while (endatap<100) {dcpt(600); }; resetdcp(); start=1; delay_ms (500); };
      //WHILE (start == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready10..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      //lcd_putc ('\f');
      delay_ms(1000);
      if (start ==0){ endatatn=0; while (endatatn<180){dctn(600); }; resetdct(); start=1; delay_ms(500); }
      //WHILE (start == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready11..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      //lcd_putc ('\f');
      delay_ms(1000);
      IF (start == 0){ tristayt=1; tayt=1; endatap=0; while (tayt==1) {dcpt(600); if (endatap>100) {resetdcp(); while (true) {}; };}; resetdcp(); start=1; trisvant = 0; vant = 1; delay_ms (500); }; 
      //WHILE (start == 1){doctayPES (); lcd_gotoxy (0,1); lcd_putc (" Ready12..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      //lcd_putc ('\f');
      delay_ms(1000);
      IF (start == 0){trisvanp = 0; vanp = 0; start = 1; delay_ms (500); }; //mo van phai
      //WHILE (start == 1){doctayPES (); lcd_gotoxy (0,1); lcd_putc (" Ready13..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      //lcd_putc ('\f');
      delay_ms(1000);
      IF (start == 0){ endatat=0; while(endatat<100) {dctt(600); lcd_putnum(endatat,0,0); };resetdct(); start=1; delay_ms(500);}
      //WHILE (start == 1){doctayPES (); lcd_gotoxy (0,1); lcd_putc (" Ready14..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      //lcd_putc ('\f');
      delay_ms(1000);
      if (start == 0){trisctp = 1; ctp = 1; WHILE (ctp == 1){dcpn (600); }; resetdcp () ; start = 1; delay_ms (500); };
      //WHILE (start == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready15..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      //lcd_putc ('\f');
      delay_ms(1000); 
      IF (start == 0){ tristayp=1; tayp=1; endatat=0; while (tayp==1) {dctt(600); if (endatat>100) {resetdct(); while (true) {}; };}; resetdct(); start=1; trisvanp = 0; vanp = 1; delay_ms (500); };
      //WHILE (start == 1){doctayPES (); lcd_gotoxy (0,1); lcd_putc (" Ready16..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      //lcd_putc ('\f');
      delay_ms(1000);
      IF (start == 0){trisvant = 0; vant = 0; start = 1; delay_ms (500); }; //mo van trai
      //WHILE (start == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready17..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      //lcd_putc ('\f');
      delay_ms(1000);
      IF (start == 0){ endatap=0; while (endatap<20) {dcpt(600); }; resetdcp(); start=1; delay_ms (500); };
      WHILE (start == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready18..."); if (select == 0) {trisvanp = 0; vanp = 0; trisvant = 0; vant = 0; } };
      lcd_putc ('\f');
      
      IF (start == 0){ WHILE (true) {} };
   }
}

