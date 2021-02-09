#include "shared.h"

void panic(uint8_t vector) {
    printf("PANIC %u", vector);        // this wont print from inside an ISR
    while(true) {
        __delay_ms(50);
        HEARTBEAT_Toggle();
    }
}

void bufferAppend(uint8_t buffer[], uint8_t *head, uint8_t *count, char byte) {
    uint8_t h = *head;
    buffer[h] = byte;
    *head = ++h;
    if(RX_BUFFER_SIZE <= *head) {
        *head = 0;
    }
    *count = *count + 1;
}

void buffer2string(uint8_t buffer[], uint8_t *head, uint8_t *tail, uint8_t *count, char string[]) {
    uint8_t i = 0;
    while(*count > 0) {
        string[i] = (char) buffer[*tail];
        *tail = *tail + 1;
        if(*tail >= RX_BUFFER_SIZE) {
            *tail = 0;
        }
        *count = *count - 1;
        i++;
    }
    string[i] = 0;
}
