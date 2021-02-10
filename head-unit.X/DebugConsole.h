#ifndef DEBUG_CONSOLE_H_
#define DEBUG_CONSOLE_H_

#include "shared.h"

void DebugConsole_init(void);
bool DebugConsole_cmdReady(void);
void DebugConsole_getCmd(char destString[]);

#endif
