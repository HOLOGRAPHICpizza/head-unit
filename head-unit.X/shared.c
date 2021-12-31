#include "shared.h"

void panic(uint8_t vector) {
    printf("PANIC %u", vector);        // this wont print from inside an ISR
    while(true) {
        __delay_ms(50);
        HEARTBEAT_OUT_Toggle();
    }
}

void LATrigger(void) {
    LATRIGGER_OUT_SetHigh();
}

void RXBufferAppend(struct RXBuffer *buffer, char byte) {
    uint8_t h = buffer->head;
    buffer->array[h] = byte;
    buffer->head = ++h;
    if(RX_BUFFER_SIZE <= buffer->head) {
        buffer->head = 0;
    }
    buffer->count = buffer->count + 1;
}

void RXBuffer2String(struct RXBuffer *buffer, char string[]) {
    uint8_t i = 0;
    while(buffer->count > 0) {
        string[i] = (char) buffer->array[buffer->tail];
        buffer->tail = buffer->tail + 1;
        if(buffer->tail >= RX_BUFFER_SIZE) {
            buffer->tail = 0;
        }
        buffer->count = buffer->count - 1;
        i++;
    }
    string[i] = 0;
}
