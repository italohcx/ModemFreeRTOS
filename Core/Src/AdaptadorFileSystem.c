/*
 * AdaptadorFileSystem.c
 *
 *  Created on: Nov 23, 2022
 *      Author: italo.francis
 */


#include "AdaptadorFileSystem.h"
#include "w25qxx.h"
#include "lfs_util.h"
#include "lfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG(...) printf(__VA_ARGS__)
#define LOG2(...) printf(__VA_ARGS__)
#define LOG3(...) printf(__VA_ARGS__)



lfs_t lfs;             // Struct de controle do File System

extern lfs_t lfs;

//#define LOG   printf   // Log de n�vel 1 - erros
//#define LOG2  printf   // Log de n�vel 2 - informa��o
//#define LOG3  //printf   // Log de n�vel 3 - debug


//
// Teste de arquivos
//
struct
{
	float min;
	double med;
	float max;
	int n;
} testeFlash;



/**
 * @brief Função de inicializa o FileSystem.
 * @note  As seguintes ações são executadas:
 *         - Inicialização da dataflash;
 *         - Inicialização do FS;
 *         - Criação de diretórios;
 *         - Leitura do arquivo de configurações;
 * @retval None
 */

void IniciarFileSystem(void) {

	int erro;

	LOG("Iniciando memoria flash\r\n");

	//inicializa a lib da
	if (W25qxx_Init()) {

		LFS_Config();

		erro = FS_InicializarFileSystem(&lfs);

		if (erro == LFS_ERR_OK)

		return 0;
	}

	return 1;
}




/**
 * @brief Função que encerra o funcionamento do FileSystem.
 * 		  As seguintes ações são executadas:
 * 		  	- Fechamento dos arquivos de agregação;
 * 		  	- Desmonta a unidade;
 * @retval int Código de erro
 */
int EncerrarFileSystem()
{
	//Dados_FecharArquivosAgregacao();
	int err = FS_Desmontar(&lfs);

	return err;
}



void TestarFileSystem() {



	 lfs_file_t arq;

	FS_CriarDiretorio(&lfs, "teste");

	//apagarArquivos(1000, 0);

	//apagarArquivos(0, 0);


	//524.288 - 131072 = 393.215 / 24 = 16384



	//CriarArquivos(16384, 18);

  //CriarArquivos(8192, 20);


	//qqCriarArquivos(4096, 20);

	//CriarArquivos(2048, 80);
	LerArquivos();



	uint8_t teste [] = {10,11,12,13,14,15,16,17,18,19,20};
    uint8_t teste1 [40] ={0};
    uint8_t teste3 [10] = {21,22,23,24,25,26,27,28,29};



   // FS_AbrirArquivo(lfs, &arq, "teste/facm.log",   LFS_O_APPEND | LFS_O_RDWR);


   // FS_EscreverArquivo(lfs, &arq, teste3, 10);


    //FS_FecharArquivo(lfs, &arq);


	//LerArquivos();

	FS_AbrirArquivo(&lfs, &arq, "teste/facm.log", LFS_O_CREAT | LFS_O_RDWR);

	lfs_ssize_t bytesLidos  = FS_LerArquivo(&lfs, &arq, &teste1, 40);

	FS_FecharArquivo(&lfs, &arq);

	//LerArquivos();



}


