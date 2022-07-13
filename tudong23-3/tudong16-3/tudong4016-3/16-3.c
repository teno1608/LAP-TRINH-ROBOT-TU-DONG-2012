
///// CHUONG TRINH CHINH
#include <khoidong.c>
#include <van-ctht.c>
#include <dongco.c>
#include <qei_piddc.c>

///// CHUONG TRINH QUET PHIM
volatile int16 dem=0, chonct=0;

///// NGAT TIMER0
char demservo, xungservo;
#int_timer0
void ngat_timer0(void) 
   {
   set_timer0(5);
   demservo++;
   if (demservo>=200)
      {
      demservo=0;
      output_high(pin_d6);
      }
   if (demservo >=xungservo) output_low(pin_d6);
      
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
   
///// NGAT TIMER5 QUET PHIM 
#int_timer5
void ngat_timer5(void) 
   {
      set_timer5(59286);
      dem++;
   }   

///// KHAI BAO NHIEM VU
#include <resetall.c>
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
   
   //resetall();
   chonct=0;
   beep(2,100); 
      
while(true)
   {
   
      
    if (ctsel==0)
      {
      dem=0;
      i=0;
      beep(1,100);
      while (i==0)
         {
         if (ctsel==1) {delay_ms(50); i=1;}
         }
      if (dem>70)
         {
         if (chonct==1) resetvan();
         if (chonct==2) nhiemvu2();
         if (chonct==3) nhiemvu3x();
         if (chonct==4) nhiemvu4();
         }
      else 
         {
         chonct++;
         if (chonct>4) {chonct=0; beep(10,100);}
         }
      }
   } 

}



