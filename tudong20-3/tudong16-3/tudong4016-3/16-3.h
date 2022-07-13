#include <18F4431.h>

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES WDT128                	//Watch Dog Timer uses 1:128 Postscale
#FUSES LP                    	//Low power osc < 200 khz
#FUSES FCMEN                 	//Fail-safe clock monitor enabled
#FUSES IESO                  	//Internal External Switch Over mode enabled
#FUSES NOPUT                 	//No Power Up Timer
#FUSES NOBROWNOUT            	//No brownout reset
#FUSES BORRES                #FUSES NOWINEN               	//WDT Timer Window Disabled
#FUSES NOPWMPIN              	//PWM outputs drive active state upon Reset
#FUSES LPOL_HIGH             	//Low-Side Transistors Polarity is Active-High (PWM 0,2,4 and 6)
	//PWM module low side output pins have active high output polar
#FUSES HPOL_HIGH             	//High-Side Transistors Polarity is Active-High (PWM 1,3,5 and 7)
	//PWM module high side output pins have active high output polarity
#FUSES T1LOWPOWER            	//Timer1 low power operation when in sleep
#FUSES FLTAC1                	//FLTA input is multiplexed with RC1
#FUSES SSP_RC                	//SCK/SCL=RC5, SDA/SDI=RC4, SDO=RC7
#FUSES PWM4B5                	//PWM4 output is multiplexed on RB5
#FUSES EXCLKC3               	//TMR0/T5CKI external clock input is muliplexed with RC3
#FUSES MCLR                  	//Master Clear pin enabled
#FUSES STVREN                	//Stack full/underflow will cause reset
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NODEBUG               	//No Debug mode for ICD
#FUSES NOPROTECT             	//Code not protected from reading
#FUSES NOCPB                 	//No Boot Block code protection
#FUSES NOCPD                 	//No EE protection
#FUSES NOWRT                 	//Program memory not write protected
#FUSES NOWRTC                	//configuration not registers write protected
#FUSES NOWRTB                	//Boot block not write protected
#FUSES NOWRTD                	//Data EEPROM not write protected
#FUSES NOEBTR                	//Memory not protected from table reads
#FUSES NOEBTRB               	//Boot block not protected from table reads

#use delay(clock=40000000)

