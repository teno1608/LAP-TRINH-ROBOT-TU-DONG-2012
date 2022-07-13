
;CodeVisionAVR C Compiler V2.05.0 Professional
;(C) Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com

;Chip type                : ATmega64
;Program type             : Application
;Clock frequency          : 11.059200 MHz
;Memory model             : Small
;Optimize for             : Size
;(s)printf features       : int, width
;(s)scanf features        : int, width
;External RAM size        : 0
;Data Stack size          : 1024 byte(s)
;Heap size                : 0 byte(s)
;Promote 'char' to 'int'  : Yes
;'char' is unsigned       : Yes
;8 bit enums              : Yes
;global 'const' stored in FLASH: No
;Enhanced core instructions    : On
;Smart register allocation     : On
;Automatic register allocation : On

	#pragma AVRPART ADMIN PART_NAME ATmega64
	#pragma AVRPART MEMORY PROG_FLASH 65536
	#pragma AVRPART MEMORY EEPROM 2048
	#pragma AVRPART MEMORY INT_SRAM SIZE 4351
	#pragma AVRPART MEMORY INT_SRAM START_ADDR 0x100

	#define CALL_SUPPORTED 1

	.LISTMAC
	.EQU UDRE=0x5
	.EQU RXC=0x7
	.EQU USR=0xB
	.EQU UDR=0xC
	.EQU SPSR=0xE
	.EQU SPDR=0xF
	.EQU EERE=0x0
	.EQU EEWE=0x1
	.EQU EEMWE=0x2
	.EQU EECR=0x1C
	.EQU EEDR=0x1D
	.EQU EEARL=0x1E
	.EQU EEARH=0x1F
	.EQU WDTCR=0x21
	.EQU MCUCR=0x35
	.EQU SPL=0x3D
	.EQU SPH=0x3E
	.EQU SREG=0x3F
	.EQU XMCRA=0x6D
	.EQU XMCRB=0x6C

	.DEF R0X0=R0
	.DEF R0X1=R1
	.DEF R0X2=R2
	.DEF R0X3=R3
	.DEF R0X4=R4
	.DEF R0X5=R5
	.DEF R0X6=R6
	.DEF R0X7=R7
	.DEF R0X8=R8
	.DEF R0X9=R9
	.DEF R0XA=R10
	.DEF R0XB=R11
	.DEF R0XC=R12
	.DEF R0XD=R13
	.DEF R0XE=R14
	.DEF R0XF=R15
	.DEF R0X10=R16
	.DEF R0X11=R17
	.DEF R0X12=R18
	.DEF R0X13=R19
	.DEF R0X14=R20
	.DEF R0X15=R21
	.DEF R0X16=R22
	.DEF R0X17=R23
	.DEF R0X18=R24
	.DEF R0X19=R25
	.DEF R0X1A=R26
	.DEF R0X1B=R27
	.DEF R0X1C=R28
	.DEF R0X1D=R29
	.DEF R0X1E=R30
	.DEF R0X1F=R31

	.EQU __SRAM_START=0x0100
	.EQU __SRAM_END=0x10FF
	.EQU __DSTACK_SIZE=0x0400
	.EQU __HEAP_SIZE=0x0000
	.EQU __CLEAR_SRAM_SIZE=__SRAM_END-__SRAM_START+1

	.MACRO __CPD1N
	CPI  R30,LOW(@0)
	LDI  R26,HIGH(@0)
	CPC  R31,R26
	LDI  R26,BYTE3(@0)
	CPC  R22,R26
	LDI  R26,BYTE4(@0)
	CPC  R23,R26
	.ENDM

	.MACRO __CPD2N
	CPI  R26,LOW(@0)
	LDI  R30,HIGH(@0)
	CPC  R27,R30
	LDI  R30,BYTE3(@0)
	CPC  R24,R30
	LDI  R30,BYTE4(@0)
	CPC  R25,R30
	.ENDM

	.MACRO __CPWRR
	CP   R@0,R@2
	CPC  R@1,R@3
	.ENDM

	.MACRO __CPWRN
	CPI  R@0,LOW(@2)
	LDI  R30,HIGH(@2)
	CPC  R@1,R30
	.ENDM

	.MACRO __ADDB1MN
	SUBI R30,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDB2MN
	SUBI R26,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDW1MN
	SUBI R30,LOW(-@0-(@1))
	SBCI R31,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW2MN
	SUBI R26,LOW(-@0-(@1))
	SBCI R27,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	SBCI R22,BYTE3(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1N
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	SBCI R22,BYTE3(-@0)
	SBCI R23,BYTE4(-@0)
	.ENDM

	.MACRO __ADDD2N
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	SBCI R24,BYTE3(-@0)
	SBCI R25,BYTE4(-@0)
	.ENDM

	.MACRO __SUBD1N
	SUBI R30,LOW(@0)
	SBCI R31,HIGH(@0)
	SBCI R22,BYTE3(@0)
	SBCI R23,BYTE4(@0)
	.ENDM

	.MACRO __SUBD2N
	SUBI R26,LOW(@0)
	SBCI R27,HIGH(@0)
	SBCI R24,BYTE3(@0)
	SBCI R25,BYTE4(@0)
	.ENDM

	.MACRO __ANDBMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ANDWMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ANDI R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ANDD1N
	ANDI R30,LOW(@0)
	ANDI R31,HIGH(@0)
	ANDI R22,BYTE3(@0)
	ANDI R23,BYTE4(@0)
	.ENDM

	.MACRO __ANDD2N
	ANDI R26,LOW(@0)
	ANDI R27,HIGH(@0)
	ANDI R24,BYTE3(@0)
	ANDI R25,BYTE4(@0)
	.ENDM

	.MACRO __ORBMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ORWMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ORI  R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ORD1N
	ORI  R30,LOW(@0)
	ORI  R31,HIGH(@0)
	ORI  R22,BYTE3(@0)
	ORI  R23,BYTE4(@0)
	.ENDM

	.MACRO __ORD2N
	ORI  R26,LOW(@0)
	ORI  R27,HIGH(@0)
	ORI  R24,BYTE3(@0)
	ORI  R25,BYTE4(@0)
	.ENDM

	.MACRO __DELAY_USB
	LDI  R24,LOW(@0)
__DELAY_USB_LOOP:
	DEC  R24
	BRNE __DELAY_USB_LOOP
	.ENDM

	.MACRO __DELAY_USW
	LDI  R24,LOW(@0)
	LDI  R25,HIGH(@0)
__DELAY_USW_LOOP:
	SBIW R24,1
	BRNE __DELAY_USW_LOOP
	.ENDM

	.MACRO __GETD1S
	LDD  R30,Y+@0
	LDD  R31,Y+@0+1
	LDD  R22,Y+@0+2
	LDD  R23,Y+@0+3
	.ENDM

	.MACRO __GETD2S
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	LDD  R24,Y+@0+2
	LDD  R25,Y+@0+3
	.ENDM

	.MACRO __PUTD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R31
	STD  Y+@0+2,R22
	STD  Y+@0+3,R23
	.ENDM

	.MACRO __PUTD2S
	STD  Y+@0,R26
	STD  Y+@0+1,R27
	STD  Y+@0+2,R24
	STD  Y+@0+3,R25
	.ENDM

	.MACRO __PUTDZ2
	STD  Z+@0,R26
	STD  Z+@0+1,R27
	STD  Z+@0+2,R24
	STD  Z+@0+3,R25
	.ENDM

	.MACRO __CLRD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R30
	STD  Y+@0+2,R30
	STD  Y+@0+3,R30
	.ENDM

	.MACRO __POINTB1MN
	LDI  R30,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW1MN
	LDI  R30,LOW(@0+(@1))
	LDI  R31,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTD1M
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __POINTW1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	LDI  R22,BYTE3(2*@0+(@1))
	LDI  R23,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTB2MN
	LDI  R26,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW2MN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTBRM
	LDI  R@0,LOW(@1)
	.ENDM

	.MACRO __POINTWRM
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __POINTBRMN
	LDI  R@0,LOW(@1+(@2))
	.ENDM

	.MACRO __POINTWRMN
	LDI  R@0,LOW(@2+(@3))
	LDI  R@1,HIGH(@2+(@3))
	.ENDM

	.MACRO __POINTWRFN
	LDI  R@0,LOW(@2*2+(@3))
	LDI  R@1,HIGH(@2*2+(@3))
	.ENDM

	.MACRO __GETD1N
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __GETD2N
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __GETB1MN
	LDS  R30,@0+(@1)
	.ENDM

	.MACRO __GETB1HMN
	LDS  R31,@0+(@1)
	.ENDM

	.MACRO __GETW1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	.ENDM

	.MACRO __GETD1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	LDS  R22,@0+(@1)+2
	LDS  R23,@0+(@1)+3
	.ENDM

	.MACRO __GETBRMN
	LDS  R@0,@1+(@2)
	.ENDM

	.MACRO __GETWRMN
	LDS  R@0,@2+(@3)
	LDS  R@1,@2+(@3)+1
	.ENDM

	.MACRO __GETWRZ
	LDD  R@0,Z+@2
	LDD  R@1,Z+@2+1
	.ENDM

	.MACRO __GETD2Z
	LDD  R26,Z+@0
	LDD  R27,Z+@0+1
	LDD  R24,Z+@0+2
	LDD  R25,Z+@0+3
	.ENDM

	.MACRO __GETB2MN
	LDS  R26,@0+(@1)
	.ENDM

	.MACRO __GETW2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	.ENDM

	.MACRO __GETD2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	LDS  R24,@0+(@1)+2
	LDS  R25,@0+(@1)+3
	.ENDM

	.MACRO __PUTB1MN
	STS  @0+(@1),R30
	.ENDM

	.MACRO __PUTW1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	.ENDM

	.MACRO __PUTD1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	STS  @0+(@1)+2,R22
	STS  @0+(@1)+3,R23
	.ENDM

	.MACRO __PUTB1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRB
	.ENDM

	.MACRO __PUTW1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRW
	.ENDM

	.MACRO __PUTD1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRD
	.ENDM

	.MACRO __PUTBR0MN
	STS  @0+(@1),R0
	.ENDM

	.MACRO __PUTBMRN
	STS  @0+(@1),R@2
	.ENDM

	.MACRO __PUTWMRN
	STS  @0+(@1),R@2
	STS  @0+(@1)+1,R@3
	.ENDM

	.MACRO __PUTBZR
	STD  Z+@1,R@0
	.ENDM

	.MACRO __PUTWZR
	STD  Z+@2,R@0
	STD  Z+@2+1,R@1
	.ENDM

	.MACRO __GETW1R
	MOV  R30,R@0
	MOV  R31,R@1
	.ENDM

	.MACRO __GETW2R
	MOV  R26,R@0
	MOV  R27,R@1
	.ENDM

	.MACRO __GETWRN
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __PUTW1R
	MOV  R@0,R30
	MOV  R@1,R31
	.ENDM

	.MACRO __PUTW2R
	MOV  R@0,R26
	MOV  R@1,R27
	.ENDM

	.MACRO __ADDWRN
	SUBI R@0,LOW(-@2)
	SBCI R@1,HIGH(-@2)
	.ENDM

	.MACRO __ADDWRR
	ADD  R@0,R@2
	ADC  R@1,R@3
	.ENDM

	.MACRO __SUBWRN
	SUBI R@0,LOW(@2)
	SBCI R@1,HIGH(@2)
	.ENDM

	.MACRO __SUBWRR
	SUB  R@0,R@2
	SBC  R@1,R@3
	.ENDM

	.MACRO __ANDWRN
	ANDI R@0,LOW(@2)
	ANDI R@1,HIGH(@2)
	.ENDM

	.MACRO __ANDWRR
	AND  R@0,R@2
	AND  R@1,R@3
	.ENDM

	.MACRO __ORWRN
	ORI  R@0,LOW(@2)
	ORI  R@1,HIGH(@2)
	.ENDM

	.MACRO __ORWRR
	OR   R@0,R@2
	OR   R@1,R@3
	.ENDM

	.MACRO __EORWRR
	EOR  R@0,R@2
	EOR  R@1,R@3
	.ENDM

	.MACRO __GETWRS
	LDD  R@0,Y+@2
	LDD  R@1,Y+@2+1
	.ENDM

	.MACRO __PUTBSR
	STD  Y+@1,R@0
	.ENDM

	.MACRO __PUTWSR
	STD  Y+@2,R@0
	STD  Y+@2+1,R@1
	.ENDM

	.MACRO __MOVEWRR
	MOV  R@0,R@2
	MOV  R@1,R@3
	.ENDM

	.MACRO __INWR
	IN   R@0,@2
	IN   R@1,@2+1
	.ENDM

	.MACRO __OUTWR
	OUT  @2+1,R@1
	OUT  @2,R@0
	.ENDM

	.MACRO __CALL1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	ICALL
	.ENDM

	.MACRO __CALL1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	CALL __GETW1PF
	ICALL
	.ENDM

	.MACRO __CALL2EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMRDW
	ICALL
	.ENDM

	.MACRO __GETW1STACK
	IN   R26,SPL
	IN   R27,SPH
	ADIW R26,@0+1
	LD   R30,X+
	LD   R31,X
	.ENDM

	.MACRO __GETD1STACK
	IN   R26,SPL
	IN   R27,SPH
	ADIW R26,@0+1
	LD   R30,X+
	LD   R31,X+
	LD   R22,X
	.ENDM

	.MACRO __NBST
	BST  R@0,@1
	IN   R30,SREG
	LDI  R31,0x40
	EOR  R30,R31
	OUT  SREG,R30
	.ENDM


	.MACRO __PUTB1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RNS
	MOVW R26,R@0
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	CALL __PUTDP1
	.ENDM


	.MACRO __GETB1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R30,Z
	.ENDM

	.MACRO __GETB1HSX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	.ENDM

	.MACRO __GETW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z+
	LD   R23,Z
	MOVW R30,R0
	.ENDM

	.MACRO __GETB2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R26,X
	.ENDM

	.MACRO __GETW2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	.ENDM

	.MACRO __GETD2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R1,X+
	LD   R24,X+
	LD   R25,X
	MOVW R26,R0
	.ENDM

	.MACRO __GETBRSX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	LD   R@0,Z
	.ENDM

	.MACRO __GETWRSX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	LD   R@0,Z+
	LD   R@1,Z
	.ENDM

	.MACRO __GETBRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	LD   R@0,X
	.ENDM

	.MACRO __GETWRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	LD   R@0,X+
	LD   R@1,X
	.ENDM

	.MACRO __LSLW8SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	CLR  R30
	.ENDM

	.MACRO __PUTB1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __CLRW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __CLRD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R30
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __PUTB2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R26
	.ENDM

	.MACRO __PUTW2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z,R27
	.ENDM

	.MACRO __PUTD2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z+,R27
	ST   Z+,R24
	ST   Z,R25
	.ENDM

	.MACRO __PUTBSRX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	ST   Z,R@0
	.ENDM

	.MACRO __PUTWSRX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	ST   Z+,R@0
	ST   Z,R@1
	.ENDM

	.MACRO __PUTB1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __MULBRR
	MULS R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRRU
	MUL  R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRR0
	MULS R@0,R@1
	.ENDM

	.MACRO __MULBRRU0
	MUL  R@0,R@1
	.ENDM

	.MACRO __MULBNWRU
	LDI  R26,@2
	MUL  R26,R@0
	MOVW R30,R0
	MUL  R26,R@1
	ADD  R31,R0
	.ENDM

;NAME DEFINITIONS FOR GLOBAL VARIABLES ALLOCATED TO REGISTERS
	.DEF _i=R5
	.DEF __lcd_x=R4
	.DEF __lcd_y=R7
	.DEF __lcd_maxx=R6

	.CSEG
	.ORG 0x00

;START OF CODE MARKER
__START_OF_CODE:

;INTERRUPT VECTORS
	JMP  __RESET
	JMP  _ext_int0_isr
	JMP  0x00
	JMP  _ext_int2_isr
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  _timer0_comp_isr
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00

_0x0:
	.DB  0x2D,0x0,0x20,0x52,0x65,0x61,0x64,0x79
	.DB  0x2E,0x2E,0x2E,0x2E,0x2E,0x0
_0x2000003:
	.DB  0x80,0xC0

__GLOBAL_INI_TBL:
	.DW  0x02
	.DW  __base_y_G100
	.DW  _0x2000003*2

_0xFFFFFFFF:
	.DW  0

__RESET:
	CLI
	CLR  R30
	OUT  EECR,R30

;INTERRUPT VECTORS ARE PLACED
;AT THE START OF FLASH
	LDI  R31,1
	OUT  MCUCR,R31
	OUT  MCUCR,R30
	STS  XMCRB,R30

;DISABLE WATCHDOG
	LDI  R31,0x18
	OUT  WDTCR,R31
	OUT  WDTCR,R30

;CLEAR R2-R14
	LDI  R24,(14-2)+1
	LDI  R26,2
	CLR  R27
__CLEAR_REG:
	ST   X+,R30
	DEC  R24
	BRNE __CLEAR_REG

;CLEAR SRAM
	LDI  R24,LOW(__CLEAR_SRAM_SIZE)
	LDI  R25,HIGH(__CLEAR_SRAM_SIZE)
	LDI  R26,LOW(__SRAM_START)
	LDI  R27,HIGH(__SRAM_START)
__CLEAR_SRAM:
	ST   X+,R30
	SBIW R24,1
	BRNE __CLEAR_SRAM

;GLOBAL VARIABLES INITIALIZATION
	LDI  R30,LOW(__GLOBAL_INI_TBL*2)
	LDI  R31,HIGH(__GLOBAL_INI_TBL*2)
__GLOBAL_INI_NEXT:
	LPM  R24,Z+
	LPM  R25,Z+
	SBIW R24,0
	BREQ __GLOBAL_INI_END
	LPM  R26,Z+
	LPM  R27,Z+
	LPM  R0,Z+
	LPM  R1,Z+
	MOVW R22,R30
	MOVW R30,R0
__GLOBAL_INI_LOOP:
	LPM  R0,Z+
	ST   X+,R0
	SBIW R24,1
	BRNE __GLOBAL_INI_LOOP
	MOVW R30,R22
	RJMP __GLOBAL_INI_NEXT
__GLOBAL_INI_END:

;HARDWARE STACK POINTER INITIALIZATION
	LDI  R30,LOW(__SRAM_END-__HEAP_SIZE)
	OUT  SPL,R30
	LDI  R30,HIGH(__SRAM_END-__HEAP_SIZE)
	OUT  SPH,R30

;DATA STACK POINTER INITIALIZATION
	LDI  R28,LOW(__SRAM_START+__DSTACK_SIZE)
	LDI  R29,HIGH(__SRAM_START+__DSTACK_SIZE)

	JMP  _main

	.ESEG
	.ORG 0

	.DSEG
	.ORG 0x500

	.CSEG
;/*****************************************************
;Chip type               : ATmega64
;Program type            : Application
;AVR Core Clock frequency: 11.059200 MHz
;Memory model            : Small
;External RAM size       : 0
;Data Stack size         : 1024
;*****************************************************/
;#include <mega64.h>
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x20
	.EQU __sm_mask=0x1C
	.EQU __sm_powerdown=0x10
	.EQU __sm_powersave=0x18
	.EQU __sm_standby=0x14
	.EQU __sm_ext_standby=0x1C
	.EQU __sm_adc_noise_red=0x08
	.SET power_ctrl_reg=mcucr
	#endif
;#include <delay.h>
;// Alphanumeric LCD Module functions
;#include <alcd.h>
;void lcd_putnum (long int so,unsigned char x,unsigned char y)
; 0000 000E {

	.CSEG
_lcd_putnum:
; 0000 000F    long int a, b, c, d, e;
; 0000 0010    lcd_gotoxy (x, y) ;
	SBIW R28,20
;	so -> Y+22
;	x -> Y+21
;	y -> Y+20
;	a -> Y+16
;	b -> Y+12
;	c -> Y+8
;	d -> Y+4
;	e -> Y+0
	LDD  R30,Y+21
	ST   -Y,R30
	LDD  R30,Y+21
	ST   -Y,R30
	CALL _lcd_gotoxy
; 0000 0011    if (so<0) {lcd_putsf("-"); so=-so; }
	LDD  R26,Y+25
	TST  R26
	BRPL _0x3
	__POINTW1FN _0x0,0
	ST   -Y,R31
	ST   -Y,R30
	CALL _lcd_putsf
	__GETD1S 22
	CALL __ANEGD1
	__PUTD1S 22
; 0000 0012    a = so / 10000;
_0x3:
	CALL SUBOPT_0x0
	__GETD1N 0x2710
	CALL __DIVD21
	__PUTD1S 16
; 0000 0013    b = (so - 10000 * a) / 1000;
	CALL SUBOPT_0x1
	CALL __SUBD21
	__GETD1N 0x3E8
	CALL __DIVD21
	__PUTD1S 12
; 0000 0014    c = (so - 10000 * a - 1000 * b) / 100;
	CALL SUBOPT_0x1
	CALL SUBOPT_0x2
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	CALL SUBOPT_0x3
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __SUBD21
	__GETD1N 0x64
	CALL __DIVD21
	__PUTD1S 8
; 0000 0015    d = (so - 10000 * a - 1000 * b - 100 * c) / 10;
	CALL SUBOPT_0x1
	CALL SUBOPT_0x2
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	CALL SUBOPT_0x3
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL SUBOPT_0x2
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	CALL SUBOPT_0x4
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __SUBD21
	__GETD1N 0xA
	CALL __DIVD21
	__PUTD1S 4
; 0000 0016    e = so - 10000 * a - 1000 * b - 100 * c - 10 * d;
	CALL SUBOPT_0x1
	CALL SUBOPT_0x2
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	CALL SUBOPT_0x3
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL SUBOPT_0x2
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	CALL SUBOPT_0x4
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL SUBOPT_0x2
	PUSH R23
	PUSH R22
	PUSH R31
	PUSH R30
	__GETD1S 4
	__GETD2N 0xA
	CALL __MULD12
	POP  R26
	POP  R27
	POP  R24
	POP  R25
	CALL __SUBD21
	CALL __PUTD2S0
; 0000 0017    if(so>10000)  lcd_putchar (a + 48) ;
	CALL SUBOPT_0x0
	__CPD2N 0x2711
	BRLT _0x4
	LDD  R30,Y+16
	CALL SUBOPT_0x5
; 0000 0018    if(so>1000) lcd_putchar (b + 48) ;
_0x4:
	CALL SUBOPT_0x0
	__CPD2N 0x3E9
	BRLT _0x5
	LDD  R30,Y+12
	CALL SUBOPT_0x5
; 0000 0019    if(so>100) lcd_putchar (c + 48) ;
_0x5:
	CALL SUBOPT_0x0
	__CPD2N 0x65
	BRLT _0x6
	LDD  R30,Y+8
	CALL SUBOPT_0x5
; 0000 001A    if(so>10) lcd_putchar (d + 48) ;
_0x6:
	CALL SUBOPT_0x0
	__CPD2N 0xB
	BRLT _0x7
	LDD  R30,Y+4
	CALL SUBOPT_0x5
; 0000 001B    lcd_putchar (e + 48) ;
_0x7:
	LD   R30,Y
	CALL SUBOPT_0x5
; 0000 001C }
	ADIW R28,26
	RET
;
;// CHUONG TRINH DOC TAY GAME PS2
;#define DATA PINB.3 // dây 1 màu nâu (chan DI)
;#define CMD PORTB.2 // dây 2 màu cam (chan DO)
;#define CLK PORTB.1 // dây 7 xanh da tr?i (chan CLK)
;#define ATT PORTB.0 // dây 6 màu vàng (chan CS)
;#define DDRDATA DDRB.3
;#define DDRCMD DDRB.2
;#define DDRCLK DDRB.1
;#define DDRATT DDRB.0
;volatile unsigned char PES[6],analog;
;volatile unsigned char L1,R1,L2,R2,L,R,start,select,up,down,left,right,nut3,nut2,nut4,nut1;
;unsigned char access(unsigned char tbyte)
; 0000 002A {
_access:
; 0000 002B unsigned char rbyte=0;
; 0000 002C unsigned int j;
; 0000 002D CLK=1;
	CALL __SAVELOCR4
;	tbyte -> Y+4
;	rbyte -> R17
;	j -> R18,R19
	LDI  R17,0
	SBI  0x18,1
; 0000 002E for(j=0;j<8;j++)
	__GETWRN 18,19,0
_0xB:
	__CPWRN 18,19,8
	BRSH _0xC
; 0000 002F {
; 0000 0030 CMD=tbyte&0x01;
	LDD  R30,Y+4
	ANDI R30,LOW(0x1)
	BRNE _0xD
	CBI  0x18,2
	RJMP _0xE
_0xD:
	SBI  0x18,2
_0xE:
; 0000 0031 delay_us(100);
	CALL SUBOPT_0x6
; 0000 0032 CLK=0;
	CBI  0x18,1
; 0000 0033 delay_us(100);
	CALL SUBOPT_0x6
; 0000 0034 rbyte=(rbyte>>1)|(DATA<<7);
	MOV  R30,R17
	LDI  R31,0
	ASR  R31
	ROR  R30
	MOV  R0,R30
	LDI  R26,0
	SBIC 0x16,3
	LDI  R26,1
	MOV  R30,R26
	ROR  R30
	LDI  R30,0
	ROR  R30
	OR   R30,R0
	MOV  R17,R30
; 0000 0035 CLK=1;
	SBI  0x18,1
; 0000 0036 tbyte=tbyte>>1;
	LDD  R30,Y+4
	LDI  R31,0
	ASR  R31
	ROR  R30
	STD  Y+4,R30
; 0000 0037 }
	__ADDWRN 18,19,1
	RJMP _0xB
_0xC:
; 0000 0038 delay_us(100);
	CALL SUBOPT_0x6
; 0000 0039 return rbyte;
	MOV  R30,R17
; 0000 003A CLK=1;
; 0000 003B }
_0x2020003:
	CALL __LOADLOCR4
	ADIW R28,5
	RET
;void DOCPS2(void)
; 0000 003D {
_DOCPS2:
; 0000 003E DDRDATA=0;
	CBI  0x17,3
; 0000 003F DDRCMD=DDRCLK=DDRATT=1;
	SBI  0x17,0
	SBI  0x17,1
	SBI  0x17,2
; 0000 0040 ATT=1;
	SBI  0x18,0
; 0000 0041 PES[2]=PES[3]=PES[4]=PES[5]=128;
	LDI  R30,LOW(128)
	__PUTB1MN _PES,5
	__PUTB1MN _PES,4
	__PUTB1MN _PES,3
	__PUTB1MN _PES,2
; 0000 0042 analog=128;
	STS  _analog,R30
; 0000 0043 ATT=0;
	CBI  0x18,0
; 0000 0044 access(0x01);
	LDI  R30,LOW(1)
	ST   -Y,R30
	RCALL _access
; 0000 0045 analog=access(0x42);
	LDI  R30,LOW(66)
	ST   -Y,R30
	RCALL _access
	STS  _analog,R30
; 0000 0046 access(0);
	CALL SUBOPT_0x7
; 0000 0047 PES[0]=access(0);
	CALL SUBOPT_0x7
	STS  _PES,R30
; 0000 0048 PES[1]=access(0);
	CALL SUBOPT_0x7
	__PUTB1MN _PES,1
; 0000 0049 if(analog==0x73||0x23||0X53)
	LDS  R26,_analog
	CPI  R26,LOW(0x73)
	BREQ _0x22
	LDI  R30,LOW(35)
	CPI  R30,0
	BRNE _0x22
	LDI  R30,LOW(83)
	CPI  R30,0
	BREQ _0x21
_0x22:
; 0000 004A {
; 0000 004B PES[2]=access(0);
	CALL SUBOPT_0x7
	__PUTB1MN _PES,2
; 0000 004C PES[3]=access(0);
	CALL SUBOPT_0x7
	__PUTB1MN _PES,3
; 0000 004D PES[4]=access(0);
	CALL SUBOPT_0x7
	__PUTB1MN _PES,4
; 0000 004E PES[5]=access(0);
	CALL SUBOPT_0x7
	__PUTB1MN _PES,5
; 0000 004F }
; 0000 0050 if(analog==0x12)
_0x21:
	LDS  R26,_analog
	CPI  R26,LOW(0x12)
	BRNE _0x24
; 0000 0051 {
; 0000 0052 PES[2]=access(0);
	CALL SUBOPT_0x7
	__PUTB1MN _PES,2
; 0000 0053 PES[3]=access(0);
	CALL SUBOPT_0x7
	__PUTB1MN _PES,3
; 0000 0054 }
; 0000 0055 ATT=1;
_0x24:
	SBI  0x18,0
; 0000 0056 
; 0000 0057 select = PES[0]&0x01;
	LDS  R30,_PES
	ANDI R30,LOW(0x1)
	STS  _select,R30
; 0000 0058 L = (PES[0]&0x02)/2;
	LDS  R30,_PES
	CALL SUBOPT_0x8
	STS  _L,R30
; 0000 0059 R = (PES[0]&0x04)/4;
	LDS  R30,_PES
	CALL SUBOPT_0x9
	STS  _R,R30
; 0000 005A start = (PES[0]&0x08)/8;
	LDS  R30,_PES
	CALL SUBOPT_0xA
	STS  _start,R30
; 0000 005B 
; 0000 005C up = (PES[0]&0x10)/16;
	LDS  R30,_PES
	CALL SUBOPT_0xB
	STS  _up,R30
; 0000 005D right = (PES[0]&0x20)/32;
	LDS  R30,_PES
	CALL SUBOPT_0xC
	STS  _right,R30
; 0000 005E down = (PES[0]&0x40)/64;
	LDS  R30,_PES
	CALL SUBOPT_0xD
	STS  _down,R30
; 0000 005F left = (PES[0]&0x80)/128;
	LDS  R30,_PES
	CALL SUBOPT_0xE
	STS  _left,R30
; 0000 0060 
; 0000 0061 L2 = (PES[1]&0x01);
	__GETB1MN _PES,1
	ANDI R30,LOW(0x1)
	STS  _L2,R30
; 0000 0062 R2 = (PES[1]&0x02)/2;
	__GETB1MN _PES,1
	CALL SUBOPT_0x8
	STS  _R2,R30
; 0000 0063 L1 = (PES[1]&0x04)/4;
	__GETB1MN _PES,1
	CALL SUBOPT_0x9
	STS  _L1,R30
; 0000 0064 R1 = (PES[1]&0x08)/8;
	__GETB1MN _PES,1
	CALL SUBOPT_0xA
	STS  _R1,R30
; 0000 0065 
; 0000 0066 nut1 = (PES[1]&0x10)/16;
	__GETB1MN _PES,1
	CALL SUBOPT_0xB
	STS  _nut1,R30
; 0000 0067 nut2 = (PES[1]&0x20)/32;
	__GETB1MN _PES,1
	CALL SUBOPT_0xC
	STS  _nut2,R30
; 0000 0068 nut3 = (PES[1]&0x40)/64;
	__GETB1MN _PES,1
	CALL SUBOPT_0xD
	STS  _nut3,R30
; 0000 0069 nut4 = (PES[1]&0x80)/128;
	__GETB1MN _PES,1
	CALL SUBOPT_0xE
	STS  _nut4,R30
; 0000 006A }
	RET
;
;// External Interrupt 0 service routine
;#define ddrkenha1 DDRD.0=0
;#define ddrkenhb1 DDRD.1=0
;#define kenhb1 PIND.1
;volatile long int ENDATA1=0;
;interrupt [EXT_INT0] void ext_int0_isr(void)
; 0000 0072 {
_ext_int0_isr:
	CALL SUBOPT_0xF
; 0000 0073 // Place your code here
; 0000 0074 if (kenhb1==1) {ENDATA1++;} else {ENDATA1--;}
	SBIS 0x10,1
	RJMP _0x27
	LDI  R26,LOW(_ENDATA1)
	LDI  R27,HIGH(_ENDATA1)
	CALL SUBOPT_0x10
	RJMP _0x28
_0x27:
	LDI  R26,LOW(_ENDATA1)
	LDI  R27,HIGH(_ENDATA1)
	CALL SUBOPT_0x11
_0x28:
; 0000 0075 }
	RJMP _0x14C
;
;// External Interrupt 2 service routine
;#define ddrkenha2 DDRD.2=0
;#define ddrkenhb2 DDRD.3=0
;#define kenhb2 PIND.3
;volatile long int ENDATA2=0;
;interrupt [EXT_INT2] void ext_int2_isr(void)
; 0000 007D {
_ext_int2_isr:
	CALL SUBOPT_0xF
; 0000 007E // Place your code here
; 0000 007F if (kenhb2==1) {ENDATA2++;} else {ENDATA2--;}
	SBIS 0x10,3
	RJMP _0x29
	LDI  R26,LOW(_ENDATA2)
	LDI  R27,HIGH(_ENDATA2)
	CALL SUBOPT_0x10
	RJMP _0x2A
_0x29:
	LDI  R26,LOW(_ENDATA2)
	LDI  R27,HIGH(_ENDATA2)
	CALL SUBOPT_0x11
_0x2A:
; 0000 0080 }
_0x14C:
	LD   R30,Y+
	OUT  SREG,R30
	LD   R31,Y+
	LD   R30,Y+
	LD   R27,Y+
	LD   R26,Y+
	LD   R23,Y+
	LD   R22,Y+
	RETI
;
;// CHUONG TRINH DIEU KHIEN DONG CO 1
;#define DDRBRA1 DDRE.6
;#define DDRDIR1 DDRB.4
;#define DDRPWMDC1 DDRB.5
;#define BRA1 PORTE.6
;#define DIR1 PORTB.4
;#define PWMDC1 OCR1A
;void DC1THUAN(long int xung)
; 0000 008A {
_DC1THUAN:
; 0000 008B DDRBRA1=1;
;	xung -> Y+0
	SBI  0x2,6
; 0000 008C DDRDIR1=1;
	SBI  0x17,4
; 0000 008D DDRPWMDC1=1;
	SBI  0x17,5
; 0000 008E BRA1=0;
	CBI  0x3,6
; 0000 008F DIR1=0;
	CBI  0x18,4
; 0000 0090 PWMDC1=xung;
	LD   R30,Y
	LDD  R31,Y+1
	OUT  0x2A+1,R31
	OUT  0x2A,R30
; 0000 0091 }
	RJMP _0x2020002
;void DC1NGUOC(long int xung)
; 0000 0093 {
_DC1NGUOC:
; 0000 0094 DDRBRA1=1;
;	xung -> Y+0
	SBI  0x2,6
; 0000 0095 DDRDIR1=1;
	SBI  0x17,4
; 0000 0096 DDRPWMDC1=1;
	SBI  0x17,5
; 0000 0097 BRA1=0;
	CBI  0x3,6
; 0000 0098 DIR1=1;
	SBI  0x18,4
; 0000 0099 PWMDC1=xung;
	LD   R30,Y
	LDD  R31,Y+1
	OUT  0x2A+1,R31
	OUT  0x2A,R30
; 0000 009A }
	RJMP _0x2020002
;void RESDC1()
; 0000 009C {
_RESDC1:
; 0000 009D DDRBRA1=1;
	SBI  0x2,6
; 0000 009E DDRDIR1=1;
	SBI  0x17,4
; 0000 009F DDRPWMDC1=1;
	SBI  0x17,5
; 0000 00A0 BRA1=1;
	SBI  0x3,6
; 0000 00A1 DIR1=0;
	CBI  0x18,4
; 0000 00A2 PWMDC1=0;
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	OUT  0x2A+1,R31
	OUT  0x2A,R30
; 0000 00A3 }
	RET
;
;// CHUONG TRINH DIEU KHIEN DONG CO 2
;#define DDRBRA2 DDRE.7
;#define DDRDIR2 DDRB.7
;#define DDRPWMDC2 DDRB.6
;#define BRA2 PORTE.7
;#define DIR2 PORTB.7
;#define PWMDC2 OCR1B
;void DC2THUAN(long int xung)
; 0000 00AD {
_DC2THUAN:
; 0000 00AE DDRBRA2=1;
;	xung -> Y+0
	SBI  0x2,7
; 0000 00AF DDRDIR2=1;
	SBI  0x17,7
; 0000 00B0 DDRPWMDC2=1;
	SBI  0x17,6
; 0000 00B1 BRA2=0;
	CBI  0x3,7
; 0000 00B2 DIR2=0;
	CBI  0x18,7
; 0000 00B3 PWMDC2=xung;
	LD   R30,Y
	LDD  R31,Y+1
	OUT  0x28+1,R31
	OUT  0x28,R30
; 0000 00B4 }
	RJMP _0x2020002
;void DC2NGUOC(long int xung)
; 0000 00B6 {
_DC2NGUOC:
; 0000 00B7 DDRBRA2=1;
;	xung -> Y+0
	SBI  0x2,7
; 0000 00B8 DDRDIR2=1;
	SBI  0x17,7
; 0000 00B9 DDRPWMDC2=1;
	SBI  0x17,6
; 0000 00BA BRA2=0;
	CBI  0x3,7
; 0000 00BB DIR2=1;
	SBI  0x18,7
; 0000 00BC PWMDC2=xung;
	LD   R30,Y
	LDD  R31,Y+1
	OUT  0x28+1,R31
	OUT  0x28,R30
; 0000 00BD }
	RJMP _0x2020002
;void RESDC2()
; 0000 00BF {
_RESDC2:
; 0000 00C0 DDRBRA2=1;
	SBI  0x2,7
; 0000 00C1 DDRDIR2=1;
	SBI  0x17,7
; 0000 00C2 DDRPWMDC2=1;
	SBI  0x17,6
; 0000 00C3 BRA2=1;
	SBI  0x3,7
; 0000 00C4 DIR2=0;
	CBI  0x18,7
; 0000 00C5 PWMDC2=0;
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	OUT  0x28+1,R31
	OUT  0x28,R30
; 0000 00C6 }
	RET
;
;//PID DONG CO 1 //////////////////
;volatile long int ERR1=0, REALVT1=0;
;void PIDDC1(volatile long int SETVT1)
; 0000 00CB      {
_PIDDC1:
; 0000 00CC      REALVT1=ENDATA1;
;	SETVT1 -> Y+0
	CALL SUBOPT_0x12
	STS  _REALVT1,R30
	STS  _REALVT1+1,R31
	STS  _REALVT1+2,R22
	STS  _REALVT1+3,R23
; 0000 00CD      if (REALVT1 < SETVT1)
	CALL SUBOPT_0x13
	CALL SUBOPT_0x14
	CALL __CPD21
	BRGE _0x67
; 0000 00CE           {
; 0000 00CF           ERR1=SETVT1-REALVT1;
	CALL SUBOPT_0x14
	CALL SUBOPT_0x13
	CALL SUBOPT_0x15
; 0000 00D0           if (ERR1>600) {DC1THUAN(600);} else {DC1THUAN(2*ERR1+200);}
	BRLT _0x68
	CALL SUBOPT_0x16
	RJMP _0x148
_0x68:
	CALL SUBOPT_0x17
_0x148:
	CALL __PUTPARD1
	RCALL _DC1THUAN
; 0000 00D1           }
; 0000 00D2      if (REALVT1 > SETVT1)
_0x67:
	CALL SUBOPT_0x18
	BRGE _0x6A
; 0000 00D3           {
; 0000 00D4           ERR1=REALVT1-SETVT1;
	CALL __GETD2S0
	LDS  R30,_REALVT1
	LDS  R31,_REALVT1+1
	LDS  R22,_REALVT1+2
	LDS  R23,_REALVT1+3
	CALL SUBOPT_0x15
; 0000 00D5           if (ERR1>600) {DC1NGUOC(600);} else {DC1NGUOC(2*ERR1+200);}
	BRLT _0x6B
	CALL SUBOPT_0x16
	RJMP _0x149
_0x6B:
	CALL SUBOPT_0x17
_0x149:
	CALL __PUTPARD1
	RCALL _DC1NGUOC
; 0000 00D6           }
; 0000 00D7      if (REALVT1 == SETVT1) { RESDC1();}
_0x6A:
	CALL SUBOPT_0x18
	BRNE _0x6D
	RCALL _RESDC1
; 0000 00D8      }
_0x6D:
	RJMP _0x2020002
;
;//PID DONG CO 2
;volatile long int ERR2=0, REALVT2=0;
;void PIDDC2(volatile long int SETVT2)
; 0000 00DD      {
_PIDDC2:
; 0000 00DE      REALVT2=ENDATA2;
;	SETVT2 -> Y+0
	CALL SUBOPT_0x19
	STS  _REALVT2,R30
	STS  _REALVT2+1,R31
	STS  _REALVT2+2,R22
	STS  _REALVT2+3,R23
; 0000 00DF      if (REALVT2 < SETVT2)
	CALL SUBOPT_0x1A
	CALL __CPD21
	BRGE _0x6E
; 0000 00E0           {
; 0000 00E1           ERR2=SETVT2-REALVT2;
	LDS  R26,_REALVT2
	LDS  R27,_REALVT2+1
	LDS  R24,_REALVT2+2
	LDS  R25,_REALVT2+3
	CALL SUBOPT_0x13
	CALL SUBOPT_0x1B
; 0000 00E2           if (ERR2>600) {DC2THUAN(600);} else {DC2THUAN(2*ERR2+200);}
	LDS  R26,_ERR2
	LDS  R27,_ERR2+1
	LDS  R24,_ERR2+2
	LDS  R25,_ERR2+3
	CALL SUBOPT_0x1C
	BRLT _0x6F
	CALL SUBOPT_0x16
	RJMP _0x14A
_0x6F:
	CALL SUBOPT_0x1D
_0x14A:
	CALL __PUTPARD1
	RCALL _DC2THUAN
; 0000 00E3           }
; 0000 00E4      if (REALVT2 > SETVT2)
_0x6E:
	CALL SUBOPT_0x1A
	CALL __CPD12
	BRGE _0x71
; 0000 00E5           {
; 0000 00E6           ERR2=REALVT2-SETVT2;
	CALL __GETD2S0
	LDS  R30,_REALVT2
	LDS  R31,_REALVT2+1
	LDS  R22,_REALVT2+2
	LDS  R23,_REALVT2+3
	CALL SUBOPT_0x1B
; 0000 00E7           if (ERR1>600) {DC2NGUOC(600);} else {DC2NGUOC(2*ERR2+200);}
	LDS  R26,_ERR1
	LDS  R27,_ERR1+1
	LDS  R24,_ERR1+2
	LDS  R25,_ERR1+3
	CALL SUBOPT_0x1C
	BRLT _0x72
	CALL SUBOPT_0x16
	RJMP _0x14B
_0x72:
	CALL SUBOPT_0x1D
_0x14B:
	CALL __PUTPARD1
	RCALL _DC2NGUOC
; 0000 00E8           }
; 0000 00E9      if (REALVT2 == SETVT2) { RESDC2();}
_0x71:
	CALL SUBOPT_0x1A
	CALL __CPD12
	BRNE _0x74
	RCALL _RESDC2
; 0000 00EA      }
_0x74:
_0x2020002:
	ADIW R28,4
	RET
;
;// NGAT TIMER0 DE PID
;volatile long int SETVT1=0, SETVT2=0;
;interrupt [TIM0_COMP] void timer0_comp_isr(void)
; 0000 00EF {
_timer0_comp_isr:
	ST   -Y,R0
	ST   -Y,R1
	ST   -Y,R15
	ST   -Y,R22
	ST   -Y,R23
	ST   -Y,R24
	ST   -Y,R25
	ST   -Y,R26
	ST   -Y,R27
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
; 0000 00F0 #asm("cli");
	cli
; 0000 00F1 PIDDC1(SETVT1);
	CALL SUBOPT_0x1E
	CALL __PUTPARD1
	RCALL _PIDDC1
; 0000 00F2 PIDDC2(SETVT2);
	CALL SUBOPT_0x1F
	CALL __PUTPARD1
	RCALL _PIDDC2
; 0000 00F3 #asm("sei");
	sei
; 0000 00F4 }
	LD   R30,Y+
	OUT  SREG,R30
	LD   R31,Y+
	LD   R30,Y+
	LD   R27,Y+
	LD   R26,Y+
	LD   R25,Y+
	LD   R24,Y+
	LD   R23,Y+
	LD   R22,Y+
	LD   R15,Y+
	LD   R1,Y+
	LD   R0,Y+
	RETI
;
;// CHUONG TRINH BEEP LOA
;void BEEP()
; 0000 00F8      {
_BEEP:
; 0000 00F9      DDRC.7=1;
	SBI  0x14,7
; 0000 00FA      PORTC.7=0;
	CBI  0x15,7
; 0000 00FB      delay_ms(30);
	LDI  R30,LOW(30)
	LDI  R31,HIGH(30)
	CALL SUBOPT_0x20
; 0000 00FC      PORTC.7=1;
	SBI  0x15,7
; 0000 00FD      delay_ms(70);
	LDI  R30,LOW(70)
	LDI  R31,HIGH(70)
	CALL SUBOPT_0x20
; 0000 00FE      }
	RET
;
;// CHUONG TRINH CHINH
;char i;
;#define DDRVAN_T1 DDRA.0
;#define VAN_T1 PORTA.0
;#define DDRVAN_T2 DDRA.1
;#define VAN_T2 PORTA.1
;
;#define DDRVAN_G1 DDRA.2
;#define VAN_G1 PORTA.2
;#define DDRVAN_G2 DDRA.3
;#define VAN_G2 PORTA.3
;
;#define DDRVAN_L DDRA.4
;#define VAN_L PORTA.4
;#define DDRVAN_D DDRA.5
;#define VAN_D PORTA.5
;
;#define DDRCTHT1 DDRD.5
;#define CTHT1 PIND.5
;#define DDRCTHT2 DDRD.7
;#define CTHT2 PIND.7
;#define DDRTAY1 DDRD.4
;#define TAY1 PIND.4
;#define DDRTAY2 DDRD.6
;#define TAY2 PIND.6
;
;void main(void)
; 0000 011B {
_main:
; 0000 011C DDRA=0xff;
	LDI  R30,LOW(255)
	OUT  0x1A,R30
; 0000 011D PORTA=0xff;
	OUT  0x1B,R30
; 0000 011E DDRC=0xff;
	OUT  0x14,R30
; 0000 011F PORTC=0xff;
	OUT  0x15,R30
; 0000 0120 DDRD=0x00;
	LDI  R30,LOW(0)
	OUT  0x11,R30
; 0000 0121 PORTD=0xff;
	LDI  R30,LOW(255)
	OUT  0x12,R30
; 0000 0122 // Timer/Counter 0 initialization
; 0000 0123 // Clock source: System Clock
; 0000 0124 // Clock value: 43.200 kHz   0.023 MS
; 0000 0125 // Mode: Normal top=0xFF
; 0000 0126 // OC0 output: Disconnected
; 0000 0127 ASSR=0x00;
	LDI  R30,LOW(0)
	OUT  0x30,R30
; 0000 0128 TCCR0=0x06;
	LDI  R30,LOW(6)
	OUT  0x33,R30
; 0000 0129 TCNT0=0x00;
	LDI  R30,LOW(0)
	OUT  0x32,R30
; 0000 012A OCR0=0x64;
	LDI  R30,LOW(100)
	OUT  0x31,R30
; 0000 012B 
; 0000 012C // Timer/Counter 1 initialization
; 0000 012D // Clock source: System Clock
; 0000 012E // Clock value: 11059.200 kHz
; 0000 012F // Mode: Fast PWM top=ICR1
; 0000 0130 // OC1A output: Non-Inv.
; 0000 0131 // OC1B output: Non-Inv.
; 0000 0132 // OC1C output: Discon.
; 0000 0133 // Noise Canceler: Off
; 0000 0134 // Input Capture on Falling Edge
; 0000 0135 // Timer1 Overflow Interrupt: Off
; 0000 0136 // Input Capture Interrupt: Off
; 0000 0137 // Compare A Match Interrupt: Off
; 0000 0138 // Compare B Match Interrupt: Off
; 0000 0139 // Compare C Match Interrupt: Off
; 0000 013A TCCR1A=0xA2;
	LDI  R30,LOW(162)
	OUT  0x2F,R30
; 0000 013B TCCR1B=0x19;
	LDI  R30,LOW(25)
	OUT  0x2E,R30
; 0000 013C TCNT1H=0x00;
	LDI  R30,LOW(0)
	OUT  0x2D,R30
; 0000 013D TCNT1L=0x00;
	OUT  0x2C,R30
; 0000 013E ICR1H=0x03;
	LDI  R30,LOW(3)
	OUT  0x27,R30
; 0000 013F ICR1L=0xe8;
	LDI  R30,LOW(232)
	OUT  0x26,R30
; 0000 0140 OCR1AH=0x00;
	LDI  R30,LOW(0)
	OUT  0x2B,R30
; 0000 0141 OCR1AL=0x00;
	OUT  0x2A,R30
; 0000 0142 OCR1BH=0x00;
	OUT  0x29,R30
; 0000 0143 OCR1BL=0x00;
	OUT  0x28,R30
; 0000 0144 OCR1CH=0x00;
	STS  121,R30
; 0000 0145 OCR1CL=0x00;
	STS  120,R30
; 0000 0146 
; 0000 0147 // Timer/Counter 2 initialization
; 0000 0148 // Clock source: System Clock
; 0000 0149 // Clock value: Timer2 Stopped
; 0000 014A // Mode: Normal top=0xFF
; 0000 014B // OC2 output: Disconnected
; 0000 014C TCCR2=0x00;
	OUT  0x25,R30
; 0000 014D TCNT2=0x00;
	OUT  0x24,R30
; 0000 014E OCR2=0x00;
	OUT  0x23,R30
; 0000 014F 
; 0000 0150 // Timer/Counter 3 initialization
; 0000 0151 // Clock source: System Clock
; 0000 0152 // Clock value: Timer3 Stopped
; 0000 0153 // Mode: Normal top=0xFFFF
; 0000 0154 // OC3A output: Discon.
; 0000 0155 // OC3B output: Discon.
; 0000 0156 // OC3C output: Discon.
; 0000 0157 // Noise Canceler: Off
; 0000 0158 // Input Capture on Falling Edge
; 0000 0159 // Timer3 Overflow Interrupt: Off
; 0000 015A // Input Capture Interrupt: Off
; 0000 015B // Compare A Match Interrupt: Off
; 0000 015C // Compare B Match Interrupt: Off
; 0000 015D // Compare C Match Interrupt: Off
; 0000 015E TCCR3A=0x00;
	STS  139,R30
; 0000 015F TCCR3B=0x00;
	STS  138,R30
; 0000 0160 TCNT3H=0x00;
	STS  137,R30
; 0000 0161 TCNT3L=0x00;
	STS  136,R30
; 0000 0162 ICR3H=0x00;
	STS  129,R30
; 0000 0163 ICR3L=0x00;
	STS  128,R30
; 0000 0164 OCR3AH=0x00;
	STS  135,R30
; 0000 0165 OCR3AL=0x00;
	STS  134,R30
; 0000 0166 OCR3BH=0x00;
	STS  133,R30
; 0000 0167 OCR3BL=0x00;
	STS  132,R30
; 0000 0168 OCR3CH=0x00;
	STS  131,R30
; 0000 0169 OCR3CL=0x00;
	STS  130,R30
; 0000 016A 
; 0000 016B // External Interrupt(s) initialization
; 0000 016C // INT0: On
; 0000 016D // INT0 Mode: Falling Edge
; 0000 016E // INT1: Off
; 0000 016F // INT2: On
; 0000 0170 // INT2 Mode: Falling Edge
; 0000 0171 // INT3: Off
; 0000 0172 // INT4: Off
; 0000 0173 // INT5: Off
; 0000 0174 // INT6: Off
; 0000 0175 // INT7: Off
; 0000 0176 EICRA=0x22;
	LDI  R30,LOW(34)
	STS  106,R30
; 0000 0177 EICRB=0x00;
	LDI  R30,LOW(0)
	OUT  0x3A,R30
; 0000 0178 EIMSK=0x05;
	LDI  R30,LOW(5)
	OUT  0x39,R30
; 0000 0179 EIFR=0x05;
	OUT  0x38,R30
; 0000 017A 
; 0000 017B // Timer(s)/Counter(s) Interrupt(s) initialization
; 0000 017C TIMSK=0x00;
	CALL SUBOPT_0x21
; 0000 017D ETIMSK=0x00;
; 0000 017E 
; 0000 017F // Timer(s)/Counter(s) Interrupt(s) initialization
; 0000 0180 //TIMSK=0x02; //////////CHO PHEP NGAT TIMER0 COMPARE MATH
; 0000 0181 //ETIMSK=0x00;
; 0000 0182 
; 0000 0183 // USART0 initialization
; 0000 0184 // USART0 disabled
; 0000 0185 UCSR0B=0x00;
	LDI  R30,LOW(0)
	OUT  0xA,R30
; 0000 0186 
; 0000 0187 // USART1 initialization
; 0000 0188 // USART1 disabled
; 0000 0189 UCSR1B=0x00;
	STS  154,R30
; 0000 018A 
; 0000 018B // Analog Comparator initialization
; 0000 018C // Analog Comparator: Off
; 0000 018D // Analog Comparator Input Capture by Timer/Counter 1: Off
; 0000 018E ACSR=0x80;
	LDI  R30,LOW(128)
	OUT  0x8,R30
; 0000 018F SFIOR=0x00;
	LDI  R30,LOW(0)
	OUT  0x20,R30
; 0000 0190 
; 0000 0191 // ADC initialization
; 0000 0192 // ADC disabled
; 0000 0193 ADCSRA=0x00;
	OUT  0x6,R30
; 0000 0194 
; 0000 0195 // SPI initialization
; 0000 0196 // SPI disabled
; 0000 0197 SPCR=0x00;
	OUT  0xD,R30
; 0000 0198 
; 0000 0199 // TWI initialization
; 0000 019A // TWI disabled
; 0000 019B TWCR=0x00;
	STS  116,R30
; 0000 019C 
; 0000 019D // Alphanumeric LCD initialization
; 0000 019E // Connections specified in the
; 0000 019F // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
; 0000 01A0 // RS - PORTC Bit 0
; 0000 01A1 // RD - PORTC Bit 1
; 0000 01A2 // EN - PORTC Bit 2
; 0000 01A3 // D4 - PORTC Bit 3
; 0000 01A4 // D5 - PORTC Bit 4
; 0000 01A5 // D6 - PORTC Bit 5
; 0000 01A6 // D7 - PORTC Bit 6
; 0000 01A7 // Characters/line: 16
; 0000 01A8 lcd_init(16);
	LDI  R30,LOW(16)
	ST   -Y,R30
	CALL _lcd_init
; 0000 01A9 lcd_putsf(" Ready.....");
	__POINTW1FN _0x0,2
	ST   -Y,R31
	ST   -Y,R30
	CALL _lcd_putsf
; 0000 01AA for (i=0; i<6; i++) {BEEP(); }
	CLR  R5
_0x7C:
	LDI  R30,LOW(6)
	CP   R5,R30
	BRSH _0x7D
	RCALL _BEEP
	INC  R5
	RJMP _0x7C
_0x7D:
; 0000 01AB lcd_clear();
	CALL _lcd_clear
; 0000 01AC 
; 0000 01AD #asm("sei");
	sei
; 0000 01AE while (1)
; 0000 01AF      {
; 0000 01B0      nut1=1;
	LDI  R30,LOW(1)
	STS  _nut1,R30
; 0000 01B1      /*
; 0000 01B2      while (nut1==1) {DOCPS2();if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100); lcd_clear();}
; 0000 01B3           BEEP();
; 0000 01B4           nut1=1;
; 0000 01B5           VAN_G1=0;
; 0000 01B6           VAN_G2=0;
; 0000 01B7           delay_ms(500);
; 0000 01B8           DDRCTHT1=0; CTHT1=1;
; 0000 01B9           while (CTHT1==1) {DC1THUAN(400); lcd_putnum(ENDATA1,0,0); }
; 0000 01BA           RESDC1();
; 0000 01BB           for (i=0; i<3; i++) {BEEP(); }
; 0000 01BC           while (CTHT2==1) {DC2THUAN(600); lcd_putnum(ENDATA2,0,0); };
; 0000 01BD           RESDC2();
; 0000 01BE           for (i=0; i<3; i++) {BEEP(); }
; 0000 01BF           ENDATA1=0;
; 0000 01C0           ENDATA2=0;
; 0000 01C1      ////////////////////////////////RES 2 DC XONG ///////////////////
; 0000 01C2      while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
; 0000 01C3           BEEP();
; 0000 01C4           nut1=1;
; 0000 01C5           ENDATA1=0;
; 0000 01C6           ENDATA2=0;
; 0000 01C7           delay_ms(1000);
; 0000 01C8           TIMSK=0x02; ///////TIMER0 COMPARE MATH PID
; 0000 01C9           ETIMSK=0x00;
; 0000 01CA           SETVT1=-195;
; 0000 01CB           SETVT2=-195;
; 0000 01CC 
; 0000 01CD      while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
; 0000 01CE           BEEP();
; 0000 01CF           nut1=1;
; 0000 01D0           TIMSK=0x00; ///////TAT TIMER0 COMPARE MATH PID
; 0000 01D1           ETIMSK=0x00;
; 0000 01D2           VAN_G1=1;
; 0000 01D3           VAN_G2=1;
; 0000 01D4       */
; 0000 01D5 
; 0000 01D6      while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
_0x81:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0x83
	CALL SUBOPT_0x22
	BRNE _0x84
	CBI  0x1B,1
	CBI  0x1B,0
_0x84:
	CALL SUBOPT_0x23
	RJMP _0x81
_0x83:
; 0000 01D7           BEEP();
	CALL SUBOPT_0x24
; 0000 01D8           nut1=1;
; 0000 01D9           VAN_L=0;
	CALL SUBOPT_0x25
; 0000 01DA      //while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
; 0000 01DB           delay_ms(1500);
; 0000 01DC           BEEP();
	CALL SUBOPT_0x24
; 0000 01DD           nut1=1;
; 0000 01DE           VAN_L=1;
	CALL SUBOPT_0x26
; 0000 01DF      //while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
; 0000 01E0           delay_ms(1500);
; 0000 01E1           BEEP();
	CALL SUBOPT_0x24
; 0000 01E2           nut1=1;
; 0000 01E3           VAN_L=0;
	CALL SUBOPT_0x25
; 0000 01E4      //while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
; 0000 01E5           delay_ms(1500);
; 0000 01E6           BEEP();
	CALL SUBOPT_0x24
; 0000 01E7           nut1=1;
; 0000 01E8           VAN_L=1;
	CALL SUBOPT_0x26
; 0000 01E9      //while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
; 0000 01EA           delay_ms(1500);
; 0000 01EB           BEEP();
	CALL SUBOPT_0x24
; 0000 01EC           nut1=1;
; 0000 01ED           VAN_L=0;
	CALL SUBOPT_0x25
; 0000 01EE      //////
; 0000 01EF      //while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
; 0000 01F0           delay_ms(1500);
; 0000 01F1           BEEP();
	CALL SUBOPT_0x24
; 0000 01F2           nut1=1;
; 0000 01F3           VAN_L=1;
	CALL SUBOPT_0x26
; 0000 01F4      //while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
; 0000 01F5           delay_ms(1500);
; 0000 01F6           BEEP();
	CALL SUBOPT_0x24
; 0000 01F7           nut1=1;
; 0000 01F8           VAN_L=0;
	CALL SUBOPT_0x25
; 0000 01F9      //while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
; 0000 01FA           delay_ms(1500);
; 0000 01FB           BEEP();
	CALL SUBOPT_0x24
; 0000 01FC           nut1=1;
; 0000 01FD           VAN_L=1;
	CALL SUBOPT_0x26
; 0000 01FE      //while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
; 0000 01FF           delay_ms(1500);
; 0000 0200           BEEP();
	CALL SUBOPT_0x24
; 0000 0201           nut1=1;
; 0000 0202           VAN_L=0;
	CALL SUBOPT_0x25
; 0000 0203      //while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
; 0000 0204           delay_ms(1500);
; 0000 0205           BEEP();
	CALL SUBOPT_0x24
; 0000 0206           nut1=1;
; 0000 0207           VAN_L=1;
	SBI  0x1B,4
; 0000 0208           for (i=0; i<20; i++) {BEEP(); }
	CLR  R5
_0x9E:
	LDI  R30,LOW(20)
	CP   R5,R30
	BRSH _0x9F
	RCALL _BEEP
	INC  R5
	RJMP _0x9E
_0x9F:
; 0000 0209 
; 0000 020A      while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
_0xA0:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0xA2
	CALL SUBOPT_0x22
	BRNE _0xA3
	CBI  0x1B,1
	CBI  0x1B,0
_0xA3:
	CALL SUBOPT_0x23
	RJMP _0xA0
_0xA2:
; 0000 020B           BEEP();
	CALL SUBOPT_0x24
; 0000 020C           nut1=1;
; 0000 020D           while(1) {}
_0xA8:
	RJMP _0xA8
; 0000 020E 
; 0000 020F 
; 0000 0210      while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
_0xAB:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0xAD
	CALL SUBOPT_0x22
	BRNE _0xAE
	CBI  0x1B,1
	CBI  0x1B,0
_0xAE:
	CALL SUBOPT_0x23
	RJMP _0xAB
_0xAD:
; 0000 0211           BEEP();
	CALL SUBOPT_0x24
; 0000 0212           nut1=1;
; 0000 0213           ENDATA1=0;
	CALL SUBOPT_0x27
; 0000 0214           ENDATA2=0;
; 0000 0215           TIMSK=0x02; ///////TIMER0 COMPARE MATH PID
; 0000 0216           ETIMSK=0x00;
; 0000 0217           SETVT1=-30;
	__GETD1N 0xFFFFFFE2
	CALL SUBOPT_0x28
; 0000 0218           SETVT2=-15;
	__GETD1N 0xFFFFFFF1
	CALL SUBOPT_0x29
; 0000 0219      //////////////////////////////////////////////////////////////////
; 0000 021A      while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100); lcd_clear(); }
_0xB3:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0xB5
	CALL SUBOPT_0x22
	BRNE _0xB6
	CBI  0x1B,1
	CBI  0x1B,0
_0xB6:
	CALL SUBOPT_0x23
	CALL _lcd_clear
	RJMP _0xB3
_0xB5:
; 0000 021B           BEEP();
	CALL SUBOPT_0x24
; 0000 021C           nut1=1;
; 0000 021D           TIMSK=0x00; ///////TAT TIMER0 COMPARE MATH PID
	CALL SUBOPT_0x21
; 0000 021E           ETIMSK=0x00;
; 0000 021F           RESDC1();
	CALL SUBOPT_0x2A
; 0000 0220           RESDC2();
; 0000 0221           VAN_T1=0;
	CBI  0x1B,0
; 0000 0222           VAN_T2=0;
	CBI  0x1B,1
; 0000 0223      while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100); lcd_clear(); }
_0xBF:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0xC1
	CALL SUBOPT_0x22
	BRNE _0xC2
	CBI  0x1B,1
	CBI  0x1B,0
