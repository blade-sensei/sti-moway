//********************************************************************************
//*    lib_sen_moway.h                                                           *
//*    version: 2.0                                                              *
//*    This library contains all the necessary functions to gestionate the Moway *
//*    sensors.					                                                 *
//*    Copyright (C) 2010  Bizintek Innova S.L.                                  *
//*                                                                              *
//********************************************************************************
//*    This program is free software; you can redistribute it and/or modify      *
//*    it under the terms of the GNU General Public License as published by      *
//*    the Free Software Foundation; either version 3 of the License, or         *
//*    (at your option) any later version.                                       *
//*                                                                              *
//*    This program is distributed in the hope that it will be useful,           *
//*    but WITHOUT ANY WARRANTY; without even the implied warranty of            *
//*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
//*    GNU General Public License for more details.                              *
//*                                                                              *
//*    You should have received a copy of the GNU General Public License along   *
//*    with this program; if not, write to the Free Software Foundation, Inc.,   *
//*    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.               *
//********************************************************************************


#include <delays.h>		//fichier qui inclut le fichier p18f86j50.h

//********************
//*   DEFINITIONS    *
//********************

//Battery level

#define   MIN_BAT_ADC		   				132			//Mínimun of battery equal to 3.3 V
#define   MAX_BAT_ADC		   				162			//Máximun of battery equal to 4.2 V
#define   DIV_100_MAX_BAT_ADC_MIN_BAT_ADC   3

#define   ACCE_TAP_SENSI		   			0b01110000			
#define   ACCE_TAP_WINDOW		   			0b01111111			
#define   ACCE_TAP_LAT		   				0b00000100			

//*************************PORTA****************************//
#define   LIGHT_SEN		PORTAbits.RA0      	   		//PORTA,0
#define   IR_RX_L_1     PORTAbits.RA1	       		//PORTA,1
#define   LINE_RX_R     PORTAbits.RA2	       		//PORTA,2
#define   IR_RX_L_2     PORTAbits.RA3	       		//PORTA,3
#define   LINE_RX_L     PORTAbits.RA5	       		//PORTA,5

//*************************PORTB****************************//

#define   ACCE_INT1_DRDY	PORTBbits.RB1		   	//PORTB,1
#define   ACCE_INT2         PORTBbits.RB2		   	//PORTB,2
#define   SPEAKER           PORTBbits.RB3		   	//PORTB,3
#define   LED_TOP_RED       PORTBbits.RB5		   	//PORTB,5
#define   LED_TOP_GREEN     PORTBbits.RB6		   	//PORTB,6

//*************************PORTC****************************//
#define   LED_FRONT		PORTCbits.RC7            	//PORTC,7

//*************************PORTD****************************//
#define   LINE_TX		PORTDbits.RD1            	//PORTD,1
#define   ACCE_SDO		PORTDbits.RD4	   		  	//PORTD,4
#define   ACCE_SDI		PORTDbits.RD5	   		  	//PORTD,5
#define   ACCE_SCL		PORTDbits.RD6			  	//PORTD,6
#define   ACCE_CSN		PORTDbits.RD7	   		  	//PORTD,7

//*************************PORTE****************************//
#define   LED_BRAKE		PORTEbits.RE5	   			//PORTE,5

//*************************PORTF****************************//
#define   IR_RX_R_2     PORTFbits.RF5      			//PORTF,5
#define   IR_RX_R_1     PORTFbits.RF6      			//PORTF,6

//*************************PORTH****************************//
#define   NTC           PORTHbits.RH5       		//PORTH,5
#define	  BATTERY_IN   	PORTHbits.RH6       		//PORTH,6
#define   MIC_IN        PORTHbits.RH7       		//PORTH,7

//*************************PORTJ****************************//
#define   LED_IR        PORTJbits.RJ7       		//PORTJ,7
#define   IR_TX         PORTJbits.RJ6       		//PORTJ,6


//*************************TRISA****************************//
#define   LIGHT_SEN_TRIS       TRISAbits.TRISA0		//TRISA,0
#define   IR_RX_L_1_TRIS       TRISAbits.TRISA1		//TRISA,1
#define   LINE_RX_R_TRIS       TRISAbits.TRISA2		//TRISA,2
#define   IR_RX_L_2_TRIS       TRISAbits.TRISA3		//TRISA,3
#define   LINE_RX_L_TRIS       TRISAbits.TRISA5		//TRISA,5

//*************************TRISB****************************//
#define   ACCE_INT1_DRDY_TRIS  TRISBbits.TRISB1		//TRISB,1
#define   ACCE_INT2_TRIS       TRISBbits.TRISB2		//TRISB,2
#define   SPEAKER_TRIS         TRISBbits.TRISB3		//TRISB,3
#define   LED_TOP_RED_TRIS     TRISBbits.TRISB5		//TRISB,5
#define   LED_TOP_GREEN_TRIS   TRISBbits.TRISB6		//TRISB,6

//*************************TRISC****************************//
#define   LED_FRONT_TRIS       TRISCbits.TRISC7		//TRISC,7


