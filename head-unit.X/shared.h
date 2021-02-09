#include "mcc_generated_files/mcc.h"
#include <pic18.h>
#include <string.h>

#define RX_BUFFER_SIZE 64
#define RX_LINE_LENGTH 64

void panic(uint8_t vector);
void bufferAppend(uint8_t buffer[], uint8_t *head, uint8_t *count, char byte);
void buffer2string(uint8_t buffer[], uint8_t *head, uint8_t *tail, uint8_t *count, char string[]);
