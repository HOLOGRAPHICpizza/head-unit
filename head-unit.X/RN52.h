#include "shared.h"

static volatile char RN52_title[RX_LINE_LENGTH];
static volatile bool RN52_titleReady = false;
static volatile char RN52_artist[RX_LINE_LENGTH];
static volatile bool RN52_artistReady = false;

char getch2(void);
void putch2(char txData);
void RN52_cmd(char cmd[]);
void RN52_RX(void);