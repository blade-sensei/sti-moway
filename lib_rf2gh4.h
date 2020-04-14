//********************************************************************************
//*    lib_rf2gh4.h                                                              *
//*    version: 2.0                                                              *
//*    Esta librería contiene las funciones necesarias para gestionar el módulo  *
//*    RF2GH4 con programas del compilador C18                                   *
//*    Copyright (C) 2010  Bizintek Innova S.L.                                  *
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
#include "spi_ext.h" // Utilise le Port d'extension en mode SPI


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
void RF_INT_EN(void);


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
unsigned char RF_CONFIG(unsigned char canal, unsigned char dir);


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
unsigned char RF_ON(void);


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
unsigned char RF_OFF(void);



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
unsigned char RF_SEND(unsigned char RF_DIR_OUT, unsigned char RF_DATA_OUT[]);





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

unsigned char RF_RECEIVE(unsigned char* RF_DIR_IN, unsigned char* RF_DATA_IN);





