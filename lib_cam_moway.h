//********************************************************************************
//*    lib_cam_moway.h                                                         	 *
//*    version: 1.0                                                              *
//*    This library written in C18 and contains the functions to manage	 		 * 
//*    the Moway Camera Board                   							     *
//*    Copyright (C) 2011  Bizintek Innova S.L.                                  *
//********************************************************************************
//*    This program is free software; you can redistribute it and/or modify      *
//*    it under the terms of the GNU General Public License as published by      *
//*    the Free Software Foundation; either version 2 of the License, or         *
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
#include "spi_ext.h"	// Utilise le Port d'extension en mode SPI	

//*******************************************
//		DEFINES FOR MCP23S08 REGISTERS
//*******************************************
// Write opcode
#define COM_WR			0x40
#define COM_RD			0x41

// Registro IODIR
#define IODIR_ADD		0x00

// Registro OLAT
#define OLAT_ADD		0x0A


//*****************************************************
//*               	CAM_INIT()          		      *
//*****************************************************
//*Description: inits camera board				 *
//*****************************************************
//*Input variables:       		                      *
//*Input variables:                               	  *
//*****************************************************
void CAM_INIT (void);


//*****************************************************
//*               	CAM_ON ()  	         		      *
//*****************************************************
//*Description: Turns on camera                       *
//*****************************************************
//*Input variables:       		                      *
//*Input variables:                                   *
//*****************************************************
void CAM_ON (void);



//*****************************************************
//*               	CAM_OFF () 	         		      *
//*****************************************************
//*Description: Turns off camera                      *
//*****************************************************
//*Input variables:       		                      *
//*Input variables:                                   *
//*****************************************************
void CAM_OFF (void);


//*****************************************************
//*               CAM_CHN_SEL ()	         		  *
//*****************************************************
//*Description: Channel selection                  	  *
//*****************************************************
//*Input variables:       	channel             	  *
//*Input variables:  	                              *
//*****************************************************
void CAM_CHN_SEL (unsigned char channel);




//Private functions

//*****************************************************
//*              CAM_SEND_COM (  )                    * 
//*****************************************************
//*Description: Sends SPI frame                       *
//*****************************************************
//*Input variables:		     command, address, data   *
//*Output variables:                                  *
//*****************************************************
void CAM_SEND_COM (unsigned char command, unsigned char address, unsigned char data);