//*************************TRISD****************************//
#define   LINE_TX_TRIS         TRISDbits.TRISD1		//TRISD,1
#define   ACCE_SDI_TRIS		   TRISDbits.TRISD5		//TRISD,5
#define   ACCE_SDO_TRIS		   TRISDbits.TRISD4		//TRISD,4
#define   ACCE_SCL_TRIS		   TRISDbits.TRISD6		//TRISD,6
#define   ACCE_CSN_TRIS		   TRISDbits.TRISD7		//TRISD,7

//*************************TRISE****************************//
#define   LED_BRAKE_TRIS	   TRISEbits.TRISE5		//TRISE,5

//*************************TRISF****************************//
#define   IR_RX_R_2_TRIS       TRISFbits.TRISF5		//TRISF,5
#define   IR_RX_R_1_TRIS       TRISFbits.TRISF6		//TRISF,6


//*************************TRISH****************************//
#define   NTC_TRIS             TRISHbits.TRISH5		//TRISH,5
#define	  BATTERY_TRIS         TRISHbits.TRISH6		//TRISH,6
#define   MIC_IN_TRIS          TRISHbits.TRISH7		//TRISH,7


//*************************TRISJ****************************//
#define   LED_IR_TRIS          TRISJbits.TRISJ7		//TRISJ,7
#define   IR_TX_TRIS           TRISJbits.TRISJ6		//TRISJ,6


//**********Accelerometer registers**********//
#define 	XOUT8		0x06
#define 	YOUT8		0x07
#define 	ZOUT8		0x08
#define 	DETSRC		0x0A
#define 	MCTL		0x16
#define 	INTRST		0x17
#define 	CTL1		0x18
#define 	PDTH		0x1B
#define 	PW			0x1C
#define 	LT			0x1D
#define 	TW			0x1E

//*********Variables to indicate the obstacle sensor to be checked**********//
#define		OBS_CENTER_L	0
#define		OBS_SIDE_L		1
#define		OBS_CENTER_R	2
#define		OBS_SIDE_R		3

//*********Variables to indicate the accelerometer axes to be checked**********//
#define 	ACCE_CHECK_X	0
#define 	ACCE_CHECK_Y	1
#define 	ACCE_CHECK_Z	2
	
//*********Variables to indicate the line to be checked**********//
#define 	LINE_L			0
#define		LINE_R			1

//*********Variables to check speaker mode**********//
#define		SPEAKER_OFF		0		
#define		SPEAKER_ON		1		
#define 	SPEAKER_TIME	2		


//**************
//*   CODE	   *
//**************
//Internal function
//void 			Delay10TCYx (unsigned char);
//void 			Delay10KTCYx (unsigned char);
void 			ACCE_WRITE(unsigned char, unsigned char);
unsigned char 	ACCE_READ(unsigned char);



//*****************************************************
//*                  SEN_CONFIG()                     *
//*****************************************************
//*Descripción: The function configurates the pic I/Os*
//* 			and the ADC.                          *
//*****************************************************
//*Input variables:                                   *
//*Output variables:                                  * 
//*****************************************************
void SEN_CONFIG(void);


//*****************************************************
//*                  SEN_LIGHT                        *
//*****************************************************
//*		Description:It returns the light percentage   *
//* 		from the light sensor (0-100)             *
//*****************************************************
//*Input variables:                                   *
//*Output variables: -SEN_LIGHT_P                     *
//*****************************************************
unsigned char SEN_LIGHT(void);


//*****************************************************
//*                  SEN_BATTERY                      *		
//*****************************************************
//*Description:It returns the battery level           *
//*****************************************************
//*Input variables:                                   *
//*Output variables: -SEN_BATTERY_P                   *
//*****************************************************

unsigned char SEN_BATTERY(void);


//*****************************************************
//*                  SEN_TEMPERATURE                  *
//*****************************************************
//*Description:It returns the temperature  		      *
//*****************************************************
//*Input variables:                                   *
//*Output variables: -SEN_TEMPERATURE_P               *
//*****************************************************
unsigned char SEN_TEMPERATURE (void);


//*****************************************************
//*                  SEN_MIC_ANALOG                   *		
//*****************************************************
//*			Description:It returns the analog         *
//*				value form the microphone      		  *
//*****************************************************
//*Input variables:                                   *
//*Output variables: -SEN_MIC                         *
//*****************************************************

unsigned char SEN_MIC_ANALOG (void);



//*****************************************************
//*                  SEN_MIC_DIG                      *	
//*****************************************************	
//*			Description:It returns the digital        *
//*				value of the microphone   		  	  *
//*****************************************************
//*Input variables:                                   *
//*Output variables: -SEN_MIC                         *
//*****************************************************

unsigned char SEN_MIC_DIG (void);


//*****************************************************
//*                  SEN_SPEAKER                      *	
//*****************************************************
//* Description:It activates the buzzer to the        * 
//*			indicated time and frequency     		  *
//*****************************************************
//*Input variables:      -SEN_SPEAKER_FREQ            *          
//*					   	 -SEN_SPEAKER_TIME  (100ms)   *                           
//*					   								  *
//*Output variables:                                  *
//*****************************************************
unsigned char SEN_SPEAKER ( unsigned char SEN_SPEAKER_FREQ, unsigned char SEN_SPEAKER_TIME, unsigned char SEN_SPEAKER_ON_OFF);


