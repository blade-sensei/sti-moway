#include "lib_rf2gh4.h"		


//*****************
//*   VARIABLES   *
//*****************

//Variables internas
static unsigned char  	   DATA_N_SND;
static unsigned char        DATA_N_RCV;


//*****************************************************
//*                    RF_INT_EN()                    *
//*****************************************************
//*Descripción:Se encarga de habilitar la interrupción*
//*externa (RB0) utilizada por el módulo de RF en la  *
//*recepción de datos.                                *
//*****************************************************
//*Variables de entrada:                              *
//*Variables de salida:                               *
//*****************************************************
void RF_INT_EN(void)
{
   	//Habilitar interrupciones externas con flanco de
   	//bajada.
   	INTCONbits.GIE=0;
   	INTCON2bits.INTEDG0=0;
	RF_IRQ=1;
   	INTCONbits.INT0E=1;
	INTCONbits.PEIE=1;
	INTCONbits.GIE=1;
}
//*****************************************************


//*****************************************************
//*        RF_CONFIG(unsigned char canal, unsigned char dir)            *
//*****************************************************
//*Descripción:Esta función se encarga de configurar  *
//*el transceptor habilitando su propia dirección de  *
//*escucha y el canal entre otros parámetros.         *
//*****************************************************
//*Variables de entrada:- Canal                       *
//*                     - Direccion                   *
//*Variables de salida: - 0: No configurado           *
//*                     - 1: Configuración correcta   *
//*****************************************************
unsigned char RF_CONFIG(unsigned char canal, unsigned char dir)
{
	static unsigned char        CONFIG_TEST;
   //Configuración I/O.
   SCK_SCL_TRIS=0;
   SDI_SDA_TRIS=1;
   SDO_TRIS=0;
   CS_EXT_TRIS=0;
   CE_EXT_TRIS=0;
   RF_IRQ_TRIS=1;

   CE_EXT=0;

   // TX_ADDR (0xFF)
   //Configuración de la dirección de envio aleatoria.
   //En la función de enviar se configura la direccion
   //deseada por el usuario.
   CS_EXT=0;
   SPI_WRITE(0x30);
   SPI_WRITE(0xFF);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   CS_EXT=1;

   // RX_ADDR_P0 (0xFF) ACK
   //Configuración de la direccióndel Pipe0 para la
   //recepción de ACK.
   CS_EXT=0;
   SPI_WRITE(0x2A);
   SPI_WRITE(0xFF);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   CS_EXT=1;

   // RX_ADDR_P1 (dir)
   //Configuración de la direccióndel Pipe1 para la
   //recepción de tramas.
   CS_EXT=0;
   SPI_WRITE(0x2B);
   SPI_WRITE(dir);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   CS_EXT=1;

   // RX_ADDR_P2 (0x00) BROADCAST
   //Configuración de la direccióndel Pipe2 para la
   //recepción de tramas
   CS_EXT=0;
   SPI_WRITE(0x2C);
   SPI_WRITE(0x00);
   CS_EXT=1;


   // EN_AA
   //Habilitar AutoAck en los Pipe0,Pipe1 y Pipe2.
   CS_EXT=0;
   SPI_WRITE(0x21);
   SPI_WRITE(0x07);
   CS_EXT=1;

   // EN_RXADDR
   //Habilitar los Pipe0,Pipe1 y Pipe2.
   CS_EXT=0;
   SPI_WRITE(0x22);
   SPI_WRITE(0x07);
   CS_EXT=1;

   // SETUP_AW
   //Configuración de la longitud de las direcciones.
   //Direcciones de 5 bytes.
   CS_EXT=0;
   SPI_WRITE(0x23);
   SPI_WRITE(0x03);
   CS_EXT=1;

   //SETUP_RETR
   //Configuración de las retrasmisiones en la transmisión.
   //Diez retransmisiones cada 336us.
   CS_EXT=0;
   SPI_WRITE(0x24);
   SPI_WRITE(0x0A);
   CS_EXT=1;


   //RF_SETUP
   //Configuración aspectos RF.
   //Ganancia máxima de LNA, 0dBm potencia de salida y 2Mbps de velocidad.
   CS_EXT=0;
   SPI_WRITE(0x26);
   SPI_WRITE(0x0F);
   CS_EXT=1;

   //STATUS
   //Reseteo del registro STATUS
   CS_EXT=0;
   SPI_WRITE(0x27);
   SPI_WRITE(0x70);
   CS_EXT=1;

   //RX_PW_P0
   //Nº de bytes en Pipe0.
   //1 byte (ACK).
   CS_EXT=0;
   SPI_WRITE(0x31);
   SPI_WRITE(0x01);
   CS_EXT=1;

   //RX_PW_P1
   //Nº de bytes en Pipe1.
   //10 byte (Direccion emisor y trama).
   CS_EXT=0;
   SPI_WRITE(0x32);
   SPI_WRITE(0x0A);
   CS_EXT=1;

   //RX_PW_P2
   //Nº de bytes en Pipe2.
   //10 byte (Direccion emisor y trama).
   CS_EXT=0;
   SPI_WRITE(0x33);
   SPI_WRITE(0x0A);
   CS_EXT=1;

   //RF_CH
   //Configuración del canal.
   //Canal elegido por el usuario (0x00 - 0x7F).
   CS_EXT=0;
   SPI_WRITE(0x25);
   SPI_WRITE(canal);
   CS_EXT=1;


   // RF_CH
   //Leemos RF_CH para comprobar que el módulos
   //se ha configurado correctamente.
   CS_EXT=0;
   SPI_WRITE(0x05);
   CONFIG_TEST=SPI_READ(0);
   CS_EXT=1;

   if(CONFIG_TEST!=canal)
      return(0);
   else
      return(1);

}
//*****************************************************


