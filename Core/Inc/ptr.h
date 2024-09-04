#ifndef PTR_H_
#define PTR_H_

#include "utils.h"

/**
 * @def IsValidPointer
 * @brief Check if the pointer is valid (e.g. ptr != NULL)
 * @param ptr pointer that will be check
 */
#define IsValidPointer(ptr)							((ptr == NULL) ? false : true)
/**
 * @def FreePointer
 * @brief This macro frees the pointer and point it to NULL, to avoid double free
 * @param ptr pointer that will be freed
 */
#define FreePointer(ptr)                if (IsValidPointer(ptr)) { free(ptr); ptr=NULL; }

/**
 * @def CheckPointer_ifError_return
 * @brief Macro that checks if the pointer is valid, and if it isn't, return the returnValue
 * @param ptr pointer that will be check
 * @param returnValue Value that will returned if the ptr is not valid
 */
#define CheckPointer_ifError_return(ptr, returnValue)	\
		if(!IsValidPointer(ptr)) { return returnValue; }

#endif /* PTR_H_ */
