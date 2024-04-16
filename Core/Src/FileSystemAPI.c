/*
// * @file FileSystemAPI.c
// *
// */
//
//


#include "FileSystemAPI.h"
#include <errno.h>



/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef PORTMACRO_H
typedef long             BaseType_t;
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

#define LOG(fmt, ...) printf(fmt "\r\n", ##__VA_ARGS__)

//#define LOG2(...)
#define LOG2 LOG


static int16_t fsError = 0;

/**
 * @struct structure to support fileno function
 * @brief store the file "number" and the related pointer of open files; the file
// *        number is needed to supoort fileno function
 */
struct
{
  int number;
  FILE_TYPE file;
} openFile[MAX_OPEN_FILES];
int openFilesCount = 0;   /// Controls the number of open files registered in openFile structure

/**
 * @brief Função de inicializa o FileSystem.
 * @note  As seguintes ações são executadas:
 *         - Inicialização da dataflash;
 *         - Inicialização do FS;
 *         - Criação de diretórios;
 *         - Leitura do arquivo de configurações;
 * @retval Nonecfg
 */
int FileSystemInit()
{

	  LOG2("Iniciando sistema de arquivos ... ");

	  int status = lfs_storage_init(&cfg);

	  if (!status)
	  {
		  LOG2( "erro: %i", status);
	    return status;
	  }

	  LOG2("OK");

  lfs_get_default_config(&cfg);

  for (int i = 0; i < MAX_OPEN_FILES; ++i)
  {
    openFile[i].number = 0;
    memset(&openFile[i].file, 0, sizeof(openFile[i].file));
  }


  LOG2("Montando sistema de arquivos ... ");

  status = lfs_mount(&lfs, &cfg);
  if (status)
  {
	  LOG2("erro: %i", status);
    // Se sistema de arquivos corrompido
    if (status == LFS_ERR_CORRUPT)
    {
      // Formata o sistema de arquivos
    	LOG2("Formatando sistema de arquivos ... ");
      status = lfs_format(&lfs, &cfg);
      if (status)
      {
    	  LOG2("erro: %d", status);
      }
    }
  }

  if (status == LFS_ERR_OK)
  {
	  LOG2("OK");
    lfs_mounted = 1;

    // Cria diretório de configurações
    lfs_mkdir(&lfs, FILESYSTEM_FOLDER_MAP);

  }

  return status;
}


/*
 * Return the (stdio) flags for a given mode.
 * Based on https://android.googlesource.com/platform/bionic/+/ics-mr0/libc/stdio/flags.c
 * Return 0 on error.
 */
static int __sflags(const char *mode)
{
  int ret, m, o;
  switch (*mode++)
  {
    case 'r': /* open for reading */
      m = LFS_O_RDONLY;
      o = 0;
      break;
    case 'w': /* open for writing */
      m = LFS_O_WRONLY;
      o = LFS_O_CREAT | LFS_O_TRUNC;
      break;
    case 'a': /* open for appending */
      m = LFS_O_WRONLY;
      o = LFS_O_CREAT | LFS_O_APPEND;
      break;
    default: /* illegal mode */
      errno = EINVAL;
      return (0);
  }
  /* [rwa]\+ or [rwa]b\+ means read and write */
  if (*mode == '+' || (*mode == 'b' && mode[1] == '+'))
  {
    m = LFS_O_RDWR;
  }
  ret = m | o;
  return (ret);
}

/**
 * @brief  Função que abre o diretório do FileSystem
 * @param  lfs  Ponteiro para o struct de controle do FileSystem
 * @param  dir  Ponteiro para o struct de controle do diretório do FileSystem
 * @param  path Ponteiro para a string contendo o path do diretório
 * @retval int  Status da operação
 */
int dir_open(const char *path, lfs_dir_t *dir)
{
  // Remove line feed and carriage return from path
  char *pchar = (char*)path;
  while (*pchar != 0)
  {
	if ((*pchar == '\r') || (*pchar == '\n'))
	  *pchar = 0;
	pchar++;
  }

  int status = lfs_dir_open(&lfs, dir, path);

	if (status != LFS_ERR_OK)
    {
		LOG2("Error lfs_dir_open - path %s - ret = %i", path, status);
      return status;
    }

	LOG2("lfs_dir_open - path %s - ret = %i", path, status);
  return status;
}

/**
 * @brief  Função que lê entrada do diretório do FileSystem
 * @param  dir  Ponteiro para o struct de controle do diretório do FileSystem
 * @param  ponteiro para estrutura com informação da entrada
 * @retval int
 * Valor positivo em caso de sucesso, 0 se fim do diretório e valor negativo em caso de erro
 */
