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

#define CFG_DIR_PATH       FILESYSTEM_FOLDER_CONFIG"/"
#define TOTAL_CFG_FILES    (2)

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

} TCfgFileIndex;



#endif /* INC_CFG_FILES_H_ */
