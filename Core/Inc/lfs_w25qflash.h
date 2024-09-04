/*
 * lfs_w25qflash.h
 *
 *  Created on: Mar 13, 2024
 *      Author: italo
 */

#ifndef INC_LFS_W25QFLASH_H_
#define INC_LFS_W25QFLASH_H_

#include "lfs.h"
#include "lfs_util.h"
#include "w25qxx.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/


#define LITTLEFS_BLOCK_CYCLES 100
/* Minimum block cache size definition */
#define LITTLEFS_CACHE_SIZE 512
/* Minimum lookahead buffer size definition */
#define LITTLEFS_LOOKAHEAD_SIZE 256

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/
int lfs_get_default_config(struct lfs_config *lfsc);
int lfs_storage_init(const struct lfs_config *lfsc);


#endif /* INC_LFS_W25QFLASH_H_ */