//-----------------------------------------------------------------
// Lê os arquivos
//-----------------------------------------------------------------
void LerArquivos(void)
{
	//FINFO info;
	struct lfs_info info;
	lfs_dir_t dir;
	int status;
	char *s = malloc(100);

	unsigned long start_t, end_t;  // contadores de tempo em ms
	//FILE *arq;            // ponteiro do arquivo  na flash
	lfs_file_t arq;         // estrutura do controle do arquivo de escrita na flash
	//char linha[100];      // Buffer para leitura do arquivo
	int n;
	float taxa;
	int tamArq;

	// 'info.fileID' must initially be set to 0.

	testeFlash.min = 1000000000;
	testeFlash.med = 0;
	testeFlash.max = 0;
	testeFlash.n = 0;

	status = lfs_dir_open(&lfs, &dir, "teste");
	if (status == LFS_ERR_OK)
	{
		LOG2("Lendo arquivos \r\n");
		//while (ffind ("*.*",&info) == 0)
		while (lfs_dir_read(&lfs, &dir, &info))
		{
			LOG2("[Info] %-32s %5d bytes, ID: %04d  \r\n", info.name, info.size);
			//LOG_(s);

			//if (info.attrib & ATTR_DIRECTORY)
			if (info.type == LFS_TYPE_DIR)
				continue;
			tamArq = 0;
			LOG3("Lendo arquivo "); LOG3(info.name); LOG3(" ... ");
			//LER_TECLA
			start_t = HAL_GetTick();

//      sprintf(s, "%s", info.name);
//      arq = fopen(s, "r");
//      if (arq != NULL)
//      {
//        //while (fgets (linha, 100, arq) != NULL)
//        int lidos;
//        while ((lidos = fread(&linha[0], 1, 30, arq)) == 30)
//          tamArq += lidos; //strlen(linha);
//        fclose(arq);

			sprintf(s, "teste/%s", info.name);
			int erro = lfs_file_open(&lfs, &arq, s, LFS_O_RDONLY);
			if (erro == LFS_ERR_OK)
			{
				char buffer[2];
				//while (fgets (linha, 100, arq) != NULL)
				//while ((c = fgetc(arq)) != EOF)
				while (lfs_file_read(&lfs, &arq, buffer, 1) == 1)
				{
					tamArq++; //strlen(linha);
				}
				//fclose(arq);
				lfs_file_close(&lfs, &arq);
				end_t = HAL_GetTick();

				LOG3("OK - ");
				n = (unsigned int) (end_t - start_t);
				LOG3("Tempo de execucao = %d ms - ", n);

				taxa = (float) tamArq / n * 1000.0;

				if (taxa > 0)
				{
					if (taxa < testeFlash.min)
						testeFlash.min = taxa;
					if (taxa > testeFlash.max)
						testeFlash.max = taxa;
					testeFlash.n++;
					testeFlash.med += taxa;
				}
				else
					taxa = 1;

				LOG3("Tamanho do arquivo = %d bytes - taxa %5.3f bytes/s\r\n", tamArq, taxa);
				//LOG(linha);
				//LER_TECLA
			}
			else
			{
				LOG2("[Erro] Nao foi possivel abrir o arquivo!\r\n");
			}

			//LER_TECLA
		}
		lfs_dir_close(&lfs, &dir);
		LOG2("[Info] Taxa leitura min/med/max: %d/%d/%d\r\n", (int )testeFlash.min, (int )(testeFlash.med / testeFlash.n), (int )testeFlash.max);
	}
	else
		LOG2("Erro ao abrir diretorio 'teste'");
	free(s);
}

/**
 * @brief  Verfica a existência do arquivo
 * @param  caminho : caminho do arquivo a ser verificado
 * @retval 1 se arquivo existe 0 caso contrário
 */
int ArquivoExiste(char *caminho)
{
	struct lfs_info info;

	int erro = lfs_stat(&lfs, caminho, &info);
	if (erro == LFS_ERR_OK)
		return 1;
	return 0;
}


/**
 * @brief  Realiza a limpeza de arquivos antigos da pasta mantendo "max" arquivos mais novos
 * @param  caminho : caminho da pasta/diretório onde os arquivos serão apagados
 * @param  max : quantidade de arquivos máximo na pasta
 * @retval nenhum
 */
void LimparPasta(char *caminho, unsigned short max)
{
	struct lfs_info info;
	lfs_dir_t dir;
	int status;
	char *s = malloc(100);

	unsigned short n = 0;
	unsigned short k = 0;

	status = lfs_dir_open(&lfs, &dir, caminho);
	if (status == LFS_ERR_OK)
	{
		while (lfs_dir_read(&lfs, &dir, &info))
		{
			// Se for uma pasta/diretório
			if (info.type == LFS_TYPE_DIR)
			{
				continue;
			}
			n++;
		}
		status = lfs_dir_rewind(&lfs, &dir);

		if (status == LFS_ERR_OK)
		{
			if (n > max)
			{
				while (lfs_dir_read(&lfs, &dir, &info) && (k < n - max))
				{
					// Se for uma pasta/diretório
					if (info.type == LFS_TYPE_DIR)
					{
						continue;
					}

					sprintf(s, "%s/%s", caminho, info.name);

					// Apaga o arquivo
					if (lfs_remove(&lfs, s) == LFS_ERR_OK)
						LOG3("Arquivo %s excluido\r\n", s);
					else
						LOG2("Erro ao excluir arquivo %s\r\n", s);
					k++;
				}
			}
		}
		lfs_dir_close(&lfs, &dir);
	}
	else
	{
		if (lfs_remove(&lfs, caminho) != LFS_ERR_OK)
			LOG2("Erro ao apagar arquivos\r\n");
	}
	free(s);
}


