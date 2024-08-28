/*
 * cfg_files.c
 *
 *  Created on: Mar 15, 2024
 *      Author: italo
 */


#include "cfg_files.h"
#include "modbus.h"

#define MODBUS_MAP_FILE_PATH "modbus.map"
#define COMM_FILE            "comm.map"
#define BOOT_FILE            "boot.bin"


//#define LOG(...)
#define LOG(fmt, ...) printf(fmt "\r\n", ##__VA_ARGS__)

//#define LOG2(...)
#define LOG2 LOG


TModbusMap modbusMap;


typedef struct Cfg_buffer_t
{
  bool busy; /**<@brief indicates the buffer is been used*/
  uint8_t buffer[2048]; /**<@brief real buffer, where all data are, this size is defined by the LPBDRIVER_OUT_BUFFER_SIZE, the highest sie buffer*/
}Cfg_buffer_t;


/**
 * Array of buffers
 */
static Cfg_buffer_t Cfg_buffers[1];


/// List of Configuration Files
static TCfgFile listCfgFiles[TOTAL_CFG_FILES] = {0};


/**
 * @fn uint8_t *CfgFiles_getBuffer()
 * @brief function to get a buffer address to be used
 * @return return the buffer pointer to be used
 */
uint8_t *CfgFiles_getBuffer()
{
  for (int count = 0; count < sizeof(Cfg_buffers) / sizeof(Cfg_buffers[0]); count++)
  {
    if (!Cfg_buffers[count].busy)
    {
      Cfg_buffers[count].busy = true;
      memset(Cfg_buffers[count].buffer, 0, sizeof(Cfg_buffers[count].buffer)/sizeof(Cfg_buffers[count].buffer[0]));
      return Cfg_buffers[count].buffer;
    }
  }
  return NULL;
}

/**
 * @fn void CfgFiles_freeBuffer(uint8_t *)
 * @brief free a specific buffer to be used latter
 * @param buf buffer pointer to be freed
 */
void CfgFiles_freeBuffer(uint8_t *buf)
{
  for (int count = 0;count < sizeof(Cfg_buffers)/sizeof(Cfg_buffers[0]); count++)
  {
    if (buf == &(Cfg_buffers[count].buffer[0]))
    {
      Cfg_buffers[count].busy = false;
      break;
    }
  }
}
/**
 * @fn void CfgFiles_cleanBuffers()
 * @brief clean all buffers that are used for read/write on file
 */
void CfgFiles_cleanBuffers()
{
  for (int count = 0;count < sizeof(Cfg_buffers)/sizeof(Cfg_buffers[0]); count++)
  {
    Cfg_buffers[count].busy = false;
    memset(Cfg_buffers[count].buffer, 0, sizeof(Cfg_buffers[count].buffer)/sizeof(Cfg_buffers[count].buffer[0]));
  }
}



/**
 * @fn bool CfgFiles_GetRemoteFilePathByIndex(uint16_t fileIndex, char *fileName)
 * @brief This function retrieves the remote file path into the fileName pointer based on the index
 * @param  fileIndex Index of the file inside the list
 * @param  fileName Pointer to file name output
 * @retval  True: Success
 * @retval  False: Fail
 */
bool CfgFilesGeFilePathByIndex(uint16_t fileIndex, char *fileName)
{
  if ((fileIndex < TOTAL_CFG_FILES) && (fileName))
  {
    strcat (fileName,(char*) &listCfgFiles[fileIndex].dirPath);
    strcat(fileName, (char*) &listCfgFiles [fileIndex].name);
    return (true);
  }
  return (false);
}


static void SetListCfgFile(int fileIndex, const char *fileName, const char *dirName, void *fileMessage)
{
  strcpy(listCfgFiles [fileIndex].name, fileName);
  strcpy(listCfgFiles [fileIndex].dirPath, dirName);

  if (fileMessage)
  {
    listCfgFiles [fileIndex].fileContent = fileMessage;

  }
}






static void CfgFilesDecodeFiles(uint16_t fileIndex, void *fileDataBuffer, size_t fileSize, bool isInitialDecode)
{
  void *file = NULL;
  size_t size = 0;

  switch (fileIndex)
  {
    case MAP_FILE_IDX:
    {
      size = sizeof(TModbusMap);
      file = pvPortMalloc(size);
      memcpy(file, fileDataBuffer, size);

      break;
    }

    case COMM_FILE_IDX:
      // Implementação para COMM_FILE_IDX
      break;

    case BOOT_FILE_IDX:
      // Implementação para BOOT_FILE_IDX
      break;

    default:
      break;
  }



  if (file)
  {
    if (size > 0)
    {
      if (isInitialDecode)
      {
        // Fill file message with decoded data
        memcpy(listCfgFiles [fileIndex].fileContent, file, size);
      }
      else
      {
        // Compares current message to the new decoded message
        if (memcmp(listCfgFiles [fileIndex].fileContent, file, size) != 0)
        {
          // Cfg File has changed; update file message
          memcpy(listCfgFiles [fileIndex].fileContent, file, size);
          listCfgFiles [fileIndex].changed = true;
        }
      }
    }

    vPortFree(file);
    file = NULL;
  }

}


