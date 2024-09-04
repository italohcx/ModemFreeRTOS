#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef LOCAL
#  define LOCAL static
#endif

typedef enum
{
  OK_U = 0x00,
  ERROR_U,
}STATUS_t;

#define ARGNOUSED(x)  (void)(x)

/**
 * @def GetVarName
 * @brief Function to get variable name
 * @param variable that the name will be gotten
 */
#define GetVarName(variable) (#variable)

/**
 * @def CheckIfItIs_valid_enum
 * @brief Check if the value is valid to enum.
 *
 */
#define CheckIfItIs_valid_enum(valueInEnum, firstEnum_ToBeConsidered, lastEnum_ToBeConsidered)\
					    ( ( (firstEnum_ToBeConsidered <= valueInEnum) && \
						  (valueInEnum <= lastEnum_ToBeConsidered) ) ? true : false )

#define getSetPos(pos)                    ( (1U) << (pos) )
#define getCleanPos(pos)                  ( ~getSetPos(pos) )
#define setPos(pos,var)                   (var) | ( getSetPos(pos) )
#define cleanPos(pos,var)                 (var) & ( ~getSetPos(pos) )
#define getPosState(pos,var)              ( (getSetPos(pos) & (var)) == 0 ) ? false : true

#endif /* UTILS_H_ */
