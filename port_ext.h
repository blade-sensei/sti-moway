#include <delays.h>		//fichier qui inclut le fichier p18f86j50.h
//*************************************************************
//*   Définitions des broches du port d'extension du moway
//*************************************************************

// PORTB
#define   RF_IRQ        PORTBbits.RB0
// PORTC
#define   SCK_SCL       PORTCbits.RC3 	// horloge en mode SPI et I2C
#define   SDI_SDA       PORTCbits.RC4	// SDI en mode SPI et SDA en mode I2C
#define   SDO           PORTCbits.RC5	// SDO en mode SPI
// PORTF
#define   CS_EXT        PORTFbits.RF2
// PORTH
#define   CE_EXT        PORTHbits.RH4	


//*************************************************************
//*   Définitions des bits de configuration des broches du port d'extension du moway
//*************************************************************
// TRISB
#define   RF_IRQ_TRIS   TRISBbits.TRISB0
// TRISC
#define   SCK_SCL_TRIS  TRISCbits.TRISC3
#define   SDI_SDA_TRIS  TRISCbits.TRISC4
#define   SDO_TRIS      TRISCbits.TRISC5
// TRISF
#define   CS_EXT_TRIS   TRISFbits.TRISF2	
// TRISH
#define   CE_EXT_TRIS   TRISHbits.TRISH4

