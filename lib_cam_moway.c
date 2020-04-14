#include "lib_cam_moway.h"		


//*****************
//*   VARIABLES   *
//*****************
volatile unsigned char CAM_STAT=0;	// Camera status

//**************
//*   CODE	   *
//**************


//*****************************************************
//*               	CAM_INIT()          		      *
//*****************************************************
//*Description: inits camera board				 *
//*****************************************************
//*Input variables:       		                      *
//*Input variables:                               	  *
//*****************************************************
void CAM_INIT (void)
{	
	// Camera board I/O configuration: 0b 1100 0000  1->Input, 0->Output
	CAM_SEND_COM (COM_WR,IODIR_ADD,0xC0);
	
	// Outputs low level (0x00)
	CAM_SEND_COM (COM_WR,OLAT_ADD,0x00);
	
	//Camera off
	CAM_STAT=0;
}


//*****************************************************
//*               	CAM_ON ()  	         		      *
//*****************************************************
//*Description: Turns on camera                       *
//*****************************************************
//*Input variables:       		                      *
//*Input variables:                                   *
//*****************************************************
void CAM_ON (void)
{
	char i;
	// Camera on
	CAM_SEND_COM (COM_WR, OLAT_ADD, 0x02);
	
	//Camera status: on
	CAM_STAT=1;
	
	//Led blink
	for(i=0;i<10;i++)
	{
		CAM_SEND_COM (COM_WR, OLAT_ADD, 0x22);
		Delay1KTCYx (50);
		CAM_SEND_COM (COM_WR, OLAT_ADD, 0x02);
		Delay1KTCYx (50);
	}
	//Led on
	CAM_SEND_COM (COM_WR, OLAT_ADD, 0x22);
}


//*****************************************************
//*               	CAM_OFF () 	         		      *
//*****************************************************
//*Description: Turns off camera                      *
//*****************************************************
//*Input variables:       		                      *
//*Input variables:                                   *
//*****************************************************
void CAM_OFF (void)
{
	// Camera off
	CAM_SEND_COM (COM_WR, OLAT_ADD, 0x00);
	
	//Camera status: off
	CAM_STAT=0;
}

//*****************************************************
//*               CAM_CHN_SEL ()	         		  *
//*****************************************************
//*Description: Channel selection                  	  *
//*****************************************************
//*Input variables:       	channel             	  *
//*Input variables:  	                              *
//*****************************************************
void CAM_CHN_SEL (unsigned char channel)
{
	switch(channel)
	{
		case 1:
			// CH1 pin output, others input (high impedance)
			CAM_SEND_COM (COM_WR, IODIR_ADD, 0xD8);
			
			//Check camera status
			if(CAM_STAT==1)
				// Camera on
				CAM_SEND_COM (COM_WR, OLAT_ADD, 0x22);
			else
				// Camera off
				CAM_SEND_COM (COM_WR, OLAT_ADD, 0x00);
			break;
			
		case 2:
			// CH2 pin output, others input
			CAM_SEND_COM (COM_WR, IODIR_ADD, 0xD4);
			
			//Check camera status
			if(CAM_STAT==1)
				// Camera on
				CAM_SEND_COM (COM_WR, OLAT_ADD, 0x22);
			else
				// Camera off
				CAM_SEND_COM (COM_WR, OLAT_ADD, 0x00);
			break;
		
		case 3:
			// CH3 pin output, others input
			CAM_SEND_COM (COM_WR, IODIR_ADD, 0xCC);
			
			//Check camera status
			if(CAM_STAT==1)
				// Camera on
				CAM_SEND_COM (COM_WR, OLAT_ADD, 0x22);
			else
				// Camera off
				CAM_SEND_COM (COM_WR, OLAT_ADD, 0x00);
			break;
			
		case 4:
			// CH4 all input
			CAM_SEND_COM (COM_WR, IODIR_ADD, 0xDC);
			
			//Check camera status
			if(CAM_STAT==1)
				// Camera on
				CAM_SEND_COM (COM_WR, OLAT_ADD, 0x22);
			else
				// Camera off
				CAM_SEND_COM (COM_WR, OLAT_ADD, 0x00);
			break;
	}
}


//Private functions


//*****************************************************
//*              CAM_SEND_COM (  )                    * 
//*****************************************************
//*Description: Sends SPI frame                       *
//*****************************************************
//*Input variables:		     command, address, data   *
//*Output variables:                                  *
//*****************************************************
void CAM_SEND_COM (unsigned char command, unsigned char address, unsigned char data)
{
	CS_EXT = 0;
	Delay10KTCYx (1);
	CS_EXT = 1;
	SPI_WRITE (command);
	SPI_WRITE (address);
	SPI_WRITE (data);
	CS_EXT = 0;
}
//*****************************************************


