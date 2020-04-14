#include "lib_mot_moway.h"		

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
void MOT_CONFIG(void)
{
   SDA_TRIS=1;
   SCL_TRIS=1;
   SDA_SOFT=0;
   SCL_SOFT=0;
   MOT_END_TRIS=1;
}
//*****************************************************



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
unsigned char MOT_STR(unsigned char MOT_VEL,unsigned char FWDBACK,unsigned char COMTYPE, unsigned char MOT_T_DIST)
{
	static unsigned char MOT_COMAND;
  //Verification of the correct data

   //The speed must be a number between 0 and 100
   if(MOT_VEL>100)
   return(2);

   //Preparation of data to be sent by I2C

   //The command to be sent is COM_STR (0x00)

   MOT_COMAND=COM_STR;

   MOT_VEL=MOT_VEL<<1;
   //The direction is packed in the LSB of the speed
   if(FWDBACK)
		MOT_VEL = MOT_VEL | 0b00000001;
   else
		MOT_VEL=MOT_VEL & 0b11111110;

    MOT_COMAND=MOT_COMAND<<2;
   //COMTYPE and RL are sent in the same byte of MOT_COMAND
	if(COMTYPE)
	{	
		MOT_COMAND = MOT_COMAND | 0b00000010;
		MOT_COMAND = MOT_COMAND & 0b11111110;
	}
	else
		MOT_COMAND=MOT_COMAND & 0b11111100;
	

   //Data are sent by I2C
   return(MOT_SND_I2C_3D(MOT_COMAND,MOT_VEL,MOT_T_DIST));
}
//*****************************************************




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
  unsigned char MOT_CHA_VEL(unsigned char MOT_VEL,unsigned char FWDBACK,unsigned char RL,unsigned char COMTYPE,unsigned char MOT_T_DIST)
{
	static unsigned char MOT_COMAND;
   //Verification of the correct data

   //The speed must be a number between 0 and 100
   if(MOT_VEL>100)
   return(2);

   //Preparation of data to be sent by I2C

   //The command to be sent is COM_CHA_VEL (0x01)
   MOT_COMAND=COM_CHA_VEL;

   MOT_VEL=MOT_VEL<<1;
   //The direction is packed in the LSB of the speed
   if(FWDBACK)
		MOT_VEL = MOT_VEL | 0b00000001;
   else
		MOT_VEL=MOT_VEL & 0b11111110;

	MOT_COMAND=MOT_COMAND<<2;
   //COMTYPE and RL are sent in the same byte of MOT_COMAND
 	if(COMTYPE)
	{	
		if(RL)
			MOT_COMAND = MOT_COMAND | 0b00000011;
		else
		{
			MOT_COMAND = MOT_COMAND | 0b00000010;
			MOT_COMAND = MOT_COMAND & 0b11111110;
		}
	}
	else
	{
		if(RL)
		{
			MOT_COMAND = MOT_COMAND & 0b11111101;
			MOT_COMAND = MOT_COMAND | 0b00000001;
		}
		else
			MOT_COMAND = MOT_COMAND & 0b11111100;
	}
		


   //Data are sent by I2C
   return(MOT_SND_I2C_3D(MOT_COMAND,MOT_VEL,MOT_T_DIST));
}
//*****************************************************



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
unsigned char MOT_ROT(unsigned char MOT_VEL,unsigned char FWDBACK,unsigned char MOT_CENWHEEL,unsigned char RL,unsigned char COMTYPE,unsigned char MOT_T_ANG)
{
	static unsigned char MOT_COMAND;
   //Verification of the correct data

   //The speed must be a number between 0 and 100
   if(MOT_VEL>100)
   return(2);

   //Rotation about the center or a wheel
   if( MOT_CENWHEEL!=1 && MOT_CENWHEEL!=0)
   return(2);

   //If it is an angle command it must be a number between 0 and 100
   //If it is not, returns 2 (Wrong data)
   if( COMTYPE==0 && MOT_T_ANG>100)
   return(2);

   //Preparation of data to be sent by I2C

   //The command to be sent is COM_ROT (0x02)
   MOT_COMAND=COM_ROT;

   MOT_VEL=MOT_VEL<<1;
   //The direction is packed in the LSB of the speed
   if(FWDBACK)
		MOT_VEL = MOT_VEL | 0b00000001;
   else
		MOT_VEL=MOT_VEL & 0b11111110;

	MOT_COMAND=MOT_COMAND<<2;
     //COMTYPE and RL are sent in the same byte of MOT_COMAND
   if(COMTYPE)
	{	
		if(RL)
			MOT_COMAND = MOT_COMAND | 0b00000011;
		else
		{
			MOT_COMAND = MOT_COMAND | 0b00000010;
			MOT_COMAND = MOT_COMAND & 0b11111110;
		}
	}
	else
	{
		if(RL)
		{
			MOT_COMAND = MOT_COMAND & 0b11111101;
			MOT_COMAND = MOT_COMAND | 0b00000001;
		}
		else
			MOT_COMAND = MOT_COMAND & 0b11111100;
	}
   //Data are sent by I2C
   return(MOT_SND_I2C_4D(MOT_COMAND,MOT_VEL,MOT_CENWHEEL,MOT_T_ANG));
}
//*****************************************************



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
unsigned char MOT_CUR(unsigned char MOT_VEL,unsigned char FWDBACK,unsigned char MOT_RAD,unsigned char RL,unsigned char COMTYPE, unsigned char MOT_T_DIST)
{
	static unsigned char MOT_COMAND;
   //Verification of the correct data

   //The speed must be a number between 0 and 100
   if(MOT_VEL>100)
   return(2);

   //Speed - radio must be smaller than 100 and smaller than 0
   if((MOT_VEL+MOT_RAD)>100 || (MOT_VEL-MOT_RAD)>156)
   return(2);

   //Preparation of data to be sent by I2C

   //The command to be sent is COM_CUR (0x03)
   MOT_COMAND=COM_CUR;
 
   MOT_VEL=MOT_VEL<<1;
   //The direction is packed in the LSB of the speed
   if(FWDBACK)
		MOT_VEL = MOT_VEL | 0b00000001;
   else
		MOT_VEL=MOT_VEL & 0b11111110;

	MOT_COMAND=MOT_COMAND<<2;
   //COMTYPE and RL are sent in the same byte of MOT_COMAND
   if(COMTYPE)
	{	
		if(RL)
			MOT_COMAND = MOT_COMAND | 0b00000011;
		else
		{
			MOT_COMAND = MOT_COMAND | 0b00000010;
			MOT_COMAND = MOT_COMAND & 0b11111110;
		}
	}
	else
	{
		if(RL)
		{
			MOT_COMAND = MOT_COMAND & 0b11111101;
			MOT_COMAND = MOT_COMAND | 0b00000001;
		}
		else
			MOT_COMAND = MOT_COMAND & 0b11111100;
	}

   //Data are sent by I2C
   return(MOT_SND_I2C_4D(MOT_COMAND,MOT_VEL,MOT_RAD,MOT_T_DIST));
}
//*****************************************************




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
unsigned char MOT_STOP(void)
{
	static unsigned char MOT_COMAND;
  //Preparation of data to be sent by I2C

   //The command to be sent is COM_STOP (0x04)
   MOT_COMAND=COM_STOP;

   MOT_COMAND=MOT_COMAND<<2;
      //COMTYPE and RL are sent in the same byte of MOT_COMAND
   MOT_COMAND = MOT_COMAND & 0b11111100;

   //Data are sent by I2C
   return(MOT_SND_I2C_1D(MOT_COMAND));
}
//*****************************************************





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
unsigned char MOT_RST(unsigned char RST_COM)
{
   RST_COM = RST_COM | 0xF0;
   //Data are sent by I2C
   return(MOT_SND_I2C_1D(RST_COM));
}
//*****************************************************




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

