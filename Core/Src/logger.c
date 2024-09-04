/*
 * logger.c
 *
 *  Created on: Sep 3, 2024
 *      Author: italo
 */

#include "logger.h"
#include "stdio.h"
#include "version.h"
#include "cfg_files.h"
#include "ptr.h"

Log_config *logConfig;
#define LOG_QNT_TempVarToRead_LogConfig  5
Log_config logConfig_tempRead[LOG_QNT_TempVarToRead_LogConfig];
 bool logFilesWasRead = false;
char* (*Log_funcToGetDateTime)();

 Log_t log_log;
#define LOG_LOGNAME                   "log"
#define LOG_LOGLEVEL_DEFAULT          Log_level_warning

/*####################### Helper Functions #######################*/

Log_level_t Log_returnLevelByString(char *level)
{
  if (!IsValidPointer(level))
  {
	return Log_level_disable + 1;
  }

  if (strcmp("trace", level) == 0)
  {
	return Log_level_trace;
  }

  if (strcmp("debug", level) == 0)
  {
	return Log_level_debug;
  }

  if (strcmp("info", level) == 0)
  {
	return Log_level_info;
  }

  if (strcmp("warning", level) == 0)
  {
	return Log_level_warning;
  }

  if (strcmp("error", level) == 0)
  {
	return Log_level_error;
  }

  if (strcmp("fatal", level) == 0)
  {
	return Log_level_fatal;
  }

  if (strcmp("disable", level) == 0)
  {
	return Log_level_disable;
  }
  return Log_level_disable + 1;
}

