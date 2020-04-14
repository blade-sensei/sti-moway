#include "port_ext.h" // broches du port d'extension du moway
//***************************************************************
//* Ce fichier contient les prototypes des fonctions permettant :
//* 	- de configurer le port d'extension dans le mode I2C
//*		- de gérer la liaison I2C coté Maître
//*****************************************************


//*****************************************************
//* M.CHAINE             Config_I2C1()			      *
//*****************************************************
//*		Description:Configuration du port d'extension
//*		en mode I2C         	  
//*****************************************************
void	Config_I2C1(void);


//*****************************************************
//* M.CHAINE             Start_I2C1()			      *
//*****************************************************
//*		Description:START condition for				  *
//*		the beginning of I2C communication         	  *
//*****************************************************
void 	Start_I2C1 (void);


//*****************************************************
//*              char IN_ACK_NACK1()	 	          *
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
char 	IN_ACK_NACK1 (void);

//*****************************************************
//* M.CHAINE             Stop_I2C1()			      *
//*****************************************************
//*		Descriptionn:STOP condition for the			  *
//*		end of I2C communication		          	  *
//*****************************************************
void 	Stop_I2C1 (void);

//*****************************************************
//* M.CHAINE      char Read_I2C1()	 	              *
//*****************************************************
//*	   Description: It receives a byte creating	  	  *
//*					at the same time the clock in SCL *
//*****************************************************
//*****************************************************
//* 	   BYTE		->	Returns dato2				  *
//*****************************************************
unsigned char 	Read_I2C1 (void);

//*****************************************************
//* M.CHAINE     Write_I2C1(char)	 	              *
//*****************************************************
//*		Description:It sends a byte creating		  *
//*					at the same time the clock in SCL *
//*****************************************************
//*****************************************************
//* 	   BYTE		->	Sends dato  				  *
//*****************************************************
void 	Write_I2C1 (unsigned char);

//*****************************************************
//* M.CHAINE   		OUT_ACK1()			              *
//*****************************************************
//*		Description: Creates an ACK signal			  *
//*****************************************************
void 	OUT_ACK1 (void);

//*****************************************************
//* M.CHAINE   		OUT_NACK1()			              *
//*****************************************************
//*		Description: Creates a NACK signal 			  *
//*****************************************************
void 	OUT_NACK1 (void);