static bool CfgFilesEncode(uint16_t fileIndex, void *fileDataBuffer, size_t *fileSize, bool setDefaultValues)
{

  switch (fileIndex)
  {
    case MAP_FILE_IDX:

      TModbusMap *modbusFile = (TModbusMap *) listCfgFiles[fileIndex].fileContent;

       if (setDefaultValues)
         CreateDefaultModbusMap(modbusFile);
       *fileSize = sizeof(TModbusMap);

       return true;

      break;

    case COMM_FILE_IDX:

      break;

    case BOOT_FILE_IDX:

      break;

    default:

  }

 return false;
}






/**
 * @fn void CfgFilesInit()
 * @brief  Initializes control struct list for Configuration Files Management
 * @param  upsQueueHandle Queue Handle for UPS Data Exchange
 * @retval None
 */
void CfgFilesInit()
{

  /*Initialize all buffer to read/write on files*/
  CfgFiles_cleanBuffers();

  //------------------------------------------------------------------------------------
  //                    Fill List of Configuration Files
  //------------------------------------------------------------------------------------
  //             FILE_INDEX     FILE_NAME              DIR_NAME        TYPE_TIPE
  SetListCfgFile(MAP_FILE_IDX,  MODBUS_MAP_FILE_PATH,  MAP_DIR_PATH,   &modbusMap);
  SetListCfgFile(COMM_FILE_IDX, COMM_FILE,             CFG_DIR_PATH,   NULL);
  SetListCfgFile(BOOT_FILE_IDX, BOOT_FILE,             BOOT_DIR_PATH,  NULL);
  //------------------------------------------------------------------------------------

  for (int i = 0; i < TOTAL_CFG_FILES; i ++)
  {
    // Print Remote File Paths
    char fileName[32] = { 0 };

    if (CfgFilesGeFilePathByIndex(i, fileName))
    {
      LOG("index = %d file path: %s", i, fileName);
    }
    else
    {
      LOG("index = %d erro to get file path: %s", i, fileName);

    }
    // Open/Create file
    uint8_t fileDataBuffer [1024 * 2 /*LPBDRIVER_OUT_BUFFER_SIZE*/] = { 0 };
    size_t fileSize = 0;
    FILE_POINTER file = NULL;

    /*verify if file exists in file system*/
    if (file_exists((char*)fileName) == LFS_ERR_OK)
    {
      file = file_open((char*) fileName, "r"); //read-only
    }

    /*if have a file*/
    if (file)
    {
      fileSize = file_size(file);
    }

    if (fileSize == 0) // File is empty or is a new file
    {
      //------------------------------------
      if (file != NULL)
      {
        file_close(file);
      }

      file = file_open((char*) fileName, "w");  // Open file as "write-only"

      if (!file)
      {
        LOG("New File - Error: file not opened for writing; File Index = %03d; File Name: %s", i, listCfgFiles [i].name);
        continue;
      }

      if (!CfgFilesEncode(i, fileDataBuffer, &fileSize, true))
      {
        file_close(file); // error to encode data; close file and continue
        continue;
      }

      // Write file content
       listCfgFiles[i].size = file_write(fileDataBuffer, 1, fileSize, file);

       if (listCfgFiles[i].size != fileSize)
       {
         LOG("Data size written in file differs from the size requested; written = %lu bytes | requested = %d bytes", listCfgFiles[i].size, fileSize);

       }
       // New file, set as "changed"
      listCfgFiles[i].changed = true;

      file_close(file);
    }
    else
    {
      // Read file content
      listCfgFiles [i].size = file_read(fileDataBuffer, 1, fileSize, file);

      if (listCfgFiles [i].size != fileSize)
      {
        LOG("Data size read from file differs from the size requested; read = %lu bytes | requested = %d bytes", listCfgFiles [i].size, fileSize);
      }

      CfgFilesDecodeFiles(i, fileDataBuffer, fileSize, true /* sempre true na inicialização */);
      file_close(file);
    }

  }

}



















FILE *open_modbus_file(const char *mode) {

    FILE *file = file_open((char*) MODBUS_MAP_FILE_PATH, "ab+");
    if (!file) {
        printf("Erro ao abrir o arquivo %s.\n", MODBUS_MAP_FILE_PATH);
    }
    return file;
}

void close_modbus_file(FILE *file) {
    if (file) {

    	file_close(file);
    }
}



