#ifndef RN52_H_
#define RN52_H_

#include "shared.h"

void RN52_init(void);
void RN52_cmd(char cmd[]);
bool RN52_metadataReady(void);
void RN52_getMetadata(char destTitleStr[], char destArtistStr[]);

#endif
