/*
 * file_system.h
 *
 *  Created on: Nov 21, 2022
 *      Author: italo.francis
 */

#ifndef INC_FILE_SYSTEM_H_
#define INC_FILE_SYSTEM_H_




//----------------------------------------------------------------------------
#include "lfs.h"	// File System LittleFS
#include "lfs_util.h"
//#include "w25qxx.h"
//----------------------------------------------------------------------------

#define _FS_DEBUG  1




void LFS_Config(void);
int FS_Montar(lfs_t *lfs);
int FS_Desmontar(lfs_t *lfs);
int FS_Formatar(lfs_t *lfs);
int FS_InicializarFileSystem(lfs_t *lfs);
int FS_CriarDiretorio(lfs_t *lfs, const char *path);
int FS_AbrirDiretorio(lfs_t *lfs, lfs_dir_t *dir, const char *path);
int FS_FecharDiretorio(lfs_t *lfs, lfs_dir_t *dir);
int FS_AbrirArquivo(lfs_t *lfs, lfs_file_t *file, const char *path, int flags);
int FS_FecharArquivo(lfs_t *lfs, lfs_file_t *file);
int FS_SalvarArquivo(lfs_t *lfs, lfs_file_t *file);
int FS_ExcluirPath(lfs_t *lfs, const char *path);
int FS_RewindArquivo(lfs_t *lfs, lfs_file_t *file);


lfs_ssize_t FS_LerArquivo(lfs_t *lfs, lfs_file_t *file, void *buffer, lfs_size_t size);
lfs_ssize_t FS_EscreverArquivo(lfs_t *lfs, lfs_file_t *file, void *buffer, lfs_size_t size);


#endif /* INC_FILE_SYSTEM_H_ */