//*****************************************************
//*               SEN_OBS_ANALOG()                    *
//*****************************************************
//*  Description: It returns if an obstacle has been  *
//*  detected on the right or left side of the Moway. *
//*****************************************************
//*Input variables:     -OBS_SIDE_L                   *
//*						-OBS_CENTRAL_L                *
//*						-OBS_CENTRAL_R	              *			
//*						-OBS_SIDE_R					  *                             
//*Output variables:   -SEN_OBS_CENTER_R              *
//*                     -SEN_OBS_CENTER_L			  *
//*						-SEN_OBS_SIDE_R               *
//*                     -SEN_OBS_SIDE_L               *
//*Output:              -0:External signal detected   *
//                        (Moway or interference)     *
//                      -(1-255):Correct reading      *
//*****************************************************

unsigned char SEN_OBS_ANALOG(unsigned char OBS_TO_CHECK);


unsigned char SEN_OBS_DIG (unsigned char OBS_TO_CHECK);

//*****************************************************
//*                 SEN_ACCE_XYZ_READ                 *
//*****************************************************
//*	   Description: It returns the accelerometer      *
//*					x,y,z value.                      *
//*****************************************************
//*Input variables:     -ACCE_CHECK_X				  *
//*						-ACCE_CHECK_Y				  *
//*						-ACCE_CHECK_Z				  *
//*Output variables:    -SEN_ACCE_X                   *
//*                     -SEN_ACCE_Y                   *
//*                     -SEN_ACCE_Z                   *
//*Output:			   	 					 		  *
//*		 	              -0:Incorrect reading	  	  *
//*                       -(1-255):Correct reading    *
//*****************************************************

unsigned char SEN_ACCE_XYZ_READ(unsigned char ACCE_TO_CHECK);



//;*****************************************************
//;*                 SEN_ACCE_CHECK_TAP          	   *	
//;*****************************************************
//;*Description: It verifies if Moway has beaten on not*
//;*****************************************************
//;*Input variables:                                   *
//;*Output variables: -SEN_ACCE_TAP	                   *
//;*****************************************************
unsigned char SEN_ACCE_CHECK_TAP(void);


//*****************************************************
//*               SEN_LINE_ANALOG()                   *		
//*****************************************************
//*Description: It returns the clarity of the floor.  *
//*It can differenciate colors depending on the       *
//*material.                                          *
//*****************************************************
//*Input variables:     -LINE_R				     	  *
//*						-LINE_L                       *
//*Output variables:    -SEN_LINE_R                   *
//*                     -SEN_LINE_L                   *
//*****************************************************

unsigned char SEN_LINE_ANALOG (unsigned char LINE_TO_CHECK);


//*****************************************************
//*               SEN_LINE_DIG()                      *		
//*****************************************************
//*Description: It returns if it has detected a black * 
//*line in a white floor.                             *
//*****************************************************
//*Input variables:     -LINE_R						  *
//*						-LINE_L                       *                 
//*Output variables:    -SEN_LINE_R                   *
//*                     -SEN_LINE_L                   *
//*****************************************************
unsigned char SEN_LINE_DIG(unsigned char LINE_TO_CHECK);



//*****************************************************
//*                   LED_xx_xx()                     *				
//*****************************************************
//*Description: Functions for the use of the LEDs     *
//*****************************************************
//*Input variables:                                   *
//*Output variables:                                  *
//*****************************************************

//The switch on of the front LED
void LED_FRONT_ON(void);

//The switch off of the front LED
void LED_FRONT_OFF(void);

//The blinking of the front LED
void LED_FRONT_ON_OFF(void);

//The switch on of the brake LED
void LED_BRAKE_ON(void);

//The switch off of the brake LED
void LED_BRAKE_OFF(void);

//The blinking of the brake LED
void LED_BRAKE_ON_OFF(void);

//The switch on of the top red LED
void LED_TOP_RED_ON(void);

//The switch off of the top red LED
void LED_TOP_RED_OFF(void);

//The blinking of the top red LED
void LED_TOP_RED_ON_OFF(void);

//The switch on of the top green LED
void LED_TOP_GREEN_ON(void);

//The switch off of the top green LED
void LED_TOP_GREEN_OFF(void);

//The blinking of the top green LED
void LED_TOP_GREEN_ON_OFF(void);

//*****************************************************

//*****************************************************
//*              ACCE_WRITE(data1, data2)			  *
//*****************************************************
//*		Description:Writting condition to  			  *
//* 	make possible the SPI communication.     	  *
//*****************************************************
void ACCE_WRITE(unsigned char data1, unsigned char data2);

//*****************************************************
//*              ACCE_READ(dato3)			          *
//*****************************************************
//*		Description:Reading condition to 			  *
//* 	make possible the SPI communication.     	  *
//*****************************************************
unsigned char ACCE_READ(unsigned char data);