_0xC2:
	CALL SUBOPT_0x23
	CALL _lcd_clear
	RJMP _0xBF
_0xC1:
; 0000 0224           BEEP();
	CALL SUBOPT_0x24
; 0000 0225           nut1=1;
; 0000 0226           VAN_T1=1;
	SBI  0x1B,0
; 0000 0227      ////////////////////////////DONG MO VAN 2 TAY XONG ////////////////////////
; 0000 0228 
; 0000 0229      while (nut1==1) {DOCPS2(); if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
_0xC9:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0xCB
	CALL SUBOPT_0x22
	BRNE _0xCC
	CBI  0x1B,1
	CBI  0x1B,0
_0xCC:
	CALL SUBOPT_0x23
	RJMP _0xC9
_0xCB:
; 0000 022A           BEEP();
	CALL SUBOPT_0x24
; 0000 022B           nut1=1;
; 0000 022C           ENDATA1=0;
	CALL SUBOPT_0x27
; 0000 022D           ENDATA2=0;
; 0000 022E           TIMSK=0x02; ///////TIMER0 COMPARE MATH PID
; 0000 022F           ETIMSK=0x00;
; 0000 0230           SETVT2=0;
	CALL SUBOPT_0x2B
; 0000 0231           while (TAY2==1) {SETVT1++; delay_ms(10); }
_0xD1:
	SBIS 0x10,6
	RJMP _0xD3
	LDI  R26,LOW(_SETVT1)
	LDI  R27,HIGH(_SETVT1)
	CALL SUBOPT_0x10
	CALL SUBOPT_0x2C
	RJMP _0xD1
_0xD3:
; 0000 0232           VAN_T2=1;
	SBI  0x1B,1
; 0000 0233           TIMSK=0x00; ///////TAT TIMER0 COMPARE MATH PID
	CALL SUBOPT_0x21
; 0000 0234           ETIMSK=0x00;
; 0000 0235           RESDC1(); RESDC2();
	CALL SUBOPT_0x2A
; 0000 0236 
; 0000 0237      while (nut1==1) {DOCPS2();if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100); lcd_clear();}
_0xD6:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0xD8
	CALL SUBOPT_0x22
	BRNE _0xD9
	CBI  0x1B,1
	CBI  0x1B,0
