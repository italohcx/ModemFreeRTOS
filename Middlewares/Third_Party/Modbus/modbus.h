/*****************************************************************************
 *
 *   modbus.h:  Header file for NXP LPC23xx/24xx Family Microprocessors
 *
 *   Copyright(C) 2008, Lupa Tecnologia e Sistemas Ltda.
 *   All rights reserved.
 *
 *   History
 *   2008.01.29  ver 1.00    Prelimnary version, first Release
 *
 *   Author: Pedro Zuchi, pedro@lupatecnologia.com.br, pedro@zuchi.com.br
 *
******************************************************************************/

#ifndef __MODBUS_H__
#define __MODBUS_H__

#include "stdint.h"

//#include <rtl.h>


#define MODBUS_BUFFER_SIZE	255
#define cPOLINOMIO 					0xA001
#define LITTLE_ENDIAN
//#define BIG_ENDIAN

 extern uint16_t  CalculaCRCByte ( uint16_t  , uint8_t );
 extern uint16_t  CalculaCRCStream ( uint8_t *, uint16_t   );
 extern uint8_t  ReadCoilRegister ( uint8_t *, uint8_t * );
 extern uint8_t  ReadInputRegister ( uint8_t *, uint8_t * );
 extern uint8_t  ReadHoldingRegister ( uint8_t *, uint8_t * );
 extern uint8_t *GetAddrCoilRegister ( uint16_t  );
 extern uint8_t *GetAddrInputRegister ( uint16_t  );
 extern uint8_t *GetAddrHoldingRegister ( uint16_t );
 extern uint8_t PresetSingleRegister ( uint8_t *, uint8_t * );
 extern uint8_t PresetMultipleRegisters ( uint8_t *, uint8_t * );

#endif

/****************************************************************************
 *                               End Of File
*****************************************************************************/
