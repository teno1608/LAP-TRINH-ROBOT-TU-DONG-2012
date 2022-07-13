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

signed INT16 endata1=0, endata1n=0; 
#INT_ext1

void ngatngoai1()
{
   triskenhBt = 1;
   IF (kenhBt == 0) endata1++; else endata1n++;
}

/////////////////////////////////////////////////
#bit triskenhAp=trisc.5
#bit kenhAp=portc.5
#bit triskenhBp=trisc.7
#bit kenhBp=portc.7

signed INT16 endata2=0, endata2n=0;

#INT_ext2

void ngatngoai2()
{ 
   triskenhBp = 1;
   IF (kenhBp == 0) endata2++; else endata2n++;
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
#bit van2=porta.2
#bit van1=porta.3
#bit van3=porta.1
#bit van4=porta.0
#bit trisvan2=trisa.2
#bit trisvan1=trisa.3
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

void dc1t(INT16 x)
{
   trispwm1 = trisdir1 = trisbr1 = 0;
   dir1 = 1;
   br1 = 0;
   setup_timer_2 (t2_div_by_4, 255, 1);
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (x);
}

void dc1n(INT16 x)
{
   trispwm1 = trisdir1 = trisbr1 = 0;
   dir1 = 0;
   br1 = 0;
   setup_timer_2 (t2_div_by_4, 255, 1);
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (x);
}

void resetdc1()
{
   trispwm1 = trisdir1 = trisbr1 = 0;
   setup_timer_2 (t2_div_by_4, 255, 1);
   setup_ccp1 (ccp_pwm);
   set_pwm1_duty (0);
   br1 = 1;
   dir1 = 0;
}

void dc2t(SIGNED INT16 x)
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   dir2 = 1;
   br2 = 0;
   setup_timer_2 (t2_div_by_4, 255, 1);
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (x);
}

void dc2n(SIGNED INT16 x)
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   br2 = 0;
   dir2 = 0;
   setup_timer_2 (t2_div_by_4, 255, 1);
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (x);
}

void resetdc2()
{
   trispwm2 = trisdir2 = trisbr2 = 0;
   br2 = 1;
   dir2 = 0;
   setup_timer_2 (t2_div_by_4, 255, 1);
   setup_ccp2 (ccp_pwm);
   set_pwm2_duty (0);
}

///////////////////////////////////////////
#bit ct1=portd.6
#bit ct2=portd.7
#bit trisct1=trisd.6
#bit trisct2=trisd.7

