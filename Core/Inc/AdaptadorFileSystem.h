/*
 * AdaptadorFileSystem.h
 *
 * @brief Funcoes adaptadoras para interface com o sistema de arquivos
 *
 * Copyright (c) 2020 Lupa Tecnologia e Sistemas Ltda. All rights reserved.
 *
 *  Created on: 26 de fev de 2021
 *      Author: Flavio Flores Villaca
 */

#ifndef INC_ADAPTADORFILESYSTEM_H_
#define INC_ADAPTADORFILESYSTEM_H_


#include <file_system.h>
#include "lfs.h"


extern lfs_t lfs;


#define NumeroMaximoDeArquivos 20
#define NumeroDeArquivos 22 // 2+Total de Arquivos -> desejados



typedef struct
{
	char NomeArquivo[NumeroMaximoDeArquivos+1][100];
	uint8_t ArqLidos;

}TListaDeArquivo;


/**
 * @brief Funcao de inicializa o FileSystem.
 * @note  As seguintes ações são executadas:
 *         - Inicialização da dataflash;
 *         - Inicialização do FS;
 *         - Criação de diretórios;
 *         - Leitura do arquivo de configurações;
 * @retval None
 */
void IniciarFileSystem(void);

/**
 * @brief Funções de encerra o funcionamento do FileSystem.
 *      As seguintes ações são executadas:
 *        - Fechamento dos arquivos de agregação;
 *        - Desmonta a unidade;
 * @retval int Código de erro
 */

int EncerrarFileSystem();

/**
 * @brief  Lista os arquivos de um diretório para envio via DNP3 (formato de arquivo)
 * @param  buffer : buffer de escrita da string contendo a lista de arquivos
 * @param  buffer : buffer de escrita da string contendo a lista de arquivos
 * @param  startRecord : AdcHandle handle
 * @retval Número de bytes da string contendo os nomes de arquivo
 */
int ArquivoExiste(char *caminho);


/**
 * @brief Função que testa o desempenho do file system.
 *        Testa o desempenho do file system nas tarefas de crição, apagamento e leitura de arquivos.
 * @retval none
 */

void TestarFileSystem();

/**
 * @brief  Apaga todos os arquivos de uma pasta
 * @param  caminho : caminho da pasta/diretório onde os arquivos serão apagados
 * @retval nenhum
 */
void ApagarArquivos(char *caminho);

/**
 * @brief  Realiza a limpeza de arquivos antigos da pasta mantendo "max" arquivos mais novos
 * @param  caminho : caminho da pasta/diretório onde os arquivos serão apagados
 * @param  max : quantidade de arquivos máximo na pasta
 * @retval nenhum
 */

void LimparPasta(char *caminho, unsigned short max);
uint8_t ListaDeArquivos(char *nomeDir, TListaDeArquivo *listaDeArquivo);
uint8_t ExclusaoListaDeArquivo(char *nomeDir, TListaDeArquivo *listaDeArquivo);


#endif /* INC_ADAPTADORFILESYSTEM_H_ */
