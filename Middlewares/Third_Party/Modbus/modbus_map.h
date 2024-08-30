/*
 * modbus_map.h
 *
 *  Created on: Mar 13, 2024
 *      Author: italo
 */

#ifndef THIRD_PARTY_MODBUS_MODBUS_MAP_H_
#define THIRD_PARTY_MODBUS_MODBUS_MAP_H_


#include "stdint.h"


#define TOTAL_VARIAVEIS_COILS   3
#define TOTAL_VARIAVEIS_INPUT   119
#define TOTAL_VARIAVEIS_HOLDING	370 + 6
#define TOTAL_VARIAVEIS_ESPELHO 75


typedef struct
{
	uint16_t COILS[TOTAL_VARIAVEIS_COILS];
	uint16_t HOLDINGREGISTERS[TOTAL_VARIAVEIS_HOLDING];
	uint16_t INPUTREGISTERS[TOTAL_VARIAVEIS_INPUT];
	uint16_t ESPELHO[TOTAL_VARIAVEIS_ESPELHO];
}
TModbusMap;


typedef enum
{
	//
	ADD_IN_1,
	ADD_IN_2,
	ADD_OUT_1
//
}
MODBUS_CR_ADD;



typedef enum
{
	//
	ADD_IMEI_1, //0
	ADD_IMEI_2, //1
	ADD_IMEI_3, //2
	ADD_IMEI_4, //3
	ADD_IMEI_5, //4
	ADD_IMEI_6, //5
	ADD_IMEI_7, //6
	ADD_IMEI_8, //7
	ADD_IMEI_9, //8
	ADD_IMEI_10, //9
	//
	ADD_SIM1_SQMVALMIN, //10
	ADD_SIM1_SQMVALMAX, //11
	ADD_SIM1_SQMVALMED, //12
	ADD_SIM1_SQMAMO, //13
	ADD_SIM1_SQMDES, //14
	ADD_SIM2_SQMVALMIN, //15
	ADD_SIM2_SQMVALMAX, //16
	ADD_SIM2_SQMVALMED, //17
	ADD_SIM2_SQMAMO, //18
	ADD_SIM2_SQMDES, //19
	//
	ADD_TEMPER, //20
	//
	ADD_VERFIR_1, // 21
	ADD_VERFIR_2, // 22
	//
	ADD_SIM1_NUMBER_1, //23
	ADD_SIM1_NUMBER_2, //24
	ADD_SIM1_NUMBER_3, //25
	ADD_SIM1_NUMBER_4, //26
	ADD_SIM1_NUMBER_5, //27
	ADD_SIM1_NUMBER_6, //28
	ADD_SIM1_NUMBER_7, //29
	ADD_SIM1_NUMBER_8, //30
	ADD_SIM1_NUMBER_9, //31
	ADD_SIM1_NUMBER_10, //32
	ADD_SIM1_NUMBER_11, //33
	ADD_SIM1_NUMBER_12, //34
	ADD_SIM1_NUMBER_13, //35
	ADD_SIM1_NUMBER_14, //36
	ADD_SIM1_NUMBER_15, //37
	//
	ADD_SIM2_NUMBER_1, //38
	ADD_SIM2_NUMBER_2, //39
	ADD_SIM2_NUMBER_3, //40
	ADD_SIM2_NUMBER_4, //41
	ADD_SIM2_NUMBER_5, //42
	ADD_SIM2_NUMBER_6, //43
	ADD_SIM2_NUMBER_7, //44
	ADD_SIM2_NUMBER_8, //45
	ADD_SIM2_NUMBER_9, //46
	ADD_SIM2_NUMBER_10, //47
	ADD_SIM2_NUMBER_11, //48
	ADD_SIM2_NUMBER_12, //49
	ADD_SIM2_NUMBER_13, //50
	ADD_SIM2_NUMBER_14, //51
	ADD_SIM2_NUMBER_15, //52
	//
	ADD_MODMAN_1, // 53
	ADD_MODMAN_2, // 54
	ADD_MODMAN_3, // 55
	ADD_MODMAN_4, // 56
	ADD_MODMAN_5, // 57
	//
	ADD_MODMOD_1, // 58
	ADD_MODMOD_2, // 59
	ADD_MODMOD_3, // 60
	ADD_MODMOD_4, // 61
	ADD_MODMOD_5, // 62
	//
	ADD_MODREV_1, // 63
	ADD_MODREV_2, // 64
	ADD_MODREV_3, // 65
	ADD_MODREV_4, // 66
	ADD_MODREV_5, // 67
	ADD_MODREV_6, // 68
	ADD_MODREV_7, // 69
	ADD_MODREV_8, // 70
	ADD_MODREV_9, // 71
	ADD_MODREV_10, // 72
	//
	//
	ADD_SIM1_OPER_1, // 73
	ADD_SIM1_OPER_2, //	74
	ADD_SIM1_OPER_3, //	75
	ADD_SIM1_OPER_4, //	76
	ADD_SIM1_OPER_5, //	77
	ADD_SIM1_OPER_6, //	78
	ADD_SIM1_OPER_7, //	79
	ADD_SIM1_OPER_8, //	80
	ADD_SIM1_OPER_9, //	81
	ADD_SIM1_OPER_10, // 82
	//
	ADD_SIM2_OPER_1, // 83
	ADD_SIM2_OPER_2, //	84
	ADD_SIM2_OPER_3, //	85
	ADD_SIM2_OPER_4, //	86
	ADD_SIM2_OPER_5, //	87
	ADD_SIM2_OPER_6, //	88
	ADD_SIM2_OPER_7, //	89
	ADD_SIM2_OPER_8, //	90
	ADD_SIM2_OPER_9, //	91
	ADD_SIM2_OPER_10, // 92
	//
	ADD_BYTES_ROTEAMENTO_1, // 93
	ADD_BYTES_ROTEAMENTO_2, // 94
	ADD_BYTES_COMUNICACAO_1, // 95
	ADD_BYTES_COMUNICACAO_2, // 96
	ADD_BYTES_FABRICANTE_1, // 97
	ADD_BYTES_FABRICANTE_2, // 98
	//
	ADD_NUM_MSG_TRA_ROT, //99 N�mero de mensagens trafegadas Roteamento
	ADD_NUM_MSG_TRA_COM, //100 N�mero de mensagens trafegadas Comunica��o
	ADD_NUM_MSG_TRA_FAB, //101 N�mero de mensagens trafegadas Fabricante
	//
	ADD_FLAG, //102
	//
	//
	ADD_IP_1, //103
	ADD_IP_2, //104
	//
	//
	ADD_STATUS_MOBILE_COUNTRY, //105
	ADD_STATUS_MOBILE_NETWORK, //106
	ADD_STATUS_LOCATION_AREA, //107
	ADD_STATUS_CELL_INDENTITY, //108
	ADD_ERB, //109
	ADD_CANAL, //110
	ADD_TIPO_HARDW, //111
	ADD_VERFIR_BOOTLOADER_1, // 112
	ADD_VERFIR_BOOTLOADER_2, // 113
	//
	ADD_ESTADO_ENT_1, //114
	ADD_ESTADO_ENT_2,  //115
	//
	ADD_TEN_BAT1, //116
	ADD_TEN_BAT2, //117
	//
	ADD_TECNOLOGIA_COMUNICACAO, //118 (2G/3G)
	///
	//IN�CIO ESPELHO//
	///
	ADD_ESP_IMEI_1 = 256, //256
	ADD_ESP_IMEI_2, //257
	ADD_ESP_IMEI_3, //258
	ADD_ESP_IMEI_4, //259
	ADD_ESP_IMEI_5, //260
	ADD_ESP_IMEI_6, //261
	ADD_ESP_IMEI_7, //262
	ADD_ESP_IMEI_8, //263
	ADD_ESP_IMEI_9, //264
	ADD_ESP_IMEI_10, //265
	//
	ADD_ESP_FLAG, //266
	//
	ADD_ESP_TEMPER, //267
	//
	ADD_ESP_SQMVALMIN, //268
	ADD_ESP_SQMVALMAX, //269
	ADD_ESP_SQMVALMED, //270
	//
	ADD_ESP_BYTES_ROTEAMENTO_1, // 271
	ADD_ESP_BYTES_ROTEAMENTO_2, // 272
	ADD_ESP_BYTES_COMUNICACAO_1, // 273
	ADD_ESP_BYTES_COMUNICACAO_2, // 274
	ADD_ESP_BYTES_FABRICANTE_1, // 275
	ADD_ESP_BYTES_FABRICANTE_2, // 276
	//
	ADD_ESP_NUM_MSG_TRA_ROT, //277 N�mero de mensagens trafegadas Roteamento
	ADD_ESP_NUM_MSG_TRA_COM, //278 N�mero de mensagens trafegadas Comunica��o
	ADD_ESP_NUM_MSG_TRA_FAB, //279 N�mero de mensagens trafegadas Fabricante
	//
	ADD_ESP_ERB, //280
	//
	ADD_ESP_CANAL, //281
	//
	ADD_ESP_IP_1, //282
	ADD_ESP_IP_2, //283
	//
	ADD_ESP_VERFIR_1, //284
	ADD_ESP_VERFIR_2, //285
	//
	ADD_ESP_SIM1_NUMBER_1, //286
	ADD_ESP_SIM1_NUMBER_2, //287
	ADD_ESP_SIM1_NUMBER_3, //288
	ADD_ESP_SIM1_NUMBER_4, //289
	ADD_ESP_SIM1_NUMBER_5, //290
	ADD_ESP_SIM1_NUMBER_6, //291
	ADD_ESP_SIM1_NUMBER_7, //292
	ADD_ESP_SIM1_NUMBER_8, //293
	ADD_ESP_SIM1_NUMBER_9, //294
	ADD_ESP_SIM1_NUMBER_10, //295
	ADD_ESP_SIM1_NUMBER_11, //296
	ADD_ESP_SIM1_NUMBER_12, //297
	ADD_ESP_SIM1_NUMBER_13, //298
	ADD_ESP_SIM1_NUMBER_14, //299
	ADD_ESP_SIM1_NUMBER_15, //300
	//

	ADD_ESP_SIM2_NUMBER_1, //301
	ADD_ESP_SIM2_NUMBER_2, //302
	ADD_ESP_SIM2_NUMBER_3, //303
	ADD_ESP_SIM2_NUMBER_4, //304
	ADD_ESP_SIM2_NUMBER_5, //305
	ADD_ESP_SIM2_NUMBER_6, //306
	ADD_ESP_SIM2_NUMBER_7, //307
	ADD_ESP_SIM2_NUMBER_8, //308
	ADD_ESP_SIM2_NUMBER_9, //309
	ADD_ESP_SIM2_NUMBER_10, //310
	ADD_ESP_SIM2_NUMBER_11, //311
	ADD_ESP_SIM2_NUMBER_12, //312
	ADD_ESP_SIM2_NUMBER_13, //313
	ADD_ESP_SIM2_NUMBER_14, //314
	ADD_ESP_SIM2_NUMBER_15, //315
	//
	ADD_ESP_NUMSER_1, //316 ( string ASCIIZ, tamanho 10 caracteres)
	ADD_ESP_NUMSER_2, //317
	ADD_ESP_NUMSER_3, //318
	ADD_ESP_NUMSER_4, //319
	ADD_ESP_NUMSER_5, //320
	//
	ADD_ESP_ESTADO_ENT_1,  //321
	ADD_ESP_ESTADO_ENT_2,  //322
	//
	ADD_ESP_TEN_BAT1, //323
	ADD_ESP_TEN_BAT2, //324
	//
	ADD_ESP_STATUS_MOBILE_COUNTRY, //325
	ADD_ESP_STATUS_MOBILE_NETWORK, //326
	ADD_ESP_STATUS_LOCATION_AREA, //327
	ADD_ESP_STATUS_CELL_INDENTITY, //328
	ADD_ESP_TECNOLOGIA_COMUNICACAO, //329
	ADD_ESP_RES330  //330
}
MODBUS_IR_ADD;