//*****************************************************
//*                    RF_ON()                        *
//*****************************************************
//*Descripción:Esta rutina activa el módulo de        *
//*radiofrecuencia en modo escucha para poder recibir *
//*datos enviados a su dirección.                     *
//*****************************************************
//*Variables de entrada:                              *
//*Variables de salida:                               *
//*Salida:              - 0: RF no conectado          *
//*                     - 1: Conexión correcta        *
//*****************************************************
unsigned char RF_ON(void)
{
	static unsigned char        CONFIG_TEST;
   CE_EXT=0;

   // CONFIG
   //Se activa el modulo, se pone en recepción,
   //se activa el CRC para que utilice 2 bytes.
   CS_EXT=0;
   SPI_WRITE(0x20);
   SPI_WRITE(0x0F);
   CS_EXT=1;

   // CONFIG
   //Leemos config para comprobar que el módulos
   //se ha activado correctamente.
   CS_EXT=0;
   SPI_WRITE(0x00);
   CONFIG_TEST=SPI_READ(0);
   CS_EXT=1;

   Delay10TCYx (200);		//Delay 2ms
   CE_EXT=1;
   Delay10TCYx (15);		//Delay 150us

   if(CONFIG_TEST!=0x0F)
   return(0);
   else
   return(1);
}
//*****************************************************





//*****************************************************
//*                 RF_OFF()                         *
//*****************************************************
//*Descripción:Este procedimiento desactiva el módulo *
//*de radiofrecuencia.                                *
//*****************************************************
//*Variables de entrada:                              *
//*Variables de salida:                               *
//*Salida:              - 0: RF no desconectado       *
//*                     - 1: Desconexión correcta     *
//*****************************************************
unsigned char RF_OFF(void)
{
	static unsigned char        CONFIG_TEST;
   CE_EXT=0;

   // CONFIG
   //Se desactiva el modulo
   CS_EXT=0;
   SPI_WRITE(0x20);
   SPI_WRITE(0x0C);
   CS_EXT=1;

   // CONFIG
   //Leemos config para comprobar que el módulos
   //se ha desactivado correctamente.
   CS_EXT=0;
   SPI_WRITE(0x00);
   CONFIG_TEST=SPI_READ(0);
   CS_EXT=1;

   if(CONFIG_TEST!=0x0C)
   return(0);
   else
   return(1);

}
//*****************************************************






