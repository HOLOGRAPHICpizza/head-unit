#ifndef RN52_H_
#define RN52_H_

#include "shared.h"

void RN52_init(void);
void RN52_cmd(char cmd[]);
bool RN52_titleReady(void);
void RN52_getTitle(char destString[]);
bool RN52_artistReady(void);
void RN52_getArtist(char destString[]);

#endif