_0xD9:
	CALL SUBOPT_0x23
	CALL _lcd_clear
	RJMP _0xD6
_0xD8:
; 0000 0238           BEEP();
	CALL SUBOPT_0x24
; 0000 0239           nut1=1;
; 0000 023A           VAN_T1=0;
	CBI  0x1B,0
; 0000 023B      while (nut1==1) {DOCPS2();if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100); lcd_clear();}
_0xE0:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0xE2
	CALL SUBOPT_0x22
	BRNE _0xE3
	CBI  0x1B,1
	CBI  0x1B,0
_0xE3:
	CALL SUBOPT_0x23
	CALL _lcd_clear
	RJMP _0xE0
_0xE2:
; 0000 023C           BEEP();
	CALL SUBOPT_0x24
; 0000 023D           nut1=1;
; 0000 023E           ENDATA1=0;
	CALL SUBOPT_0x27
; 0000 023F           ENDATA2=0;
; 0000 0240           TIMSK=0x02; ///////TIMER0 COMPARE MATH PID
; 0000 0241           ETIMSK=0x00;
; 0000 0242           SETVT2=-100;
	__GETD1N 0xFFFFFF9C
	CALL SUBOPT_0x2D
; 0000 0243           SETVT1=0;
; 0000 0244           while (ENDATA2>-50) {}
_0xE8:
	CALL SUBOPT_0x2E
	__CPD2N 0xFFFFFFCF
	BRGE _0xE8