//*****************************************************
//*                 RF_SEND()                         *
//*****************************************************
//*Descripción:Esta función envía 8 Bytes de datos a  *
//*la dirección indicada informando de la correcta    *
//*recepción en el destinatario.                      *
//*****************************************************
//*Variables de entrada:- RF_DATA_OUT[]               *
//*                     - RF_DIR_OUT                  *
//*Variables de salida: -                             *
//*Salida:              - 0: Envío correcto (ACK OK)  *
//*                     - 1: No recepcibido (NO ACK)  *
//*                     - 2: No enviado               *
//*****************************************************
unsigned char RF_SEND(unsigned char RF_DIR_OUT, unsigned char RF_DATA_OUT[])
{
   unsigned char i;
   unsigned char estado;
   static unsigned char RF_PAY_OUT[8];
   static unsigned char RF_PAY_DIR;
   static unsigned char INTER_RF;
	static int NO_RF;

   if(INTCONbits.INT0E)
      INTER_RF=1;
   else
      INTER_RF=0;

   INTCONbits.GIE=0;

   // INICIO
   CE_EXT=0;

   //STATUS
   //Reseteo del registro STATUS
   CS_EXT=0;
   SPI_WRITE(0x27);
   SPI_WRITE(0x70);
   CS_EXT=1;

   // EN_RXADDR
   //Se habilita el Pipe0 para la recepción del ACK
   CS_EXT=0;
   SPI_WRITE(0x22);
   SPI_WRITE(0x01);
   CS_EXT=1;

   // TX_ADDR
   //Se configura la dirección de transmisión=RF_DIR
   CS_EXT=0;
   SPI_WRITE(0x30);
   SPI_WRITE(RF_DIR_OUT);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   CS_EXT=1;

   // RX_ADDR_P0
   //Para la recepción del ACK se debe configurar el Pipe0 con
   //la misma dirección a trasmitir.
   CS_EXT=0;
   SPI_WRITE(0x2A);
   SPI_WRITE(RF_DIR_OUT);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   SPI_WRITE(0xC2);
   CS_EXT=1;

   // RX_ADDR_P1
   //Se mete en RF_DIR la direccion propia.
   //De esta manera el receptor sabe la dirección
   //del transmisor.
   CS_EXT=0;
   SPI_WRITE(0x0B);
   RF_PAY_DIR=SPI_READ(0);
   SPI_READ(0);
   SPI_READ(0);
   SPI_READ(0);
   SPI_READ(0);
   CS_EXT=1;

   // W_TX_PAYLOAD
   //Se manda los datos al transductor
   CS_EXT=0;
   SPI_WRITE(0xA0);

   DATA_N_SND++;

   for(i=0;i<8;i++)
      RF_PAY_OUT[i]=RF_DATA_OUT[i];

   SPI_WRITE(DATA_N_SND);
   SPI_WRITE(RF_PAY_DIR);

   for (i=0;i<8;i++)
      SPI_WRITE(RF_PAY_OUT[i]);

   CS_EXT=1;

   // CONFIG
   //Se pasa a modo transmisión.
   CS_EXT=0;
   SPI_WRITE(0x20);
   SPI_WRITE(0x0E);
   CS_EXT=1;

   // Pulso de comienzo de envío
   CE_EXT=1;
   Delay10TCYx(1);
   Delay1TCY();
   Delay1TCY();
   CS_EXT=0;

   NO_RF=0;

   while (RF_IRQ) {
      NO_RF++;
      //Si no da respuesta en 7ms, no se ha enviado.
      if(NO_RF==500){
      break;
         }
   }

   // STATUS
   //Lectura del estado en el registro estatus.
   CS_EXT=0;
   estado=SPI_READ(0x27);
   SPI_WRITE(0x70);
   CS_EXT=1;

   // EN_RXADDR
   //Habilitar los Pipe0,Pipe1 y Pipe2.
   CS_EXT=0;
   SPI_WRITE(0x22);
   SPI_WRITE(0x07);
   CS_EXT=1;

   // TX_FLUSH
   //Limpieza de la FIFO de salida
   CS_EXT=0;
   SPI_WRITE(0xE1);
   CS_EXT=1;

   // CONFIG
   //Paso a modo recepción
   CS_EXT=0;
   SPI_WRITE(0x20);
   SPI_WRITE(0x0F);
   CS_EXT=1;

   // FIN
   CE_EXT=1;

   Delay10TCYx (15);

   //Si no da respuesta en 7ms, no se ha enviado.
   if(NO_RF==500 ||NO_RF==0){
		INTCONbits.INT0F=0;
        if(INTER_RF==1)
        INTCONbits.GIE=1;
        return(2);
   }

   //estado
   //Chequeo de los bit del registro STATUS que indican si se ha recibido
   //ACK y si se ha terminado las retrasmisiones sin ningun ACK.
   if ((estado&(1<<4))==0 && (estado&(1<<5))!=0){
      INTCONbits.INT0F=0;
      if(INTER_RF==1)
      INTCONbits.GIE=1;
      return(0);
      }
   else{
      INTCONbits.INT0F=0;
      if(INTER_RF==1)
      INTCONbits.GIE=1;
      return(1);
      }
}
//*****************************************************







