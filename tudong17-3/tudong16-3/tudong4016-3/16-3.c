
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
   if (input(ChanelB)) {En2--;} 
   else {En2++;}
   }
else 
   { 
   if (input(ChanelB)) {En2++;}
   else {En2--;}
   }
}
#int_EXT2
void  EXT2_isr(void) 
{
INTEDG2^=1;
if (INTEDG2)
   {
   if (input(ChanelA)) {En2++;} 
   else {En2--;}
   }
else 
   { 
   if (input(ChanelA)) {En2--;}
   else {En2++;}
   }
}

/// PID DONG CO 1 //////////////////
float kp=2, ki=0.2,kd=0.7, pid1;
signed int16 realvt1, errs1=0, err1, delta1=0, epre1=0, duty1 ;
volatile unsigned int8 Ti1,Ti2;
volatile signed int16 setvt1,setvt2;

void piddc1(signed int16 setvt1)
     {
     br1=0;
     realvt1 =  qei_get_count(); 
     err1 = setvt1 - realvt1;
     if(Ti1>=2)
     {
       delta1 = err1-epre1;
       Ti1=0;
       if(delta1>-10) errs1 += err1;//(err1>-20)&&(err1<20)
       if (errs1 > 200 ) errs1=200;
       if (errs1 < -200 ) errs1=-200;
       epre1=err1;
     }
  
     pid1 =kp*err1 + ki*errs1+kd*delta1; 
     duty1=pid1;   
     if (duty1 > 0)   dir1 = 0;
     if (duty1 <  0)    dir1 = 1;
     duty1= abs(duty1);
     if(duty1>5) duty1+=200;
     if(duty1>500) duty1=500;
     set_pwm1_duty (duty1);
     }
     
/// PID DONG CO 2 //////////////////
signed int16 realvt2, errs2=0, err2, delta2=0, epre2=0, duty2 ;
float pid2;
void piddc2(signed int16 setvt2)
     {
     br2=0;
     realvt2 =  En2; 
     err2 = setvt2 - realvt2;
     if(Ti2>=2)
     {
       Ti2=0;
       if((err2>-20)&&(err2<20)) errs2 += err2;
       if (errs2 > 200 ) errs2=200;
       if (errs2 < -200 ) errs2=-200;
       delta2 = err2-epre2;
       epre2=err2;
     }
  
     pid2 =kp*err2 + ki*errs2+kd*delta2; 
     duty2=pid2;    
     if (duty2 > 0)   dir2 = 1;
     if (duty2 <  0)    dir2 = 0;
     duty2= abs(duty2);
     if(duty2>5) duty2+=200;
     if(duty2>400) duty2=400;
     set_pwm2_duty (duty2);
     }
     
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
      output_high(pin_d2);
      }
   if (demservo >=xungservo) output_low(pin_d2);
      
   }
     
///// NGAT TIMER1 PID
#int_timer1
void ngat_timer1(void) 
   {
      set_timer1(59286);
      Ti1++;
      Ti2++;
      dem++;
      piddc1(setvt1);
      piddc2(setvt2);
   }

///// KHAI BAO NHIEM VU
#include <resetall.c>
#include <nhiemvu2.c>
#include <nhiemvu3.c>
#include <nhiemvu4.c>

///// MAIN /////
int8 i=0;

void main()
{
   khoidong(); 
   resetall();
   chonct=0;
   xungservo=12;
   beep(1,100); 
   
   
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
      if (dem>50)
         {
         if (chonct==1) resetall();
         if (chonct==2) nhiemvu2();
         if (chonct==3) nhiemvu3();
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



