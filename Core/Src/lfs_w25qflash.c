/*
 * lfs_w25qflash.c
 *
 *  Created on: Mar 13, 2024
 *      Author: italo
 */

#include "lfs_w25qflash.h"
#define LOG printf

#define LOG2(...)
//#define LOG2 printf

#ifdef LFS_THREADSAFE
#include "cmsis_os.h"
#endif

/***********************************************************************************************************************
 * Callback functions
 **********************************************************************************************************************/
/* LittleFS read a block region callback*/
int lfs_w25qflash_read(const struct lfs_config*, lfs_block_t, lfs_off_t, void*, lfs_size_t);
/* LittleFS program a block region callback*/
int lfs_w25qflash_prog(const struct lfs_config*, lfs_block_t, lfs_off_t, const void*, lfs_size_t);
/* LittleFS erase a block callback*/
int lfs_w25qflash_erase(const struct lfs_config*, lfs_block_t);
/* LittleFS state sync callback*/
int lfs_w25qflash_sync(const struct lfs_config*);

#ifdef LFS_THREADSAFE
/* LittleFS lock callback*/
static int lfs_lock(const struct lfs_config *c);
/* LittleFS unlock callback*/
static int lfs_unlock(const struct lfs_config *c);
#endif



extern w25qxx_t w25qxx;
struct lfs_config littlefs_config;

/*******************************************************************************
 * Variables
 ******************************************************************************/

//struct lfs_mflash_ctx LittleFS_ctx = {LITTLEFS_START_ADDR};



void lfs_w25qflash_config_init ()

{

littlefs_config.read = lfs_w25qflash_read;
littlefs_config.prog = lfs_w25qflash_prog;
littlefs_config.erase = lfs_w25qflash_erase;
littlefs_config.sync = lfs_w25qflash_sync;
#ifdef LFS_THREADSAFE
littlefs_config.lock = lfs_lock;
littlefs_config.unlock = lfs_unlock;
#endif

 littlefs_config.read_size = w25qxx.PageSize;
 littlefs_config.prog_size = w25qxx.PageSize;
 littlefs_config.block_size = w25qxx.SectorSize;
 littlefs_config.block_count = w25qxx.SectorCount;
 littlefs_config.block_cycles = 100;
 littlefs_config.cache_size = LITTLEFS_CACHE_SIZE;
 littlefs_config.lookahead_size = LITTLEFS_LOOKAHEAD_SIZE;
}


/**
 * @brief Função de interface do LittleFS com a biblioteca da memória Flash NAND para operação de leitura
 */
int lfs_w25qflash_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size) {

	if (W25qxx_ReadSector((uint8_t*) buffer, block, off, size)) {

		LOG2("Leitura da flash no  - bloco %lu - off %lu - %lu bytes lidos\r\n", block, off, size);

		return LFS_ERR_OK;

	} else {

	  return LFS_ERR_CORRUPT;
	}
}


/**
 * @brief Função de interface do LittleFS com a biblioteca da memória Flash NAND para operação de escrita
 */

int lfs_w25qflash_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size) {

	if (W25qxx_WriteSector((uint8_t*) buffer, block, off, size)) {

		LOG2("Escrita da flash no - bloco %lu - off %lu  - %lu bytes escritos\r\n", block, off, size);

		return LFS_ERR_OK;

	} else {

		return LFS_ERR_CORRUPT;
	}
}

/**
 * @brief Função de interface do LittleFS com a biblioteca da memória Flash NAND para operação de apagamento (erase)
 */
int lfs_w25qflash_erase(const struct lfs_config *c, lfs_block_t block) {

  	 W25qxx_EraseSector(block);
	return LFS_ERR_OK;
}

/**
 * @brief Função de interface do LittleFS com a biblioteca da memória Flash NAND para operação de sincronismo
 * 		  (para a Flash NAND esta função não é necessária, apenas retorna OK)
 */

int lfs_w25qflash_sync(const struct lfs_config *c) {

	return LFS_ERR_OK;
}


int lfs_get_default_config(struct lfs_config *lfsc)
{

	lfs_w25qflash_config_init();

    *lfsc = littlefs_config; /* copy pre-initialized lfs config structure */
    return 0;
}

int lfs_storage_init(const struct lfs_config *lfsc)
{
    uint16_t status;

    /* initialize mflash */
    status = W25qxx_Init();

    return status;
}

#ifdef LFS_THREADSAFE

//============================================================================

#if (osCMSIS < 0x20000U) /* CMSIS V1 */

//****************************************************************************
// Não existem métodos para lock e unlock do kernel RTOS no CMSIS V1
// Utilizando código abaixo extraído do CMSIS V2
//****************************************************************************

//***  cmsis_os2.h
/// Status code values returned by CMSIS-RTOS functions.
typedef enum {
 // osOK                      =  0,         ///< Operation completed successfully.
  osError                   = -1,         ///< Unspecified RTOS error: run-time error but no other error message fits.
  osErrorTimeout            = -2,         ///< Operation not completed within the timeout period.
 // osErrorResource           = -3,         ///< Resource not available.
 // osErrorParameter          = -4,         ///< Parameter error.
//  osErrorNoMemory           = -5,         ///< System is out of memory: it was impossible to allocate or reserve memory for the operation.
 // osErrorISR                = -6,         ///< Not allowed in ISR context: the function cannot be called from interrupt service routines.
  osStatusReserved          = 0x7FFFFFFF  ///< Prevents enum down-size compiler optimization.
} osStatus_t;

