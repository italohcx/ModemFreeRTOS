/*
 * logger.h
 *
 *  Created on: Sep 3, 2024
 *      Author: italo
 */

#ifndef INC_LOGGER_H_
#define INC_LOGGER_H_

#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"
#include "stdio.h"
#include "ptr.h"
#include "utils.h"

#define Log_newLine       "\r\n"

#define LOG_ENABLE      1

extern char * (*Log_funcToGetDateTime) ();

#if !LOG_ENABLE
#  undef print
#  define print(...)
#endif

#define LOG_NAME_MAXSIZE    10


#if LOG_ENABLE

#define Log_printPtr(StructLogPtrToBePrinted, levelToBeConsidered, fmt_s, ...) \
        if ((StructLogPtrToBePrinted->level < Log_level_disable) && \
            (levelToBeConsidered < Log_level_disable) && \
            (StructLogPtrToBePrinted->level <= levelToBeConsidered)) \
        {\
          printf("%s %s %s: %s[%d] " fmt_s "" Log_newLine,\
                Log_funcToGetDateTime(),\
                (char *)StructLogPtrToBePrinted->name,\
                (char *)Log_returnLevelString(levelToBeConsidered),\
                __func__, __LINE__, ##__VA_ARGS__); \
        }

// Lembrar do dateTime Get
#define Log_print(StructLogToBePrinted, levelToBeConsidered, fmt_s, ...) \
    if ((StructLogToBePrinted.level < Log_level_disable) && \
        (levelToBeConsidered < Log_level_disable) && \
        (StructLogToBePrinted.level <= levelToBeConsidered)) \
    {\
      printf("%s %s %s: %s[%d] " fmt_s "" Log_newLine,\
    	    Log_funcToGetDateTime(),\
            (char *)StructLogToBePrinted.name,\
            (char *)Log_returnLevelString(levelToBeConsidered),\
            __func__, __LINE__, ##__VA_ARGS__); \
    }

#else /*LOG_ENABLE*/

#define Log_printPtr(...)
#define Log_print(...)

#endif



/* Enum definitions */
typedef enum _Log_level_t {
    Log_level_trace = 0,
    Log_level_debug = 1,
    Log_level_info = 2,
    Log_level_warning = 3,
    Log_level_error = 4,
    Log_level_fatal = 5,
    Log_level_disable = 6
} Log_level_t;


/* Struct definitions */
typedef struct _Log_t {
    uint32_t pos; /* Log pos on array */
    char name[11]; /* Log name */
    Log_level_t level; /* Log level, more than that will be printed */
    Log_level_t levelDefault; /* Log level default */
    uint32_t ptrAddress; /* Log ptr to the outside address */
} Log_t;

typedef struct _Log_config {
    bool enable; /* If log is enabled */
    uint16_t logList_count;
    Log_t logList[50]; /* List with all logs on the application */
} Log_config;

/**
  * @brief Initialize the inputed log
  * @param log Log to be initialized
  * @param logName The inputed log name
  * @param level the default level to be considered
  * @return True if it was successfully
  */
 bool Log_init (Log_t *log, char logName[], Log_level_t level);
 /**
  * @brief Restore all configurations from default values
  */
 void Log_restoreDefault ();
 /**
  * @brief read and restore log configuration from file
  * @return True if it was successfully
  */
 bool Log_readFileConfig ();
 /**
  * @brief save current log configuration to file
  * @return True if it was successfully
  */
 bool Log_SaveFileConfig ();
 /**
  * @brief print all logs there were initialized
  */
 void Log_printAllLogsOnTheList ();
 /**
  * @brief Get the level that is represented by the string
  * @param level string log level
  * @return the level that is represented by the string
  */
 Log_level_t Log_returnLevelByString (char *level);
 /**
  * @brief returns the string that represents the level
  * @param level the value that the string will be got
  * @return string with level representation
  */
 char* Log_returnLevelString (Log_level_t level);
 /**
  * @brief Look for the log pointer that has the inputed name
  * @param logName the log name that will be looked for
  * @return The pointer to the log
  */
 Log_t* Log_getLogByName (char *logName);
 /**
  * @brief Set a level for the log with inputed name
  * @param logName the log name that will be changed
  * @param level the new level
  * @return True if it was successfully
  */
 bool Log_setLevelWithName (char *logName, Log_level_t level);
 /**
  * @brief Set a level for the log
  * @param log the log that will be changed
  * @param level the new level
  * @return True if it was successfully
  */
 bool Log_setLevel (Log_t *log, Log_level_t level);
 /**
  * @brief Set all logs at the same level
  * @param level the new level
  */
 void Log_setAllLogsAtLevel (Log_level_t level);
 /**
  * @brief Get the level for the log
  * @param log the log that the level will be got
  * @return the log's level
  */
 Log_level_t Log_getLevel (Log_t *log);
 /**
  * @brief Print a frame like wireshark (has to be finished)
  * @param log The log which will be printed
  * @param logLevel log level to be considered
  * @param forcePrint If the print is to be forced
  * @param frame the frame that will be printed
  * @param frameSize the frame size that will be printed
  * @param addtionalMessage if it is desired to print additional message
  */
 void Log_printFrame (Log_t *log, Log_level_t logLevel, bool forcePrint,
                      uint8_t *frame, uint32_t frameSize,
                      const char *addtionalMessage);

 /**
  * @brief Initialize th
#define LOG_NAME_MAXSIZE    10
  * is log module
  * @param funcToGetDateTime function the get date time to print on log
  */
 void Log_initModule (char *(*funcToGetDateTime) ());


 /**
  * @brief Restore configuration from file
  */
 void Log_restoreConfigFile();
 /**
  * @brief Initialize the CLI Log commands
  */
 void Logger_CLI_initCommands ();
 /**
  * @brief Just print the version on CLI
  */
 void Log_printVersion();
 /**
  * @brief Just print the logo on CLI
  */
 void Log_printLogo();


#endif /* INC_LOGGER_H_ */
