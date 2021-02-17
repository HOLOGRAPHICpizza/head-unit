#ifndef KNOBS_H
#define	KNOBS_H

#include "shared.h"

void Knobs_init(void);

void Knobs_tick(void);

// Has volume changed since last getVolume?
bool Knobs_volumeChanged(void);

// return volume between 0.0 and 1.0
uint8_t Knobs_getVolume(void);

#endif