; 0000 0245           SETVT1=-200;
	__GETD1N 0xFFFFFF38
	CALL SUBOPT_0x28
; 0000 0246           while (ENDATA2>-100) {}
_0xEB:
	CALL SUBOPT_0x2E
	__CPD2N 0xFFFFFF9D
	BRGE _0xEB
; 0000 0247           ENDATA2=0;
	LDI  R30,LOW(0)
	STS  _ENDATA2,R30
	STS  _ENDATA2+1,R30
	STS  _ENDATA2+2,R30
	STS  _ENDATA2+3,R30
; 0000 0248           while (TAY1==1) {SETVT2--; delay_ms(10); }
_0xEE:
	SBIS 0x10,4
	RJMP _0xF0
	LDI  R26,LOW(_SETVT2)
	LDI  R27,HIGH(_SETVT2)
	CALL SUBOPT_0x11
	CALL SUBOPT_0x2C
	RJMP _0xEE
_0xF0:
; 0000 0249           VAN_T1=1;
	SBI  0x1B,0
; 0000 024A           TIMSK=0x00; ///////TAT TIMER0 COMPARE MATH PID
	CALL SUBOPT_0x21
; 0000 024B           ETIMSK=0x00;
; 0000 024C           RESDC1(); RESDC2();
	CALL SUBOPT_0x2A