typedef enum
{
	//
	ADD_TEMVALCONGPR, //0
	//
	ADD_MODOPE, //1
	//
	ADD_SIMCARSEL, //2
	//
	ADD_SIM1_TEL_1, //3
	ADD_SIM1_TEL_2, //4
	ADD_SIM1_TEL_3, //5
	ADD_SIM1_TEL_4, //6
	ADD_SIM1_TEL_5, //7
	ADD_SIM1_TEL_6, //8
	ADD_SIM1_TEL_7, //9
	ADD_SIM1_TEL_8, //10
	ADD_SIM1_TEL_9, //11
	ADD_SIM1_TEL_10, //12
	//
	ADD_SIM2_TEL_1, //13
	ADD_SIM2_TEL_2, //14
	ADD_SIM2_TEL_3, //15
	ADD_SIM2_TEL_4, //16
	ADD_SIM2_TEL_5, //17
	ADD_SIM2_TEL_6, //18
	ADD_SIM2_TEL_7, //19
	ADD_SIM2_TEL_8, //20
	ADD_SIM2_TEL_9, //21
	ADD_SIM2_TEL_10, //22
	//
	ADD_SIM1, //23
	//
	ADD_SIM1_PIN1, //24
	ADD_SIM1_PIN2, //25
	//
	ADD_SIM1_PUK1_1, //26
	ADD_SIM1_PUK1_2, //27
	ADD_SIM1_PUK2_1, //28
	ADD_SIM1_PUK2_2, //29
	//
	//
	ADD_ALTERAR_PIN1_SIM1, //30
	ADD_HAB_PIN1_SIM1, //31
	ADD_NOVO_SIM1_PIN1, //32
	//
	ADD_SIM1_APN1, //33
	//
	ADD_SIM1_APN1_1, //34
	ADD_SIM1_APN1_2, //35
	ADD_SIM1_APN1_3, //36
	ADD_SIM1_APN1_4, //37
	ADD_SIM1_APN1_5, //38
	ADD_SIM1_APN1_6, //39
	ADD_SIM1_APN1_7, //40
	ADD_SIM1_APN1_8, //41
	ADD_SIM1_APN1_9, //42
	ADD_SIM1_APN1_10, //43
	ADD_SIM1_APN1_11, //44
	ADD_SIM1_APN1_12, //45
	ADD_SIM1_APN1_13, //46
	ADD_SIM1_APN1_14, //47
	ADD_SIM1_APN1_15, //48
	ADD_SIM1_APN1_16, //49
	ADD_SIM1_APN1_17, //50
	ADD_SIM1_APN1_18, //51
	ADD_SIM1_APN1_19, //52
	ADD_SIM1_APN1_20, //53
	//
	ADD_RES54, //54 //Aten��o ao usar essa �rea de mem�ria. Pesquisar no firmware os locais onde ele est� sendo usada para renomear.
	ADD_RES55, //55
	ADD_RES56, //56
	ADD_RES57, //57
	ADD_RES58, //58
	ADD_RES59, //59
	//
	ADD_RES60, //60 //Aten��o ao usar essa �rea de mem�ria. Pesquisar no firmware os locais onde ele est� sendo usada para renomear.
	ADD_RES61, //61
	ADD_RES62, //62
	ADD_RES63, //63
	ADD_RES64, //64
	ADD_RES65, //65
	//
	//
	ADD_SIM1_APN1_IPPOR_SEL, //66 Par IP/Porta selecionado no sim 1 (1 ou 2)
	//
	//
	ADD_SIM1_APN1_IP1, //67
	ADD_SIM1_APN1_IP1_1, //68
	ADD_SIM1_APN1_IP1_2, //69
	ADD_SIM1_APN1_POR1, //70
	//
	ADD_SIM1_APN1_IP2, //71
	ADD_SIM1_APN1_IP2_1, //72
	ADD_SIM1_APN1_IP2_2, //73
	ADD_SIM1_APN1_POR2, //74
	//
	ADD_SIM1_SOCKET1_UART, //75
	ADD_SIM1_SOCKET2_UART, //76
	//
	ADD_SIM1_NIV_PRI, //77
	ADD_SIM1_EST_CAR, //78
	//
	//
	ADD_DES_PIN1_SIM1, //79
	ADD_DES_PIN1_SIM2, //80
	ADD_USO_PIN1_SIM1, //81
	ADD_USO_PIN1_SIM2, //82
	//
	ADD_COPIA_TIPO_HARDW, //83 Para possibilitar a grava��o do tipo de hardware via CfgHorus
	//
	ADD_SIM2, //84
	//
	ADD_SIM2_PIN1, //85
	ADD_SIM2_PIN2, //86
	//
	ADD_SIM2_PUK1_1, //87
	ADD_SIM2_PUK1_2, //88
	ADD_SIM2_PUK2_1, //89
	ADD_SIM2_PUK2_2, //90
	//
	//
	ADD_ALTERAR_PIN1_SIM2, //91
	ADD_HAB_PIN1_SIM2, //92
	ADD_NOVO_SIM2_PIN1, //93
	//
	ADD_SIM2_APN1, //94
	//
	ADD_SIM2_APN1_1, //95
	ADD_SIM2_APN1_2, //96
	ADD_SIM2_APN1_3, //97
	ADD_SIM2_APN1_4, //98
	ADD_SIM2_APN1_5, //99
	ADD_SIM2_APN1_6, //100
	ADD_SIM2_APN1_7, //101
	ADD_SIM2_APN1_8, //102
	ADD_SIM2_APN1_9, //103
	ADD_SIM2_APN1_10, //104
	ADD_SIM2_APN1_11, //105
	ADD_SIM2_APN1_12, //106
	ADD_SIM2_APN1_13, //107
	ADD_SIM2_APN1_14, //108
	ADD_SIM2_APN1_15, //109
	ADD_SIM2_APN1_16, //110
	ADD_SIM2_APN1_17, //111
	ADD_SIM2_APN1_18, //112
	ADD_SIM2_APN1_19, //113
	ADD_SIM2_APN1_20, //114
	//
	ADD_RES115, //115 //Aten��o ao usar essa �rea de mem�ria. Pesquisar no firmware os locais onde ele est� sendo usada para renomear.
	ADD_RES116, //116
	ADD_RES117, //117
	ADD_RES118, //118
	ADD_RES119, //119
	ADD_RES120, //120
	//
	ADD_RES121, //121 //Aten��o ao usar essa �rea de mem�ria. Pesquisar no firmware os locais onde ele est� sendo usada para renomear.
	ADD_RES122, //122
	ADD_RES123, //123
	ADD_RES124, //124
	ADD_RES125, //125
	ADD_RES126, //126
	//
	ADD_SIM2_APN1_IPPOR_SEL, //127 Par IP/Porta selecionado no sim 2 (1 ou 2)
	//
	ADD_SIM2_APN1_IP1, //128
	ADD_SIM2_APN1_IP1_1, //129
	ADD_SIM2_APN1_IP1_2, //130
	ADD_SIM2_APN1_POR1, //131
	//
	ADD_SIM2_APN1_IP2, //132
	ADD_SIM2_APN1_IP2_1, //133
	ADD_SIM2_APN1_IP2_2, //134
	ADD_SIM2_APN1_POR2, //135
	//
	ADD_SIM2_SOCKET1_UART, //136
	ADD_SIM2_SOCKET2_UART, //137
	//
	//
	ADD_SIM2_NIV_PRI, //138
	ADD_SIM2_EST_CAR, //139
	//
	ADD_IP_SOCFAB_1, //140
	ADD_IP_SOCFAB_2, //141
	ADD_IP_SOCFAB, //142 //Vari�vel para indicar o uso de IP diferente p/ socket fabricante
	//
	ADD_MODO_SERIAL1, //143
	//
	ADD_ATIVAR_SOCKET_COM, //144
	//
	ADD_ATIVAR_SOCKET_FAB, ////145
	//
	ADD_TEMDESSOCFAB, //146
	ADD_TEMINASOCFAB, //147
	ADD_TEMDESSOCCOM, //148 Tempo de perman�ncia no socket de comunica��o
	ADD_TEMINASOCCOM, //149 Tempo de inatividade do socket de comunica��o
	//
	ADD_SOCKETCOM_POR, //150
	ADD_SOCKETFAB_POR, //151
	//
	//
	//
	ADD_SIM17, //152
	ADD_SIM18, //153
	ADD_SIM19, //154
	ADD_SIM20, //155
	ADD_SIM21, //156
	//
	//
	//
	ADD_COM0_CONFIG_PORT, //157
	ADD_COM1_CONFIG_PORT, //158
	ADD_COM2_CONFIG_PORT, //159
	ADD_COM3_CONFIG_PORT, //160
	//
	ADD_TEMMANMODCFG, //161
	ADD_TEMINAMODCFG, //162
	//
	ADD_TEMMANMODTTY, //163
	ADD_TEMINAMODTTY, //164
	//
	ADD_TOTMEDMODSQM, //165
	//
	ADD_TEMMANMODGPR, //166
	ADD_TEMINAMODGPR, //167
	//
	ADD_TEMPERCONRED, //168
	//
	ADD_SERCMD, //169
	//
	//
	ADD_TEMAGUATT, //170
	ADD_TOTTENATT, //171
	//
	ADD_FTP_FLAG_BOOTLOADER, //172
	//
	ADD_FTP_USUARIO_1, //173 ( string ASCIIZ, tamanho 12 caracteres)
	ADD_FTP_USUARIO_2, //174
	ADD_FTP_USUARIO_3, //175
	ADD_FTP_USUARIO_4, //176
	ADD_FTP_USUARIO_5, //177
	ADD_FTP_USUARIO_6, //178
	//
	ADD_FTP_SENHA_1, //179 ( string ASCIIZ, tamanho 12 caracteres)
	ADD_FTP_SENHA_2, //180
	ADD_FTP_SENHA_3, //181
	ADD_FTP_SENHA_4, //182
	ADD_FTP_SENHA_5, //183
	ADD_FTP_SENHA_6, //184
	//
	ADD_FTP_SIM1_APN1_IP1_1, // 185 ( 2 octetos podendo cada um variar de 0.. 255, ex.: 192.168 )
	ADD_FTP_SIM1_APN1_IP1_2, // 186 ( 2 octetos podendo cada um variar de 0.. 255, ex.: 192.168 )
	//
	ADD_FTP_SIM1_APN1_POR1, // 187 ( 0..65535 )
	//
	ADD_FTP_SIM2_APN1_IP1_1, // 188 ( 2 octetos podendo cada um variar de 0.. 255, ex.: 192.168 )
	ADD_FTP_SIM2_APN1_IP1_2, // 189 ( 2 octetos podendo cada um variar de 0.. 255, ex.: 192.168 )
	//
	ADD_FTP_SIM2_APN1_POR1, // 190 ( 0..65535 )
	//
	ADD_FTP_NOMEARQ_1, // 191 ( string ASCIIZ, tamanho 12 caracteres)
	ADD_FTP_NOMEARQ_2, // 192
	ADD_FTP_NOMEARQ_3, // 193
	ADD_FTP_NOMEARQ_4, // 194
	ADD_FTP_NOMEARQ_5, // 195
	ADD_FTP_NOMEARQ_6, // 196
	//
	ADD_FTP_CAMINHO_1, // 197 ( string ASCIIZ, tamanho 20 caracteres)
	ADD_FTP_CAMINHO_2, // 198
	ADD_FTP_CAMINHO_3, // 199
	ADD_FTP_CAMINHO_4, // 200
	ADD_FTP_CAMINHO_5, // 201
	ADD_FTP_CAMINHO_6, // 202
	ADD_FTP_CAMINHO_7, // 203
	ADD_FTP_CAMINHO_8, // 204
	ADD_FTP_CAMINHO_9, // 205
	ADD_FTP_CAMINHO_10, // 206
	//
	ADD_FTP_SIMSEL, // 207
	//
	ADD_MODO_GPRS_STANDBY, // 208
	ADD_VAL_SOCK_FAB, // 209
	ADD_RESET_FLAG, // 210
	ADD_FAT_COR_TEM_1, // 211 Fator de corre��o da temperatura
	ADD_FAT_COR_TEM_2, // 212
	ADD_CONTR_FALHA, // 213
	ADD_CONTR_RESET, // 214
	ADD_TEMPERSERRED, // 215  Tempo de perman�ncia no servidor redundante
	ADD_SIM1_IP_EXTERNO_SERPRI_1, // 216
	ADD_SIM1_IP_EXTERNO_SERPRI_2, // 217
	ADD_SIM1_IP_EXTERNO_SERRED_1, // 218
	ADD_SIM1_IP_EXTERNO_SERRED_2, // 219
	ADD_TEMPERAPNPUB, // 220
	ADD_SIM2_IP_EXTERNO_SERPRI_1, // 221
	ADD_SIM2_IP_EXTERNO_SERPRI_2, // 222
	ADD_SIM2_IP_EXTERNO_SERRED_1, // 223
	ADD_SIM2_IP_EXTERNO_SERRED_2, // 224
	ADD_SOCKETCOM_PORALT, // 225
	ADD_PORALTSOCCOM, // 226
	ADD_TEMPORELE, // 227
	//** Altera'coes para suportar at'e 30 caracteres em login e senha
	ADD_SIM1_LOG1_1, //228
	ADD_SIM1_LOG1_2, //229
	ADD_SIM1_LOG1_3, //230
	ADD_SIM1_LOG1_4, //231
	ADD_SIM1_LOG1_5, //232
	ADD_SIM1_LOG1_6, //233
	ADD_SIM1_LOG1_7, //234
	ADD_SIM1_LOG1_8, //235
	ADD_SIM1_LOG1_9, //236
	ADD_SIM1_LOG1_10, //237
	ADD_SIM1_LOG1_11, //238
	ADD_SIM1_LOG1_12, //239
	ADD_SIM1_LOG1_13, //240
	ADD_SIM1_LOG1_14, //241
	ADD_SIM1_LOG1_15, //242
	//
	ADD_SIM1_PAS1_1, //243
	ADD_SIM1_PAS1_2, //244
	ADD_SIM1_PAS1_3, //245
	ADD_SIM1_PAS1_4, //246
	ADD_SIM1_PAS1_5, //247
	ADD_SIM1_PAS1_6, //248
	ADD_SIM1_PAS1_7, //249
	ADD_SIM1_PAS1_8, //250
	ADD_SIM1_PAS1_9, //251
	ADD_SIM1_PAS1_10, //252
	ADD_SIM1_PAS1_11, //253
	ADD_SIM1_PAS1_12, //254
	ADD_SIM1_PAS1_13, //255
	ADD_SIM1_PAS1_14, //256
	ADD_SIM1_PAS1_15, //257
	//
	ADD_SIM2_LOG1_1, //258
	ADD_SIM2_LOG1_2, //259
	ADD_SIM2_LOG1_3, //260
	ADD_SIM2_LOG1_4, //261
	ADD_SIM2_LOG1_5, //262
	ADD_SIM2_LOG1_6, //263
	ADD_SIM2_LOG1_7, //264
	ADD_SIM2_LOG1_8, //265
	ADD_SIM2_LOG1_9, //266
	ADD_SIM2_LOG1_10, //267
	ADD_SIM2_LOG1_11, //268
	ADD_SIM2_LOG1_12, //269
	ADD_SIM2_LOG1_13, //270
	ADD_SIM2_LOG1_14, //271
	ADD_SIM2_LOG1_15, //272
	//
	ADD_SIM2_PAS1_1, //273
	ADD_SIM2_PAS1_2, //274
	ADD_SIM2_PAS1_3, //275
	ADD_SIM2_PAS1_4, //276
	ADD_SIM2_PAS1_5, //277
	ADD_SIM2_PAS1_6, //278
	ADD_SIM2_PAS1_7, //279
	ADD_SIM2_PAS1_8, //280
	ADD_SIM2_PAS1_9, //281
	ADD_SIM2_PAS1_10, //282
	ADD_SIM2_PAS1_11, //283
	ADD_SIM2_PAS1_12, //284
	ADD_SIM2_PAS1_13, //285
	ADD_SIM2_PAS1_14, //286
	ADD_SIM2_PAS1_15, //287
	//----------------
	ADD_SIM1_TIPOAUTENTICACAO, //288
	ADD_SIM2_TIPOAUTENTICACAO, //289
	// Ethernet
	ADD_MAC_ADDRESS,   // 290
	ADD_MAC_ADDRESS_1, // 291
	ADD_MAC_ADDRESS_2, // 292

	ADD_DHCP_HABILITADO, // 293

	ADD_IP_ETH_1, //294
	ADD_IP_ETH_2, //295
	ADD_GATEWAY_ETH_1, //296
	ADD_GATEWAY_ETH_2, //297
	ADD_MASC_ETH_1, //298
	ADD_MASC_ETH_2, //299

	// PORTA SUPERVISAO 1 - SERIAL1 ou SOCKET0
	ADD_TIPO_CON_SUPERVISAO, //300
	// PORTA FABRICANTE - SERIAL2 ou SOCKET1
	ADD_TIPO_CON_FABRICANTE, //301

	// SOCKET0
	ADD_TIPO_SOCK0, //302   cliente ou servidor
	ADD_IP_SOCK0_1, //303
	ADD_IP_SOCK0_2, //304
	ADD_PORTA_SOCK0, //305
	// SOCKET1
	ADD_TIPO_SOCK1, //306   cliente ou servidor
	ADD_IP_SOCK1_1, //307
	ADD_IP_SOCK1_2, //308
	ADD_PORTA_SOCK1, //309
	//-----------------
	ADD_CALARM, // 310
	//Bateria
	ADD_CARGA_BAT1, //311
	ADD_CARGA_BAT2, //312
	//--------------------
	//SMS para conhecimento do Telefone
	ADD_NUMTELSMS_1, // 313
	ADD_NUMTELSMS_2, // 314
	ADD_NUMTELSMS_3, // 315
	ADD_NUMTELSMS_4, // 316
	ADD_NUMTELSMS_5, // 317
	ADD_NUMTELSMS_6, // 318
	ADD_NUMTELSMS_7, // 319
	//--------------------
	//DNS 1 - 40 caracteres
	ADD_DNS1_1, //320
	ADD_DNS1_2, //321
	ADD_DNS1_3, //322
	ADD_DNS1_4, //323
	ADD_DNS1_5, //324
	ADD_DNS1_6, //325
	ADD_DNS1_7, //326
	ADD_DNS1_8, //327
	ADD_DNS1_9, //328
	ADD_DNS1_10, //329
	ADD_DNS1_11, //330
	ADD_DNS1_12, //331
	ADD_DNS1_13, //332
	ADD_DNS1_14, //333
	ADD_DNS1_15, //334
	ADD_DNS1_16, //335
	ADD_DNS1_17, //336
	ADD_DNS1_18, //337
	ADD_DNS1_19, //338
	ADD_DNS1_20, //339
	//DNS 2 - 40 caracteres
	ADD_DNS2_1, //340
	ADD_DNS2_2, //341
	ADD_DNS2_3, //342
	ADD_DNS2_4, //343
	ADD_DNS2_5, //344
	ADD_DNS2_6, //345
	ADD_DNS2_7, //346
	ADD_DNS2_8, //347
	ADD_DNS2_9, //348
	ADD_DNS2_10, //349
	ADD_DNS2_11, //350
	ADD_DNS2_12, //351
	ADD_DNS2_13, //352
	ADD_DNS2_14, //353
	ADD_DNS2_15, //354
	ADD_DNS2_16, //355
	ADD_DNS2_17, //356
	ADD_DNS2_18, //357
	ADD_DNS2_19, //358
	ADD_DNS2_20, //359
	//----------------
	//KEEPALIVE
	ADD_KEEPALIVE, // 360  //Ativa/desativa keepalive do modulo
	ADD_TEMPO_KEEPALIVE, //361 //Configura a tempo de envio do keepalive do modulo
	//-------------------
	ADD_PRIORIDADE_PPP, //362
	//------------------
	ADD_TEMPO_PING, //363
	//------------------
	ADD_BLOQUEIO_REDUNDANCIA_APN, //364
	//------------------
	ADD_SAIDIG1, //365 //Saida digital 1. Se valor = 1 ABRE / Se valor = 2 FECHA / Se valor > PULSA pelo tempo configurado nos bits de 2 a 15
	//------------------
	ADD_BLOQUEIO_DESLIGAMENTO,  //366 - Bloqueia DESLIGAMENTO
	ADD_TEMPO_DESLIGAMENTO_1,  //367 - TEMPO DESLIGAMENTO
	ADD_TEMPO_DESLIGAMENTO_2,  //368 - TEMPO DESLIGAMENTO
	//------------------
	ADD_RES369, //369
	//-------------------
	ADD_NUMSER_1 = 500, //( string ASCIIZ, tamanho 10 caracteres)
	ADD_NUMSER_2, //501
	ADD_NUMSER_3, //502
	ADD_NUMSER_4, //503
	ADD_NUMSER_5, //504
	ADD_MODELO,   //505
	ADD_RES506    //506

}
MODBUS_HR_ADD;

