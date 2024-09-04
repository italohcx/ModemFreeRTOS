/*
 * cfg_files.h
 *
 *  Created on: Mar 15, 2024
 *      Author: italo
 */

#ifndef INC_CFG_FILES_H_
#define INC_CFG_FILES_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "cmsis_os.h"
#include "FileSystemAPI.h"
#include "modbus_map.h"

#define MAP_DIR_PATH       FILESYSTEM_FOLDER_MAP"/"
#define CFG_DIR_PATH       FILESYSTEM_FOLDER_CONFIG"/"
#define BOOT_DIR_PATH      FILESYSTEM_FOLDER_BOOTLOADER"/"
#define TOTAL_CFG_FILES    (3)

#define MAX_SIZE_FILE_NAME   32
#define MAX_SIZE_DIR_PATH    8



typedef enum {
    CfgFiles_success = 0,
    CfgFiles_error_badPointer = -1,
    CfgFiles_error_invalidParameter = -2,
    CfgFiles_error_fileOpenFailed = -3,
    CfgFiles_error_fileOperationFailed = -4,
	CfgFiles_error_unknownError = -5
} cfg_file_status_t;

/// Enum for file index definition into configuration file control structure



typedef enum CfgFileIndex
{
  MAP_FILE_IDX = 0,
  COMM_FILE_IDX,
  BOOT_FILE_IDX,

} TCfgFileIndex;


typedef struct _CFG_FILE
{
	char name[MAX_SIZE_FILE_NAME];
	uint32_t size;
	bool changed;
	void *file;
	bool isOpened;
	char dirPath[MAX_SIZE_DIR_PATH];
	void *fileContent;
} TCfgFile;


extern TModbusMap modbusMapFile;

bool CfgFiles_UpdateCfgFileByIndex(uint16_t fileIndex, bool setDefaultValues);

void CfgFilesInit();

#endif /* INC_CFG_FILES_H_ */
