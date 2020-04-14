//********************************************************************************
//*    lib_mot_moway.h                                                           *
//*    version: 2.0                                                              *
//*    Functions to control mOway´s engines                                                 *
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

#include <delays.h> //fichier qui inclut le fichier p18f86j50.h
//********************
//*   DEFINITIONS   *
//********************
//*************************PORTE****************************//
#define SDA_SOFT      PORTEbits.RE1				//  PIN_E1
#define SCL_SOFT      PORTEbits.RE0				//	PIN_E0
#define MOT_END       PORTEbits.RE7				//	PIN_E7

//*************************TRISE***************************//
#define SCL_TRIS      TRISEbits.TRISE0			//	TRISE,0
#define SDA_TRIS      TRISEbits.TRISE1			//	TRISE,1
#define MOT_END_TRIS  TRISEbits.TRISE7			//	TRISE,7


//Engine module adress

#define   MOT_DIR         0x10

//Comands
//Byte MOT_COMAND                nºbit    7   6   5   4   3   2   1   0
//                                       --------------------------------
//Movement commands
#define   COM_STR         0x00   //      "0   0   0   0   0   0   CT  RL"
#define   COM_CHA_VEL     0x01   //      "0   0   0   0   0   1   CT  RL"
#define   COM_ROT         0x02   //      "0   0   0   0   1   0   CT  RL"
#define   COM_CUR         0x03   //      "0   0   0   0   1   1   CT  RL"
#define   COM_STOP        0x04   //      "0   0   0   1   0   0   CT  RL"

//Information commands
#define   STATUS_T        0x00   //      "1   0   0   0   0   0   0   0 "
#define   STATUS_A        0x01   //      "1   0   0   0   0   0   0   1 "
#define   STATUS_V_R      0x02   //      "1   0   0   0   0   0   1   0 "
#define   STATUS_V_L      0x03   //      "1   0   0   0   0   0   1   1 "
#define   STATUS_D_R      0x04   //      "1   0   0   0   0   1   0   0 "
#define   STATUS_D_L      0x05   //      "1   0   0   0   0   1   0   1 "
#define   STATUS_KM       0x06   //      "1   0   0   0   0   1   1   0 "

//Reset commands
#define   RST_T           0x00   //      "1   1   1   1   0   0   0   0 "
#define   RST_D           0x01   //      "1   1   1   1   0   0   0   1 "
#define   RST_KM          0x02   //      "1   1   1   1   0   0   1   0 "


//Parameters
#define   RIGHT           1
#define   LEFT            0

#define   DISTANCE        0
#define   TIME            1
#define   ANGLE           0

#define   FWD             1
#define   BACK            0

#define   CENTER          1
#define   WHEEL           0


//**************
//*   CODE	   *
//**************
//Internal functions
void 		 Start_I2C2 (void);
unsigned char 		 IN_ACK_NACK2 (void);
void 		 Stop_I2C2 (void);
unsigned char 		 Read_I2C2 (void);
void 		 Write_I2C2 (auto unsigned char);
void 		 OUT_ACK2 (void);
void 		 OUT_NACK2 (void);
unsigned char 		 MOT_SND_I2C_1D(unsigned char);
unsigned char 		 MOT_SND_I2C_3D(unsigned char,unsigned char,unsigned char);
unsigned char		 MOT_SND_I2C_4D(unsigned char,unsigned char,unsigned char,unsigned char);
//*****************************************************
//*                   MOT_CONFIG()                    *
//*****************************************************
//*Description:This function is inunsigned charged of the      *
//*configuration for the PIC to make possible the     *
//*communication with the engine module.		      * 
//*****************************************************
//*Input variables:    								  *
//*Output variables:   							      *
//*****************************************************
void MOT_CONFIG(void);


//*****************************************************
//*        MOT_STR(unsigned char, unsigned char, unsigned char, unsigned char)            *
//*****************************************************
//*Description: Command to make Moway walk straight   *
//*on. It is necessary to specify the speed,          *
//*the direction, the kind of command and the time or *
//*the distance.							  		  *
//*****************************************************
//*Input variables:		- MOT_VEL    : 0    - 100     *
//*                     - FWDBACK    : FWD  - BACK    *
//*                     - COMTYPE    : TIME - DISTANCE*
//*                     - MOT_T_DIST : 0    - 255     *
//*Output variables:    ----------------------------- *
//*Output:	            - 0: Correct sending          *
//*                     - 1: Wrong sending		      *
//*                     - 2: Wrong data               *
//*****************************************************
unsigned char MOT_STR(unsigned char MOT_VEL,unsigned char FWDBACK,unsigned char COMTYPE, unsigned char MOT_T_DIST);

//*****************************************************
//*     MOT_CHA_VEL(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char)     *
//*****************************************************
//*Description: Command to make the Moway change the  *
//*speed of one of the engines. It is necessary to    *
//*specify the speed, the direction, if it is the     *
//*right or the left engine the one to be changed,    *
//*the kind of command and the time or the distance.  *
//*****************************************************
//*Input variables:     - MOT_VEL    : 0    - 100     *
//*                     - FWDBACK    : FWD  - BACK    *
//*                     - RL         : RIGHT- LEFT    *
//*                     - COMTYPE    : TIME - DISTANCE*
//*                     - MOT_T_DIST : 0    - 255     *
//*Output variables:    ----------------------------- *
//*Output:	            - 0: Correct sending          *
//*                     - 1: Wrong sending            *
//*                     - 2: Wrong data               *
//*****************************************************
unsigned char MOT_CHA_VEL(unsigned char MOT_VEL,unsigned char FWDBACK,unsigned char RL,unsigned char COMTYPE,unsigned char MOT_T_DIST);