int dir_read(lfs_dir_t *dir, struct lfs_info *info)
{
	int status = lfs_dir_read(&lfs, dir, info);
	if (status < 0)
	{
		LOG2( "Error lfs_dir_read - status = %i", status);
	}
	else if (status == 0)
	{
		LOG2("End of Directory - lfs_dir_read - status = %i", status);
	}
	return status;
}

/**
 * @brief  Função que retorna posição de leitura do diretório para o início
 * @param  dir  Ponteiro para o struct de controle do diretório do FileSystem
 * @retval int
 * Valor positivo em caso de sucesso, 0 se fim do diretório e valor negativo em caso de erro
 */
int dir_rewind(lfs_dir_t *dir)
{
  int status = lfs_dir_rewind(&lfs, dir);
  if (status < 0)
  {
	  LOG2("Error lfs_dir_rewind - status = %i", status);
  }
  else if (status == 0)
  {
	  LOG2("Directory Rewind - lfs_dir_rewind - status = %i", status);
  }
  return status;
}

/**
 * @brief  Função que fecha o diretório do FileSystem
 * @param  lfs Ponteiro para o struct de controle do FileSystem
 * @param  dir Ponteiro para o struct de controle do diretório do FileSystem
 * @retval int Status da operação
 */
int dir_close(lfs_dir_t *dir)
{
  int status = lfs_dir_close(&lfs, dir);
  if (status != LFS_ERR_OK)
  {
	  LOG2("Erro lfs_dir_close - ret = %i", status);
    return status;
  }

  LOG2("lfs_dir_close - ret = %i",status);
  return status;
}

/**
 * @brief  Função de abertura do arquivo
 * @param  path  Ponteiro para a string contendo o path do arquivo
 * @param  mode  C string contendo o modo de acesso do arquivo
 * @retval file  Ponteiro para o struct de controle do arquivo
 */
FILE_POINTER file_open(const char *path, const char *mode)
{
  int flags;
  int count = 0;

  if (openFilesCount >= MAX_OPEN_FILES)
    return NULL;

  if ((flags = __sflags(mode)) == 0)
    return (NULL);

  // Remove line feed and carriage return from path
  char *pchar = (char*)path;
  while (*pchar != 0)
  {
    if ((*pchar == '\r') || (*pchar == '\n'))
      *pchar = 0;
    pchar++;
  }

  // Create a entry for the file in openFile structure
  for (count = 0; count < MAX_OPEN_FILES; ++count)
  {
    if (openFile[count].number == 0)
    {
      openFile[count].number = openFilesCount++;
      break;
    }
  }

  int status = lfs_file_open(&lfs, &(openFile[count].file), path, flags);

  if (status != LFS_ERR_OK)
  {
    openFile[count].number = 0;
    openFilesCount--;
    LOG2("Error lfs_file_open - file %s - ret = %i", path, status);
    return NULL;
  }

  LOG2("lfs_file_open - file %s - ret = %i", path, status);
  return &openFile[count].file;
}

/**
 * @brief  Função de fechamento do arquivo
 * @param  file Ponteiro para o struct de controle do arquivo
 * @retval int  Status da operação
 */
int file_close(FILE_POINTER file)
{
  //***FS_Flush(lfs, file);
  int status = lfs_file_close(&lfs, file);

  // Delete the entry assigned to file in openFile structure
  for (int i = 0; i < MAX_OPEN_FILES; ++i)
  {
    if (&(openFile[i].file) == file)
    {
      openFile[i].number = 0;
      memset(&openFile[i].file, 0, sizeof(openFile[i].file));
      break;
    }
  }

  if (status != LFS_ERR_OK)
  {
	  LOG2("Erro lfs_file_close - ret = %i", status);
    return status;
  }

  openFilesCount--;
  LOG2("lfs_file_close - ret = %i",
            status);
  return status;
}

/**
 * @brief  Função que lê dados do arquivo do FileSystem.
 *       Esta função não realiza operações com o ponteiro de posicionamento de leitura do arquivo,
 *       apenas efetua a leitura da quantidade de bytes informada no parâmetro.
 * @param  ptr  Ponteiro para o destino da leitura
 * @param  file Ponteiro para o struct de controle do arquivo do FileSystem
 * @param  size Quantidade de bytes solicitados para leitura
 * @param  count Quantidade de leituras
 * @retval int  Quantidade de bytes lidos
 */
