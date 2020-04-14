//********************************************************************************************
//*                          Programme de mise en oeuvre du MOWAY                            *
//********************************************************************************************
//*                                                                                          *
//********************************************************************************************
//*    This program is free software; you can redistribute it and/or modify                  *
//*    it under the terms of the GNU General Public License as published by                  *
//*    the Free Software Foundation; either version 2 of the License, or                     *
//*    (at your option) any later version.                                                   *
//*                                                                                          *
//*    This program is distributed in the hope that it will be useful,                       *
//*    but WITHOUT ANY WARRANTY; without even the implied warranty of                        *
//*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                         *
//*    GNU General Public License for more details.                                          *
//*                                                                                          *
//*    You should have received a copy of the GNU General Public License along               *
//*    with this program; if not, write to the Free Software Foundation, Inc.,               *
//*    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.                           *
//********************************************************************************************
// Fecha: 14/03/2011
//*********************************************************************************************

//#include "p18f86j50.h"  		//Microcontrolador de Moway


#include "port_ext.h"
#include "i2c_ext.h"
#include "spi_ext.h"

#include "lib_rf2gh4.h"			//Librería de rf
#include "lib_cam_moway.h"		//Librería de cam
#include "lib_mot_moway.h"		//Librería de motores
#include "lib_sen_moway.h"		//Librería de sensores

//****************************************************************************************************************//
// SALTO DEL BOOTLOADER
//****************************************************************************************************************//
#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018

void YourHighPriorityISRCode();
void YourLowPriorityISRCode();

	unsigned char data_in[8];
	unsigned char data_in_dir;
	
extern void _startup (void);     
#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
void _reset (void){
    _asm goto _startup _endasm
}
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
void Remapped_High_ISR (void)	{
     _asm goto YourHighPriorityISRCode _endasm
}
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
void Remapped_Low_ISR (void){
     _asm goto YourLowPriorityISRCode _endasm
}
	
#pragma code
	
#pragma interrupt YourHighPriorityISRCode
void YourHighPriorityISRCode()	{
	RF_RECEIVE(&data_in_dir,data_in);
}	

#pragma interruptlow YourLowPriorityISRCode
void YourLowPriorityISRCode()	{

}	

#pragma code


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
//																 //
//                          FONCTIONS                            //
//																 //
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

// Pour mémoire, voici deux fonctions existantes
// pour les temporisations: 
//   						- Delay10KTCYx(nbre de dizaine de ms) 
//          				- Delay10TCYx (nbre de dizaine de us)

//*****************************************************
//*     PAUSE_SECONDE(unsigned char)            
//*****************************************************
//* Attente d'un certain nombre de secondes
//*****************************************************
//*Input variables:			nb_secondes : 0 - 255
//*Output variables:        
//*****************************************************

void PAUSE_SECONDE(unsigned char nb_secondes)
{
	unsigned char i;
	for (i=0;i<nb_secondes;i++)
	{
		Delay10KTCYx (100);		//pause de 1 seconde
	}
}

//*****************************************************
//*             MOT_DISTANCE_PARCOURUE()                 
//*****************************************************
//* Renvoie la distance parcourue en mm depuis le 
//* dernier appel de MOT_RST(RST_KM)
//* utilise la fonction MOT_FDBCK() 
//*****************************************************
//*Input variables:							          *
//*Output variables:  la distance en mm sur 16 bits	  *
//*****************************************************
unsigned short int MOT_DISTANCE_PARCOURUE()
{
	unsigned char *ptr_distance;
	unsigned char valH, valL;
	unsigned short int distance;

    // Lecture de la distance
	ptr_distance=MOT_FDBCK(STATUS_KM);  
	valH=*(ptr_distance+1); // MSB de la distance
	valL=*(ptr_distance+0); // LSB de la distance
	
    // Concaténation	
	distance=valH;  
	distance = distance<<8;
	distance = distance | valL;
	return distance;
}


//--------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------//
//																						//
//					P R O G R A M M E			P R I N C I P A L						//
//																						//
//--------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------//

void main()
{
}