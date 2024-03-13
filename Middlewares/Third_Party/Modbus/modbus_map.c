/*
 * modbus_map.c
 *
 *  Created on: Mar 13, 2024
 *      Author: italo
 */

#include "modbus_map.h"
#include "modbus.h"

MB modbus;

uint16_t InterpreterMODBUS(uint8_t *msg, uint16_t len)
{
	uint8_t *ptr;
	uint16_t crccal, crcrec, address, totalbytes;

	crccal = 0;
	crcrec = 0;
	address = (msg[2] << 8) | msg[3];
	//bytecount = msg[6];
	crccal = CalculaCRCStream(msg, len - 2);
	crcrec = (msg[len - 1] << 8) | msg[len - 2];

	if (crccal == crcrec)
	{
		switch (msg[0])
		{
		case 0x01: // Escravo 1
			switch (msg[1])
			{
			case 0x01: // Read coil registers

				ptr = GetAddrCoilRegister(address); // Pega o endereco real na memeria do CR
				totalbytes = ReadCoilRegister(msg, ptr); // Le o valor do IR e monta parte da mensagem
				break;
			case 0x02: // Read input status
				break;
			case 0x03: // Read holding registers
				ptr = GetAddrHoldingRegister(address); // Pega o endereco real na memoria do HR
				totalbytes = ReadHoldingRegister(msg, ptr);	// Le o valor do IR e monta parte da mensagem
				break;
			case 0x04: // Read input registers
				ptr = GetAddrInputRegister(address); // Pega o endereco real na memoria do IR
				totalbytes = ReadInputRegister(msg, ptr); // Le o valor do IR e monta parte da mensagem
				break;
			case 0x05: // Force single coil
				break;
			case 0x06: // Preset single register
				ptr = GetAddrHoldingRegister(address); // Pega o endereco real na memoria do HR
				totalbytes = PresetSingleRegister(msg, ptr); // Grava o valor do HR e monta parte da mensagem

				//eeprom_write_char ( address, *( ptr ) );
				//eeprom_write_char ( address + 1, *( ptr + 1 ) );

				if (totalbytes)
				{ //Implementado para possibilitar a gravacao do Tipo de Hardware (Input Register) via CfgHorus

					if ((modbus.HOLDINGREGISTERS[ADD_COPIA_TIPO_HARDW] != 0) && (modbus.INPUTREGISTERS[ADD_TIPO_HARDW] != modbus.HOLDINGREGISTERS[ADD_COPIA_TIPO_HARDW]))
					{
						//if((modbusMapa.COPIA_TIPO_HARDW != 0) && (modbusMapa.TIPO_HARDW != modbusMapa.COPIA_TIPO_HARDW)){

						modbus.INPUTREGISTERS[ADD_TIPO_HARDW] =
								modbus.HOLDINGREGISTERS[ADD_COPIA_TIPO_HARDW];

						//modbusMapa.TIPO_HARDW = modbusMapa.COPIA_TIPO_HARDW;

						ptr = (uint8_t*) GetAddrInputRegister(ADD_TIPO_HARDW);

						//while(eeprom_write_int(END_TIPO_HARDW_EEPROM, MB.TIPO_HARDW));
					}
				}
#ifdef WATCHDOG
        fWatchDogReset();
#endif
				//Carrega conte�do gravado para RAM para comparacao no CfgHorus
				ptr = GetAddrHoldingRegister(address); // Pega o endereco real na memoria do HR

				//eeprom_read_stream(ptr, bytecount, (address * 2));
				break;
			case 0x0F: // Preset multiple coils
				break;
			case 0x10: // Preset multiple resgisters
				ptr = GetAddrHoldingRegister(address); // Pega o endereco real na memeria do HR

				totalbytes = PresetMultipleRegisters(msg, ptr); // Grava o valor do HR e monta parte da mensagem

				//eeprom_write_stream((address * 2), bytecount, ptr);

				if (totalbytes)
				{ //Implementado para possibilitar a gravacao do Tipo de Hardware (Input Register) via CfgHorus

					if ((modbus.HOLDINGREGISTERS[ADD_COPIA_TIPO_HARDW] != 0) && (modbus.INPUTREGISTERS[ADD_TIPO_HARDW] != modbus.HOLDINGREGISTERS[ADD_COPIA_TIPO_HARDW]))
					{

						//if((modbusMapa.COPIA_TIPO_HARDW != 0) && (modbusMapa.TIPO_HARDW != modbusMapa.COPIA_TIPO_HARDW)){
						// modbusMapa.TIPO_HARDW = modbusMapa.COPIA_TIPO_HARDW;
						modbus.INPUTREGISTERS[ADD_TIPO_HARDW] = modbus.HOLDINGREGISTERS[ADD_COPIA_TIPO_HARDW];

						ptr = (uint8_t*) GetAddrInputRegister(ADD_TIPO_HARDW);
						// while(eeprom_write_int(END_TIPO_HARDW_EEPROM,modbusMapa.TIPO_HARDW));
					}
				}
#ifdef WATCHDOG
        fWatchDogReset();
#endif
				//Carrega conte�do gravado para RAM para comparacao no CfgHorus
				ptr = GetAddrHoldingRegister(address); // Pega o endereco real na memoria do HR
				// eeprom_read_stream(ptr, bytecount, (address * 2));
				break;
			}
			break;
		}
	}
	else
	{

		totalbytes = 0;
	}

	return totalbytes;
}