//-----------------------------------------------------------------
// Apaga os arquivos pares ou impares
//-----------------------------------------------------------------

void apagarArquivos(int par, int idMin)
{
	//FINFO info;
	struct lfs_info info;
	lfs_dir_t dir;
	int status;
	char *s = malloc(100);

	// 'info.fileID' must initially be set to 0.
	//info.fileID = 0;
	status = lfs_dir_open(&lfs, &dir, "teste");
	if (status == LFS_ERR_OK)
	{
		LOG2("Apagando arquivos ...\r\n");

//#if FLASH_TYPE
//  while (ffind ("M0:\\lupa\\*.*",&info) == 0)
//#else
//  while (ffind ("S:\\lupa\\*.*",&info) == 0)
//#endif

		while (lfs_dir_read(&lfs, &dir, &info))
		{
			LOG3("%-80s %5ld bytes, tipo: %d \r\n",
					info.name,
					info.size,
					info.type);

#if WATCHDOG == 1
			WWDT_Feed();
#endif

			if ((dir.pos < idMin) || (info.type == LFS_TYPE_DIR))
				continue;
			sprintf(s, "teste/%s", info.name);
			// Apaga os arquivos com id par ou impar
			if (par)
			{
				// Se o identificador do arquivo é par, apaga
				if (dir.pos % 2 == 0)
				{
					//if (fdelete(s) == 0)
					if (lfs_remove(&lfs, s) == LFS_ERR_OK)
						LOG3("Arquivo %s excluido\r\n", s);
					else
						LOG2("Erro ao excluir arquivo %s\r\n", s);
				}
			}
			else
			{
				// Se o identificador do arquivo é impar, apaga
				if (dir.pos % 2 != 0)
				{
					//if (fdelete(s) == 0)
					if (lfs_remove(&lfs, s) == LFS_ERR_OK)
						LOG3("Arquivo %s excluido\r\n", s);
					else
						LOG2("Erro ao excluir arquivo %s\r\n", s);
				}
			}
			//LER_TECLA
		}
		lfs_dir_close(&lfs, &dir);
		//LOG("OK\r\n");
	}
	else
		LOG2("Erro ao apagar arquivos\r\n");
	free(s);
}



//-----------------------------------------------------------------
// Cria os arquivos para o teste da flash
//-----------------------------------------------------------------
void CriarArquivos(int tamArq, int numArquivos)
{
	int i;
	//S32 livre = ffree(FLASH_DRIVE);

	testeFlash.min = 1000000000;
	testeFlash.med = 0;
	testeFlash.max = 0;
	testeFlash.n = 0;

	LOG2("Criando arquivos ");
	//while (livre > 10000)
	for (i = 0; i < numArquivos; i++)
	{
		//LOG2("[Info] Espaco livre: %d bytes", livre);
		if (!CriarArquivo(tamArq))
			i--;
		//LOG2(".");
		//LER_TECLA
		//livre = ffree(FLASH_DRIVE);
	}
	LOG2(" OK");
	LOG2("[Info] Taxa escrita arquivos de %d bytes -  min/med/max: %d/%d/%d\r\n", tamArq, (int )testeFlash.min, (int )(testeFlash.med / testeFlash.n), (int )testeFlash.max);

	//ListarArquivos();
}



