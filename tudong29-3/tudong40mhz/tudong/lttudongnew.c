
///// CHUONG TRINH CHINH

#include <lttudongnew.h>
#include <PIC18F4431_registers.h>
#include <khoidong.c>
#include <van-ctht.c>
#include <dongco.c>
#include <qei_piddc.c>

///// CHUONG TRINH QUET PHIM
int8 demct=0;

///// NGAT TIMER0 LEO THANG, SERVO
volatile char demservo=0, xungleo=100;
volatile int1 dclep=0 ;
int16 demvanduoi=0;
#int_timer0
void ngat_timer0(void) 
   {
   demvanduoi++;
   if (dclep==1)
   {
      set_timer0(5);
      demservo++;
      if (demservo>100)
         {
         demservo=0;
         pwm3=0;
         }
      if (demservo >=xungleo) pwm3=1;
   }
   else
      {
      set_timer0(5);
      demservo++;
      if (demservo>=200)
         {
         demservo=0;
         output_high(pin_c7);
         }
      if (demservo >=xungleo) output_low(pin_c7);
      }
   }   
     
///// NGAT TIMER1 PID
 volatile int8 chonpid;
#int_timer1
void ngat_timer1(void) 
   {
      set_timer1(58286);
      Ti1++;
      Ti2++;
      switch (chonpid)  
         {
          case 0 : disable_interrupts(int_timer1); resetdc1(); resetdc2(); break;
          case 1 : resetdc2(); piddc1(setvt1,vt1); break;
          case 2 : resetdc1(); piddc2(setvt2,vt2); break;
          case 3 : {piddc1(setvt1,vt1); piddc2(setvt2,vt2);}  break;
         }
 
   }
   
///// NGAT TIMER5 QUET PHIM 
#int_timer5
void ngat_timer5(void) 
   {
      set_timer5(53035);
      demct++;
      if (demct==2) { beep(1,50); }
      if (demct==50) { beep(1,50); }
      if (demct==100) { beep(1,50); }
      if (demct==150) { beep(1,50); }
      if (demct>200) {demct=0; disable_interrupts(int_timer5); }
      
      
   }   

///// KHAI BAO NHIEM VU
//#include <resetall.c>
#include <resetvan.c>
#include <nhiemvu2.c>
#include <nhiemvu3.c>
#include <nhiemvu3x.c>
#include <nhiemvu4.c>

///// MAIN /////
int8 i=0;

void main()
{
   khoidong(); 
   En2=0;
   Ti1=0;
   Ti2=0;
   setvt1=0;
   setvt2=0;
   beep(2,100); 
  
while(true)
   {
   
   if (ctsel==0) 
      {
      enable_interrupts(int_timer5);
      demct=0; i=1; delay_ms(10); 
      while (ctsel==0) {}
      }
      
   while (i==1) 
      {
      if ( demct<50 ) {disable_interrupts(int_timer5); i=0; demct=0;  resetvan(); }
      if ((50<demct)&(demct<100)) {disable_interrupts(int_timer5); i=0; demct=0; nhiemvu2(); } 
      if ((100<demct)&(demct<150)) {disable_interrupts(int_timer5); i=0; demct=0; nhiemvu3x(); }
      if ((150<demct)&(demct<200)) {disable_interrupts(int_timer5); i=0; demct=0; nhiemvu4(); }
      }
    
   }


}