uint8_t* GetAddrCoilRegister(uint16_t address)
{

	uint8_t *ptr;

	switch (address)
	{

	case ADD_IN_1:
		ptr = (uint8_t*) &modbus.COILS[ADD_IN_1];
		break;
	case ADD_IN_2:
		ptr = (uint8_t*) &modbus.COILS[ADD_IN_2];
		break;
	case ADD_OUT_1:
		ptr = (uint8_t*) &modbus.COILS[ADD_OUT_1];
		break;
	}
	return ptr;
}

uint8_t* GetAddrInputRegister(uint16_t address)
{

	uint8_t *ptr;

	if (address < 256)

		ptr = (uint8_t*) &modbus.INPUTREGISTERS[ADD_IMEI_1 + (address)];
	else
		ptr = (uint8_t*) &modbus.ESPELHO[ADD_IMEI_1 + ((address - 256))];
	return ptr;
}

uint8_t* GetAddrHoldingRegister(uint16_t address)
{

	uint8_t *ptr;

	if (address < 500)

		ptr = (uint8_t*) &modbus.HOLDINGREGISTERS[ADD_TEMVALCONGPR + (address)];
	//ptr = (uint8_t*) &modbusMapa.TEMVALCONGPR + (address * 2);
	else
		ptr = (uint8_t*) &modbus.HOLDINGREGISTERS[(ADD_NUMSER_1 - 130)
				+ (address - 500)];
	//ptr = (uint8_t*) &modbusMapa.NUMSER_1 + ((address - 500) * 2);
	return ptr;
}

uint8_t SeparaMensagensMODBUS(uint8_t *bufMsg, int tamanho)
{
	uint8_t tamMsg = 0;

	switch (bufMsg[0])
	{
	case 0x01:
		switch (bufMsg[1])
		{
		case 0x01: // Read coil registers
		case 0x02: // Read input status
		case 0x03: // Read holding registers
		case 0x04: // Read input registers
			tamMsg = 8; //Escravo + comando + 2 bytes endere�o + 2 bytes registros + 2 bytes CRC
			break;
		case 0x05: //Force single coil
		case 0x06: // Preset single register
		case 0x0F: // Preset multiple coils
		case 0x10: // Preset multiple resgisters
			tamMsg = 2 + 2 + 2 + 1 + bufMsg[6] + 2; //Escravo + comando + 2 bytes endere�o + 2 bytes de registros + 1 byte total + dados + 2 bytes CRC
			break;
		default:
			return tamanho;
		}
		break;
	default:
		return tamanho;
	}
	if (tamMsg > tamanho)
		return tamanho;

	return tamMsg;
}

void LoadHoldingRegisterRAM(void)
{

	for (int var = 0; var < TOTAL_VARIAVEIS_HOLDING; ++var)
	{

		modbus.HOLDINGREGISTERS[var] = var + 3;
	}
}

void LoadInputRegisterRAM(void)
{

	for (int var = 0; var < TOTAL_VARIAVEIS_INPUT; ++var)
	{

		modbus.INPUTREGISTERS[var] = var + 10;
	}

}

void LoadCoilRegisterRAM(void)
{

	for (int var = 0; var < TOTAL_VARIAVEIS_COILS; ++var)
	{

		modbus.COILS[var] = var;
	}

}

void LoadEspelhoRAM(void)
{

	for (int var = 0; var < TOTAL_VARIAVEIS_ESPELHO; ++var)
	{
		modbus.ESPELHO[var] = var + 5;
	}

}