//*****************************************************
unsigned char* MOT_FDBCK(unsigned char STATUS_COM)
{
	  static unsigned char   MOT_ACK;
	  static unsigned char   MOT_SND_OK;
	  static unsigned char  MOT_RE_SND;
	  static unsigned char  MOT_STATUS_DATA[2];
	  STATUS_COM= STATUS_COM | 0b10000000;
       //Data are sent by I2C
      if(MOT_SND_I2C_1D(STATUS_COM)!=0)
      return(&MOT_STATUS_DATA[0]);

      //It is sent the command to read
      MOT_RE_SND=10;
      while(MOT_RE_SND>0){
      while(1){
      Start_I2C2();
	  Write_I2C2(0x11);
      MOT_ACK=IN_ACK_NACK2();
      if (MOT_ACK){
         Stop_I2C2();
         MOT_RE_SND--;
         MOT_SND_OK=1;
         break;
      }

      //First data is read
      MOT_STATUS_DATA[0]=Read_I2C2();
	  OUT_ACK2();
      //Second data is read
      MOT_STATUS_DATA[1]=Read_I2C2();
	  OUT_NACK2();

      Stop_I2C2();
      MOT_RE_SND=0;
      MOT_SND_OK=0;
      break;
      }
   }
   return(&MOT_STATUS_DATA[0]);
}
//*****************************************************


