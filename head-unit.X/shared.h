#ifndef SHARED_H_
#define SHARED_H_

#include "mcc_generated_files/mcc.h"
#include <pic18.h>
#include <string.h>

#define RX_BUFFER_SIZE 64
#define RX_LINE_LENGTH 64

// tick time in ms THIS DOES NOT ACTUALLY SET THE TICK TIMER, just used for calculations
#define TICK_MS 16          // ~60Hz
#define INFO_DISPLAY_MS 400 // how long to display info such as volume changes

struct RXBuffer {
    uint8_t array[RX_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t count;
};

void panic(uint8_t vector);
void LATrigger(void);
void RXBufferAppend(struct RXBuffer *buffer, char byte);
void RXBuffer2String(struct RXBuffer *buffer, char string[]);

#endif