int CriarArquivo1(const char *nomeArq, int tamArq) {

	lfs_file_t arq;      // estrutura do controle do arquivo de escrita na flash

	int erro = 0;

	char *buffEsc = malloc(256);     // Buffer para escrita no arquivo


	LOG3("Criando arquivo "); LOG3(nomeArq); LOG3(" ... ");

	// Escreve dados em um stream do arquivo

	memset(buffEsc, 0xAA, 256);

	erro = lfs_file_open(&lfs, &arq, nomeArq, LFS_O_CREAT | LFS_O_RDWR);

	if (erro == LFS_ERR_OK) {


		LOG2("Arquivo %s criado com sucesso - ret = %i \r\n", nomeArq, erro);

		uint32_t bytesEscrita = tamArq;
		uint32_t bytesAEscrever = tamArq;
		do {
			// Se vai escrever mais 4096 bytes tem que quebrar a escrita em várias
			if (bytesEscrita > 256) {
				bytesEscrita = 256;
			}

			//if (fwrite(buffEsc, tamArq, 1 , arq) == 0)
			lfs_ssize_t bytesEscritos = lfs_file_write(&lfs, &arq, buffEsc, bytesEscrita);

			if (bytesEscritos != bytesEscrita)
				erro = 1;

			if (!erro) {

				bytesAEscrever -= bytesEscrita;
				bytesEscrita = bytesAEscrever;
			}
		} while (bytesAEscrever > 0);


		lfs_file_close(&lfs, &arq);
	}

	else if (erro == LFS_ERR_EXIST) {

		LOG2("Arquivo %s ja existe - ret = %i \r\n", nomeArq, erro);
	}

	else {

		LOG2("Erro ao criar o arquivo %s - ret = %i \r\n", nomeArq, erro);
	}

	free(buffEsc);
	return erro;
}



//-----------------------------------------------------------------
// Cria arquivo de teste na flash
//-----------------------------------------------------------------

int i = 1;
int CriarArquivo(int tamArq)
{
	unsigned long start_t, end_t;  // contadores de tempo em ms
	//FILE *arq;           // ponteiro do arquivo de escrita na flash
	lfs_file_t arq;                 // estrutura do controle do arquivo de escrita na flash
	char *nomeArq = malloc(100);    // nome do arquivo de escrita na flash
	char *buffEsc = malloc(256);     // Buffer para escrita no arquivo
	int erro = 0;


	//int tamArq = 0;

	//RTC_DateTypeDef data;
	//RTC_TimeTypeDef tempo;
	//HAL_RTC_GetTime(&_RTC, &tempo, RTC_FORMAT_BIN);
	//HAL_RTC_GetDate(&_RTC, &data, RTC_FORMAT_BIN);

	//sprintf(nomeArq, "/teste/teste_%2d-%2d-%2d_%2d-%2d-%2d-%3ld.txt", data.Year, data.Month, data.Date, tempo.Hours, tempo.Minutes, tempo.Seconds, tempo.SubSeconds); // );



	sprintf(nomeArq, "/teste/teste_%d.txt", i);

	i++;


	LOG3("Criando arquivo "); LOG3(nomeArq); LOG3(" ... ");
	//LER_TECLA

	// Escreve dados em um stream do arquivo
	memset(buffEsc, 0xAA, 256);

	start_t = HAL_GetTick();
	//arq = fopen(nomeArq, "w");
	//if (arq != NULL)
	erro = lfs_file_open(&lfs, &arq, nomeArq, LFS_O_CREAT | LFS_O_RDWR);
	if (erro == LFS_ERR_OK)
	{
		//unsigned timeMS;
		float taxa;
		//float msec = 0;
		//int i;
		int n;
		//while (n == 0)
		//  n = TimeMS % 100;
		//timeMS = n;
		//tamArq = 512;
		uint32_t bytesEscrita = tamArq;
		uint32_t bytesAEscrever = tamArq;

		do
		{
			// Se vai escrever mais 4096 bytes tem que quebrar a escrita em várias
			if (bytesEscrita > 4096)
			{
				bytesEscrita = 4096;
			}

			//if (fwrite(buffEsc, tamArq, 1 , arq) == 0)
			lfs_ssize_t bytesEscritos = lfs_file_write(&lfs, &arq, buffEsc, bytesEscrita);

			if (bytesEscritos != bytesEscrita)
				erro = 1;

			if (!erro)
			{
				bytesAEscrever -= bytesEscrita;
				bytesEscrita = bytesAEscrever;
			}
		} while (bytesAEscrever > 0);

		end_t = HAL_GetTick();
		//fclose(arq);
		lfs_file_close(&lfs, &arq);
		n = (unsigned int) (end_t - start_t);
		LOG3("OK - Tempo de execucao = %d ms\r\n", n);

		taxa = (float) tamArq / n * 1000.0;

		if (taxa > 0)
		{
			if (taxa < testeFlash.min)
				testeFlash.min = taxa;
			if (taxa > testeFlash.max)
				testeFlash.max = taxa;
				testeFlash.n++;
				testeFlash.med += taxa;
		}
		else
			taxa = 1;

		LOG3("Tamanho do arquivo = %d bytes - taxa %5.3f bytes/s\r\n", tamArq, taxa);
	}
	else
	{
		LOG2("[Erro] Nao foi possivel criar arquivo de teste!\r\n");
		erro = 1;
	}

	free(nomeArq);
	free(buffEsc);

	if (erro)
		return 0;
	else
		return 1;
}