//*****************************************************
//*              Start_I2C2()			              *
//*****************************************************
//*		Description:START condition for				  *
//*		the beginning of I2C communication         	  *
//*****************************************************

void Start_I2C2 (void)
{
	SDA_TRIS=1;			//SDA as an input (Logic level 1)
	SCL_TRIS=1;			//SCL as an input (Logic level 1)
	SDA_SOFT=0;			//SDA is 0 while SCL is high
	SDA_TRIS=0;			//SDA as an output (Logic level 0)
	SCL_SOFT=0;			//SCL is 0
	SCL_TRIS=0;			//SCL as an output (Logic level 0)
}
//*****************************************************


//*****************************************************
//*              unsigned char IN_ACK_NACK2()	 	              *
//*****************************************************
//*		Description: It reads the ACK or NACK from	  *
//*				     the SLAVE. It is not necessary   *
//*					 to configure SDA as an input     *
//*					 (this rutine makes it        	  *
//*					 automatically)   	              *
//*****************************************************
//*****************************************************
//*	ACK				->	Returns 0			  		  *
//*	NACK			->	Returns 1				      *
//*****************************************************
unsigned char IN_ACK_NACK2 (void)
{
	SDA_TRIS=1;			//SDA as an input (Logic level 1)
	SCL_TRIS=1;			//SCL as an input (Logic level 1)
	if(SDA_SOFT)
	{	
		SDA_TRIS=0;			//SDA as an output (Logic level 0)
		SCL_TRIS=0;			//SCL as an output (Logic level 0)
		return 1;		// NACK
	}
	else
	{
		SDA_TRIS=0;			//SDA as an output (Logic level 0)		
		SCL_TRIS=0;			//SCL as an output (Logic level 0)
		return 0;		// ACK
	}
}
//*****************************************************


//*****************************************************
//*              Stop_I2C2()			              *
//*****************************************************
//*		Descriptionn:STOP condition for the			  *
//*		end of I2C communication		          	  *
//*****************************************************

void Stop_I2C2 (void)
{
	SCL_TRIS=1;			//SCL as an input (Logic level 1)
	SDA_TRIS=1;			//SDA as an input (Logic level 1)
}
//*****************************************************