size_t file_read(void *ptr, size_t size, size_t count, FILE_POINTER file)
{
  lfs_ssize_t qtdBytes = lfs_file_read(&lfs, file, ptr, size * count);
  if (qtdBytes < 0)
  {
	  LOG2("Erro lfs_file_read - ret = %li", qtdBytes);
    return 0;

  }
  if (qtdBytes != (size * count))
  {
	  LOG2("Erro lfs_file_read - Quantidade de bytes lidos (%li) diferente do solicitado (%li)", qtdBytes, size);
  }
  return qtdBytes;
}

/**
 * @brief  Função que lê uma linha do arquivo do FileSystem.
 * @param  str  string de destino
 * @param  file Ponteiro para o struct de controle do arquivo do FileSystem
 * @param  size Quantidade de bytes solicitados para leitura
 * @retval int  Ponteiro para a string lida ou NULL se houver erro
 */
char* file_gets(char *str, size_t size, FILE_POINTER file)
{
  int i = 0;
  char ch;
  memset(str, 0, size);
  lfs_ssize_t qtdBytes = lfs_file_read(&lfs, file, &ch, 1);
  while (ch != '\n' && qtdBytes > 0 && i < size - 1)
  {
    str[i] = ch;
    qtdBytes = lfs_file_read(&lfs, file, &ch, 1);
    i++;
  }
  if (ch == '\n')
    str[i] = '\n';
  if (i == 0 && qtdBytes == 0)
  {
      return NULL;
  }
  return str;
}

/**
 * @brief  Função que escreve dados no arquivo do FileSystem.
 *       Esta função não realiza operações com o ponteiro de posicionamento de escrita do arquivo,
 *       apenas efetua a escrita da quantidade de bytes informada no parâmetro.
 * @param  file Ponteiro para o struct de controle do arquivo do FileSystem
 * @param  path Ponteiro para o buffer que receberá os dados escritos
 * @param  size Quantidade de bytes solicitados para escrita
 * @retval int  Quantidade de bytes escritos
 */
size_t file_write(const void *ptr, lfs_size_t size, size_t count, FILE_POINTER file)
{
  lfs_ssize_t qtdBytes = 0;
  if (file->flags & (LFS_O_RDWR | LFS_O_APPEND | LFS_O_WRONLY))     // Verifica o status da flag do arquivo aberto
  {
    qtdBytes = lfs_file_write(&lfs, file, ptr, size * count);
    if (qtdBytes < 0)
    {
    	LOG2("Erro lfs_file_write - ret = %li", qtdBytes);
      return 0;
    }
    if (qtdBytes != (size * count))
    {
    	LOG2("Erro lfs_file_write - Quantidade de bytes escritos (%li) diferente do solicitado (%li)",
          qtdBytes, size);
    }
  }
  else
  {
    // Caso o arquivo não seja compativel com a operação requerida, apenas informa que não foi executado
	  LOG2("Arquivo não alterado, flag do file [ 0x%lx ]", file->flags);
  }
  return (size_t)(qtdBytes / size);
}

/**
 * @fn int file_delete(const char*)
 * @brief exclui arquivo do FileSystem
 * @param path  Ponteiro para a string contendo o path do arquivo
 * @return int  Status da operação
 */
int file_delete(const char *path)
{
  return lfs_remove(&lfs, path);
}

/**
 * @fn int file_exists(const char*)
 * @brief verifica a existencia do path de arquivo ou diretório
 * @param path  Ponteiro para a string contendo o path do arquivo ou diretório
 * @return int  Status da operação
 */
int file_exists(const char *path)
{
  struct lfs_info info;

  // Remove line feed and carriage return from path
  char *pchar = (char*)path;
  while (*pchar != 0)
  {
    if ((*pchar == '\r') || (*pchar == '\n'))
      *pchar = 0;
    pchar++;
  }

  int status = lfs_stat(&lfs, path, &info);

  return status;
}

/**
 * @fn int file_ls(const char*, void*, uint8_t(*)(void*, uint8_t*))
 * @brief lista os arquivos do diretório e envia as strings para o socket
 * @param path  Ponteiro para a string contendo o path do arquivo
 * @param OUTHandle handle da conexão
 * @param send_func Ponteiro para função de envio dos nomes de arquivo
 * @return int  Status da operação
 */