uint8_t ListaDeArquivos(char *nomeDir, TListaDeArquivo *listaDeArquivo)
{
	struct lfs_info info;
	lfs_dir_t dir;
	uint8_t contArqu = 0;
	uint8_t Reorganizar = 0;
	int tickCnt = uwTick;

	int erro = lfs_dir_open(&lfs, &dir, nomeDir);
	if (erro == LFS_ERR_OK)
	{
		while (lfs_dir_read(&lfs, &dir, &info))
		{        //Conta a quantidade de arquivos existentes no diretório
			contArqu++;

		}
		if (contArqu != listaDeArquivo->ArqLidos)
		{
			lfs_dir_rewind(&lfs, &dir);
			if(contArqu == 2) // Pasta vazia ou cmd de apagar todos os arquivos
				memset(&listaDeArquivo->NomeArquivo,0x0,sizeof(listaDeArquivo->NomeArquivo));
			contArqu = 0;
			while (lfs_dir_read(&lfs, &dir, &info) && contArqu < NumeroMaximoDeArquivos)
			{        //Atualiza a lista de arquivos
				{
					memcpy(&listaDeArquivo->NomeArquivo[contArqu], &info.name, sizeof(listaDeArquivo->NomeArquivo[contArqu])); // Copia o nome do arquivo
					contArqu++;
				}
			}
			listaDeArquivo->ArqLidos = contArqu;
			Reorganizar++;
		}

		if (Reorganizar)
		{
			int n = sizeof(listaDeArquivo->NomeArquivo) / sizeof(listaDeArquivo->NomeArquivo[0]);
			sort(&listaDeArquivo->NomeArquivo, n);
		}
	}
	lfs_dir_close(&lfs, &dir);
	int tickCnt2 = uwTick - tickCnt;
//	printf("Tempo Organizar Arq = %d ms\r\n", tickCnt2);
	return contArqu; //  retorna o numero total + 2
}


//-----------------------------------------------------------------
// Lê o arquivo da flash
//-----------------------------------------------------------------
void LerArquivo(char *nomeArq, unsigned char imprimir)
{
	unsigned long start_t, end_t;  // contadores de tempo em ms
	//FILE *arq;            // ponteiro do arquivo  na flash
	lfs_file_t arq;         // estrutura do controle do arquivo de escrita na flash

	//char linha[100];      // Buffer para leitura do arquivo
	int n;
	float taxa;
	int tamArq = 0;

	LOG3("Lendo arquivo "); LOG3(nomeArq); LOG3(" ... ");
	//LER_TECLA
	start_t = HAL_GetTick();
	//arq = fopen(nomeArq, "r");
	//if (arq != NULL)
	int erro = lfs_file_open(&lfs, &arq, nomeArq, LFS_O_RDONLY);
	if (erro == LFS_ERR_OK)
	{
		char buffer[2];
		//while (fgets (linha, 100, arq) != NULL)
		//while ((c = fgetc(arq)) != EOF)
		while (lfs_file_read(&lfs, &arq, buffer, 1) == 1)
		{
			tamArq++; //strlen(linha);
		}
		//fclose(arq);
		lfs_file_close(&lfs, &arq);
		end_t = HAL_GetTick();
		n = (unsigned int) (end_t - start_t);
		LOG3("Tempo de execucao = %d ms", n);

		taxa = (float) tamArq / n * 1000.0;

		if (taxa > 0)
		{
			if (taxa < testeFlash.min)
				testeFlash.min = taxa;
			if (taxa > testeFlash.max)
				testeFlash.max = taxa;
			testeFlash.n++;
			testeFlash.med += taxa;
		}

		LOG3("Tamanho do arquivo = %d bytes - taxa %5.3f bytes/s", tamArq, taxa);
		//LER_TECLA
	}
	else
	{
		LOG2("Nao foi possivel abrir o arquivo!");
	}
}




