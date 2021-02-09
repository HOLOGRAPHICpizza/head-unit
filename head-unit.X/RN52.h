#include "shared.h"

bool RN52_titleReady(void);
void RN52_getTitle(char destString[]);
bool RN52_artistReady(void);
void RN52_getArtist(char destString[]);

char getch2(void);
void putch2(char txData);
void RN52_cmd(char cmd[]);
void RN52_RX(void);