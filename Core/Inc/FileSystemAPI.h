/*
 * @file FileSystemAPI.h
 *
 *
 */

#include "lfs.h"
#include "lfs_util.h"
#include "lfs_w25qflash.h"


#define FILE_POINTER           lfs_file_t*
#define FILE_TYPE              lfs_file_t
#define DIRECTORY_POINTER      lfs_dir_t*
#define DIRECTORY_TYPE         lfs_dir_t
#define FILESYSTEM_FOLDER_MAP           "map"
#define FILESYSTEM_FOLDER_CONFIG        "cfg"
#define FILESYSTEM_FOLDER_BOOTLOADER    "boot"




#define MAX_OPEN_FILES           (4)


extern int lfs_mounted;
extern lfs_t lfs;
extern struct lfs_config cfg;



/**
 * @brief Função de inicializa o FileSystem.
 * @note  As seguintes ações são executadas:
 *         - Inicialização da dataflash;
 *         - Inicialização do FS;
 *         - Criação de diretórios;
 *         - Leitura do arquivo de configurações;
 * @retval None
 */
int FileSystemInit();

/**
 * @brief  Função de abertura do arquivo
 * @param  path  Ponteiro para a string contendo o path do arquivo
 * @param  mode  C string contendo o modo de acesso do arquivo
 * @retval file  Ponteiro para o struct de controle do arquivo
 */
FILE_POINTER file_open(const char *path, const char *mode);

/**
 * @brief  Função de fechamento do arquivo
 * @param  file Ponteiro para o struct de controle do arquivo
 * @retval int  Status da operação
 */
int file_close(lfs_file_t *file);

/**
 * @brief  Função que lê dados do arquivo do FileSystem.
 *       Esta função não realiza operações com o ponteiro de posicionamento de leitura do arquivo,
 *       apenas efetua a leitura da quantidade de bytes informada no parâmetro.
 * @param  file Ponteiro para o struct de controle do arquivo do FileSystem
 * @param  path Ponteiro para o buffer que receberá os dados lidos
 * @param  size Quantidade de bytes solicitados para leitura
 * @retval int  Quantidade de bytes lidos
 */
size_t file_read(void *ptr, size_t size, size_t count, lfs_file_t *file);

/**
 * @brief  Função que lê uma linha do arquivo do FileSystem.
 * @param  str  string de destino
 * @param  file Ponteiro para o struct de controle do arquivo do FileSystem
 * @param  size Quantidade de bytes solicitados para leitura
 * @retval int  Ponteiro para a string lida ou NULL se houver erro
 */
char* file_gets(char *str, size_t size, FILE_POINTER file);

/**
 * @brief  Função que escreve dados no arquivo do FileSystem.
 *       Esta função não realiza operações com o ponteiro de posicionamento de escrita do arquivo,
 *       apenas efetua a escrita da quantidade de bytes informada no parâmetro.
 * @param  file Ponteiro para o struct de controle do arquivo do FileSystem
 * @param  path Ponteiro para o buffer que receberá os dados escritos
 * @param  size Quantidade de bytes solicitados para escrita
 * @retval int  Quantidade de bytes escritos
 */
size_t file_write(const void *ptr, lfs_size_t size, size_t count, lfs_file_t *file);

/**
 * @fn int file_delete(const char*)
 * @brief exclui arquivo do FileSystem
 * @param path  Ponteiro para a string contendo o path do arquivo
 * @return int  Status da operação
 */
int file_delete(const char *path);

/**
 * @fn int file_exists(const char*)
 * @brief verifica a existencia do arquivo
 * @param path  Ponteiro para a string contendo o path do arquivo
 * @return int  Status da operação
 */
int file_exists(const char *path);

/**
 * @fn int file_ls(const char*, void*, uint8_t(*)(void*, uint8_t*))
 * @brief lista os arquivos do diretório e envia as strings para o socket
 * @param path  Ponteiro para a string contendo o path do arquivo
 * @param OUTHandle handle da conexão
 * @param send_func Ponteiro para função de envio dos nomes de arquivo
 * @return int  Status da operação
 */
int file_ls(const char *path, void *OUTHandle, uint8_t (*send_func)(void*, uint8_t*));

/**
 * @fn int file_size(lfs_file_t*)
 * @brief return file size
 * @param file  point to file
 * @return  file size or error (negative value)
 */
int file_size(FILE_POINTER file);

/**
 * @fn int file_tell(lfs_file_t*)
 * @brief return position of the file
 * @param file  point to file
 * @return  file position or error (negative value)
 */
int file_tell(FILE_POINTER file);

int file_rename (const char *oldpath, const char *newpath);

int file_printf(FILE_POINTER file, const char *fmt_s, ...);

int file_number (FILE_POINTER file);

#include <sys/stat.h>

int file_stat (int __fd, struct stat *__sbuf );

int file_seek (FILE_POINTER file, long offset, int whence);

int file_error(FILE_POINTER file);

int file_eof(FILE_POINTER file);

//lfs_dir_t *dir_open(const char *path);
int dir_open(const char *path, lfs_dir_t *dir);

//struct lfs_info *dir_read(lfs_dir_t *dir);
int dir_read(lfs_dir_t *dir, struct lfs_info *info);

int dir_close(lfs_dir_t *dir);

int list_files(const char *path);