typedef struct
{
	//
	// Coils
	//
	uint16_t IN_1; // 0
	uint16_t IN_2; // 1
	uint16_t OUT_1; // 2
	//
	// IR, input registers
	//
	uint16_t IMEI_1; // 0 ( string ASCIIZ, tamanho 20 caracteres)
	uint16_t IMEI_2; // 1
	uint16_t IMEI_3; // 2
	uint16_t IMEI_4; // 3
	uint16_t IMEI_5; // 4
	uint16_t IMEI_6; // 5
	uint16_t IMEI_7; // 6
	uint16_t IMEI_8; // 7
	uint16_t IMEI_9; // 8
	uint16_t IMEI_10; // 9
	//
	uint16_t SIM1_SQMVALMIN; // 10 ( 0..31 ou 99 )
	uint16_t SIM1_SQMVALMAX; // 11 ( 0..31 ou 99 )
	uint16_t SIM1_SQMVALMED; // 12 ( 0..31 ou 99 )
	uint16_t SIM1_SQMAMO; //	13
	uint16_t SIM1_SQMDES; //	14
	uint16_t SIM2_SQMVALMIN; // 15 ( 0..31 ou 99 )
	uint16_t SIM2_SQMVALMAX; // 16 ( 0..31 ou 99 )
	uint16_t SIM2_SQMVALMED; // 17 ( 0..31 ou 99 )
	uint16_t SIM2_SQMAMO; //	18
	uint16_t SIM2_SQMDES; // 19
	//
	uint16_t TEMPER; // 20
	//
	uint16_t VERFIR_1; // 21 ( 4 octetos podendo cada um variar de 0.. 255, ex.: 2.0.5.0 )
	uint16_t VERFIR_2; // 22
	//
	uint16_t SIM1_NUMBER_1; // 23
	uint16_t SIM1_NUMBER_2; // 24
	uint16_t SIM1_NUMBER_3; // 25
	uint16_t SIM1_NUMBER_4; // 26
	uint16_t SIM1_NUMBER_5; // 27
	uint16_t SIM1_NUMBER_6; // 28
	uint16_t SIM1_NUMBER_7; // 29
	uint16_t SIM1_NUMBER_8; // 30
	uint16_t SIM1_NUMBER_9; // 31
	uint16_t SIM1_NUMBER_10; // 32
	uint16_t SIM1_NUMBER_11; // 33
	uint16_t SIM1_NUMBER_12; // 34
	uint16_t SIM1_NUMBER_13; // 35
	uint16_t SIM1_NUMBER_14; // 36
	uint16_t SIM1_NUMBER_15; // 37
	//
	uint16_t SIM2_NUMBER_1; // 38
	uint16_t SIM2_NUMBER_2; // 39
	uint16_t SIM2_NUMBER_3; // 40
	uint16_t SIM2_NUMBER_4; // 41
	uint16_t SIM2_NUMBER_5; // 42
	uint16_t SIM2_NUMBER_6; // 43
	uint16_t SIM2_NUMBER_7; // 44
	uint16_t SIM2_NUMBER_8; // 45
	uint16_t SIM2_NUMBER_9; // 46
	uint16_t SIM2_NUMBER_10; // 47
	uint16_t SIM2_NUMBER_11; // 48
	uint16_t SIM2_NUMBER_12; // 49
	uint16_t SIM2_NUMBER_13; // 50
	uint16_t SIM2_NUMBER_14; // 51
	uint16_t SIM2_NUMBER_15; // 52
	//
	uint16_t MODMAN_1; // 53
	uint16_t MODMAN_2; // 54
	uint16_t MODMAN_3; // 55
	uint16_t MODMAN_4; // 56
	uint16_t MODMAN_5; // 57
	//
	uint16_t MODMOD_1; // 58
	uint16_t MODMOD_2; // 59
	uint16_t MODMOD_3; // 60
	uint16_t MODMOD_4; // 61
	uint16_t MODMOD_5; // 62
	//
	uint16_t MODREV_1; // 63
	uint16_t MODREV_2; // 64
	uint16_t MODREV_3; // 65
	uint16_t MODREV_4; // 66
	uint16_t MODREV_5; // 67
	uint16_t MODREV_6; // 68
	uint16_t MODREV_7; // 69
	uint16_t MODREV_8; // 70
	uint16_t MODREV_9; // 71
	uint16_t MODREV_10; // 72
	//
	//
	uint16_t SIM1_OPER_1; // 73
	uint16_t SIM1_OPER_2; //	74
	uint16_t SIM1_OPER_3; //	75
	uint16_t SIM1_OPER_4; //	76
	uint16_t SIM1_OPER_5; //	77
	uint16_t SIM1_OPER_6; //	78
	uint16_t SIM1_OPER_7; //	79
	uint16_t SIM1_OPER_8; //	80
	uint16_t SIM1_OPER_9; //	81
	uint16_t SIM1_OPER_10; // 82
	//
	uint16_t SIM2_OPER_1; // 83
	uint16_t SIM2_OPER_2; //	84
	uint16_t SIM2_OPER_3; //	85
	uint16_t SIM2_OPER_4; //	86
	uint16_t SIM2_OPER_5; //	87
	uint16_t SIM2_OPER_6; //	88
	uint16_t SIM2_OPER_7; //	89
	uint16_t SIM2_OPER_8; //	90
	uint16_t SIM2_OPER_9; //	91
	uint16_t SIM2_OPER_10; // 92

	uint32_t BYTES_ROTEAMENTO; // 93
	uint32_t BYTES_COMUNICACAO; // 95
	uint32_t BYTES_FABRICANTE; // 97
	//
	uint16_t NUM_MSG_TRA_ROT; //99 N�mero de mensagens trafegadas Roteamento
	uint16_t NUM_MSG_TRA_COM; //100 N�mero de mensagens trafegadas Comunica��o
	uint16_t NUM_MSG_TRA_FAB; //101 N�mero de mensagens trafegadas Fabricante
	//
	uint16_t FLAG; //102
	//
	//
	uint16_t IP_1; //103
	uint16_t IP_2; //104
	//
	//
	uint16_t STATUS_MOBILE_COUNTRY; //105
	uint16_t STATUS_MOBILE_NETWORK; //106
	uint16_t STATUS_LOCATION_AREA; //107
	uint16_t STATUS_CELL_INDENTITY; //108
	uint16_t ERB; //109
	uint16_t CANAL; //110
	uint16_t TIPO_HARDW; //111 Tipo de hardware: 1 = mono-sim, 2 = dual-sim
	uint16_t VERFIR_BOOTLOADER_1; // 112 ( 4 octetos podendo cada um variar de 0.. 255, ex.: 2.0.5.0 )
	uint16_t VERFIR_BOOTLOADER_2; // 113
	uint16_t ESTADO_ENT_1; //114
	uint16_t ESTADO_ENT_2;  //115
	uint16_t TEN_BAT1; //116
	uint16_t TEN_BAT2; //117
	//
	uint16_t TECNOLOGIA_COMUNICACAO; //118
	//
	//
	// HR, holding registers
	//
	//
	uint16_t TEMVALCONGPR; //0
	//
	uint16_t MODOPE; //1
	//
	uint16_t SIMCARSEL; //2
	//
	uint16_t SIM1_TEL_1; //3
	uint16_t SIM1_TEL_2; //4
	uint16_t SIM1_TEL_3; //5
	uint16_t SIM1_TEL_4; //6
	uint16_t SIM1_TEL_5; //7
	uint16_t SIM1_TEL_6; //8
	uint16_t SIM1_TEL_7; //9
	uint16_t SIM1_TEL_8; //10
	uint16_t SIM1_TEL_9; //11
	uint16_t SIM1_TEL_10; //12
	//
	uint16_t SIM2_TEL_1; //13
	uint16_t SIM2_TEL_2; //14
	uint16_t SIM2_TEL_3; //15
	uint16_t SIM2_TEL_4; //16
	uint16_t SIM2_TEL_5; //17
	uint16_t SIM2_TEL_6; //18
	uint16_t SIM2_TEL_7; //19
	uint16_t SIM2_TEL_8; //20
	uint16_t SIM2_TEL_9; //21
	uint16_t SIM2_TEL_10; //22
	//
	uint16_t SIM1; //23
	//
	uint16_t SIM1_PIN1; //24
	uint16_t SIM1_PIN2; //25
	//
	uint16_t SIM1_PUK1_1; //26
	uint16_t SIM1_PUK1_2; //27
	uint16_t SIM1_PUK2_1; //28
	uint16_t SIM1_PUK2_2; //29
	//
	//
	uint16_t ALTERAR_PIN1_SIM1; //30
	uint16_t HAB_PIN1_SIM1; //31
	uint16_t NOVO_SIM1_PIN1; //32
	//
	uint16_t SIM1_APN1; //33
	//
	uint16_t SIM1_APN1_1; //34
	uint16_t SIM1_APN1_2; //35
	uint16_t SIM1_APN1_3; //36
	uint16_t SIM1_APN1_4; //37
	uint16_t SIM1_APN1_5; //38
	uint16_t SIM1_APN1_6; //39
	uint16_t SIM1_APN1_7; //40
	uint16_t SIM1_APN1_8; //41
	uint16_t SIM1_APN1_9; //42
	uint16_t SIM1_APN1_10; //43
	uint16_t SIM1_APN1_11; //44
	uint16_t SIM1_APN1_12; //45
	uint16_t SIM1_APN1_13; //46
	uint16_t SIM1_APN1_14; //47
	uint16_t SIM1_APN1_15; //48
	uint16_t SIM1_APN1_16; //49
	uint16_t SIM1_APN1_17; //50
	uint16_t SIM1_APN1_18; //51
	uint16_t SIM1_APN1_19; //52
	uint16_t SIM1_APN1_20; //53
	//
	uint16_t RES54; //54 //Aten��o ao usar essa �rea de mem�ria. Pesquisar no firmware os locais onde ele est� sendo usada para renomear.
	uint16_t RES55; //55
	uint16_t RES56; //56
	uint16_t RES57; //57
	uint16_t RES58; //58
	uint16_t RES59; //59
	//
	uint16_t RES60; //60 //Aten��o ao usar essa �rea de mem�ria. Pesquisar no firmware os locais onde ele est� sendo usada para renomear.
	uint16_t RES61; //61
	uint16_t RES62; //62
	uint16_t RES63; //63
	uint16_t RES64; //64
	uint16_t RES65; //65
	//
	//
	uint16_t SIM1_APN1_IPPOR_SEL; //66 Par IP/Porta selecionado no sim 1 (1 ou 2)
	//
	//
	uint16_t SIM1_APN1_IP1; //67
	uint16_t SIM1_APN1_IP1_1; //68
	uint16_t SIM1_APN1_IP1_2; //69
	uint16_t SIM1_APN1_POR1; //70
	//
	uint16_t SIM1_APN1_IP2; //71
	uint16_t SIM1_APN1_IP2_1; //72
	uint16_t SIM1_APN1_IP2_2; //73
	uint16_t SIM1_APN1_POR2; //74
	//
	uint16_t SIM1_SOCKET1_UART; //75
	uint16_t SIM1_SOCKET2_UART; //76
	//
	uint16_t SIM1_NIV_PRI; //77
	uint16_t SIM1_EST_CAR; //78
	//
	//
	uint16_t DES_PIN1_SIM1; //79
	uint16_t DES_PIN1_SIM2; //80
	uint16_t USO_PIN1_SIM1; //81
	uint16_t USO_PIN1_SIM2; //82
	//
	uint16_t COPIA_TIPO_HARDW; //83 Para possibilitar a grava��o do tipo de hardware via CfgHorus
	//
	uint16_t SIM2; //84
	//
	uint16_t SIM2_PIN1; //85
	uint16_t SIM2_PIN2; //86
	//
	uint16_t SIM2_PUK1_1; //87
	uint16_t SIM2_PUK1_2; //88
	uint16_t SIM2_PUK2_1; //89
	uint16_t SIM2_PUK2_2; //90
	//
	//
	uint16_t ALTERAR_PIN1_SIM2; //91
	uint16_t HAB_PIN1_SIM2; //92
	uint16_t NOVO_SIM2_PIN1; //93
	//
	uint16_t SIM2_APN1; //94
	//
	uint16_t SIM2_APN1_1; //95
	uint16_t SIM2_APN1_2; //96
	uint16_t SIM2_APN1_3; //97
	uint16_t SIM2_APN1_4; //98
	uint16_t SIM2_APN1_5; //99
	uint16_t SIM2_APN1_6; //100
	uint16_t SIM2_APN1_7; //101
	uint16_t SIM2_APN1_8; //102
	uint16_t SIM2_APN1_9; //103
	uint16_t SIM2_APN1_10; //104
	uint16_t SIM2_APN1_11; //105
	uint16_t SIM2_APN1_12; //106
	uint16_t SIM2_APN1_13; //107
	uint16_t SIM2_APN1_14; //108
	uint16_t SIM2_APN1_15; //109
	uint16_t SIM2_APN1_16; //110
	uint16_t SIM2_APN1_17; //111
	uint16_t SIM2_APN1_18; //112
	uint16_t SIM2_APN1_19; //113
	uint16_t SIM2_APN1_20; //114
	//
	uint16_t RES115; //115 //Aten��o ao usar essa �rea de mem�ria. Pesquisar no firmware os locais onde ele est� sendo usada para renomear.
	uint16_t RES116; //116
	uint16_t RES117; //117
	uint16_t RES118; //118
	uint16_t RES119; //119
	uint16_t RES120; //120
	//
	uint16_t RES121; //121 //Aten��o ao usar essa �rea de mem�ria. Pesquisar no firmware os locais onde ele est� sendo usada para renomear.
	uint16_t RES122; //122
	uint16_t RES123; //123
	uint16_t RES124; //124
	uint16_t RES125; //125
	uint16_t RES126; //126
	//
	uint16_t SIM2_APN1_IPPOR_SEL; //127 Par IP/Porta selecionado no sim 2 (1 ou 2)
	//
	uint16_t SIM2_APN1_IP1; //128
	uint16_t SIM2_APN1_IP1_1; //129
	uint16_t SIM2_APN1_IP1_2; //130
	uint16_t SIM2_APN1_POR1; //131
	//
	uint16_t SIM2_APN1_IP2; //132
	uint16_t SIM2_APN1_IP2_1; //133
	uint16_t SIM2_APN1_IP2_2; //134
	uint16_t SIM2_APN1_POR2; //135
	//
	uint16_t SIM2_SOCKET1_UART; //136
	uint16_t SIM2_SOCKET2_UART; //137
	//
	//
	uint16_t SIM2_NIV_PRI; //138
	uint16_t SIM2_EST_CAR; //139
	//
	uint16_t IP_SOCFAB_1; //140
	uint16_t IP_SOCFAB_2; //141
	uint16_t IP_SOCFAB; //142 Vari�vel para indicar o uso de IP diferente p/ socket fabricante
	//
	uint16_t MODO_SERIAL1; //143 0=RS232 / 1=RS485
	//
	uint16_t ATIVAR_SOCKET_COM; //144
	//
	uint16_t ATIVAR_SOCKET_FAB; ////145
	//
	uint16_t TEMDESSOCFAB; //146
	uint16_t TEMINASOCFAB; //147
	uint16_t TEMDESSOCCOM; //148 Tempo de perman�ncia no socket de comunica��o
	uint16_t TEMINASOCCOM; //149 Tempo de inatividade do socket de comunica��o
	//
	uint16_t SOCKETCOM_POR; //150
	uint16_t SOCKETFAB_POR; //151
	//
	//
	//
	uint16_t SIM17; //152
	uint16_t SIM18; //153
	uint16_t SIM19; //154
	uint16_t SIM20; //155
	uint16_t SIM21; //156
	//
	//
	//
	uint16_t COM0_CONFIG_PORT; //157
	uint16_t COM1_CONFIG_PORT; //158
	uint16_t COM2_CONFIG_PORT; //159
	uint16_t COM3_CONFIG_PORT; //160
	//
	uint16_t TEMMANMODCFG; //161
	uint16_t TEMINAMODCFG; //162
	//
	uint16_t TEMMANMODTTY; //163
	uint16_t TEMINAMODTTY; //164
	//
	uint16_t TOTMEDMODSQM; //165
	//
	uint16_t TEMMANMODGPR; //166
	uint16_t TEMINAMODGPR; //167
	//
	uint16_t TEMPERCONRED; //168
	//
	uint16_t SERCMD; //169
	//
	//
	uint16_t TEMAGUATT; //170
	uint16_t TOTTENATT; //171
	//
	uint16_t FTP_FLAG_BOOTLOADER; //172 Flag para envio p/ bootloader
	//
	uint16_t FTP_USUARIO_1; //173 ( string ASCIIZ; tamanho 12 caracteres)
	uint16_t FTP_USUARIO_2; //174
	uint16_t FTP_USUARIO_3; //175
	uint16_t FTP_USUARIO_4; //176
	uint16_t FTP_USUARIO_5; //177
	uint16_t FTP_USUARIO_6; //178
	//
	uint16_t FTP_SENHA_1; //179 ( string ASCIIZ; tamanho 12 caracteres)
	uint16_t FTP_SENHA_2; //180
	uint16_t FTP_SENHA_3; //181
	uint16_t FTP_SENHA_4; //182
	uint16_t FTP_SENHA_5; //183
	uint16_t FTP_SENHA_6; //184
	//
	uint16_t FTP_SIM1_APN1_IP1_1; // 185 ( 2 octetos podendo cada um variar de 0.. 255; ex.: 192.168 )
	uint16_t FTP_SIM1_APN1_IP1_2; // 186 ( 2 octetos podendo cada um variar de 0.. 255; ex.: 192.168 )
	//
	uint16_t FTP_SIM1_APN1_POR1; // 187 ( 0..65535 )
	//
	uint16_t FTP_SIM2_APN1_IP1_1; // 188 ( 2 octetos podendo cada um variar de 0.. 255; ex.: 192.168 )
	uint16_t FTP_SIM2_APN1_IP1_2; // 189 ( 2 octetos podendo cada um variar de 0.. 255; ex.: 192.168 )
	//
	uint16_t FTP_SIM2_APN1_POR1; // 190 ( 0..65535 )
	//
	uint16_t FTP_NOMEARQ_1; // 191 ( string ASCIIZ; tamanho 12 caracteres)
	uint16_t FTP_NOMEARQ_2; // 192
	uint16_t FTP_NOMEARQ_3; // 193
	uint16_t FTP_NOMEARQ_4; // 194
	uint16_t FTP_NOMEARQ_5; // 195
	uint16_t FTP_NOMEARQ_6; // 196
	//
	uint16_t FTP_CAMINHO_1; // 197 ( string ASCIIZ; tamanho 20 caracteres)
	uint16_t FTP_CAMINHO_2; // 198
	uint16_t FTP_CAMINHO_3; // 199
	uint16_t FTP_CAMINHO_4; // 200
	uint16_t FTP_CAMINHO_5; // 201
	uint16_t FTP_CAMINHO_6; // 202
	uint16_t FTP_CAMINHO_7; // 203
	uint16_t FTP_CAMINHO_8; // 204
	uint16_t FTP_CAMINHO_9; // 205
	uint16_t FTP_CAMINHO_10; // 206
	//
	uint16_t FTP_SIMSEL; // 207
	//
	uint16_t MODO_GPRS_STANDBY; // 208
	uint16_t VAL_SOCK_FAB; // 209
	uint16_t RESET_FLAG; // 210 //RESET da FLAG de Controle/Alarme
	uint16_t FAT_COR_TEM[2]; // 211
	uint16_t CONTR_FALHA; // 213
	uint16_t CONTR_RESET; // 214 //1 -> SMS ; 2 -> Reinicio do Sistema
	uint16_t TEMPERSERRED; // 215  //Tempo de perman�ncia no servidor redundante
	uint16_t SIM1_IP_EXTERNO_SERPRI_1; // 216
	uint16_t SIM1_IP_EXTERNO_SERPRI_2; // 217
	uint16_t SIM1_IP_EXTERNO_SERRED_1; // 218
	uint16_t SIM1_IP_EXTERNO_SERRED_2; // 219
	uint16_t TEMPERAPNPUB; // 220 Tempo de perman�ncia na APN p�blica
	uint16_t SIM2_IP_EXTERNO_SERPRI_1; // 221
	uint16_t SIM2_IP_EXTERNO_SERPRI_2; // 222
	uint16_t SIM2_IP_EXTERNO_SERRED_1; // 223
	uint16_t SIM2_IP_EXTERNO_SERRED_2; // 224
	uint16_t SOCKETCOM_PORALT; // 225
	uint16_t PORALTSOCCOM; //226 //Ativa utiliza��o da porta redundante para o socket de comunica��o
	uint16_t TEMPORELE; // 227
	//**Altera'cao para comportar mais caracter em login e senha
	uint16_t SIM1_LOG1_1; //228
	uint16_t SIM1_LOG1_2; //229
	uint16_t SIM1_LOG1_3; //230
	uint16_t SIM1_LOG1_4; //231
	uint16_t SIM1_LOG1_5; //232
	uint16_t SIM1_LOG1_6; //233
	uint16_t SIM1_LOG1_7; //234
	uint16_t SIM1_LOG1_8; //235
	uint16_t SIM1_LOG1_9; //236
	uint16_t SIM1_LOG1_10; //237
	uint16_t SIM1_LOG1_11; //238
	uint16_t SIM1_LOG1_12; //239
	uint16_t SIM1_LOG1_13; //240
	uint16_t SIM1_LOG1_14; //241
	uint16_t SIM1_LOG1_15; //242
	//
	uint16_t SIM1_PAS1_1; //243
	uint16_t SIM1_PAS1_2; //244
	uint16_t SIM1_PAS1_3; //245
	uint16_t SIM1_PAS1_4; //246
	uint16_t SIM1_PAS1_5; //247
	uint16_t SIM1_PAS1_6; //248
	uint16_t SIM1_PAS1_7; //249
	uint16_t SIM1_PAS1_8; //250
	uint16_t SIM1_PAS1_9; //251
	uint16_t SIM1_PAS1_10; //252
	uint16_t SIM1_PAS1_11; //253
	uint16_t SIM1_PAS1_12; //254
	uint16_t SIM1_PAS1_13; //255
	uint16_t SIM1_PAS1_14; //256
	uint16_t SIM1_PAS1_15; //257
	//
	uint16_t SIM2_LOG1_1; //258
	uint16_t SIM2_LOG1_2; //259
	uint16_t SIM2_LOG1_3; //260
	uint16_t SIM2_LOG1_4; //261
	uint16_t SIM2_LOG1_5; //262
	uint16_t SIM2_LOG1_6; //263
	uint16_t SIM2_LOG1_7; //264
	uint16_t SIM2_LOG1_8; //265
	uint16_t SIM2_LOG1_9; //266
	uint16_t SIM2_LOG1_10; //267
	uint16_t SIM2_LOG1_11; //268
	uint16_t SIM2_LOG1_12; //269
	uint16_t SIM2_LOG1_13; //270
	uint16_t SIM2_LOG1_14; //271
	uint16_t SIM2_LOG1_15; //272
	//
	uint16_t SIM2_PAS1_1; //273
	uint16_t SIM2_PAS1_2; //274
	uint16_t SIM2_PAS1_3; //275
	uint16_t SIM2_PAS1_4; //276
	uint16_t SIM2_PAS1_5; //277
	uint16_t SIM2_PAS1_6; //278
	uint16_t SIM2_PAS1_7; //279
	uint16_t SIM2_PAS1_8; //280
	uint16_t SIM2_PAS1_9; //281
	uint16_t SIM2_PAS1_10; //282
	uint16_t SIM2_PAS1_11; //283
	uint16_t SIM2_PAS1_12; //284
	uint16_t SIM2_PAS1_13; //285
	uint16_t SIM2_PAS1_14; //286
	uint16_t SIM2_PAS1_15; //287
	//----------------
	uint16_t SIM1_TIPOAUTENTICACAO; //288
	uint16_t SIM2_TIPOAUTENTICACAO; //289
	// Ethernet
	uint16_t MAC_ADDRESS;   // 290
	uint16_t MAC_ADDRESS_1; // 291
	uint16_t MAC_ADDRESS_2; // 292

	uint16_t DHCP_HABILITADO; // 293

	uint16_t IP_ETH_1; //294
	uint16_t IP_ETH_2; //295
	uint16_t GATEWAY_ETH_1; //296
	uint16_t GATEWAY_ETH_2; //297
	uint16_t MASC_ETH_1; //298
	uint16_t MASC_ETH_2; //299

	// PORTA SUPERVISAO 1 - SERIAL1 ou SOCKET0
	uint16_t TIPO_CON_SUPERVISAO; //300
	// PORTA FABRICANTE - SERIAL2 ou SOCKET1
	uint16_t TIPO_CON_FABRICANTE; //301

	// SOCKET0
	uint16_t TIPO_SOCK0; //302   cliente ou servidor
	uint16_t IP_SOCK0_1; //303
	uint16_t IP_SOCK0_2; //304
	uint16_t PORTA_SOCK0; //305
	// SOCKET1
	uint16_t TIPO_SOCK1; //306   cliente ou servidor
	uint16_t IP_SOCK1_1; //307
	uint16_t IP_SOCK1_2; //308
	uint16_t PORTA_SOCK1; //309
	//-----------------
	uint16_t CALARM; // 310
	//Bateria
	uint16_t CARGA_BAT1; //311
	uint16_t CARGA_BAT2; //312
	//--------------------
	//SMS para conhecimento do Telefone
	uint16_t NUMTELSMS_1; // 313
	uint16_t NUMTELSMS_2; // 314
	uint16_t NUMTELSMS_3; // 315
	uint16_t NUMTELSMS_4; // 316
	uint16_t NUMTELSMS_5; // 317
	uint16_t NUMTELSMS_6; // 318
	uint16_t NUMTELSMS_7; // 319
	//--------------------
	//DNS 1 - 40 caracteres
	uint16_t DNS1_1; //320
	uint16_t DNS1_2; //321
	uint16_t DNS1_3; //322
	uint16_t DNS1_4; //323
	uint16_t DNS1_5; //324
	uint16_t DNS1_6; //325
	uint16_t DNS1_7; //326
	uint16_t DNS1_8; //327
	uint16_t DNS1_9; //328
	uint16_t DNS1_10; //329
	uint16_t DNS1_11; //330
	uint16_t DNS1_12; //331
	uint16_t DNS1_13; //332
	uint16_t DNS1_14; //333
	uint16_t DNS1_15; //334
	uint16_t DNS1_16; //335
	uint16_t DNS1_17; //336
	uint16_t DNS1_18; //337
	uint16_t DNS1_19; //338
	uint16_t DNS1_20; //339
	//DNS 2 - 40 caracteres
	uint16_t DNS2_1; //340
	uint16_t DNS2_2; //341
	uint16_t DNS2_3; //342
	uint16_t DNS2_4; //343
	uint16_t DNS2_5; //344
	uint16_t DNS2_6; //345
	uint16_t DNS2_7; //346
	uint16_t DNS2_8; //347
	uint16_t DNS2_9; //348
	uint16_t DNS2_10; //349
	uint16_t DNS2_11; //350
	uint16_t DNS2_12; //351
	uint16_t DNS2_13; //352
	uint16_t DNS2_14; //353
	uint16_t DNS2_15; //354
	uint16_t DNS2_16; //355
	uint16_t DNS2_17; //356
	uint16_t DNS2_18; //357
	uint16_t DNS2_19; //358
	uint16_t DNS2_20; //359
	//----------------
	//KEEPALIVE
	uint16_t KEEPALIVE; // 360  //Ativa/desativa keepalive do modulo
	uint16_t TEMPO_KEEPALIVE; //361 //Configura a tempo de envio do keepalive do modulo
	//-------------------
	uint16_t PRIORIDADE_PPP; //362
	//------------------
	uint16_t TEMPO_PING; //363
	//------------------
	uint16_t BLOQUEIO_REDUNDANCIA_APN;  //364 - Bloqueia a redundancia de APN
	//------------------
	uint16_t SAIDIG1; //365 //Saida digital 1. Se valor = 1 ABRE / Se valor = 2 FECHA / Se valor > PULSA pelo tempo configurado nos bits de 2 a 15
	//------------------
	uint16_t BLOQUEIO_DESLIGAMENTO;  //366 - Bloqueia DESLIGAMENTO
	uint16_t TEMPO_DESLIGAMENTO_1;  //367 - TEMPO DESLIGAMENTO
	uint16_t TEMPO_DESLIGAMENTO_2;  //368 - TEMPO DESLIGAMENTO
	//------------------
	uint16_t RES369;
	//    ---
	uint16_t NUMSER_1; //500 ( string ASCIIZ, tamanho 10 caracteres)
	uint16_t NUMSER_2; //501
	uint16_t NUMSER_3; //502
	uint16_t NUMSER_4; //503
	uint16_t NUMSER_5; //504
	uint16_t MODELO;   //505
	uint16_t RES506;   //506
}

TGetIndexModbus;

extern uint16_t InterpreterMODBUS(uint8_t*, uint16_t);
extern uint8_t SeparaMensagensMODBUS(uint8_t*, int);

void LoadHoldingRegisterRAM(void);
void LoadInputRegisterRAM(void);
void LoadCoilRegisterRAM(void);
void LoadEspelhoRAM(void);
void CreateDefaultModbusMap (void *fileDataBuffer, TModbusMap * modbusMap);
void ModbusInit ();

#endif /* THIRD_PARTY_MODBUS_MODBUS_MAP_H_ */