; 0000 024D      while (nut1==1) {DOCPS2();if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100); lcd_clear();}
_0xF3:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0xF5
	CALL SUBOPT_0x22
	BRNE _0xF6
	CBI  0x1B,1
	CBI  0x1B,0
_0xF6:
	CALL SUBOPT_0x23
	RCALL _lcd_clear
	RJMP _0xF3
_0xF5:
; 0000 024E           BEEP();
	CALL SUBOPT_0x24
; 0000 024F           nut1=1;
; 0000 0250           VAN_T2=0;
	CBI  0x1B,1
; 0000 0251      while (nut1==1) {DOCPS2();if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100); lcd_clear();}
_0xFD:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0xFF
	CALL SUBOPT_0x22
	BRNE _0x100
	CBI  0x1B,1
	CBI  0x1B,0
_0x100:
	CALL SUBOPT_0x23
	RCALL _lcd_clear
	RJMP _0xFD
_0xFF:
; 0000 0252           BEEP();
	CALL SUBOPT_0x24
; 0000 0253           nut1=1;
; 0000 0254           ENDATA1=0;
	CALL SUBOPT_0x27
; 0000 0255           ENDATA2=0;
; 0000 0256           TIMSK=0x02; ///////TIMER0 COMPARE MATH PID
; 0000 0257           ETIMSK=0x00;
; 0000 0258           SETVT1=100;
	__GETD1N 0x64
	CALL SUBOPT_0x28