//*****************************************************
//*     MOT_ROT(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char)   *  
//*****************************************************
//*Description: Command to make Moway rotate. It is   *
//*necessary to specify the speed, the direction, if  *
//*the rotation is about the center or a wheel, the   *
//*kind of command and the time or the angle.         *
//*****************************************************
//*Input variables:		- MOT_VEL     : 0     - 100   *
//*                     - FWDBACK     : FWD   - BACK  *
//*                     - MOT_CENWHEEL: CENTER- WHEEL *
//*                     - RL          : RIGHT - LEFT  *
//*                     - COMTYPE     : TIME  - ANGLE *
//*                     - MOT_T_ANG   :(0-255)-(0-100)*
//*Output variables:    ----------------------------- *
//*Output:              - 0: Correct sending          *
//*                     - 1: Wrong sending	          *
//*                     - 2: Wrong data		          *
//*****************************************************
unsigned char MOT_ROT(unsigned char MOT_VEL,unsigned char FWDBACK,unsigned char MOT_CENWHEEL,unsigned char RL,unsigned char COMTYPE,unsigned char MOT_T_ANG);




//*****************************************************
//*     MOT_CUR(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char)   *
//*****************************************************
//*Description: Command for curves. It is necessary	  *
//*to specify the speed, the direction, the radio,    *
//*if the curve is to the left or to the right, the   *
//*kind of command and the time or the distance.   	  *
//*****************************************************
//*Input variables:		- MOT_VEL : 0     - 100       *
//*                     - FWDBACK : FWD   - BACK      *
//*                     - MOT_RAD :                   *
//*                        - 0<(MOT_VEL-MOT_RAD)<100  *
//*                     - RL      : RIGHT- LEFT       *
//*                     - COMTYPE : TIME - DISTANCE   *
//*                     - MOT_T_DIST  : 0    - 255    *
//*Output variables:    ----------------------------- *
//*Output:	            - 0: Correct sending          *
//*                     - 1: Wrong sending        	  *
//*                     - 2: Wrong data		          *
//*****************************************************
unsigned char MOT_CUR(unsigned char MOT_VEL,unsigned char FWDBACK,unsigned char MOT_RAD,unsigned char RL,unsigned char COMTYPE, unsigned char MOT_T_DIST);



//*****************************************************
//*                    MOT_STOP()                     *
//*****************************************************
//*Description: Command to make Moway stop.           *
//*****************************************************
//*Input variables:     							  *
//*Output variables:     							  *
//*Output:              - 0: Correct sending          *
//*                     - 1: Wrong sending            *
//*                     - 2: Wrong data               *
//*****************************************************
unsigned char MOT_STOP(void);





//*****************************************************
//*                  MOT_RST(unsigned char)                    *
//*****************************************************
//*Description: Command to reset the time,            *
//*distance or the speedometer.                       *
//*****************************************************
//*Input variables:         -RST_COM:                 *
//*                         -RST_T                    *
//*                         -RST_D                    *
//*                         -RST_KM                   *
//*Output variables:                                  *
//*              		- 0: Correct sending          *
//*                     - 1: Wrong sending            *
//*****************************************************
unsigned char MOT_RST(unsigned char RST_COM);


//*****************************************************
//*                 MOT_FDBCK(unsigned char)                  *
//*****************************************************
//*Description: Command to know several parameters    *
//*from the engine module: the time, the walked angle,*
//*the speed of the two engines, the walked distance  *
//*and the speedometer value (2 output variables).    *
//*****************************************************
//*Input variables:			-STATUS_COM:              *
//*                         -STATUS_T                 *
//*                         -STATUS_A                 *
//*                         -STATUS_V_R               *
//*                         -STATUS_V_L               *
//*                         -STATUS_D_R               *
//*                         -STATUS_D_L               *
//*                         -STATUS_KM                *
//*Output variables:        					      *
//*Salida:              - Pointer to 2 unsigned char			  *
//*****************************************************
unsigned char* MOT_FDBCK(unsigned char STATUS_COM);



//*****************************************************
//*             MOT_DISTANCE_PARCOURUE()                 
//*****************************************************
//* Renvoie la distance parcourue depuis le derner appel
//* à MOT_RST(RST_KM)
//* utilise la fonction MOT_FDBCK() 
//*****************************************************
//*Input variables:							          *
//*Output variables:       la distance sur 16 bits	  *
//*****************************************************
unsigned short int MOT_DISTANCE_PARCOURUE();


//*****************************************************
//*     MOT_LONGUE_DISTANCE(unsigned char,unsigned char,unsigned short int)                 
//*****************************************************
//* Commande le déplacement du robot en ligne droite 
//* sur une distance D exprimée en mm à la vitesse VIT
//* Attention : le compteur de distance totale parcourue est modifié
//*****************************************************
//*Input variables:			D : 0 - 65535
//*							SENS : FWD ou BACK
//*							VIT : 0 - 100
//*Output variables:        
//*****************************************************
void MOT_LONGUE_DISTANCE (unsigned char VIT,unsigned char SENS,unsigned short int D);

