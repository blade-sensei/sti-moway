#include "spi_ext.h"		

//*****************************************************
//*               CONFIG_SPI()                        *
//*****************************************************
//*Descripción: La función configura el módulo SPI del*
//*microcontrolador.En ella se especifica como salida *
//*SDO y como entrada SDI_SDA entre otros parámetros  *
//*del protocolo SPI.                                 *
//*****************************************************
//*Variables de entrada:                              *
//*Variables de salida:                               *
//*****************************************************
void CONFIG_SPI(void)
{
   //Configuration de E/S (0 = Sortie)
   
   SCK_SCL_TRIS=0;
   SDI_SDA_TRIS=1;
   SDO_TRIS=0;
   CS_EXT_TRIS=0;
   CE_EXT_TRIS=0;
   RF_IRQ_TRIS=1;

	//Configuración del módulo SPI
	SSP1STAT=0b11000000;
	SSPCON1=0b00100000;
	SSPCON2=0b00000000;
}

//*****************************************************
//*      void SPI_WRITE(unsigned char data)           *
//*****************************************************
//*Descripción:Saca datos por spi			          *
//*****************************************************
//*Variables de entrada:- data                        *
//*Variables de salida:       						  *
//*****************************************************
void SPI_WRITE(unsigned char data)
{
	SSP1BUF=data;		//Load send data
	while(SSP1STATbits.BF!=1)	{};	//wait
}

//*****************************************************
//*      unsigned char SPI_READ(unsigned char data)            *
//*****************************************************
//*Descripción:Saca datos por spi y devuelve          *
//*****************************************************
//*Variables de entrada:- data                        *
//*Variables de salida: -Lectura				      *
//*****************************************************
unsigned char SPI_READ(unsigned char data)
{
	SSP1BUF=data;					//Load send data
	while(SSP1STATbits.BF!=1)	{};	//wait
	return(SSP1BUF);
}

