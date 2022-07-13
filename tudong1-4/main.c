#include <18f4431.h>
#include <PIC18F4431_registers.h>
#fuses   hs,nolvp,nowdt,ssp_rd
#use     delay(clock=20000000)
///// CHUONG TRINH HIEN THI LCD
#define LCD_RS_PIN      PIN_D5                                 
#define LCD_RW_PIN      PIN_D6    
#define LCD_ENABLE_PIN  PIN_D7                                                              
#define LCD_DATA4       PIN_B0                                 
#define LCD_DATA5       PIN_B1                                  
#define LCD_DATA6       PIN_B2                                   
#define LCD_DATA7       PIN_B3
#include <lcd.c>

///// NGAT NHAN SPI
signed int16 spi_data=0;
#int_ssp
void nhan_dulieu(void) 
   {
   spi_data=spi_read();
   }

///// CHUONG TRINH CHINH   

void main(void) 
{
   lcd_init();  
   setup_spi(SPI_SLAVE |SPI_L_TO_H  );
   enable_interrupts(int_ssp);
   clear_interrupt(int_ssp);
   enable_interrupts(global);
   

while(true)
   {
   printf(LCD_PUTC,"\fxung %5ld",spi_data);
   delay_ms(10);
   }
   
}