; 0000 0259           SETVT2=0;
	CALL SUBOPT_0x2B
; 0000 025A           while (ENDATA1<99) {}
_0x105:
	LDS  R26,_ENDATA1
	LDS  R27,_ENDATA1+1
	LDS  R24,_ENDATA1+2
	LDS  R25,_ENDATA1+3
	__CPD2N 0x63
	BRLT _0x105
; 0000 025B           RESDC1();
	CALL SUBOPT_0x2A
; 0000 025C           RESDC2();
; 0000 025D           TIMSK=0x00; ///////TAT TIMER0 COMPARE MATH PID
	CALL SUBOPT_0x21
; 0000 025E           ETIMSK=0x00;
; 0000 025F 
; 0000 0260      while (nut1==1) {DOCPS2();if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100); lcd_clear();}
_0x108:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0x10A
	CALL SUBOPT_0x22
	BRNE _0x10B
	CBI  0x1B,1
	CBI  0x1B,0
_0x10B:
	CALL SUBOPT_0x23
	RCALL _lcd_clear
	RJMP _0x108
_0x10A:
; 0000 0261           BEEP();
	CALL SUBOPT_0x24
; 0000 0262           nut1=1;
; 0000 0263           TIMSK=0x02; ///////TIMER0 COMPARE MATH PID
	LDI  R30,LOW(2)
	OUT  0x37,R30
; 0000 0264           ETIMSK=0x00;
	LDI  R30,LOW(0)
	STS  125,R30
; 0000 0265           SETVT2=190;
	__GETD1N 0xBE
	CALL SUBOPT_0x29
; 0000 0266           delay_ms(200);
	LDI  R30,LOW(200)
	LDI  R31,HIGH(200)
	CALL SUBOPT_0x20
; 0000 0267      while (nut1==1) {DOCPS2();if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100); lcd_clear();}
_0x110:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0x112
	CALL SUBOPT_0x22
	BRNE _0x113
	CBI  0x1B,1
	CBI  0x1B,0
_0x113:
	CALL SUBOPT_0x23
	RCALL _lcd_clear
	RJMP _0x110
_0x112:
; 0000 0268           BEEP();
	CALL SUBOPT_0x24
; 0000 0269           nut1=1;
; 0000 026A           while (TAY2==1) {SETVT1++; delay_ms(10); }
_0x118:
	SBIS 0x10,6
	RJMP _0x11A
	LDI  R26,LOW(_SETVT1)
	LDI  R27,HIGH(_SETVT1)
	CALL SUBOPT_0x10
	CALL SUBOPT_0x2C
	RJMP _0x118
_0x11A:
; 0000 026B           VAN_T2=1;
	SBI  0x1B,1
; 0000 026C           TIMSK=0x00; ///////TAT TIMER0 COMPARE MATH PID
	CALL SUBOPT_0x21
; 0000 026D           ETIMSK=0x00;
; 0000 026E           RESDC1(); RESDC2();
	CALL SUBOPT_0x2A
; 0000 026F      while (nut1==1) {DOCPS2();if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100); lcd_clear();}
_0x11D:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0x11F
	CALL SUBOPT_0x22
	BRNE _0x120
	CBI  0x1B,1
	CBI  0x1B,0
_0x120:
	CALL SUBOPT_0x23
	RCALL _lcd_clear
	RJMP _0x11D
_0x11F:
; 0000 0270           BEEP();
	CALL SUBOPT_0x24
; 0000 0271           nut1=1;
; 0000 0272           VAN_T1=0;
	CBI  0x1B,0
; 0000 0273      while (nut1==1) {DOCPS2();if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100); lcd_clear();}
_0x127:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0x129
	CALL SUBOPT_0x22
	BRNE _0x12A
	CBI  0x1B,1
	CBI  0x1B,0
_0x12A:
	CALL SUBOPT_0x23
	RCALL _lcd_clear
	RJMP _0x127
_0x129:
; 0000 0274           BEEP();
	CALL SUBOPT_0x24
; 0000 0275           nut1=1;
; 0000 0276           ENDATA1=0;
	CALL SUBOPT_0x27
; 0000 0277           ENDATA2=0;
; 0000 0278           TIMSK=0x02; ///////TIMER0 COMPARE MATH PID
; 0000 0279           ETIMSK=0x00;
; 0000 027A           SETVT2=-30;
	__GETD1N 0xFFFFFFE2
	CALL SUBOPT_0x2D
; 0000 027B           SETVT1=0;
; 0000 027C      while (ENDATA2>-30) {}
_0x12F:
	CALL SUBOPT_0x2E
	__CPD2N 0xFFFFFFE3
	BRGE _0x12F
; 0000 027D           TIMSK=0x00; ///////TAT TIMER0 COMPARE MATH PID
	CALL SUBOPT_0x21
; 0000 027E           ETIMSK=0x00;
; 0000 027F           RESDC1(); RESDC2();
	CALL SUBOPT_0x2A
; 0000 0280 
; 0000 0281 
; 0000 0282      while (nut1==1) {DOCPS2();if (nut4==0) {VAN_T1=VAN_T2=0;}; lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100); lcd_clear();}
_0x132:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0x134
	CALL SUBOPT_0x22
	BRNE _0x135
	CBI  0x1B,1
	CBI  0x1B,0
_0x135:
	CALL SUBOPT_0x23
	RCALL _lcd_clear
	RJMP _0x132
_0x134:
; 0000 0283           while(1) {}
_0x13A:
	RJMP _0x13A
; 0000 0284 
; 0000 0285 
; 0000 0286      while (nut1==1) {DOCPS2(); lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0); delay_ms(100);}
_0x13D:
	LDS  R26,_nut1
	CPI  R26,LOW(0x1)
	BRNE _0x13F
	RCALL _DOCPS2
	CALL SUBOPT_0x23
	RJMP _0x13D
_0x13F:
; 0000 0287           BEEP();
	CALL SUBOPT_0x24
; 0000 0288           nut1=1;
; 0000 0289           TIMSK=0x02; ///////TIMER0 COMPARE MATH PID
	LDI  R30,LOW(2)
	OUT  0x37,R30
; 0000 028A           ETIMSK=0x00;
	LDI  R30,LOW(0)
	STS  125,R30
; 0000 028B 
; 0000 028C           while(1)
_0x140:
; 0000 028D           {
; 0000 028E           DOCPS2();
	RCALL _DOCPS2
; 0000 028F           if (up==0) { SETVT1=SETVT1+5; BEEP(); }
	LDS  R30,_up
	CPI  R30,0
	BRNE _0x143
	CALL SUBOPT_0x1E
	__ADDD1N 5
	CALL SUBOPT_0x28
	RCALL _BEEP
; 0000 0290           if (down==0) { SETVT1=SETVT1-5; BEEP(); }
_0x143:
	LDS  R30,_down
	CPI  R30,0
	BRNE _0x144
	CALL SUBOPT_0x1E
	__SUBD1N 5
	CALL SUBOPT_0x28
	RCALL _BEEP
; 0000 0291           if (left==0) { SETVT2=SETVT2+5; BEEP(); }
_0x144:
	LDS  R30,_left
	CPI  R30,0
	BRNE _0x145
	CALL SUBOPT_0x1F
	__ADDD1N 5
	CALL SUBOPT_0x29
	RCALL _BEEP
; 0000 0292           if (right==0) { SETVT2=SETVT2-5; BEEP(); }
_0x145:
	LDS  R30,_right
	CPI  R30,0
	BRNE _0x146
	CALL SUBOPT_0x1F
	__SUBD1N 5
	CALL SUBOPT_0x29
	RCALL _BEEP
; 0000 0293           lcd_putnum(ENDATA1,0,0); lcd_putnum(ENDATA2,8,0);
_0x146:
	RCALL SUBOPT_0x12
	CALL __PUTPARD1
	LDI  R30,LOW(0)
	ST   -Y,R30
	ST   -Y,R30
	RCALL _lcd_putnum
	CALL SUBOPT_0x19
	CALL __PUTPARD1
	LDI  R30,LOW(8)
	ST   -Y,R30
	LDI  R30,LOW(0)
	ST   -Y,R30
	RCALL _lcd_putnum
; 0000 0294           lcd_putnum(SETVT1,0,1); lcd_putnum(SETVT2,8,1);
	CALL SUBOPT_0x1E
	CALL __PUTPARD1
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R30,LOW(1)
	ST   -Y,R30
	RCALL _lcd_putnum
	CALL SUBOPT_0x1F
	CALL __PUTPARD1
	LDI  R30,LOW(8)
	ST   -Y,R30
	LDI  R30,LOW(1)
	ST   -Y,R30
	RCALL _lcd_putnum
; 0000 0295           delay_ms(100);
	LDI  R30,LOW(100)
	LDI  R31,HIGH(100)
	CALL SUBOPT_0x20
; 0000 0296           lcd_clear();
	RCALL _lcd_clear
; 0000 0297           };
	RJMP _0x140
