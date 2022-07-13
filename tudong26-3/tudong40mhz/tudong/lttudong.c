
///// CHUONG TRINH CHINH
#include <khoidong.c>
#include <van-ctht.c>
#include <dongco.c>
#include <qei_piddc.c>

///// CHUONG TRINH QUET PHIM
int8 demct=0, chonct=0;

///// NGAT TIMER0
volatile int8 demservo, xungleo=0;
#int_timer0
void ngat_timer0(void) 
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
     
///// NGAT TIMER1 PID
#int_timer1
void ngat_timer1(void) 
   {
      set_timer1(59286);
      Ti1++;
      Ti2++;
      piddc1(setvt1,vt1);
      piddc2(setvt2,vt2);
      
   }
   
///// NGAT TIMER2 LEO THANG
/*
char demxleo, xungleo;
#int_timer2
void ngat_timer2(void) 
   {
   demxleo++;
   if (demxleo>=200)
      {
      demxleo=0;
      output_high(pin_d6);
      }
   if (demxleo >=xungleo) output_low(pin_d6);
   }
 */ 
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
   chonct=0;
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
      if ( demct<50 ) {i=0; resetvan(); }
      if ((50<demct)&(demct<100)) {i=0; nhiemvu2(); } 
      if ((100<demct)&(demct<150)) {i=0; nhiemvu3x(); }
      if ((150<demct)&(demct<200)) {i=0; nhiemvu4(); }
      }
    
   }

}




