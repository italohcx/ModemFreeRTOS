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

#define CFG_DIR_PATH       FILESYSTEM_FOLDER_CONFIG"/"

typedef enum
{
  CfgFiles_success                       =  0, /**<@brief everything was ok*/
  CfgFiles_error_badPointer              = -1, /**<@brief bad pointer error*/
  CfgFiles_error_unknownError            = -2, /**<@brief unknown error*/
  CfgFiles_error_noCallbackFound         = -3, /**<@brief If we are looking for a callback and found not similar */
  CfgFiles_error_semaphoreInitialization = -4, /**<@brief Get timeout while was waiting initialized */
  CfgFiles_error_invalidParameter        = -5, /**<@brief Parameter is invalid */
  CfgFiles_error_transferFailed          = -6, /**<@brief  Transfer failed */
} cfg_file_status_t;

/// Enum for file index definition into configuration file control structure
typedef enum CfgFileIndex
{
  MAP_FILE_IDX = 0,
  COMM_FILE_IDX,

} TCfgFileIndex;

/// Control struct for configuration file management
typedef struct _CFG_FILE
{
  char name[MAX_SIZE_FILE_NAME];
  uint32_t size;
  char localDirPath[MAX_SIZE_DIR_PATH];
  void *file;
}TCfgFile;






#endif /* INC_CFG_FILES_H_ */