; 0000 0298 
; 0000 0299      }
; 0000 029A 
; 0000 029B //////////////////////////////////////////////////////////
; 0000 029C /*
; 0000 029D while (1)
; 0000 029E       {
; 0000 029F       nut1=1;
; 0000 02A0       while (nut1==1) {DOCPS2(); }
; 0000 02A1           VAN_G=0;
; 0000 02A2       while (nut1==1) {DOCPS2(); }
; 0000 02A3           CTHT1=1;
; 0000 02A4           while (CTHT1 ==1) {DC1THUAN(300); }
; 0000 02A5           RESDC1();
; 0000 02A6           CTHT2=1;
; 0000 02A7           while (CTHT2 ==1) {DC2THUAN(300); }
; 0000 02A8           RESDC2();
; 0000 02A9 
; 0000 02AA       while (nut1==1) {DOCPS2();}
; 0000 02AB           ENDATA1=0; ENDATA2=0;
; 0000 02AC           #asm("sei");
; 0000 02AD           SETVT1=-30;
; 0000 02AE           SETVT2=0;
; 0000 02AF           VAN_T1=0;
; 0000 02B0           VAN_T2=0;
; 0000 02B1 
; 0000 02B2       while (nut1==1) {DOCPS2();}
; 0000 02B3           VAN_T1=1;
; 0000 02B4 
; 0000 02B5       while (nut1==1) {DOCPS2();}
; 0000 02B6           TAY2=1;
; 0000 02B7           SETVT1=0;
; 0000 02B8           if (TAY2==0) {VAN_T2=1; }
; 0000 02B9           while (TAY2==1)
; 0000 02BA                {
; 0000 02BB 
; 0000 02BC                }
; 0000 02BD 
; 0000 02BE 
; 0000 02BF       } */
; 0000 02C0 }
_0x147:
	RJMP _0x147
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x20
	.EQU __sm_mask=0x1C
	.EQU __sm_powerdown=0x10
	.EQU __sm_powersave=0x18
	.EQU __sm_standby=0x14
	.EQU __sm_ext_standby=0x1C
	.EQU __sm_adc_noise_red=0x08
	.SET power_ctrl_reg=mcucr
	#endif

	.DSEG

	.CSEG
__lcd_write_nibble_G100:
	LD   R30,Y
	ANDI R30,LOW(0x10)
	BREQ _0x2000004
	LDS  R30,98
	ORI  R30,0x10
	RJMP _0x200001D
_0x2000004:
	LDS  R30,98
	ANDI R30,0xEF
_0x200001D:
	STS  98,R30
	LD   R30,Y
	ANDI R30,LOW(0x20)
	BREQ _0x2000006
	LDS  R30,98
	ORI  R30,0x20
	RJMP _0x200001E
_0x2000006:
	LDS  R30,98
	ANDI R30,0xDF
_0x200001E:
	STS  98,R30
	LD   R30,Y
	ANDI R30,LOW(0x40)
	BREQ _0x2000008
	LDS  R30,98
	ORI  R30,0x40
	RJMP _0x200001F
_0x2000008:
	LDS  R30,98
	ANDI R30,0xBF
_0x200001F:
	STS  98,R30
	LD   R30,Y
	ANDI R30,LOW(0x80)
	BREQ _0x200000A
	LDS  R30,98
	ORI  R30,0x80
	RJMP _0x2000020
_0x200000A:
	LDS  R30,98
	ANDI R30,0x7F
_0x2000020:
	STS  98,R30
	__DELAY_USB 7
	LDS  R30,98
	ORI  R30,4
	STS  98,R30
	__DELAY_USB 18
	LDS  R30,98
	ANDI R30,0xFB
	STS  98,R30
	__DELAY_USB 18
	RJMP _0x2020001
__lcd_write_data:
	LD   R30,Y
	ST   -Y,R30
	RCALL __lcd_write_nibble_G100
    ld    r30,y
    swap  r30
    st    y,r30
	LD   R30,Y
	ST   -Y,R30
	RCALL __lcd_write_nibble_G100
	__DELAY_USB 184
	RJMP _0x2020001
_lcd_gotoxy:
	LD   R30,Y
	LDI  R31,0
	SUBI R30,LOW(-__base_y_G100)
	SBCI R31,HIGH(-__base_y_G100)
	LD   R30,Z
	LDD  R26,Y+1
	ADD  R30,R26
	ST   -Y,R30
	RCALL __lcd_write_data
	LDD  R4,Y+1
	LDD  R7,Y+0
	ADIW R28,2
	RET
_lcd_clear:
	LDI  R30,LOW(2)
	RCALL SUBOPT_0x2F
	LDI  R30,LOW(12)
	ST   -Y,R30
	RCALL __lcd_write_data
	LDI  R30,LOW(1)
	RCALL SUBOPT_0x2F
	LDI  R30,LOW(0)
	MOV  R7,R30
	MOV  R4,R30
	RET
_lcd_putchar:
	LD   R26,Y
	CPI  R26,LOW(0xA)
	BREQ _0x2000011
	CP   R4,R6
	BRLO _0x2000010
_0x2000011:
	LDI  R30,LOW(0)
	ST   -Y,R30
	INC  R7
	ST   -Y,R7
	RCALL _lcd_gotoxy
	LD   R26,Y
	CPI  R26,LOW(0xA)
	BRNE _0x2000013
	RJMP _0x2020001
_0x2000013:
_0x2000010:
	INC  R4
	LDS  R30,98
	ORI  R30,1
	STS  98,R30
	LD   R30,Y
	ST   -Y,R30
	RCALL __lcd_write_data
	LDS  R30,98
	ANDI R30,0xFE
	STS  98,R30
	RJMP _0x2020001
_lcd_putsf:
	ST   -Y,R17
_0x2000017:
	LDD  R30,Y+1
	LDD  R31,Y+1+1
	ADIW R30,1
	STD  Y+1,R30
	STD  Y+1+1,R31
	SBIW R30,1
	LPM  R30,Z
	MOV  R17,R30
	CPI  R30,0
	BREQ _0x2000019
	ST   -Y,R17
	RCALL _lcd_putchar
	RJMP _0x2000017
_0x2000019:
	LDD  R17,Y+0
	ADIW R28,3
	RET
_lcd_init:
	LDS  R30,97
	ORI  R30,0x10
	RCALL SUBOPT_0x30
	ORI  R30,0x20
	RCALL SUBOPT_0x30
	ORI  R30,0x40
	RCALL SUBOPT_0x30
	ORI  R30,0x80
	RCALL SUBOPT_0x30
	ORI  R30,4
	RCALL SUBOPT_0x30
	ORI  R30,1
	RCALL SUBOPT_0x30
	ORI  R30,2
	STS  97,R30
	LDS  R30,98
	ANDI R30,0xFB
	STS  98,R30
	LDS  R30,98
	ANDI R30,0xFE
	STS  98,R30
	LDS  R30,98
	ANDI R30,0xFD
	STS  98,R30
	LDD  R6,Y+0
	LD   R30,Y
	SUBI R30,-LOW(128)
	__PUTB1MN __base_y_G100,2
	LD   R30,Y
	SUBI R30,-LOW(192)
	__PUTB1MN __base_y_G100,3
	LDI  R30,LOW(20)
	LDI  R31,HIGH(20)
	RCALL SUBOPT_0x20
	RCALL SUBOPT_0x31
	RCALL SUBOPT_0x31
	RCALL SUBOPT_0x31
	LDI  R30,LOW(32)
	ST   -Y,R30
	RCALL __lcd_write_nibble_G100
	RCALL SUBOPT_0x6
	LDI  R30,LOW(40)
	ST   -Y,R30
	RCALL __lcd_write_data
	LDI  R30,LOW(4)
	ST   -Y,R30
	RCALL __lcd_write_data
	LDI  R30,LOW(133)
	ST   -Y,R30
	RCALL __lcd_write_data
	LDI  R30,LOW(6)
	ST   -Y,R30
	RCALL __lcd_write_data
	RCALL _lcd_clear
_0x2020001:
	ADIW R28,1
	RET

	.DSEG
_PES:
	.BYTE 0x6
_analog:
	.BYTE 0x1
_L1:
	.BYTE 0x1
_R1:
	.BYTE 0x1
_L2:
	.BYTE 0x1
_R2:
	.BYTE 0x1
_L:
	.BYTE 0x1
_R:
	.BYTE 0x1
_start:
	.BYTE 0x1
_select:
	.BYTE 0x1
_up:
	.BYTE 0x1
_down:
	.BYTE 0x1
_left:
	.BYTE 0x1
_right:
	.BYTE 0x1
_nut3:
	.BYTE 0x1
_nut2:
	.BYTE 0x1
_nut4:
	.BYTE 0x1
_nut1:
	.BYTE 0x1
_ENDATA1:
	.BYTE 0x4
_ENDATA2:
	.BYTE 0x4
_ERR1:
	.BYTE 0x4
_REALVT1:
	.BYTE 0x4
_ERR2:
	.BYTE 0x4
_REALVT2:
	.BYTE 0x4
_SETVT1:
	.BYTE 0x4
_SETVT2:
	.BYTE 0x4
__base_y_G100:
	.BYTE 0x4

	.CSEG
;OPTIMIZER ADDED SUBROUTINE, CALLED 9 TIMES, CODE SIZE REDUCTION:13 WORDS
SUBOPT_0x0:
	__GETD2S 22
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:27 WORDS
SUBOPT_0x1:
	__GETD1S 16
	__GETD2N 0x2710
	CALL __MULD12
	RJMP SUBOPT_0x0

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x2:
	CALL __SWAPD12
	CALL __SUBD12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:13 WORDS
SUBOPT_0x3:
	__GETD1S 12
	__GETD2N 0x3E8
	CALL __MULD12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x4:
	__GETD1S 8
	__GETD2N 0x64
	CALL __MULD12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x5:
	SUBI R30,-LOW(48)
	ST   -Y,R30
	RJMP _lcd_putchar

;OPTIMIZER ADDED SUBROUTINE, CALLED 7 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0x6:
	__DELAY_USW 276
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 9 TIMES, CODE SIZE REDUCTION:13 WORDS
SUBOPT_0x7:
	LDI  R30,LOW(0)
	ST   -Y,R30
	JMP  _access

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:4 WORDS
SUBOPT_0x8:
	ANDI R30,LOW(0x2)
	LDI  R31,0
	MOVW R26,R30
	LDI  R30,LOW(2)
	LDI  R31,HIGH(2)
	CALL __DIVW21
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:4 WORDS
SUBOPT_0x9:
	ANDI R30,LOW(0x4)
	LDI  R31,0
	MOVW R26,R30
	LDI  R30,LOW(4)
	LDI  R31,HIGH(4)
	CALL __DIVW21
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:4 WORDS
SUBOPT_0xA:
	ANDI R30,LOW(0x8)
	LDI  R31,0
	MOVW R26,R30
	LDI  R30,LOW(8)
	LDI  R31,HIGH(8)
	CALL __DIVW21
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:4 WORDS
SUBOPT_0xB:
	ANDI R30,LOW(0x10)
	LDI  R31,0
	MOVW R26,R30
	LDI  R30,LOW(16)
	LDI  R31,HIGH(16)
	CALL __DIVW21
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:4 WORDS
SUBOPT_0xC:
	ANDI R30,LOW(0x20)
	LDI  R31,0
	MOVW R26,R30
	LDI  R30,LOW(32)
	LDI  R31,HIGH(32)
	CALL __DIVW21
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:4 WORDS
SUBOPT_0xD:
	ANDI R30,LOW(0x40)
	LDI  R31,0
	MOVW R26,R30
	LDI  R30,LOW(64)
	LDI  R31,HIGH(64)
	CALL __DIVW21
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:4 WORDS
SUBOPT_0xE:
	ANDI R30,LOW(0x80)
	LDI  R31,0
	MOVW R26,R30
	LDI  R30,LOW(128)
	LDI  R31,HIGH(128)
	CALL __DIVW21
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0xF:
	ST   -Y,R22
	ST   -Y,R23
	ST   -Y,R26
	ST   -Y,R27
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:24 WORDS
SUBOPT_0x10:
	CALL __GETD1P_INC
	__SUBD1N -1
	CALL __PUTDP1_DEC
	SBIW R30,1
	SBCI R22,0
	SBCI R23,0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:15 WORDS
SUBOPT_0x11:
	CALL __GETD1P_INC
	SBIW R30,1
	SBCI R22,0
	SBCI R23,0
	CALL __PUTDP1_DEC
	__SUBD1N -1
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 18 TIMES, CODE SIZE REDUCTION:99 WORDS
SUBOPT_0x12:
	LDS  R30,_ENDATA1
	LDS  R31,_ENDATA1+1
	LDS  R22,_ENDATA1+2
	LDS  R23,_ENDATA1+3
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 8 TIMES, CODE SIZE REDUCTION:11 WORDS
SUBOPT_0x13:
	CALL __GETD1S0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:15 WORDS
