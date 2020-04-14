#include "port_ext.h" // broches du port d'extension du moway
//***************************************************************
//* Ce fichier contient les prototypes des fonctions permettant :
//* 	- de configurer le port d'extension dans le mode SPI
//*		- d'�crire et de lire un octet
//*****************************************************



//*****************************************************
//*               CONFIG_SPI()                     *
//*****************************************************
//*Descripci�n: La funci�n configura el m�dulo SPI del*
//*microcontrolador.En ella se especifica como salida *
//*SDO y como entrada SDI_SDA entre otros par�metros del  *
//*protocolo SPI.                                     *
//*****************************************************
//*Variables de entrada:                              *
//*Variables de salida:                               *
//*****************************************************
void CONFIG_SPI(void);





//*****************************************************
//*      unsigned char SPI_READ(unsigned char data)            *
//*****************************************************
//*Descripci�n:Saca datos por spi y devuelve          *
//*****************************************************
//*Variables de entrada:- data                        *
//*Variables de salida: -Lectura				      *
//*****************************************************
unsigned char SPI_READ(unsigned char);





//*****************************************************
//*      		  void SPI_WRITE(unsigned char data)           *
//*****************************************************
//*Descripci�n:Saca datos por spi			          *
//*****************************************************
//*Variables de entrada:- data                        *
//*Variables de salida:       						  *
//*****************************************************
void SPI_WRITE(unsigned char);