//***  cmsis_os2.h
/// Kernel state.
typedef enum {
  osKernelInactive        =  0,         ///< Inactive.
  osKernelReady           =  1,         ///< Ready.
  osKernelRunning_enum         =  2,         ///< Running.
  osKernelLocked          =  3,         ///< Locked.
  osKernelSuspended       =  4,         ///< Suspended.
  osKernelError           = -1,         ///< Error.
  osKernelReserved        = 0x7FFFFFFFU ///< Prevents enum down-size compiler optimization.
} osKernelState_t;

//*** cmsis_os2.c
#define IS_IRQ_MODE()             (__get_IPSR() != 0U)
#define IS_IRQ()                  IS_IRQ_MODE()

//*** cmsis_os2.c
osKernelState_t osKernelGetState (void) {
  osKernelState_t state;

  switch (xTaskGetSchedulerState()) {
    case taskSCHEDULER_RUNNING:
      state = osKernelRunning_enum;
      break;

    case taskSCHEDULER_SUSPENDED:
      state = osKernelLocked;
      break;

    case taskSCHEDULER_NOT_STARTED:
    default:
      //if (KernelState == osKernelReady) {
      //  state = osKernelReady;
      //} else {
        state = osKernelInactive;
      //}
      break;
  }

  return (state);
}

//*** cmsis_os2.c
int32_t osKernelLock (void) {
  int32_t lock;

  if (IS_IRQ()) {
    lock = (int32_t)osErrorISR;
  }
  else {
    switch (xTaskGetSchedulerState()) {
      case taskSCHEDULER_SUSPENDED:
        lock = 1;
        break;

      case taskSCHEDULER_RUNNING:
        vTaskSuspendAll();
        lock = 0;
        break;

      case taskSCHEDULER_NOT_STARTED:
      default:
        lock = (int32_t)osError;
        break;
    }
  }

  return (lock);
}

//*** cmsis_os2.c
int32_t osKernelUnlock (void) {
  int32_t lock;

  if (IS_IRQ()) {
    lock = (int32_t)osErrorISR;
  }
  else {
    switch (xTaskGetSchedulerState()) {
      case taskSCHEDULER_SUSPENDED:
        lock = 1;

        if (xTaskResumeAll() != pdTRUE) {
          if (xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED) {
            lock = (int32_t)osError;
          }
        }
        break;

      case taskSCHEDULER_RUNNING:
        lock = 0;
        break;

      case taskSCHEDULER_NOT_STARTED:
      default:
        lock = (int32_t)osError;
        break;
    }
  }

  return (lock);
}

//*** cmsis_os2.c
int32_t osKernelRestoreLock (int32_t lock) {

  if (IS_IRQ()) {
    lock = (int32_t)osErrorISR;
  }
  else {
    switch (xTaskGetSchedulerState()) {
      case taskSCHEDULER_SUSPENDED:
      case taskSCHEDULER_RUNNING:
        if (lock == 1) {
          vTaskSuspendAll();
        }
        else {
          if (lock != 0) {
            lock = (int32_t)osError;
          }
          else {
            if (xTaskResumeAll() != pdTRUE) {
              if (xTaskGetSchedulerState() != taskSCHEDULER_RUNNING) {
                lock = (int32_t)osError;
              }
            }
          }
        }
        break;

      case taskSCHEDULER_NOT_STARTED:
      default:
        lock = (int32_t)osError;
        break;
    }
  }

  return (lock);
}
#endif  /* (osCMSIS < 0x20000U) */

//============================================================================

// Variável auxiliar para manter o valor do estado de Lock do RTOS nas funções lock e unlock abaixo
static int32_t rtos_lockState = 0;

/**
 * @brief Função de interface THREADSAFE do LittleFS com o RTOS para função de LOCK
 */
int lfs_lock(const struct lfs_config *c)
{
	if(osKernelGetState() == osKernelInactive)
	{
		// RTOS ainda não inicializou
		return  LFS_ERR_OK;
	}

	rtos_lockState = osKernelLock();
	int ret = LFS_ERR_OK;

	if (rtos_lockState < 0)
	{
		ret = LFS_ERR_IO;
	}
	return ret;
}
/**
 * @brief Função de interface THREADSAFE do LittleFS com o RTOS para função de UNLOCK
 */
int lfs_unlock(const struct lfs_config *c)
{
	if(osKernelGetState() == osKernelInactive)
	{
		// RTOS ainda não inicializou
		return  LFS_ERR_OK;
	}

	//int state = osKernelUnlock();
	int newLockState = osKernelRestoreLock(rtos_lockState);
	int ret = LFS_ERR_OK;

	if (newLockState < 0)
	{
		ret = LFS_ERR_IO;
	}
	return ret;
}
#endif







