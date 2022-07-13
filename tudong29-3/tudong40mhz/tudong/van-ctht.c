
///// DEFINE VAN

#bit vantay1=porta.5
#bit vantay2=porte.0
#bit vancanh2=porta.0    
#bit vancanh1=porta.1    
#bit vanduoi=porta.2

///// DEFINE CONG TAC HANH TRINH
#bit ctt2=portb.0
#bit ctc2=portb.1
#bit ctt1=portb.2
#bit ctc1=portb.3

#bit ctld=portb.4
#bit ctlt=portb.5

#bit ctsel=portb.7
#bit cten=portb.6

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

