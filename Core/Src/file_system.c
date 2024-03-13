///*----------------------------------------------------------------------------
// *   File System - Lupa Tecnologia e Sistemas Ltda
// *----------------------------------------------------------------------------
// *   Nome:    file_system.c
// *   Descriao: Camada de interface entre o sistema de arquivos e a memoria
// *
// *----------------------------------------------------------------------------
// * 11.11.2020 - Dominique Ign�cio - Sistema de arquivos
// * 				Implementa��o do sistema de arquivos LittleFS com a mem�ria
// * 				Micron Serial NOR Flash MT25QL256ABA
// *
// * 				Links de refer�ncia:
// * 				 - https://github.com/littlefs-project/littlefs
// * 				 - https://os.mbed.com/blog/entry/littlefs-high-integrity-embedded-fs/
// * 				 - https://www.micron.com/products/nand-flash/mlc-nand
// *
// * 30.11.2022. Italo Francis  - Sistema de arquivos
// *			   Implementacao do sistema de arquivos LittleFs com a memoria
// *			   Winbond NAND Flash W25Q40CL e as demais da mesma familia
// *
// *			   Links de referencia:
// *			   	- https://github.com/nimaltd/w25qxx (lib da SPI)
// *              - http://merkles.com/MediaWiki/index.php/LittleFS_Flash_File_System
// *              - https://uimeter.com/2018-04-12-Try-LittleFS-on-STM32-and-SPI-Flash/
// *              - https://github.com/littlefs-project/littlefs/issues/441
// *
// *----------------------------------------------------------------------------
// *   Copyright (c) 2022 Lupa Tecnologia e Sistemas Ltda. All rights reserved.
// *---------------------------------------------------------------------------*/
//
//
//#include <file_system.h>
//#include <w25qxx.h>
//#include "lfs.h"
//#include "lfs_util.h"lfs
//#include "cmsis_os.h"
//
//
//#define FS_MAX_TENTATIVAS	25
//
//
//#define LOG printf
//
//#define LOG2(...)
////#define LOG2 printf
//
////struct que carrega as inforamções da memória FLASH carregada da lin
//extern w25qxx_t w25qxx;
//
///***********************************************************************************************************************
// * Callback functions
// **********************************************************************************************************************/
//
//
//int lsfs_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size);
//int lsfs_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size);
//int lsfs_erase(const struct lfs_config *c, lfs_block_t block);
//int lsfs_sync(const struct lfs_config *c);
//
//
//struct lfs_config littlefs_config;
//
//#ifdef LFS_THREADSAFE
///* LittleFS lock callback*/
//static int lfs_lock(const struct lfs_config *c);
///* LittleFS unlock callback*/
//static int lfs_unlock(const struct lfs_config *c);
//#endif
//
//
//// na Struct de configuracao abaixo preve a possibilidade de aumento da memória flash da mesma familia, tendo suporte as memórias de até 4Mb
////caso exista uma reducao de tamanho reajustar os valores do parametro littlefs_config.block_count o qual subtrai 128Kb para o bootloader do STM32F072
//
//void LFS_Config(void) {
//
//
//
//	// block device operation
//
//	littlefs_config.read = lsfs_read;
//	littlefs_config.prog = lsfs_prog;
//	littlefs_config.erase = lsfs_erase;
//	littlefs_config.sync = lsfs_sync;
//
//	// block device configuration
//	// Minimum size of a block read in bytes. All read operations will be a
//	// multiple of this value.
//
//	//Recebe o tamanho de pagina da memoria da lib
//	littlefs_config.read_size = w25qxx.PageSize;
//
//	// Minimum size of a block program in bytes. All program operations will be
//	// a multiple of this value.
//
//	//Recebe o tamanho de pagina da memoria da lin
//	littlefs_config.prog_size = w25qxx.PageSize;
//
//	// Size of an erasable block in bytes. This does not impact ram consumption
//	// and may be larger than the physical erase size. However, non-inlined
//	// files take up at minimum one block. Must be a multiple of the read and
//	// program sizes.
//
//	//Recebe o tamanho do setor da lib
//	littlefs_config.block_size = w25qxx.SectorSize;
//
//	// Number of erasable blocks on the device.
//	//Recebe a quantidade setores subtraindo 128Kb para atualizacao de firmware
//
//	//(524288 bytes - 131072 bytes = (393.216 / 4096) = 96 block
//	littlefs_config.block_count = w25qxx.SectorCount; // = 4096 * 32 = 131702
//
//	// Size of block caches in bytes. Each cache buffers a portion of a block in
//	// RAM. The littlefs needs a read cache, a program cache, and one additional
//	// cache per file. Larger caches can improve performance by storing more
//	// data and reducing the number of disk accesses. Must be a multiple of the
//	// read and program sizes, and a factor of the block size.
//	littlefs_config.cache_size = 1024;
//
//	// Size of the lookahead buffer in bytes. A larger lookahead buffer
//	// increases the number of blocks found during an allocation pass. The
//	// lookahead buffer is stored as a compact bitmap, so each byte of RAM
//	// can track 8 blocks. Must be a multiple of 8.
//
//	//Melhor config para desempenho
//	//littlefs_config.lookahead_size = (littlefs_config.block_count / 8) + 52  ; //>= block count /8
//
//	littlefs_config.lookahead_size = 256;
//
//	// Number of erase cycles before littlefs evicts metadata logs and moves
//	// the metadata to another block. Suggested values are in the
//	// range 100-1000, with large values having better performance at the cost
//	// of less consistent wear distribution.
//	// Set to -1 to disable block-level wear-leveling.
//	littlefs_config.block_cycles = 100;
//	//parametros não necessários
//	//.name_max = LFS_NAME_MAX,
//	//.file_max = LFS_FILE_MAX
//}
//
//
////--------------------------------------------------------------------------------------------------
//
///**
// * @brief Função de interface do LittleFS com a biblioteca da memória Flash NAND para operação de leitura
// */
//int lsfs_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size) {
//
//	if (W25qxx_ReadSector((uint8_t*) buffer, block, off, size)) {
//
//		LOG2("Leitura da flash no  - bloco %lu - off %lu - %lu bytes lidos\r\n", block, off, size);
//
//		return LFS_ERR_OK;
//
//	} else {
//
//	  return LFS_ERR_CORRUPT;
//	}
//
//}
//
////--------------------------------------------------------------------------------------------------
//
///**
// * @brief Função de interface do LittleFS com a biblioteca da memória Flash NAND para operação de escrita
// */
//
//int lsfs_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size) {
//
//	if (W25qxx_WriteSector((uint8_t*) buffer, block, off, size)) {
//
//		LOG2("Escrita da flash no - bloco %lu - off %lu  - %lu bytes escritos\r\n", block, off, size);
//
//		return LFS_ERR_OK;
//
//	} else {
//
//		return LFS_ERR_CORRUPT;
//	}
//}
//
////--------------------------------------------------------------------------------------------------
//
///**
// * @brief Função de interface do LittleFS com a biblioteca da memória Flash NAND para operação de apagamento (erase)
// */
//int lsfs_erase(const struct lfs_config *c, lfs_block_t block) {
//
//  	 W25qxx_EraseSector(block);
//
//	return LFS_ERR_OK;
//}
//
////--------------------------------------------------------------------------------------------------
//
///**
// * @brief Função de interface do LittleFS com a biblioteca da memória Flash NAND para operação de sincronismo
// * 		  (para a Flash NAND esta função não é necessária, apenas retorna OK)
// */
//
//int lsfs_sync(const struct lfs_config *c) {
//
//	return LFS_ERR_OK;
//}
//
///**
// * @brief Funcao que monta o FileSystem
// * @retval int C�digo de erro
// */
//int FS_Montar(lfs_t *lfs)
//{
//
//  int status = lfs_mount(lfs, &littlefs_config);
//  if (status != LFS_ERR_OK)
//  {
//    LOG("Erro ao montar FS - Cod Erro = [%5i]\r\n", status);
//
//    int nTentativas = 0;
//
//    while (status != LFS_ERR_OK && status != LFS_ERR_NOMEM /*&& status != LFS_ERR_NOENT*/&& ++nTentativas < 10)
//    {
//
//    	HAL_Delay(50);
//
//      //osDelay(50);
//      status = lfs_mount(lfs, &littlefs_config);
//      LOG("Tentando novamente, lfs_mount - Cod Erro = [%5i]\r\n", status);
//    }
//  }
//  return status;
//}
//
///**
// * @brief Funcao que desmonta o FileSystem
// * @retval int Codigo de erro
// */
//int FS_Desmontar(lfs_t *lfs)
//{
//  int err = lfs_unmount(lfs);
//
//  if (err != LFS_ERR_OK)
//  {
//    LOG("Erro ao desmontar FS - Cod Erro = [%5i]\r\n", err);
//  }
//  return err;
//}
//
////--------------------------------------------------------------------------------------------------
///**
// * @brief Função de inicializa o FileSystem
// * @retval int Código de erro
// */
//int FS_InicializarFileSystem(lfs_t *lfs)
//{
//  LOG("Iniciando FileSystem ...\r\n");
//
//#ifdef LFS_THREADSAFE
//  /* creation of SemaforoFS */
//  //SemaforoFSHandle = osSemaphoreNew(1, 1, &SemaforoFS_attributes);
//#endif
//
//  // mount the filesystem
//  int err = FS_Montar(lfs);
//  if (err)
//  {
//    // reformat if we can't mount the filesystem
//    // this should only happen on the first boot
//    //debug_flash = 1;
//    //LOG("Erro ao montar FileSystem - Cod Erro = [%5i]\r\n", err);
//    //LOG("Formatando flash... ");
//    err = lfs_format(lfs, &littlefs_config);
//    if (err)
//    {
//      LOG("Erro ao formatar - Cod Erro = [%5i]\r\n", err);
//      return err;
//    }
//    LOG("Formatacao realizada com sucesso - Cod Erro = [%5i]\r\n", err);
//    err = lfs_mount(lfs, &littlefs_config);
//    //debug_flash = 0;
//  }
//  if (err)
//    LOG("Erro ao montar FileSystem - Cod Erro = [%5i]\r\n", err);
//  else
//    LOG("Inicializacao do FileSystem concluida - Cod Erro = %i\r\n", err);
//  return err;
//}
//
///**
// * @brief Funcao que formata o FileSystem
// * @retval int Codigo de erro
// */
//int FS_Formatar(lfs_t *lfs)
//{
//  int err = lfs_format(lfs, &littlefs_config);
//  if (err != LFS_ERR_OK)
//  {
//    LOG("Erro ao formatar FS - Cod Erro = [%5i]\r\n", err);
//  }
//  return err;
//}
//
//int FS_CriarDiretorio(lfs_t *lfs, const char *path)
//{
//  int status = lfs_mkdir(lfs, path);
//  if (status == LFS_ERR_OK)
//    LOG2("Diretorio %s criado com sucesso - ret = %i \r\n", path, status);
//  else if (status == LFS_ERR_EXIST)
//    LOG2("Diretorio %s ja existe - ret = %i \r\n", path, status);
//  else
//    LOG("Erro ao criar Diretorio %s - lfs_mkdir - ret = %i \r\n", path, status);
//  return status;
//}
//
///**
// * @brief  Função que abre o diretório do FileSystem
// * @param  lfs  Ponteiro para o struct de controle do FileSystem
// * @param  dir  Ponteiro para o struct de controle do diretório do FileSystem
// * @param  path Ponteiro para a string contendo o path do diretório
// * @retval int  Status da operação
// */
//int FS_AbrirDiretorio(lfs_t *lfs, lfs_dir_t *dir, const char *path)
//{
//  int nTentativas = 0;
//  int status = lfs_dir_open(lfs, dir, path);
//  while (status != LFS_ERR_OK && status != LFS_ERR_NOENT && ++nTentativas < FS_MAX_TENTATIVAS)
//  {
//    LOG("Erro lfs_dir_open - ret = %i \r\n", status);
//
//    //osDelay(1);
//
//    status = lfs_dir_open(lfs, dir, path);
//  }
////	LOG("lfs_dir_open - ret = %i \r\n", status);
//  return status;
//}
//
///**
// * @brief  Função que fecha o diretório do FileSystem
// * @param  lfs Ponteiro para o struct de controle do FileSystem
// * @param  dir Ponteiro para o struct de controle do diretório do FileSystem
// * @retval int Status da operação
// */
//int FS_FecharDiretorio(lfs_t *lfs, lfs_dir_t *dir)
//{
//  int nTentativas = 0;
//  int status = lfs_dir_close(lfs, dir);
//  while (status != LFS_ERR_OK && status != LFS_ERR_NOENT && ++nTentativas < FS_MAX_TENTATIVAS)
//  {
//    LOG("Erro lfs_dir_close - ret = %i \r\n", status);
//    //osDelay(1);
//    status = lfs_dir_close(lfs, dir);
//  }
////	LOG("lfs_dir_close - ret = %i \r\n", status);
//  return status;
//}
//
///**
// * @brief  Função que abre o arquivo do FileSystem
// * @param  lfs   Ponteiro para o struct de controle do FileSystem
// * @param  file  Ponteiro para o struct de controle do arquivo do FileSystem
// * @param  path  Ponteiro para a string contendo o path do arquivo
// * @param  flags Flags de controle que definem o modo de operação e funcionamento do arquivo
// * @retval int   Status da operação
// */
//int FS_AbrirArquivo(lfs_t *lfs, lfs_file_t *file, const char *path, int flags)
//{
//  int status = lfs_file_open(lfs, file, path, flags);
//
//  if (status != LFS_ERR_OK && status != LFS_ERR_NOMEM /*&& status != LFS_ERR_NOENT*/)
//  {
//    LOG("Erro lfs_file_open - file %s - ret = %i \r\n", path, status);
//    int nTentativas = 0;
//    while (status != LFS_ERR_OK && status != LFS_ERR_NOMEM /*&& status != LFS_ERR_NOENT*/&& ++nTentativas < FS_MAX_TENTATIVAS)
//    {
//     // osDelay(1);
//      status = lfs_file_open(lfs, file, path, flags);
//      LOG("Tentando novamente, lfs_file_open - file %s - ret = %i \r\n", path, status);
//    }
//  }
////	LOG("lfs_file_open - file %s - ret = %i \r\n", path, status);
//  return status;
//}
//
///**
// * @brief  Função que fecha o arquivo do FileSystem
// * @param  lfs  Ponteiro para o struct de controle do FileSystem
// * @param  file Ponteiro para o struct de controle do arquivo do FileSystem
// * @retval int  Status da operação
// */
//int FS_FecharArquivo(lfs_t *lfs, lfs_file_t *file)
//{
//  //***FS_Flush(lfs, file);
//  int nTentativas = 0;
//  int status = lfs_file_close(lfs, file);
//  while (status != LFS_ERR_OK && status != LFS_ERR_NOENT && ++nTentativas < FS_MAX_TENTATIVAS)
//  {
//    LOG("Erro lfs_file_close - ret = %i \r\n", status);
//    //***FS_Flush(lfs, file);
//    //osDelay(1);
//    status = lfs_file_close(lfs, file);
//  }
////	LOG("lfs_file_close - ret = %i \r\n", status);
//  return status;
//}
//
///**
// * @brief  Função que salva o arquivo no FileSystem.
// * 		   Executa a função lfs_file_sync, que grava os dados do buffer na
// * 		   memória e atualiza os structs de controle do arquivo.
// * @param  lfs  Ponteiro para o struct de controle do FileSystem
// * @param  file Ponteiro para o struct de controle do arquivo do FileSystem
// * @retval int  Status da operação
// */
//int FS_SalvarArquivo(lfs_t *lfs, lfs_file_t *file)
//{
//  //*** FS_Flush(lfs, file);
//  int status = lfs_file_sync(lfs, file);
//  int nTentativas = 0;
//  while (status != LFS_ERR_OK && ++nTentativas < FS_MAX_TENTATIVAS)
//  {
//    LOG("Erro lfs_file_sync - ret = %i \r\n", status);
//   // osDelay(1);
//    status = lfs_file_sync(lfs, file);
//  }
//  return status;
//}
//
///**
// * @brief  Função que exclui o arquivo ou diretório no FileSystem.
// * 		   Para excluir o diretório, este precisa estar vazio.
// * @param  lfs  Ponteiro para o struct de controle do FileSystem
// * @param  path Ponteiro para a string contendo o path do arquivo ou diretório
// * @retval int  Status da operação
// */
//int FS_ExcluirPath(lfs_t *lfs, const char *path)
//{
//  int status = lfs_remove(lfs, path);
//  int nTentativas = 0;
//  while ((status != LFS_ERR_OK) && (status != LFS_ERR_NOENT) && ++nTentativas < FS_MAX_TENTATIVAS)
//  {
//    LOG("Erro lfs_remove - ret = %i - path: %s \r\n", status, path);
//    //osDelay(1);
//    status = lfs_remove(lfs, path);
//  }
//  return status;
//}
//
///**
// * @brief  Função que posiciona o ponteiro do arquivo no início.
// * @param  lfs  Ponteiro para o struct de controle do FileSystem
// * @param  file Ponteiro para o struct de controle do arquivo do FileSystem
// * @retval int  Status da operação
// */
//int FS_RewindArquivo(lfs_t *lfs, lfs_file_t *file)
//{
//  int status = lfs_file_rewind(lfs, file);
//  int nTentativas = 0;
//  while (status != LFS_ERR_OK && ++nTentativas < FS_MAX_TENTATIVAS)
//  {
//    LOG("Erro lfs_file_rewind - ret = %i  \r\n", status);
//  //  osDelay(1);
//    status = lfs_file_rewind(lfs, file);
//  }
//  return status;
//}
//
///**
// * @brief  Função que lê dados do arquivo do FileSystem.
// * 		   Esta função não realiza operações com o ponteiro de posicionamento de leitura do arquivo,
// * 		   apenas efetua a leitura da quantidade de bytes informada no parâmetro.
// * @param  lfs  Ponteiro para o struct de controle do FileSystem
// * @param  file Ponteiro para o struct de controle do arquivo do FileSystem
// * @param  path Ponteiro para o buffer que receberá os dados lidos
// * @param  size Quantidade de bytes solicitados para leitura
// * @retval int  Quantidade de bytes lidos
// */
//lfs_ssize_t FS_LerArquivo(lfs_t *lfs, lfs_file_t *file, void *buffer, lfs_size_t size)
//{
//  lfs_ssize_t qtdBytes = lfs_file_read(lfs, file, buffer, size);
//  int nTentativas = 0;
//  while (qtdBytes < 0 && ++nTentativas < FS_MAX_TENTATIVAS)
//  {
//    LOG("Erro lfs_file_read - ret = %li \r\n", qtdBytes);
//  //  osDelay(1);
//    qtdBytes = lfs_file_read(lfs, file, buffer, size);
//  }
//  if (qtdBytes != size)
//  {
//    LOG("Erro lfs_file_read - Quantidade de bytes lidos (%li) diferente do solicitado (%li) \r\n", qtdBytes, size);
//  }
//  return qtdBytes;
//}
//
///**winbond
// * @brief  Função que escrever dados no arquivo do FileSystem.
// * 		   Esta função não realiza operações com o ponteiro de posicionamento de escrita do arquivo,
// * 		   apenas efetua a escrita da quantidade de bytes informada no parâmetro.
// * @param  lfs  Ponteiro para o struct de controle do FileSystem
// * @param  file Ponteiro para o struct de controle do arquivo do FileSystem
// * @param  path Ponteiro para o buffer que receberá os dados escritos
// * @param  size Quantidade de bytes solicitados para escrita
// * @retval int  Quantidade de bytes escritos
// */
//
//lfs_ssize_t FS_EscreverArquivo(lfs_t *lfs, lfs_file_t *file, void *buffer, lfs_size_t size)
//{
//  lfs_ssize_t qtdBytes = 0;
//
//  if (file->flags & (LFS_O_RDWR | LFS_O_APPEND | LFS_O_WRONLY))                                        // Verifica o status da flag do arquivo aberto
//  {
//    qtdBytes = lfs_file_write(lfs, file, buffer, size);
//    int nTentativas = 0;
//    while (qtdBytes < 0 && ++nTentativas < FS_MAX_TENTATIVAS)
//    {
//      LOG("Erro lfs_file_write - ret = %li \r\n", qtdBytes);
//      //osDelay(1);
//      qtdBytes = lfs_file_write(lfs, file, buffer, size);
//    }
//    if (qtdBytes != size)
//    {
//      LOG("Erro lfs_file_write - Quantidade de bytes escritos (%li) diferente do solicitado (%li) \r\n", qtdBytes, size);
//    }
//  }
//  else
//  {
//    // Caso o arquivo não seja compativel com a operação requerida, apenas informa que não foi executado
//    LOG("Arquivo não alterado, flag do file [ 0x%lx ] \r\n", file->flags);
//  }
//  return qtdBytes;
//}
//
////-- Varre dentro do diretório buscando o arquivo com o nome 'arquivo'
////-- Não trata o caso quando lfs_dir_read(lfs, dir, info) == false
//
//int FS_DIR_FIND(lfs_t *lfs, lfs_dir_t *dir, char *pathAgg10m, struct lfs_info *info, char arquivo[])
//{
//  //struct lfs_info info;
//  int status = 0;
////	int NaoExisteArquivo = 0;
////	uint8_t tamanhaoDir = 0;
//  int nTentativas = 0;
//
//  status = lfs_dir_rewind(lfs, dir);
//  while (status < 0 && ++nTentativas < FS_MAX_TENTATIVAS)
//  {
//    //Deu erro
//    LOG("\r\n  Falha no Rewind  \r\n");
//  //  osDelay(1);
//    status = lfs_dir_rewind(lfs, dir);
//  }
//
//  nTentativas = 0;
//  while (lfs_dir_read(lfs, dir, info) == true && ++nTentativas < FS_MAX_TENTATIVAS)
//  {
//    LOG("        %-20s", info->name);
//    if (info->type == LFS_TYPE_DIR)
//    {
//      LOG("        %-25s \r\n", "<DIR>");
//    }
//    else
//    {
//      LOG("        %-25lu\r\n", (unsigned long) info->size);
//    }
//   // osDelay(1);
//    if (memcmp(&arquivo[7], &info->name, 14) == 0)
//      break;
//  }
//  return status;
//}
//
////-- Seleciona o próximo arquivo do diretório para executar a leitura sequencial: xxx.txt --> (xxx+1).txt
//
//int FS_CONT_ARQ(lfs_t *lfs, lfs_dir_t *dir, struct lfs_info *info, char arquivo[], char *pathAgg10m)
//{
//  int totalArquivos = 0;
////	int status = 0;
//  //Contagem de arquivos
//  int contFile = arquivo[20] - 48 + 10 * (arquivo[19] - 48) + 100 * (arquivo[18] - 48) + 1;                                        //Soma 1 no indice do arquivo
//  arquivo[20] = contFile % 10 + 48;                                        // Atualiza para buscar o próximo arquivo
//  arquivo[19] = contFile / 10 + 48;
//  arquivo[18] = contFile / 100 + 48;
//  if (contFile < dir->m.count)
//  {
//    /*status = */FS_DIR_FIND(lfs, dir, pathAgg10m, info, arquivo);
//  }
//  totalArquivos = 1;
//  return totalArquivos;
//}
//
////-------------------------
////-- Informa quantos arquivos existem no diretório.
//int FS_CONT_DIR(lfs_t *lfs, lfs_dir_t *dir, char *pathAgg10m, struct lfs_info *info)
//{
//  int status;
////	int contDir = 0;
//  int nTentativas = 0;
//  status = lfs_dir_rewind(lfs, dir);
//  while (status < 0 && ++nTentativas < FS_MAX_TENTATIVAS)
//  {
//    //Deu erro
//    LOG("\r\n  Falha no Rewind  \r\n");
//   // osDelay(1);
//    status = lfs_dir_rewind(lfs, dir);
//  }
//  //-- Imprime todo o diretório aberto
//  nTentativas = 0;
//  while (lfs_dir_read(lfs, dir, info) == true && ++nTentativas < FS_MAX_TENTATIVAS)
//  {
//    LOG("        %-20s", info->name);
//    if (info->type == LFS_TYPE_DIR)
//    {
//      LOG("        %-25s \r\n", "<DIR>");
//    }
//    else
//    {
//      LOG("        %-25lu\r\n", (unsigned long) info->size);
//    }
//    //contDir++;
//  }
//  return dir->m.count;
//}
//
//
//
//
//
//
////
////
////
////
////#ifdef LFS_THREADSAFE
////
//////============================================================================
////
////#if (osCMSIS < 0x20000U) /* CMSIS V1 */
////
//////****************************************************************************
////// Não existem métodos para lock e unlock do kernel RTOS no CMSIS V1
////// Utilizando código abaixo extraído do CMSIS V2
//////****************************************************************************
////
//////***  cmsis_os2.h
/////// Status code values returned by CMSIS-RTOS functions.
////typedef enum {
//// // osOK                      =  0,         ///< Operation completed successfully.
////  osError                   = -1,         ///< Unspecified RTOS error: run-time error but no other error message fits.
////  osErrorTimeout            = -2,         ///< Operation not completed within the timeout period.
//// // osErrorResource           = -3,         ///< Resource not available.
//// // osErrorParameter          = -4,         ///< Parameter error.
//////  osErrorNoMemory           = -5,         ///< System is out of memory: it was impossible to allocate or reserve memory for the operation.
//// // osErrorISR                = -6,         ///< Not allowed in ISR context: the function cannot be called from interrupt service routines.
////  osStatusReserved          = 0x7FFFFFFF  ///< Prevents enum down-size compiler optimization.
////} osStatus_t;
////
//////***  cmsis_os2.h
/////// Kernel state.
////typedef enum {
////  osKernelInactive        =  0,         ///< Inactive.
////  osKernelReady           =  1,         ///< Ready.
////  osKernelRunning_enum         =  2,         ///< Running.
////  osKernelLocked          =  3,         ///< Locked.
////  osKernelSuspended       =  4,         ///< Suspended.
////  osKernelError           = -1,         ///< Error.
////  osKernelReserved        = 0x7FFFFFFFU ///< Prevents enum down-size compiler optimization.
////} osKernelState_t;
////
//////*** cmsis_os2.c
////#define IS_IRQ_MODE()             (__get_IPSR() != 0U)
////#define IS_IRQ()                  IS_IRQ_MODE()
////
//////*** cmsis_os2.c
////osKernelState_t osKernelGetState (void) {
////  osKernelState_t state;
////
////  switch (xTaskGetSchedulerState()) {
////    case taskSCHEDULER_RUNNING:
////      state = osKernelRunning_enum;
////      break;
////
////    case taskSCHEDULER_SUSPENDED:
////      state = osKernelLocked;
////      break;
////
////    case taskSCHEDULER_NOT_STARTED:
////    default:
////      //if (KernelState == osKernelReady) {
////      //  state = osKernelReady;
////      //} else {
////        state = osKernelInactive;
////      //}
////      break;
////  }
////
////  return (state);
////}
////
//////*** cmsis_os2.c
////int32_t osKernelLock (void) {
////  int32_t lock;
////
////  if (IS_IRQ()) {
////    lock = (int32_t)osErrorISR;
////  }
////  else {
////    switch (xTaskGetSchedulerState()) {
////      case taskSCHEDULER_SUSPENDED:
////        lock = 1;
////        break;
////
////      case taskSCHEDULER_RUNNING:
////        vTaskSuspendAll();
////        lock = 0;
////        break;
////
////      case taskSCHEDULER_NOT_STARTED:
////      default:
////        lock = (int32_t)osError;
////        break;
////    }
////  }
////
////  return (lock);
////}
////
//////*** cmsis_os2.c
////int32_t osKernelUnlock (void) {
////  int32_t lock;
////
////  if (IS_IRQ()) {
////    lock = (int32_t)osErrorISR;
////  }
////  else {
////    switch (xTaskGetSchedulerState()) {
////      case taskSCHEDULER_SUSPENDED:
////        lock = 1;
////
////        if (xTaskResumeAll() != pdTRUE) {
////          if (xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED) {
////            lock = (int32_t)osError;
////          }
////        }
////        break;
////
////      case taskSCHEDULER_RUNNING:
////        lock = 0;
////        break;
////
////      case taskSCHEDULER_NOT_STARTED:
////      default:
////        lock = (int32_t)osError;
////        break;
////    }
////  }
////
////  return (lock);
////}
////
//////*** cmsis_os2.c
////int32_t osKernelRestoreLock (int32_t lock) {
////
////  if (IS_IRQ()) {
////    lock = (int32_t)osErrorISR;
////  }
////  else {
////    switch (xTaskGetSchedulerState()) {
////      case taskSCHEDULER_SUSPENDED:
////      case taskSCHEDULER_RUNNING:
////        if (lock == 1) {
////          vTaskSuspendAll();
////        }
////        else {
////          if (lock != 0) {
////            lock = (int32_t)osError;
////          }
////          else {
////            if (xTaskResumeAll() != pdTRUE) {
////              if (xTaskGetSchedulerState() != taskSCHEDULER_RUNNING) {
////                lock = (int32_t)osError;
////              }
////            }
////          }
////        }
////        break;
////
////      case taskSCHEDULER_NOT_STARTED:
////      default:
////        lock = (int32_t)osError;
////        break;
////    }
////  }
////
////  return (lock);
////}
////#endif  /* (osCMSIS < 0x20000U) */
////
//////============================================================================
////
////// Variável auxiliar para manter o valor do estado de Lock do RTOS nas funções lock e unlock abaixo
////static int32_t rtos_lockState = 0;
////
/////**
//// * @brief Função de interface THREADSAFE do LittleFS com o RTOS para função de LOCK
//// */
////int lfs_lock(const struct lfs_config *c)
////{
////
////
////
////
////
////	//****************************************************************************
////	// Não existem métodos para lock e unlock do kernel RTOS no CMSIS V1
////	// Utilizando código abaixo extraído do CMSIS V2
////	//****************************************************************************
////
////	//***  cmsis_os2.h
////	/// Status code values returned by CMSIS-RTOS functions.
////	typedef enum {
////	 // osOK                      =  0,         ///< Operation completed successfully.
////	  osError                   = -1,         ///< Unspecified RTOS error: run-time error but no other error message fits.
////	  osErrorTimeout            = -2,         ///< Operation not completed within the timeout period.
////	 // osErrorResource           = -3,         ///< Resource not available.
////	 // osErrorParameter          = -4,         ///< Parameter error.
////	//  osErrorNoMemory           = -5,         ///< System is out of memory: it was impossible to allocate or reserve memory for the operation.
////	 // osErrorISR                = -6,         ///< Not allowed in ISR context: the function cannot be called from interrupt service routines.
////	  osStatusReserved          = 0x7FFFFFFF  ///< Prevents enum down-size compiler optimization.
////	} osStatus_t;
////
////	//***  cmsis_os2.h
////	/// Kernel state.
////	typedef enum {
////	  osKernelInactive        =  0,         ///< Inactive.
////	  osKernelReady           =  1,         ///< Ready.
////	  osKernelRunning_enum         =  2,         ///< Running.
////	  osKernelLocked          =  3,         ///< Locked.
////	  osKernelSuspended       =  4,         ///< Suspended.
////	  osKernelError           = -1,         ///< Error.
////	  osKernelReserved        = 0x7FFFFFFFU ///< Prevents enum down-size compiler optimization.
////	} osKernelState_t;
////
////	//*** cmsis_os2.c
////	#define IS_IRQ_MODE()             (__get_IPSR() != 0U)
////	#define IS_IRQ()                  IS_IRQ_MODE()
////
////	//*** cmsis_os2.c
////	osKernelState_t osKernelGetState (void) {
////	  osKernelState_t state;
////
////	  switch (xTaskGetSchedulerState()) {
////	    case taskSCHEDULER_RUNNING:
////	      state = osKernelRunning_enum;
////	      break;
////
////	    case taskSCHEDULER_SUSPENDED:
////	      state = osKernelLocked;
////	      break;
////
////	    case taskSCHEDULER_NOT_STARTED:
////	    default:
////	      //if (KernelState == osKernelReady) {
////	      //  state = osKernelReady;
////	      //} else {
////	        state = osKernelInactive;
////	      //}
////	      break;
////	  }
////
////	  return (state);
////	}
////
////	//*** cmsis_os2.c
////	int32_t osKernelUnlock (void) {
////	  int32_t lock;
////
////	  if (IS_IRQ()) {
////	    lock = (int32_t)osErrorISR;
////	  }
////	  else {
////	    switch (xTaskGetSchedulerState()) {
////	      case taskSCHEDULER_SUSPENDED:
////	        lock = 1;
////
////	        if (xTaskResumeAll() != pdTRUE) {
////	          if (xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED) {
////	            lock = (int32_t)osError;
////	          }
////	        }mcu.externaltools.gnu-tools-for-stm32.11.3.rel1.linux64_1.1.100.202309141235/tools/bin/../lib/gcc/arm-none-eabi/11.3.1/../../../../arm-none-eabi/bin/ld: ./Core/Src/lfs_w25qflash.o:/home/italo/STM32CubeIDE/workspace_1.14.0/STM32F4_BOARD/Debug/../Core/Src/lfs_w25qflash.c:38: multiple definition of `littlefs_config'; ./Core/Src/file_system.o:/home/italo/STM32CubeIDE/workspace_1.14.0/STM32F4_BOARD/Debug/../Core/Src/file_system.c:61: first defined here
////collect2: error: ld returned 1 exit status
////	        break;
////
////	      case taskSCHEDULER_RUNNING:
////	        lock = 0;
////	        break;
////
////	      case taskSCHEDULER_NOT_STARTED:
////	      default:
////	        lock = (int32_t)osError;
////	        break;
////	    }
////	  }
////
////	  return (lock);
////	}
////
////	//*** cmsis_os2.c
////	int32_t osKernelRestoreLock (int32_t lock) {
////
////	  if (IS_IRQ()) {
////	    lock = (int32_t)osErrorISR;
////	  }
////	  else {
////	    switch (xTaskGetSchedulerState()) {
////	      case taskSCHEDULER_SUSPENDED:
////	      case taskSCHEDULER_RUNNING:
////	        if (lock == 1) {
////	          vTaskSuspendAll();
////	        }
////	        else {
////	          if (lock != 0) {
////	            lock = (int32_t)osError;
////	          }
////	          else {
////	            if (xTaskResumeAll() != pdTRUE) {
////	              if (xTaskGetSchedulerState() != taskSCHEDULER_RUNNING) {
////	                lock = (int32_t)osError;
////	              }
////	            }
////	          }
////	        }
////	        break;
////
////	      case taskSCHEDULER_NOT_STARTED:
////	      default:
////	        lock = (int32_t)osError;
////	        break;
////	    }
////	  }
////
////	  return (lock);
////	}
////	#endif  /* (osCMSIS < 0x20000U) */
////
////	//============================================================================
////
////	// Variável auxiliar para manter o valor do estado de Lock do RTOS nas funções lock e unlock abaixo
////	static int32_t rtos_lockState = 0;
////
////	/**
////	 * @brief Função de interface THREADSAFE do LittleFS com o RTOS para função de LOCK
////	 */
////	int lfs_lock(const struct lfs_config *c)
////	{
////		if(osKernelGetState() == osKernelInactive)
////		{
////			// RTOS ainda não inicializou
////			return  LFS_ERR_OK;
////		}
////
////		rtos_lockState = osKernelLock();
////		int ret = LFS_ERR_OK;
////
////		if (rtos_lockState < 0)
////		{
////			ret = LFS_ERR_IO;
////		}
////		return ret;
////	}
////
////	/**
////	 * @brief Função de interface THREADSAFE do LittleFS com o RTOS para função de UNLOCK
////	 */
////	int lfs_unlock(const struct lfs_config *c)
////	{
////		if(osKernelGetState() == osKernelInactive)
////		{
////			// RTOS ainda não inicializou
////			return  LFS_ERR_OK;
////		}
////
////		//int state = osKernelUnlock();
////		int newLockState = osKernelRestoreLock(rtos_lockState);
////		int ret = LFS_ERR_OK;
////
////		if (newLockState < 0)
////		{
////			ret = LFS_ERR_IO;
////		}
////		return ret;
////	}
////	#endif
////
////
////
////
////
////
////
////
////
////	if(osKernelGetState() == osKernelInactive)
////	{
////		// RTOS ainda não inicializou
////		return  LFS_ERR_OK;
////	}
////
////	rtos_lockState = osKernelLock();
////	int ret = LFS_ERR_OK;
////
////	if (rtos_lockState < 0)
////	{
////		ret = LFS_ERR_IO;
////	}
////	return ret;
////}
////
/////**
//// * @brief Função de interface THREADSAFE do LittleFS com o RTOS para função de UNLOCK
//// */
////int lfs_unlock(const struct lfs_config *c)
////{
////	if(osKernelGetState() == osKernelInactive)
////	{
////		// RTOS ainda não inicializou
////		return  LFS_ERR_OK;
////	}
////
////	//int state = osKernelUnlock();
////	int newLockState = osKernelRestoreLock(rtos_lockState);
////	int ret = LFS_ERR_OK;
////
////	if (newLockState < 0)
////	{
////		ret = LFS_ERR_IO;
////	}
////	return ret;
////}
////#endif