//*****************************************************
//*              unsigned char Read_I2C2()	 	              *
//*****************************************************
//*	   Description: It receives a byte creating	  	  *
//*					at the same time the clock in SCL *
//*****************************************************
//*****************************************************
//* 	   BYTE		->	Returns dato2				  *
//*****************************************************
unsigned char Read_I2C2 (void)
{
	int i;
	unsigned char dato2=0;
	SDA_TRIS=1;			//SDA as an input (Logic level 1)
	for(i=0;i<=7;i++)
	{	
		SCL_TRIS=1;			//SCL as an input (Logic level 1)
		while(SCL_SOFT==0){}
		if(i==0)
		{
			if(SDA_SOFT)
			{	
				dato2 = dato2 | (0b10000000);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
			else
			{
				dato2 = dato2 & (0b01111111);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
		}
		if(i==1)
		{
			if(SDA_SOFT)
			{	
				dato2 = dato2 | (0b01000000);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
			else
			{
				dato2 = dato2 & (0b10111111);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
		}
		if(i==2)
		{
			if(SDA_SOFT)
			{	
				dato2 = dato2 | (0b00100000);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
			else
			{
				dato2 = dato2 & (0b11011111);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
		}
		if(i==3)
		{
			if(SDA_SOFT)
			{	
				dato2 = dato2 | (0b00010000);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
			else
			{
				dato2 = dato2 & (0b11101111);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
		}
		if(i==4)
		{
			if(SDA_SOFT)
			{	
				dato2 = dato2 | (0b00001000);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
			else
			{
				dato2 = dato2 & (0b11110111);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
		}
		if(i==5)
		{
			if(SDA_SOFT)
			{	
				dato2 = dato2 | (0b00000100);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
			else
			{
				dato2 = dato2 & (0b11111011);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}

		}	
		if(i==6)
		{
			if(SDA_SOFT)
			{	
				dato2 = dato2 | (0b00000010);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
			else
			{
				dato2 = dato2 & (0b11111101);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
		}
		if(i==7)
		{
			if(SDA_SOFT)
			{	
				dato2 = dato2 | (0b00000001);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
			else
			{
				dato2 = dato2 & (0b11111110);
				SCL_SOFT=0;			//SCL is 0
				SCL_TRIS=0;			//SCL as an output (Logic level 0)
			
			}
		
		}
		
	}

	SDA_SOFT=0;			//SDA is 0
	SDA_TRIS=0;			//SDA as an output (Logic level 0)
	return dato2;
}
//*****************************************************


//*****************************************************
//*              Write_I2C2(unsigned char)	 	              *
//*****************************************************
//*		Description:It sends a byte creating		  *
//*					at the same time the clock in SCL *
//*****************************************************
//*****************************************************
//* 	   BYTE		->	Sends dato  				  *
//*****************************************************
void Write_I2C2 (auto unsigned char dato)
{
	
	int i;
	for(i=0;i<=7;i++)
	{
		if(((dato<<i) | 0b01111111)==0b11111111)
		{
			
			SDA_TRIS=1;			//SDA as an input (Logic level 1)
			SCL_TRIS=1;			//SCL as an input (Logic level 1)
			Delay1TCY();
			Delay1TCY();
			Delay1TCY();
			Delay1TCY();	
			Delay1TCY();
			Delay1TCY();
			SCL_TRIS=0;			//SCL as an output (Logic level 0)
			Delay1TCY();
			Delay1TCY();
			Delay1TCY();
			Delay1TCY();	
			Delay1TCY();
			Delay1TCY();
		}	
		else
		{
			SDA_SOFT=0;			//SDA is 0
			SDA_TRIS=0;			//SDA as an output (Logic level 0)			
			SCL_TRIS=1;			//SCL as an input (Logic level 1)
			Delay1TCY();
			Delay1TCY();
			Delay1TCY();
			Delay1TCY();	
			Delay1TCY();
			Delay1TCY();
			SCL_TRIS=0;			//SCL as an output (Logic level 0)
			Delay1TCY();
			Delay1TCY();
			Delay1TCY();
			Delay1TCY();	
			Delay1TCY();
			Delay1TCY();
		
		}	
	}
}
//*****************************************************


//*****************************************************
//*            		OUT_ACK2()			              *
//*****************************************************
//*		Description: Creates an ACK signal			  *
//*****************************************************

void OUT_ACK2 (void)
{
	SDA_SOFT=0;			//SDA is 0
	SDA_TRIS=0;			//SDA as an output (Logic level 0)
	SCL_TRIS=1;			//SCL as an input (Logic level 1)
	SCL_TRIS=0;			//SCL as an output (Logic level 0)
	SDA_TRIS=1;			//SCL as an input (Logic level 1)
}
//*****************************************************


//*****************************************************
//*            		OUT_NACK2()			              *
//*****************************************************
//*		Description: Creates a NACK signal 			  *
//*****************************************************


void OUT_NACK2 (void)
{
	SDA_TRIS=1;			//SDA as an input (Logic level 1)
	SCL_TRIS=1;			//SCL as an input (Logic level 1)
	SCL_TRIS=0;			//SCL as an output (Logic level 0)
	SDA_TRIS=1;			//SDA as an input (Logic level 1)
}
//*****************************************************



//*****************************************************
//*              MOT_SND_I2C_1D(unsigned char )                *
//*****************************************************
//*Description:Low level I2C communication function	  *
//*inunsigned charged of sending an only data.            	  *
//*****************************************************
//*Input variables:		- Data to be sent             *
//*Output variables:    ----------------------------- *
//*Output:	            - 0: Correct sending          *
//*                     - 1: Wrong sending	          *
//*****************************************************

unsigned char MOT_SND_I2C_1D(unsigned char MOT_DATA_0) 
{
	static unsigned char   MOT_ACK;
	static unsigned char   MOT_SND_OK;
	static unsigned char  MOT_RE_SND;
   MOT_RE_SND=10;

   while(MOT_RE_SND>0){
      while(1){
      Start_I2C2();
      Write_I2C2(MOT_DIR);
	  MOT_ACK=IN_ACK_NACK2();
      if (MOT_ACK){
         Stop_I2C2();
         MOT_RE_SND--;
         MOT_SND_OK=1;
         break;
         }
	  Write_I2C2(MOT_DATA_0);
      MOT_ACK=IN_ACK_NACK2();
      if (MOT_ACK){
         Stop_I2C2();
         MOT_RE_SND--;
         MOT_SND_OK=1;
         break;
         }
      Stop_I2C2();
      MOT_RE_SND=0;
      MOT_SND_OK=0;
      break;
      }
   }
   return(MOT_SND_OK);
}
//*****************************************************


//*****************************************************
//*       MOT_SND_I2C_3D(unsigned char, unsigned char, unsigned char)            *
//*****************************************************
//*Description:Low level I2C communication function	  *
//*inunsigned charged of sending three data.            	  	  *
//*****************************************************
//*Input variables:		- Data to be sent             *
//*Output variables:    ----------------------------- *
//*Output:	            - 0: Correct sending          *
//*                     - 1: Wrong sending	          *
//*****************************************************
unsigned char MOT_SND_I2C_3D(unsigned char MOT_DATA_0,unsigned char MOT_DATA_1,unsigned char MOT_DATA_2)
{
	static unsigned char   MOT_ACK;
	static unsigned char   MOT_SND_OK;
	static unsigned char  MOT_RE_SND;
   MOT_RE_SND=10;

   while(MOT_RE_SND>0){
      while(1){
      Start_I2C2();
	  Write_I2C2(0x10);
      MOT_ACK=IN_ACK_NACK2();
      if (MOT_ACK){
         Stop_I2C2();
         MOT_RE_SND--;
         MOT_SND_OK=1;
         break;
         }
      Write_I2C2(MOT_DATA_0);
      MOT_ACK=IN_ACK_NACK2();
      if (MOT_ACK){
         Stop_I2C2();
         MOT_RE_SND--;
         MOT_SND_OK=1;
         break;
         }
      Write_I2C2(MOT_DATA_1);
      MOT_ACK=IN_ACK_NACK2();
      if (MOT_ACK){
         Stop_I2C2();
         MOT_RE_SND--;
         MOT_SND_OK=1;
         break;
         }
      Write_I2C2(MOT_DATA_2);
      MOT_ACK=IN_ACK_NACK2();
      if (MOT_ACK){
         Stop_I2C2();
         MOT_RE_SND--;
         MOT_SND_OK=1;
         break;
         }
      Stop_I2C2();
      MOT_RE_SND=0;
      MOT_SND_OK=0;
      break;
      }
   }
   return(MOT_SND_OK);
}
//*****************************************************







//*****************************************************
//*     MOT_SND_I2C_4D(int8, int8, int8, int8)        *
//*****************************************************
//*Description:Low level I2C communication function	  *
//*inunsigned charged of sending four data.           *
//*****************************************************
//*Input variables:		- Data to be sent             *
//*Output variables:    ----------------------------- *
//*Output:              - 0: Correct sending          *
//*                     - 1: Wrong sending	          *
//*****************************************************

unsigned char MOT_SND_I2C_4D(unsigned char MOT_DATA_0,unsigned char MOT_DATA_1,unsigned char MOT_DATA_2, unsigned char MOT_DATA_3)
{
	static unsigned char   MOT_ACK;
	static unsigned char   MOT_SND_OK;
	static unsigned char  MOT_RE_SND;
   MOT_RE_SND=10;

   while(MOT_RE_SND>0){							
      while(1){
      Start_I2C2();
      Write_I2C2(MOT_DIR);
      MOT_ACK=IN_ACK_NACK2();
      if (MOT_ACK){
         Stop_I2C2();
         MOT_RE_SND--;
         MOT_SND_OK=1;
         break;
         }
      Write_I2C2(MOT_DATA_0);
      MOT_ACK=IN_ACK_NACK2();
      if (MOT_ACK){
         Stop_I2C2();
         MOT_RE_SND--;
         MOT_SND_OK=1;
         break;
         }
      Write_I2C2(MOT_DATA_1);
      MOT_ACK=IN_ACK_NACK2();
      if (MOT_ACK){
         Stop_I2C2();
         MOT_RE_SND--;
         MOT_SND_OK=1;
         break;
         }
      Write_I2C2(MOT_DATA_2);
      MOT_ACK=IN_ACK_NACK2();
      if (MOT_ACK){
         Stop_I2C2();
         MOT_RE_SND--;
         MOT_SND_OK=1;
         break;
         }
      Write_I2C2(MOT_DATA_3);
      MOT_ACK=IN_ACK_NACK2();
      if (MOT_ACK){
         Stop_I2C2();
         MOT_RE_SND--;
         MOT_SND_OK=1;
         break;
         }
      Stop_I2C2();
      MOT_RE_SND=0;
      MOT_SND_OK=0;
      break;
      }
   }
   return(MOT_SND_OK);
}
//*****************************************************




