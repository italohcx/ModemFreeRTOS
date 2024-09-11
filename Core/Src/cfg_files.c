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
#define LOG_FILE_CONFIG      "log-config.bin"

#define LOG(...)
//#define LOG(fmt, ...) printf(fmt "\r\n", ##__VA_ARGS__)

#define LOG2(...)
//#define LOG2 LOG


TModbusMap modbusMapFile;
Log_config logConfigFile;


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

  case LOG_FILE_IDX:

	size = sizeof(Log_config);
	file = pvPortMalloc(size);
	memcpy(file, fileDataBuffer, size);

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
		memcpy(listCfgFiles[fileIndex].fileContent, file, size);
	  }
	  else
	  {
		// Compares current message to the new decoded message
		if (memcmp(listCfgFiles[fileIndex].fileContent, file, size) != 0)
		{
		  // Cfg File has changed; update file message
		  memcpy(listCfgFiles[fileIndex].fileContent, file, size);
		  listCfgFiles[fileIndex].changed = true;
		}
	  }
	}

	vPortFree(file);
	file = NULL;
  }

}


static bool CfgFilesEncode(uint16_t fileIndex, void *fileDataBuffer,
	size_t *fileSize, bool setDefaultValues)
{

  switch (fileIndex)
  {
  case MAP_FILE_IDX:

	TModbusMap *modbusFile = (TModbusMap*) listCfgFiles[fileIndex].fileContent;

	if (setDefaultValues)
	{
	  CreateDefaultModbusMap(fileDataBuffer, modbusFile);

	}
	else
	{

	  memcpy(fileDataBuffer, modbusFile, sizeof(TModbusMap));
	}

	*fileSize = sizeof(TModbusMap);

	return true;

	break;

  case COMM_FILE_IDX:

	break;

  case BOOT_FILE_IDX:

	break;

  case LOG_FILE_IDX:

	Log_config *logConfig = (Log_config*) listCfgFiles[fileIndex].fileContent;

	if (setDefaultValues)
	{
	  memset(logConfig, 0, sizeof(Log_config));

	 logConfig->enable = true;
	 logConfig->logList_count = 0;

	}
	else
	{

	  memcpy(fileDataBuffer, logConfig, sizeof(Log_config));
	}

	*fileSize = sizeof(Log_config);
	break;

  default:

  }

  return false;
}




/**
 * @fn void CfgFilesInit()
 * @brief  Initializes control struct list for Configuration Files Management
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
  SetListCfgFile(MAP_FILE_IDX,  MODBUS_MAP_FILE_PATH,  MAP_DIR_PATH,   &modbusMapFile);
  SetListCfgFile(COMM_FILE_IDX, COMM_FILE,             CFG_DIR_PATH,   NULL);
  SetListCfgFile(BOOT_FILE_IDX, BOOT_FILE,             BOOT_DIR_PATH,  NULL);
  SetListCfgFile(LOG_FILE_IDX,  LOG_FILE_CONFIG,       MAP_DIR_PATH,   &logConfigFile);


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

bool CfgFiles_UpdateCfgFileByIndex(uint16_t fileIndex, bool setDefaultValues)

{
  // Print Remote File Paths
  char fileName [32] = { 0 };

  if (!CfgFilesGeFilePathByIndex(fileIndex, fileName))
  {
    return false;
  }

  LOG("Updating config file; File Index = %d; File Name: %s", fileIndex, fileName);

  // Open/Create file
  uint8_t *fileDataBuffer = CfgFiles_getBuffer();
  if (!fileDataBuffer)
  {
    return false;
  }

  size_t fileSize = 0;
  FILE_POINTER file = NULL;
  file = file_open((char*) fileName, "w"); //write-only
  fileSize = file_size(file);

  if (!CfgFilesEncode(fileIndex, fileDataBuffer, &fileSize, setDefaultValues))
  {
    file_close(file); // error to encode data; close file and continue
    return false;
  }

  // Write file content
  listCfgFiles [fileIndex].size = file_write(fileDataBuffer, 1, fileSize, file);

  if (listCfgFiles [fileIndex].size != fileSize)
  {

    LOG("Data size written in file differs from the size requested; written = %lu bytes | requested = %d bytes", listCfgFiles [fileIndex].size, fileSize);
  }

  file_close(file);
  CfgFiles_freeBuffer(fileDataBuffer);
  return true;

}

void CfgFiles_RestoreFactoryDefault()
{
  for (int i = 0; i < TOTAL_CFG_FILES; i++)
  {

    CfgFiles_UpdateCfgFileByIndex(i, false);

  }

}