int file_ls(const char *path, void *OUTHandle, uint8_t (*send_func)(void*, uint8_t*))
{
  int res;
  lfs_dir_t dir;
  struct lfs_info info;
  char *tempBuffer[256];

  if (!lfs_mounted)
  {
    return LFS_ERR_IO;
  }

  /* open the directory */
  res = lfs_dir_open(&lfs, &dir, path);
  if (res)
  {
    return LFS_ERR_NOTDIR;
  }

  /* iterate until end of directory */
  while ((res = lfs_dir_read(&lfs, &dir, &info)) != 0)
  {
    char mode[11] = "-rw-rw-rw-";
    BaseType_t st_nlink = 1;
    const char user[5] = "lupa";
    const char group[5] = "lupa";
    const char date[] = "Jan 01 00:00";

    if (res < 0)
    {
      /* break the loop in case of an error */
      break;
    }

    if (info.type == LFS_TYPE_REG)
    {
      //SHELL_Printf("%8d %s\r\n", info.size, info.name);
      //send_func(OUTHandle, (uint8_t*) info.name);
    }
    else if (info.type == LFS_TYPE_DIR)
    {
      //SHELL_Printf("%     DIR %s\r\n", info.name);
      mode[0] = 'd';
      //sprintf(tempBuffer, "<DIR> %s", info.name);
    }
    else
    {
      //SHELL_Printf("%???\r\n");
      continue;
    }
    sprintf(tempBuffer, "%s %3ld %-4s %-4s %8d %12s %s\r\n",  mode, st_nlink, user, group, (int)info.size, date, info.name);
    send_func(OUTHandle, (uint8_t*) tempBuffer);
  }

  res = lfs_dir_close(&lfs, &dir);
  if (res)
  {
    return LFS_ERR_IO;
  }

  return LFS_ERR_OK;
}

/**
 * @fn int file_size(lfs_file_t*)
 * @brief return file size
 * @param file  point to file
 * @return  file size or error (negative value)
 */
int file_size(FILE_POINTER file)
{
  int status;
  if ((status = lfs_file_seek(&lfs, file, 0, LFS_SEEK_CUR)) < 0)
    return status;
  int currentPosition = status;
  if ((status = lfs_file_seek(&lfs, file, 0, LFS_SEEK_END)) < 0)
    return status;
  lfs_file_seek(&lfs, file, currentPosition, LFS_SEEK_SET);
  return status;
}

#include <stdarg.h>

int file_printf(FILE_POINTER file, const char *format, ...)
{
  int result = 0;
  char buffer[256];

  if (file == NULL)
    return 0;
  va_list args;
  va_start (args, format);
  result = vsprintf (buffer, format, args);
  //perror (buffer);
  va_end (args);

  if (result > 0)
  {
    result = file_write(buffer, result, 1, file);
  }

  return result;
}

int file_number (FILE_POINTER file)
{
  if (file == NULL)
    return -1;

  // Return the entry assigned to file in openFile structure
  for (int i = 0; i < MAX_OPEN_FILES; ++i)
  {
    if (&openFile[i].file == file)
    {
      return openFile[i].number;
    }
  }

  return 0;
}

//int fstat (int __fd, struct stat *__sbuf );

// Find info about a file or directory
//
// Fills out the info structure, based on the specified file or directory.
// Returns a negative error code on failure.
//int lfs_stat(lfs_t *lfs, const char *path, struct lfs_info *info);

int file_stat (int __fd, struct stat *__sbuf )
{
  FILE_POINTER file = NULL;

  // Return the entry assigned to file in openFile structure
  for (int i = 0; i < MAX_OPEN_FILES; ++i)
  {
    if (openFile[i].number == __fd)
    {
      file = &openFile[i].file;
      break;
    }
  }

  if (file == NULL)
  {
    //fsError = LFS_ERR_NOENT;
    return LFS_ERR_NOENT;
  }

  memset(__sbuf, 0, sizeof(struct stat));
  __sbuf->st_size = lfs_file_size(&lfs, file);
  return 0;
}

int file_seek (FILE_POINTER file, long offset, int whence)
{
  int res = lfs_file_seek(&lfs, file, offset, whence);
  if (res > 0)
    return 0;
  else
    return res;
}

int file_error(FILE_POINTER file)
{
  return fsError;
}

int file_eof(FILE_POINTER file)
{
	if (file->pos >= file->ctz.size)
	{
		return 1;
	}
	return 0;
}

int file_tell(FILE_POINTER file)
{
  return lfs_file_tell(&lfs, file);
}

int file_rename (const char *oldpath, const char *newpath)
{
  return lfs_rename (&lfs, oldpath, newpath);
}