SUBOPT_0x14:
	LDS  R26,_REALVT1
	LDS  R27,_REALVT1+1
	LDS  R24,_REALVT1+2
	LDS  R25,_REALVT1+3
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:20 WORDS
SUBOPT_0x15:
	CALL __SUBD12
	STS  _ERR1,R30
	STS  _ERR1+1,R31
	STS  _ERR1+2,R22
	STS  _ERR1+3,R23
	LDS  R26,_ERR1
	LDS  R27,_ERR1+1
	LDS  R24,_ERR1+2
	LDS  R25,_ERR1+3
	__CPD2N 0x259
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x16:
	__GETD1N 0x258
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0x17:
	LDS  R30,_ERR1
	LDS  R31,_ERR1+1
	LDS  R22,_ERR1+2
	LDS  R23,_ERR1+3
	CALL __LSLD1
	__ADDD1N 200
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x18:
	RCALL SUBOPT_0x13
	RCALL SUBOPT_0x14
	CALL __CPD12
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 18 TIMES, CODE SIZE REDUCTION:99 WORDS
SUBOPT_0x19:
	LDS  R30,_ENDATA2
	LDS  R31,_ENDATA2+1
	LDS  R22,_ENDATA2+2
	LDS  R23,_ENDATA2+3
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:13 WORDS
SUBOPT_0x1A:
	RCALL SUBOPT_0x13
	LDS  R26,_REALVT2
	LDS  R27,_REALVT2+1
	LDS  R24,_REALVT2+2
	LDS  R25,_REALVT2+3
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x1B:
	CALL __SUBD12
	STS  _ERR2,R30
	STS  _ERR2+1,R31
	STS  _ERR2+2,R22
	STS  _ERR2+3,R23
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:2 WORDS
SUBOPT_0x1C:
	__CPD2N 0x259
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0x1D:
	LDS  R30,_ERR2
	LDS  R31,_ERR2+1
	LDS  R22,_ERR2+2
	LDS  R23,_ERR2+3
	CALL __LSLD1
	__ADDD1N 200
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:15 WORDS
SUBOPT_0x1E:
	LDS  R30,_SETVT1
	LDS  R31,_SETVT1+1
	LDS  R22,_SETVT1+2
	LDS  R23,_SETVT1+3
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:15 WORDS
SUBOPT_0x1F:
	LDS  R30,_SETVT2
	LDS  R31,_SETVT2+1
	LDS  R22,_SETVT2+2
	LDS  R23,_SETVT2+3
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 35 TIMES, CODE SIZE REDUCTION:65 WORDS
SUBOPT_0x20:
	ST   -Y,R31
	ST   -Y,R30
	JMP  _delay_ms

;OPTIMIZER ADDED SUBROUTINE, CALLED 7 TIMES, CODE SIZE REDUCTION:15 WORDS
SUBOPT_0x21:
	LDI  R30,LOW(0)
	OUT  0x37,R30
	STS  125,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 15 TIMES, CODE SIZE REDUCTION:39 WORDS
SUBOPT_0x22:
	CALL _DOCPS2
	LDS  R30,_nut4
	CPI  R30,0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 16 TIMES, CODE SIZE REDUCTION:327 WORDS
SUBOPT_0x23:
	RCALL SUBOPT_0x12
	CALL __PUTPARD1
	LDI  R30,LOW(0)
	ST   -Y,R30
	ST   -Y,R30
	CALL _lcd_putnum
	RCALL SUBOPT_0x19
	CALL __PUTPARD1
	LDI  R30,LOW(8)
	ST   -Y,R30
	LDI  R30,LOW(0)
	ST   -Y,R30
	CALL _lcd_putnum
	LDI  R30,LOW(100)
	LDI  R31,HIGH(100)
	RJMP SUBOPT_0x20

;OPTIMIZER ADDED SUBROUTINE, CALLED 24 TIMES, CODE SIZE REDUCTION:66 WORDS
SUBOPT_0x24:
	CALL _BEEP
	LDI  R30,LOW(1)
	STS  _nut1,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0x25:
	CBI  0x1B,4
	LDI  R30,LOW(1500)
	LDI  R31,HIGH(1500)
	RJMP SUBOPT_0x20

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:6 WORDS
SUBOPT_0x26:
	SBI  0x1B,4
	LDI  R30,LOW(1500)
	LDI  R31,HIGH(1500)
	RJMP SUBOPT_0x20

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:81 WORDS
SUBOPT_0x27:
	LDI  R30,LOW(0)
	STS  _ENDATA1,R30
	STS  _ENDATA1+1,R30
	STS  _ENDATA1+2,R30
	STS  _ENDATA1+3,R30
	STS  _ENDATA2,R30
	STS  _ENDATA2+1,R30
	STS  _ENDATA2+2,R30
	STS  _ENDATA2+3,R30
	LDI  R30,LOW(2)
	OUT  0x37,R30
	LDI  R30,LOW(0)
	STS  125,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:21 WORDS
SUBOPT_0x28:
	STS  _SETVT1,R30
	STS  _SETVT1+1,R31
	STS  _SETVT1+2,R22
	STS  _SETVT1+3,R23
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:27 WORDS
SUBOPT_0x29:
	STS  _SETVT2,R30
	STS  _SETVT2+1,R31
	STS  _SETVT2+2,R22
	STS  _SETVT2+3,R23
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x2A:
	CALL _RESDC1
	JMP  _RESDC2

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:4 WORDS
SUBOPT_0x2B:
	LDI  R30,LOW(0)
	STS  _SETVT2,R30
	STS  _SETVT2+1,R30
	STS  _SETVT2+2,R30
	STS  _SETVT2+3,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x2C:
	LDI  R30,LOW(10)
	LDI  R31,HIGH(10)
	RJMP SUBOPT_0x20

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:6 WORDS
SUBOPT_0x2D:
	RCALL SUBOPT_0x29
	LDI  R30,LOW(0)
	STS  _SETVT1,R30
	STS  _SETVT1+1,R30
	STS  _SETVT1+2,R30
	STS  _SETVT1+3,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0x2E:
	LDS  R26,_ENDATA2
	LDS  R27,_ENDATA2+1
	LDS  R24,_ENDATA2+2
	LDS  R25,_ENDATA2+3
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:2 WORDS
SUBOPT_0x2F:
	ST   -Y,R30
	RCALL __lcd_write_data
	LDI  R30,LOW(3)
	LDI  R31,HIGH(3)
	RJMP SUBOPT_0x20

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x30:
	STS  97,R30
	LDS  R30,97
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x31:
	LDI  R30,LOW(48)
	ST   -Y,R30
	RCALL __lcd_write_nibble_G100
	RJMP SUBOPT_0x6


	.CSEG
_delay_ms:
	ld   r30,y+
	ld   r31,y+
	adiw r30,0
	breq __delay_ms1
__delay_ms0:
	__DELAY_USW 0xACD
	wdr
	sbiw r30,1
	brne __delay_ms0
__delay_ms1:
	ret

__SUBD12:
	SUB  R30,R26
	SBC  R31,R27
	SBC  R22,R24
	SBC  R23,R25
	RET

__SUBD21:
	SUB  R26,R30
	SBC  R27,R31
	SBC  R24,R22
	SBC  R25,R23
	RET

__ANEGW1:
	NEG  R31
	NEG  R30
	SBCI R31,0
	RET

__ANEGD1:
	COM  R31
	COM  R22
	COM  R23
	NEG  R30
	SBCI R31,-1
	SBCI R22,-1
	SBCI R23,-1
	RET

__LSLD1:
	LSL  R30
	ROL  R31
	ROL  R22
	ROL  R23
	RET

__MULD12U:
	MUL  R23,R26
	MOV  R23,R0
	MUL  R22,R27
	ADD  R23,R0
	MUL  R31,R24
	ADD  R23,R0
	MUL  R30,R25
	ADD  R23,R0
	MUL  R22,R26
	MOV  R22,R0
	ADD  R23,R1
	MUL  R31,R27
	ADD  R22,R0
	ADC  R23,R1
	MUL  R30,R24
	ADD  R22,R0
	ADC  R23,R1
	CLR  R24
	MUL  R31,R26
	MOV  R31,R0
	ADD  R22,R1
	ADC  R23,R24
	MUL  R30,R27
	ADD  R31,R0
	ADC  R22,R1
	ADC  R23,R24
	MUL  R30,R26
	MOV  R30,R0
	ADD  R31,R1
	ADC  R22,R24
	ADC  R23,R24
	RET

__MULD12:
	RCALL __CHKSIGND
	RCALL __MULD12U
	BRTC __MULD121
	RCALL __ANEGD1
__MULD121:
	RET

__DIVW21U:
	CLR  R0
	CLR  R1
	LDI  R25,16
__DIVW21U1:
	LSL  R26
	ROL  R27
	ROL  R0
	ROL  R1
	SUB  R0,R30
	SBC  R1,R31
	BRCC __DIVW21U2
	ADD  R0,R30
	ADC  R1,R31
	RJMP __DIVW21U3
__DIVW21U2:
	SBR  R26,1
__DIVW21U3:
	DEC  R25
	BRNE __DIVW21U1
	MOVW R30,R26
	MOVW R26,R0
	RET

__DIVW21:
	RCALL __CHKSIGNW
	RCALL __DIVW21U
	BRTC __DIVW211
	RCALL __ANEGW1
__DIVW211:
	RET

__DIVD21U:
	PUSH R19
	PUSH R20
	PUSH R21
	CLR  R0
	CLR  R1
	CLR  R20
	CLR  R21
	LDI  R19,32
__DIVD21U1:
	LSL  R26
	ROL  R27
	ROL  R24
	ROL  R25
	ROL  R0
	ROL  R1
	ROL  R20
	ROL  R21
	SUB  R0,R30
	SBC  R1,R31
	SBC  R20,R22
	SBC  R21,R23
	BRCC __DIVD21U2
	ADD  R0,R30
	ADC  R1,R31
	ADC  R20,R22
	ADC  R21,R23
	RJMP __DIVD21U3
__DIVD21U2:
	SBR  R26,1
__DIVD21U3:
	DEC  R19
	BRNE __DIVD21U1
	MOVW R30,R26
	MOVW R22,R24
	MOVW R26,R0
	MOVW R24,R20
	POP  R21
	POP  R20
	POP  R19
	RET

__DIVD21:
	RCALL __CHKSIGND
	RCALL __DIVD21U
	BRTC __DIVD211
	RCALL __ANEGD1
__DIVD211:
	RET

__CHKSIGNW:
	CLT
	SBRS R31,7
	RJMP __CHKSW1
	RCALL __ANEGW1
	SET
__CHKSW1:
	SBRS R27,7
	RJMP __CHKSW2
	COM  R26
	COM  R27
	ADIW R26,1
	BLD  R0,0
	INC  R0
	BST  R0,0
__CHKSW2:
	RET

__CHKSIGND:
	CLT
	SBRS R23,7
	RJMP __CHKSD1
	RCALL __ANEGD1
	SET
__CHKSD1:
	SBRS R25,7
	RJMP __CHKSD2
	CLR  R0
	COM  R26
	COM  R27
	COM  R24
	COM  R25
	ADIW R26,1
	ADC  R24,R0
	ADC  R25,R0
	BLD  R0,0
	INC  R0
	BST  R0,0
__CHKSD2:
	RET

__GETD1P_INC:
	LD   R30,X+
	LD   R31,X+
	LD   R22,X+
	LD   R23,X+
	RET

__PUTDP1_DEC:
	ST   -X,R23
	ST   -X,R22
	ST   -X,R31
	ST   -X,R30
	RET

__GETD1S0:
	LD   R30,Y
	LDD  R31,Y+1
	LDD  R22,Y+2
	LDD  R23,Y+3
	RET

__GETD2S0:
	LD   R26,Y
	LDD  R27,Y+1
	LDD  R24,Y+2
	LDD  R25,Y+3
	RET

__PUTD2S0:
	ST   Y,R26
	STD  Y+1,R27
	STD  Y+2,R24
	STD  Y+3,R25
	RET

__PUTPARD1:
	ST   -Y,R23
	ST   -Y,R22
	ST   -Y,R31
	ST   -Y,R30
	RET

__SWAPD12:
	MOV  R1,R24
	MOV  R24,R22
	MOV  R22,R1
	MOV  R1,R25
	MOV  R25,R23
	MOV  R23,R1

__SWAPW12:
	MOV  R1,R27
	MOV  R27,R31
	MOV  R31,R1

__SWAPB12:
	MOV  R1,R26
	MOV  R26,R30
	MOV  R30,R1
	RET

__CPD12:
	CP   R30,R26
	CPC  R31,R27
	CPC  R22,R24
	CPC  R23,R25
	RET

__CPD21:
	CP   R26,R30
	CPC  R27,R31
	CPC  R24,R22
	CPC  R25,R23
	RET

__SAVELOCR4:
	ST   -Y,R19
__SAVELOCR3:
	ST   -Y,R18
__SAVELOCR2:
	ST   -Y,R17
	ST   -Y,R16
	RET

__LOADLOCR4:
	LDD  R19,Y+3
__LOADLOCR3:
	LDD  R18,Y+2
__LOADLOCR2:
	LDD  R17,Y+1
	LD   R16,Y
	RET

;END OF CODE MARKER
__END_OF_CODE:
