#include "i2c_ext.h"		

//*****************************************************
//* Al@Dyn            Config_I2C1()			          *
//*****************************************************
//*		Description:Configuration du port d'extension
//*		en mode I2C         	  
//*****************************************************
void	Config_I2C1(void)
{
    //Configuration du module MSSP
	SSP1STAT=0;
	SSPCON1=0;	// on inhibe le port série

	SDI_SDA_TRIS=1;			//SDA as an input (Logic level 1)
	Delay1TCY();			// un petit delai
	Delay1TCY();
	Delay1TCY();
	SCK_SCL_TRIS=1;			//SCL as an input (Logic level 1)
	Delay1TCY();			// un petit delai
	Delay1TCY();
	Delay1TCY();
}




//*****************************************************
//* Al@Dyn             Start_I2C1()		    	      *
//*****************************************************
//*		Description:START condition for				  *
//*		the beginning of I2C communication         	  *
//*****************************************************
void Start_I2C1 (void)
{
	SDI_SDA_TRIS=1;			//SDA as an input (Logic level 1)
	SCK_SCL_TRIS=1;			//SCL as an input (Logic level 1)
	Delay1TCY();			// un petit delai
	Delay1TCY();
	Delay1TCY();
	SDI_SDA=0;			//SDA is 0 while SCL is high
	SDI_SDA_TRIS=0;			//SDA as an output (Logic level 0)
	Delay1TCY();			// Pour le pic16f88 esclave qui commande le servomoteur
	Delay1TCY();			// il faut un délai plus long
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();	
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();	
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();	
	Delay1TCY();
	SCK_SCL=0;			//SCL is 0
	SCK_SCL_TRIS=0;			//SCL as an output (Logic level 0)
	Delay1TCY();
}
//*****************************************************


//*****************************************************
//* Al@Dyn      char IN_ACK_NACK1()	 	              *
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
char IN_ACK_NACK1 (void)
{
	char res;
	SDI_SDA_TRIS=1;			//SDA as an input (Logic level 1)
	Delay1TCY();
	Delay1TCY();	
	Delay1TCY();
	SCK_SCL_TRIS=1;			//SCL as an input (Logic level 1)
	Delay1TCY();
	Delay1TCY();	
	Delay1TCY();
	if(SDI_SDA)	
		res=1;
	else
		res=0;
	Delay1TCY();
	Delay1TCY();	
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();	
	Delay1TCY();
	SCK_SCL=0;
	SCK_SCL_TRIS=0;	
	return res;		// on sort avec SCL=0 et SDA en haute impédance
}
//*****************************************************

//*****************************************************
//* Al@Dyn            Stop_I2C1()			          *
//*****************************************************
//*		Descriptionn:STOP condition for the			  *
//*		end of I2C communication		          	  *
//*****************************************************
void Stop_I2C1 (void)
{
	SDI_SDA=0;			// pour pouvoir générer un front montant sur SDA
	SDI_SDA_TRIS=0;
	Delay1TCY();
	Delay1TCY();	
	Delay1TCY();
	SCK_SCL_TRIS=1;			//SCL as an input (Logic level 1)
	Delay1TCY();
	Delay1TCY();	
	Delay1TCY();
	SDI_SDA_TRIS=1;			//front montant sur SDA alors que SCL est au niveau haut
	Delay1TCY();
	Delay1TCY();	
	Delay1TCY();
}
//*****************************************************

//*****************************************************
//* Al@Dyn     char Read_I2C1()	 	                  *
//*****************************************************
//*	   Description: It receives a byte creating	  	  *
//*					at the same time the clock in SCL *
//*****************************************************
//*****************************************************
//* 	   BYTE		->	Returns dato2				  *
//*****************************************************
unsigned char Read_I2C1 (void)
{
	int i;
	unsigned char dato2;
	unsigned char masque=0x80;
	SDI_SDA_TRIS=1;			//SDA as an input (Logic level 1)
	for(i=0;i<=7;i++)
	{	
		Delay1TCY();
		Delay1TCY();	
		Delay1TCY();
		SCK_SCL_TRIS=1;			//SCL as an input (Logic level 1)
		Delay1TCY();
		Delay1TCY();
		Delay1TCY();	
		if(SDI_SDA)
			dato2=dato2 | masque;
		else
			dato2=dato2 & (~masque);		// on aurait pu aussi initialiser à 0, mais sans le sinon, le TON de SCL est plus court
											// quand on lit un 0
		Delay1TCY();
		Delay1TCY();
		Delay1TCY();
		SCK_SCL=0;			//SCL is 0
		SCK_SCL_TRIS=0;			//SCL as an output (Logic level 0)	
		masque=masque>>1;		
	}
	return dato2;		// on sort avec SCL=0 et SDA en haute impédance
}
//*****************************************************


//*****************************************************
//* Al@Dyn    Write_I2C1(char)	 	              *
//*****************************************************
//*		Description:It sends a byte creating		  *
//*					at the same time the clock in SCL *
//*****************************************************
//*****************************************************
//* 	   BYTE		->	Sends dato  				  *
//*****************************************************
void Write_I2C1 (unsigned char dato)
{
	// quand on entre dans Write(), SCL est à 0
	// quand on en sort, idem
	unsigned char data_decale=dato;
	int i;
	for(i=0;i<=7;i++)
	{
		if((data_decale & 0b10000000)==0b10000000)
			SDI_SDA_TRIS=1;			//SDA as an input (Logic level 1)
		else
		{
			SDI_SDA=0;			//SDA is 0
			SDI_SDA_TRIS=0;
		}
		Delay1TCY();
		Delay1TCY();
		Delay1TCY();
		SCK_SCL_TRIS=1;				// SCL as input
		data_decale=data_decale<<1;	// positionné ici pour allonger le Ton
		Delay1TCY();	
		Delay1TCY();
		Delay1TCY();
		Delay1TCY();
		Delay1TCY();
		SCK_SCL=0;
		SCK_SCL_TRIS=0;			//SCL as an output (Logic level 0)
		
	}	
}

//*****************************************************

//*****************************************************
//* Al@Dyn  		OUT_ACK1()			              *
//*****************************************************
//*		Description: Creates an ACK signal			  *
//*****************************************************
void OUT_ACK1 (void)
{
	SDI_SDA=0;			//SDA is 0
	SDI_SDA_TRIS=0;			//SDA as an output (Logic level 0)
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	SCK_SCL_TRIS=1;			//SCL as an input (Logic level 1)
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	SCK_SCL=0;
	SCK_SCL_TRIS=0;			//SCL as an output (Logic level 0)
}
//*****************************************************


//*****************************************************
//* Al@Dyn  		OUT_NACK1()			              *
//*****************************************************
//*		Description: Creates a NACK signal 			  *
//*****************************************************
void OUT_NACK1 (void)
{
	SDI_SDA_TRIS=1;			//SDA as an input, suit un appel à read(), donc déja positionné en input
	Delay1TCY();
	SCK_SCL_TRIS=1;			//SCL as an input (Logic level 1)
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	SCK_SCL=0;
	SCK_SCL_TRIS=0;			//SCL as an output (Logic level 0)
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
}