#bit tay2=portd.5
#bit tay1=portd.4
#bit tristay2=trisd.5
#bit tristay1=trisd.4


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
      nut1 = 1;
      WHILE (nut1 == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready1..."); if (nut4 == 0) {trisvan1 = 0; van1 = 0; trisvan2 = 0; van2 = 0; } };
      lcd_putc ('\f');
      
      trisct1 = 1; ct1 = 1; WHILE (ct1 == 1){dc1n (600); }; resetdc1 ();//vi tri dc1 ctht
      delay_ms(100);
      
      trisct2 = 1; ct2 = 1; WHILE (ct2 == 1) {dc2t (600); }; resetdc2();//vi tri dc2 ctht
      delay_ms(100);
      
      endata2n = 0; WHILE (endata2n <180) {dc2n (600); }; resetdc2 ();start = 1; //vi tri reset
      delay_ms(100);
      
      endata1 = 0; WHILE (endata1 <180) {dc1t (600); }; resetdc1 ();start = 1;//vi tri reset
      delay_ms(100);
      
      nut1 = 1;
      WHILE (nut1 == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready1+..."); if (nut4 == 0) {trisvan1 = 0; van1 = 0; trisvan2 = 0; van2 = 0; } };
      lcd_putc ('\f');
      
      trisct1 = 1; ct1 = 1; WHILE (ct1 == 1){dc1n (600); }; resetdc1 ();//vi tri dc1 ctht
      delay_ms(100);
      
      trisct2 = 1; ct2 = 1; WHILE (ct2 == 1) {dc2t (600); }; resetdc2();//vi tri dc2 ctht
      delay_ms(100);
      
      endata2n = 0; WHILE (endata2n <35) {dc2n (600); }; resetdc2 ();nut1 = 1; trisvan2=0; van2=0; //vi tri ket, mo van 2  
      delay_ms(100);
      
      WHILE (nut1 == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready5..."); if (nut4 == 0) {trisvan1 = 0; van1 = 0; trisvan2 = 0; van2 = 0; }; };
      lcd_putc ('\f');
 
      trisvan2 = 0; van2 = 1; nut1 = 1; delay_ms (300); //dong van 2
      WHILE (nut1 == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready6..."); if (nut4 == 0) {trisvan1 = 0; van1 = 0; trisvan2 = 0; van2 = 0; }; };
      lcd_putc ('\f');
      
      trisvan1 = 0; van1 = 0; start = 1; delay_ms (200); //mo van 1
     
      tristay1=1; tay1=1; endata2=0; while (tay1==1) {dc2t(600); if (endata2>60) {resetdc2(); while (true) {}; };}; resetdc2(); start=1; trisvan1 = 0; van1 = 1; start = 1; delay_ms (300); //dong van phai
      
      trisvan2 = 0; van2 = 0; start = 1; delay_ms (200); //mo van 2
      
      endata1=0; while (endata1<100) {dc1t(600); }; resetdc1(); start=1; delay_ms (10);
      
      endata2n=0; while (endata2n<180){dc2n(600); }; resetdc2(); start=1; delay_ms(10);
      
      tristay2=1; tay2=1; endata1=0; while (tay2==1) {dc1t(600); if (endata1>100) {resetdc1(); while (true) {}; };}; resetdc1(); start=1; trisvan2 = 0; van2 = 1; delay_ms (300);
         
      trisvan1 = 0; van1 = 0; start = 1; delay_ms (200); //mo van 1
      
      endata2=0; while(endata2<100) {dc2t(600); lcd_putnum(endata2,0,0); };resetdc2(); start=1; delay_ms(10);
      
      trisct1 = 1; ct1 = 1; WHILE (ct1 == 1){dc1n (600); }; resetdc1() ; start = 1; delay_ms (10);
      
      tristay1=1; tay1=1; endata2=0; while (tay1==1) {dc2t(600); if (endata2>100) {resetdc2(); while (true) {}; };}; resetdc2(); start=1; trisvan1 = 0; van1 = 1; delay_ms (300);
      
      trisvan2 = 0; van2 = 0; nut1 = 1; delay_ms (200); //mo van 2
      
      endata1=0; while (endata1<30) {dc1t(600); }; resetdc1(); start=1; delay_ms (300);
      WHILE (nut1 == 1){doctayPES (); lcd_gotoxy (0, 1); lcd_putc (" Ready18..."); if (nut4 == 0) {trisvan1 = 0; van1 = 0; trisvan2 = 0; van2 = 0; } };
      lcd_putc ('\f');
     
      /////////////////////////////////////////////////////////////////////////////////////////////////
    
      tristay2=1; tay2=1; endata1n=0; while (tay2==1) {dc1n(600); if (endata1n>60) {resetdc1(); while (true) {}; };}; resetdc1(); start=1; trisvan2 = 0; van2 = 1; delay_ms (300);
      delay_ms(300);
      
      trisvan1 = 0; van1 = 0; start = 1; delay_ms (300); //mo van 1
      
      endata2n=0; while (endata2n<40) {dc2n(600); }; resetdc2();
      
      tristay1=1; tay1=1; endata1=0; while (tay1==1) {dc2n(600); if (endata1<190) {dc1t(700);} else {resetdc1();}; }; resetdc2();  trisvan1 = 0; van1 = 1; delay_ms (300);
      
      trisvan2 = 0; van2 = 0; start = 1; delay_ms (300); //mo van 2
      
      endata1n=0; while (endata1n<40) {dc1n(600);}; resetdc1();
      
      tristay2=1; tay2=1; endata2=0; while (tay2==1) {dc1n(600); if (endata2<190) {dc2t(700); } else {resetdc2();}; }; resetdc1(); trisvan2 = 0; van2 = 1; delay_ms(300);
      
      trisvan1 = 0; van1 = 0; start = 1; delay_ms (300); //mo van 1
      
      endata2n = 0; WHILE (endata2n <35) {dc2n (700); }; resetdc2 ();//vi tri ket  
      delay_ms(300);
      
      
      
      
      
      
      IF (start == 0){ WHILE (true) {}; };
   }
}


