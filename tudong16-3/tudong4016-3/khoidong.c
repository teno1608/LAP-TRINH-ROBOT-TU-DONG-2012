
///// KHOI DONG PIC

#include <18F4431.h>
#include <PIC18F4431_registers.h>
#include <stdlib.h>
#include <stdio.h>
#FUSES NOWDT, H4,PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT//, SSP_RD
#use delay(clock=40000000)

//#use spi(MASTER ,FORCE_HW, BITS=16)
//#bit ss1 = PORTD.0

#use fast_io(a)
#use fast_io(d)
#use fast_io(c)
#use fast_io(e)

void khoidong()
{
   trisa=0b00011000; /// DAU VAO QEI CUNG
   trisb=0b11111111; /// DAU VAO CONG TAC HANH TRINH
   port_b_pullups(0xff);
   trisc=0b00110000; /// DAU VAO QEI MEM
   portc=0b00000000;
   trisd=0b00000100; /// DAU VAO SPI 0b00000100
   trise=0b00000000;
   
   enable_interrupts(INT_EXT1);
   enable_interrupts(INT_EXT2);
   
   enable_interrupts(int_timer0);
   enable_interrupts(int_timer1);
   
   enable_interrupts(GLOBAL);
   ext_int_edge(1,L_to_H);
   ext_int_edge(2,L_to_H);
   
   clear_interrupt(INT_EXT1);
   clear_interrupt(INT_EXT2);
   clear_interrupt(int_timer0);
   clear_interrupt(int_timer1);
   
   setup_qei(qei_mode_x4,qei_filter_enable_qea|qei_filter_enable_qeb|qei_filter_div_2,65535);
   qei_set_count(0);
   
   setup_timer_0(T0_INTERNAL|RTCC_DIV_32);      //210 ms overflow, 3.2us
   set_timer0(59285);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);      //52.4 ms overflow, 0.8us
   set_timer1(59286);
   
   //setup_spi(SPI_MASTER|SPI_L_TO_H|SPI_CLK_DIV_16);
   //ss1=1;
   
   setup_timer_2 (t2_div_by_1, 249, 1);
   setup_ccp1 (ccp_pwm);
  
}