// Função para salvar a estrutura MB no arquivo
cfg_file_status_t save_mb_to_file(const TModbusMap *mb) {
    // Abra o arquivo para escrita binária
    FILE_POINTER file = open_modbus_file("wb");

    if (!file) {
        return CfgFiles_error_unknownError;
    }

    // Escreva a estrutura MB no arquivo
    size_t bytes_written = fwrite(mb, sizeof(TModbusMap), 1, file);

    if (bytes_written != 1) {

    	printf("Erro ao escrever no arquivo.\n");
        close_modbus_file(file);
        return CfgFiles_error_unknownError;
    }

    // Feche o arquivo
    close_modbus_file(file);

    printf("Dados salvos com sucesso no arquivo modbus.map.\n");

    return CfgFiles_success;
}


cfg_file_status_t load_mb_from_file(TModbusMap *mb) {
    // Abra o arquivo para leitura binária
    FILE_POINTER file = open_modbus_file("rb");
    if (!file) {
        return CfgFiles_error_unknownError;
    }

    // Leia os dados do arquivo para a estrutura MB
    size_t bytes_read = fread(mb, sizeof(TModbusMap), 1, file);
    if (bytes_read != 1) {
        printf("Erro ao ler do arquivo.\n");
        close_modbus_file(file);
        return CfgFiles_error_unknownError;
    }

    // Feche o arquivo
    close_modbus_file(file);

    printf("Dados carregados com sucesso do arquivo modbus.map \r\n");

    return CfgFiles_success;
}










cfg_file_status_t write_to_mb_single_register(TModbusMap *mb, int index, uint16_t value)
{
    if (mb == NULL)
    {
        printf("Ponteiro para estrutura MB inválido.\n");
        return CfgFiles_error_invalidParameter;
    }

    // Verifica se o índice está dentro dos limites do array HOLDINGREGISTERS
    if (index < 0 || index >= TOTAL_VARIAVEIS_HOLDING)
    {
        printf("Índice de registro inválido.\n");
        return CfgFiles_error_invalidParameter;
    }

    // Abrir o arquivo correspondente aos registros no sistema de arquivos LittleFS
    FILE_POINTER file = open_modbus_file("rb+");
    if (!file)
    {
        printf("Erro ao abrir o arquivo.\n");
        return CfgFiles_error_fileOperationFailed;
    }

    // Calcular a posição do registro no arquivo
    int position = index * sizeof(uint16_t);

    // Posicionar o cursor do arquivo na posição do registro
    if (file_seek(file, position, SEEK_SET) != 0)
    {
        printf("Erro ao posicionar o cursor do arquivo.\n");
        file_close(file);
        return CfgFiles_error_fileOperationFailed;
    }

    // Escrever o valor no registro
    size_t bytes_written = file_write(&value, sizeof(uint16_t), 1, file);
    if (bytes_written != 1)
    {
        printf("Erro ao escrever no arquivo.\n");
        file_close(file);
        return CfgFiles_error_fileOperationFailed;
    }

    // Fechar o arquivo
    if (file_close(file) != 0)
    {
        printf("Erro ao fechar o arquivo.\n");
        return CfgFiles_error_fileOperationFailed;
    }

    return CfgFiles_success;
}




uint16_t read_from_mb_address(const TModbusMap *mb, int function_index, int array_index) {

    if (mb == NULL) {
        printf("Ponteiro para estrutura MB inválido.\n");
        return 0; // ou qualquer outro valor de erro
    }

    int total_array_sizes[4] = {TOTAL_VARIAVEIS_COILS, TOTAL_VARIAVEIS_INPUT, TOTAL_VARIAVEIS_HOLDING, TOTAL_VARIAVEIS_ESPELHO};

    if (function_index < 0 || function_index >= 4) {
        printf("Índice de função inválido.\n");
        return 0; // ou qualquer outro valor de erro
    }

    if (array_index < 0 || array_index >= total_array_sizes[function_index]) {
        printf("Índice de array inválido.\n");
        return 0; // ou qualquer outro valor de erro
    }

    FILE_POINTER file = file_open(MODBUS_MAP_FILE_PATH, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return 0; // ou qualquer outro valor de erro
    }

    int array_start_position = 0;
    for (int i = 0; i < function_index; i++) {
        array_start_position += sizeof(uint16_t) * total_array_sizes[i];
    }

    int position = array_start_position + sizeof(uint16_t) * array_index;

    if (file_seek(file, position, SEEK_SET) != 0) {
        printf("Erro ao posicionar o cursor do arquivo.\n");
        file_close(file);
        return 0; // ou qualquer outro valor de erro
    }

    uint16_t value;
    if (file_read(&value, sizeof(uint16_t), 1, file) != 1) {
        printf("Erro ao ler do arquivo.\n");
        file_close(file);
        return 0; // ou qualquer outro valor de erro
    }

    file_close(file);

    return value;
}
