

#include "modbus.h"






//volatile uint8_t modbus_buffer [ MODBUS_BUFFER_SIZE ] @ "EMAC_DMA_RAM";

//
// Calcula o CRC 16 do byte passado como par�metro levando em considera��o o valor anterior do CRC
//
uint16_t CalculaCRCByte ( uint16_t crc, uint8_t byte ) {
  uint8_t i;
  crc = crc^byte;
  for ( i = 0; i < 8; i++ ) {
    if ( ( crc & 1 ) == 1 ) crc = ( crc >> 1 ) ^cPOLINOMIO;
    else crc = crc >> 1;
  }
  return crc;
}

//
// Calcula o CRC 16 da stream passada como par�metro
//
uint16_t CalculaCRCStream ( uint8_t *str, uint16_t tam ) {
  uint16_t i,crc;
  crc = 0xFFFF;
  for( i = 0; i < tam; i++, str++ ) crc = CalculaCRCByte ( crc, *str );
  return crc;
}


uint8_t ReadCoilRegister ( uint8_t *buffer, uint8_t *ptr ) {
	uint8_t bytecount, i;
	uint16_t crc;
	bytecount = 2 * buffer [ 5 ];
	buffer [ 2 ] = bytecount;
	for ( i = 0; i < bytecount; i += 2 ) {
		#ifdef LITTLE_ENDIAN
		buffer [ i + 3 ] = *( ptr + i + 1 );
		buffer [ i + 3 + 1 ] = *( ptr + i );
		#endif
		#ifdef BIG_ENDIAN
		buffer [ i + 3 ] = *( ptr + i );
		buffer [ i + 3 + 1 ] = *( ptr + i + 1 );
		#endif
	}
	crc = CalculaCRCStream ( buffer, bytecount + 3 );
	buffer [ bytecount + 3 ] = ( uint8_t ) ( crc & 0x00FF );
	buffer [ bytecount + 4 ] = ( uint8_t ) ( crc >> 8);
	return ( bytecount + 5 );
}


uint8_t ReadInputRegister ( uint8_t *buffer, uint8_t *ptr ) {
	uint8_t bytecount, i;
	uint16_t crc;
	bytecount = 2 * buffer [ 5 ];
	buffer [ 2 ] = bytecount;
	for ( i = 0; i < bytecount; i += 2 ) {
		#ifdef LITTLE_ENDIAN
		buffer [ i + 3 ] = *( ptr + i + 1 );
		buffer [ i + 3 + 1 ] = *( ptr + i );
		#endif
		#ifdef BIG_ENDIAN
		buffer [ i + 3 ] = *( ptr + i );
		buffer [ i + 3 + 1 ] = *( ptr + i + 1 );
		#endif
	}
	crc = CalculaCRCStream ( buffer, bytecount + 3 );
	buffer[ bytecount + 3 ] = ( uint8_t ) ( crc & 0x00FF );
	buffer[ bytecount + 4 ] = ( uint8_t ) ( crc >> 8 );
	return ( bytecount + 5 );
}


uint8_t ReadHoldingRegister ( uint8_t *buffer, uint8_t *ptr ) {
	uint8_t bytecount, i;
	uint16_t crc;
	bytecount = 2 * buffer [ 5 ];
	buffer [ 2 ] = bytecount;
	for( i = 0; i < bytecount; i += 2) {
		#ifdef LITTLE_ENDIAN
		buffer [ i + 3 ] = *( ptr + i + 1 );
		buffer [ i + 3 + 1 ] = *( ptr + i );
		#endif
		#ifdef BIG_ENDIAN
		buffer [ i + 3 ]   = *( ptr + i );
		buffer [ i + 3 + 1 ] = *( ptr + i + 1 );
		#endif
	}
	crc = CalculaCRCStream(buffer, bytecount + 3 );
	buffer[ bytecount + 3 ] = ( uint8_t ) ( crc & 0x00FF );
	buffer[ bytecount + 4 ] = ( uint8_t ) ( crc >> 8 );
	return ( bytecount + 5 );
}


uint8_t PresetSingleRegister ( uint8_t *buffer, uint8_t *ptr ) {
	#ifdef LITTLE_ENDIAN
	*( ptr ) = buffer [ 5 ];
	*( ptr + 1 ) = buffer [ 4 ];
	#endif
	#ifdef BIG_ENDIAN
	*( ptr ) = buffer [ 4 ];
	*( ptr + 1 ) = buffer [ 5 ];
	#endif
	return ( 8 );
}


uint8_t PresetMultipleRegisters ( uint8_t *buffer, uint8_t *ptr ) {
	uint8_t bytecount, i;
	uint16_t crc;
	bytecount = buffer [ 6 ];
	for ( i = 0; i < bytecount; i += 2 ) {
		#ifdef LITTLE_ENDIAN
		*( ptr + i ) = buffer [ 7 + i + 1 ];
		*( ptr + i + 1 ) = buffer [ 7 + i ];
		#endif
		#ifdef BIG_ENDIAN
		*( ptr + i ) = buffer [ 7 + i ];
		*( ptr + i + 1 ) = buffer [ 7 + i + 1 ];
		#endif
	}
	crc = CalculaCRCStream ( buffer, 6 );
	buffer [ 6 ] = ( uint8_t ) ( crc & 0x00FF );
	buffer [ 7 ] = ( uint8_t ) ( crc >> 8 );
	return ( 8 );
}
