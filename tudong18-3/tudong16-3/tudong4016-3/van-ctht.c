
///// DEFINE VAN

#bit vantay1=porte.1
#bit vantay2=porte.0
#bit vancanh1=porta.2    
#bit vancanh2=porta.0    
#bit vanleo=porta.1
#bit vanduoi=porta.5

///// DEFINE CONG TAC HANH TRINH
#bit ctc1=portb.0
#bit ctt1=portb.1
#bit ctc2=portb.2
#bit ctt2=portb.3
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
   delay_ms(30);
   loa = 1;
   delay_ms(time-30);
   }
}