//*****************************************************
//*                 RF_RECEIVE()                      *
//*****************************************************
//*Descripción: Esta rutina se encarga de comprobar si*
//*se ha producido una recepción y de ser así,        *
//*devuelve la trama recibida.                        *
//*****************************************************
//*Variables de entrada:-                             *
//*Variables de salida: - RF_DATA_IN[]                *
//*                     - RF_DIR_IN                   *
//*Salida:         - 0: Recepción correcta y única    *
//*                - 1: Recepción correcta y múltiple *
//*                - 2: No se ha producido recepción  *
//*****************************************************

unsigned char RF_RECEIVE(unsigned char* RF_DIR_IN, unsigned char* RF_DATA_IN)
{

   unsigned char i;
   unsigned char mas;
   unsigned char estado;
   static unsigned char INTER_RF;

   if(INTCONbits.INT0E)
   {
      INTER_RF=1;
	  INTCONbits.GIE=0;
   }
   else
   {
      INTER_RF=0;
   }
			

   //FIFO_STATUS
   //Comprobación del estado de la FIFO de
   //recepción para comprobar si hay más datos
   CS_EXT=0;
   SPI_WRITE(0x17);
   mas=SPI_READ(0);
   CS_EXT=1;


   if (RF_IRQ==1 &&  mas&1!=0){
	  if(INTER_RF==1)INTCONbits.GIE=1;
      return (2);
   }

   //STATUS
   //Lectura del registro STATUS
   CS_EXT=0;
   estado=SPI_READ(0x07);
   CS_EXT=1;


   if(RF_IRQ==0 && estado&(1<<6)==0)
   {
      if(INTER_RF==1)INTCONbits.GIE=1;
      return(2);
   }

   INTCONbits.INT0F=0;

   //R_RX_PAYLOAD
   //Lectura de los datos recibidos.
   CS_EXT=0;
   SPI_WRITE(0x61);
   DATA_N_RCV=SPI_READ(0);
   *RF_DIR_IN=SPI_READ(0);
   for (i=0;i<8;i++)
   {
      RF_DATA_IN[i]=SPI_READ(0);
      
   }
   CS_EXT=1;


   //STATUS
   //Lectura y reseteo del registro STATUS
   CS_EXT=0;
   estado=SPI_READ(0x27);
   SPI_WRITE(0x70);
   CS_EXT=1;

   //FIFO_STATUS
   //Comprobación del estado de la FIFO de
   //recepción para comprobar si hay más datos
   CS_EXT=0;
   SPI_WRITE(0x17);
   mas=SPI_READ(0);
   CS_EXT=1;

   if (mas&1==0){
      if(INTER_RF==1)INTCONbits.GIE=1;
      return(1);
   }
      if(INTER_RF==1)INTCONbits.GIE=1;
      return(0);
}