char* Log_returnLevelString(Log_level_t level)
{
  switch (level)
  {
  case Log_level_trace:
	return "trace";

  case Log_level_debug:
	return "debug";

  case Log_level_info:
	return "info";

  case Log_level_warning:
	return "Warning";

  case Log_level_error:
	return "ERROR";

  case Log_level_fatal:
	return "FATAL";

  case Log_level_disable:
	return "disable";

  default:
	return "INVALID";
  }
}

  bool Log_insertOnTheList(Log_t *log)
  {
	CheckPointer_ifError_return(log, false);
	uint32_t count = 0;

	/* look if it is already on the list */
	for (count = 0; count < logConfig->logList_count; count++)
	{
	  if (memcmp(logConfig->logList[count].name, log->name, sizeof(log->name))
		  == 0)
	  {
		log->pos = logConfig->logList[count].pos;
		log->level = logConfig->logList[count].level;
		logConfig->logList[count].levelDefault = log->levelDefault;
		logConfig->logList[count].ptrAddress = (uint32_t) log;
		Log_print(log_log, Log_level_trace, "Log %s restored from file",log->name);
		return true;
	  }
	}

	log->pos = logConfig->logList_count;
	memcpy(&(logConfig->logList[logConfig->logList_count]), log, sizeof(Log_t));
	logConfig->logList_count++;
	if (logFilesWasRead)
	{
	  if (!Log_SaveFileConfig())
	  {
		Log_print(log_log, Log_level_error, "Failed to save log %s on file",
			log->name);
	  }
	}

	Log_print(log_log, Log_level_trace, "Log %s was added on the list",
		log->name);
	return true;
  }

  void Log_printAllLogsOnTheList()
  {
	uint32_t count = 0;
	if (logConfig->logList_count == 0)
	{
	  printf("There is no log on the list"Log_newLine);
	  return;
	}
	printf("There are %d logs registered"Log_newLine""Log_newLine,
		logConfig->logList_count);
	printf(" |-------------|-------------|--------------|"Log_newLine);
	printf(" |     Name    |     Level   | DefaultLevel |"Log_newLine);
	printf(" |-------------|-------------|--------------|"Log_newLine);
	for (count = 0; count < logConfig->logList_count; count++)
	{
	  printf(" | %11s | %7s[%02d] |  %7s[%02d] |"Log_newLine,
		  logConfig->logList[count].name,
		  Log_returnLevelString(logConfig->logList[count].level),
		  logConfig->logList[count].level,
		  Log_returnLevelString(logConfig->logList[count].levelDefault),
		  logConfig->logList[count].levelDefault);
	}
	printf(" |-------------|-------------|--------------|"Log_newLine);
  }


  Log_t* Log_getLogByName (char *logName)
  {
    uint32_t count = 0;
    bool found = false;
    CheckPointer_ifError_return(logName, NULL);
    for (count = 0; count < logConfig->logList_count; count++)
    {
      if (strlen (logName) != strlen (logConfig->logList[count].name))
      {
        continue;
      }
      if (strncmp (logName, logConfig->logList[count].name, LOG_NAME_MAXSIZE) == 0)
      {
        found = true;
        break;
      }
    }
    if (found)
    {
      return (&logConfig->logList[count]);
    }
    return NULL;
  }



  bool Log_setLevelWithName (char *logName, Log_level_t level)
  {
    Log_t *logOnList = NULL;
    CheckPointer_ifError_return(logName, false);

    logOnList = Log_getLogByName (logName);
    if (!IsValidPointer(logOnList))
    {
      Log_print(log_log, Log_level_error, "Log %s not found on the list", logName);
      return false;
    }

    return Log_setLevel(logOnList, level);
  }



  bool Log_setLevel(Log_t *log, Log_level_t level)
  {
	CheckPointer_ifError_return(log, false);
	if (!CheckIfItIs_valid_enum(level, Log_level_trace, Log_level_disable))
	{
	  Log_print(log_log, Log_level_error, "Invalid log level value");
	  return false;
	}

	Log_print(log_log, Log_level_warning, "Log %s has updated the level from %s to %s", log->name,
		Log_returnLevelString(log->level), Log_returnLevelString(level));
	log->level = level;
	((Log_t*) log->ptrAddress)->level = level;
	Log_SaveFileConfig();

	return true;
  }


  void Log_setAllLogsAtLevel (Log_level_t level)
  {
    for (int count =0 ; count < logConfig->logList_count; count++)
    {
      (void) Log_setLevel(&(logConfig->logList[count]), level);
    }
  }

  Log_level_t Log_getLevel (Log_t *log)
  {
    CheckPointer_ifError_return(log, 0xff);
    Log_t *logOnList = NULL;
    Log_level_t output = 0xff;
    if (log->pos < (sizeof(logConfig->logList) / sizeof(logConfig->logList[0])))
    {
      output = logConfig->logList[log->pos].level;
    }
    else
    {
      logOnList = Log_getLogByName (log->name);
      if (IsValidPointer(logOnList))
      {
        output = logOnList->level;
      }
    }
    return output;
  }

  void Log_restoreDefault()
  {
	uint8_t count = 0;
	for (count = 0; count < logConfig->logList_count; count++)
	{
	  Log_setLevel(&(logConfig->logList[count]),logConfig->logList[count].levelDefault);
	}
  }



  bool Log_init(Log_t *log, char logName[], Log_level_t level)
  {
#if LOG_ENABLE
	CheckPointer_ifError_return(log, false);
	if (!CheckIfItIs_valid_enum(level, Log_level_trace, Log_level_disable))
	{
	  Log_print(log_log, Log_level_error, "Invalid log level value");
	  return false;
	}

	memset(log->name, 0, sizeof(log->name));
	strncpy(log->name, logName, sizeof(log->name) - 1);
	log->level = level;
	log->levelDefault = level;
	log->ptrAddress = (uint32_t) log;

	if (!Log_insertOnTheList(log))
	{
	  return false;
	}
#endif /*LOG_ENABLE*/

	return true;
  }


  bool Log_SaveFileConfig()
  {

	if (!CfgFiles_UpdateCfgFileByIndex(LOG_FILE_IDX, false))
	{
	 // Log_print(log_log, Log_level_error, "Failed to LOG config file");
	  return false;
	}
	return true;
  }




  bool Log_readFileConfig()
  {

	Log_t *registeredLog;

	/* Loop to check if there is something different from zero */
	for (int count = 0; count < logConfig->logList_count; count++)
	{
	  Log_insertOnTheList(&(logConfig->logList[count]));
	}

	/* restored from file */
	for (int count = 0; count < logConfig->logList_count; count++)
	{
	  /*Check if it is already on the list*/
	  registeredLog = Log_getLogByName(logConfig->logList[count].name);
	  if (IsValidPointer(registeredLog))
	  {
		// It is on the list
		registeredLog->level = logConfig->logList[count].level;
		logConfig->logList[count].levelDefault = registeredLog->levelDefault;
	  }
	  else
	  {
		// It isn't on the list
		logConfig->logList[count].ptrAddress = 0;
		Log_insertOnTheList(&(logConfig->logList[count]));
	  }
	}
	return false;
  }

  void Log_printVersion()
  {
	printf(Log_newLine"HorusGateway"Log_newLine);
	printf("  Firmware v.%d.%d%d"Log_newLine, FW_MAJOR_VERSION,
		FW_MINOR_VERSION, FW_BUILD_VERSION);
	printf("  Build %s %s"Log_newLine, __DATE__, __TIME__);

  }

  void Log_printLogo()
  {
	printf(LOGO);
  }


  /*####################### List Log Functions #######################*/

  //void Log_initModule(char* (*funcToGetDateTime)())
  void Log_initModule()
  {
	memset(&logConfig, 0, sizeof(logConfig));
//	Log_funcToGetDateTime = funcToGetDateTime;

	Log_init(&log_log, LOG_LOGNAME, LOG_LOGLEVEL_DEFAULT);

	//  Logger_CLI_initCommands ();
	Log_printLogo();
	Log_printVersion();

	logConfig = &logConfigFile;
	Log_printAllLogsOnTheList();


  }

  void Log_restoreConfigFile()
  {
	if (Log_readFileConfig())
	{
	  Log_print(log_log, Log_level_trace, "Config file was restore");
	}
	else
	{
	  Log_print(log_log, Log_level_trace,
		  "Failed to restore from config log file");
	}
	logFilesWasRead = true;
  }




  /*####################### Print functions #######################*/

  void Log_printFrame (Log_t *log, Log_level_t logLevel, bool forcePrint,
                       uint8_t *frame, uint32_t frameSize,
                       const char *addtionalMessage)
  {
    uint8_t count = 0;
    char *fullMsg = NULL;
    if ((!forcePrint) && (log->level > logLevel))
    {
      return;
    }
    fullMsg = (char*) malloc (6 * frameSize);
    if (!IsValidPointer(fullMsg))
    {
      return;
    }
    for (count = 0; count < frameSize; count++)
    {
      snprintf (fullMsg, 2, "%02X | ", frame[count]);
      if (count % 16 == 0)
      {
        snprintf (fullMsg, 2, "%s", Log_newLine);
      }
    }
    if (IsValidPointer(addtionalMessage))
    {
      Log_printPtr(log, logLevel, "Frame for %s:", addtionalMessage);
    }
    else
    {
      Log_printPtr(log, logLevel, "Frame: ");
    }
    print("%s"Log_newLine, fullMsg);
    FreePointer(fullMsg);
  }






