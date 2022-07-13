
///// CHUONG TRINH CHINH
#include <khoidong.c>
#include <van-ctht.c>
#include <dongco.c>

///// QEI MEM + DU LIEU QEI
signed int16 En2;
#define ChanelA PIN_C4
#define ChanelB PIN_C5
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

/// PID DONG CO 1 //////////////////
signed int16 err1=0, realvt1=0;
void piddc1(signed int16 setvt1)
     {
     realvt1 = qei_get_count(); 
     if ( realvt1 < setvt1 ) { err1=setvt1-realvt1;} //dc1 nguoc
     if (err1>600) dc1n(600); else dc1n(err1+200);
     
     if ( realvt1 > setvt1 ) { err1=realvt1-setvt1; } //dc1 thuan
     if (err1>600) dc1t(600); else dc1t(err1+200);
     
     if (realvt1 == setvt1) {resetdc1();}
     }
     
///// NGAT TIMER0
#int_timer0
void ngat_timer0(void) 
   {
      set_timer0(50000);
      
   }
     
///// NGAT TIMER1
#int_timer1
void ngat_timer1(void) 
   {
      set_timer1(3035);
   }

///// KHAI BAO NHIEM VU

#include <nhiemvu1.c>
#include <nhiemvu2.c>
#include <nhiemvu3.c>
#include <nhiemvu4.c>

///// CHUONG TRINH QUET PHIM
signed int8 chonct;

void quetphim()
{
while (cten==0) 
   {
   if (ctsel==0) 
      {
      chonct++;
      beep(1,100);
      while (ctsel==0){};
      }
   if (chonct>4) { chonct=0; beep(4,100); }
   }
}


///// MAIN /////
void main()
{
   khoidong(); 
   br1=br2=1;
   dir1=pwm1=dir2=pwm2=0;
   vantay1=vantay2=vancanh1=vanleo=vancanh2=vanduoi=1;
   ///En1=0; /// dc1 quay nguoc la duong
   En2=0; /// dc2 quay nguoc la am
   
   beep(2,100);   
while(true)
   {
   switch(chonct)
      {
      case 1:  beep(1,100); 
               nhiemvu1(); 
               break;
      
      case 2:  beep(2,100);
               nhiemvu2();
               break;
      
      case 3:  beep(3,100);
               nhiemvu3();
               break;
      
      case 4:  beep(4,100);
               nhiemvu4();
               break;
      }
     
   } 
  

}

