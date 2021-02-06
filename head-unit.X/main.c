// Peak 15 Labs Head Unit
// for PIC18F26K83

#include "mcc_generated_files/mcc.h"
#include "OLED.h"
#include <pic18.h>

static volatile uint8_t debugConsoleBuffer[64];
static volatile uint8_t debugConsoleBufferHead = 0;
static volatile uint8_t debugConsoleBufferTail = 0;
static volatile bool debugConsoleCmdReady = false;
static volatile char debugConsoleCmd[64];

void panic(void) {
    printf("PANIC");        // this wont print from inside an ISR
    while(true) {
        __delay_ms(50);
        HEARTBEAT_Toggle();
    }
}

// UART1 RX ISR
// UART1 is debug console
void debugConsoleRX(void) {
    // call default ISR
    UART1_Receive_ISR();
    
    // get character and echo
    char c = getch();
    putch(c);
    
    // newline?
    //TODO: This only works with screen for some reason
    if(c == '\r') {
        putch('\n');
        
        // check for race condition
        if(debugConsoleCmdReady) {
            // oh shit we lost the race
            panic();
        }
        
        // build string from buffer
        for(uint8_t i=0; i < debugConsoleBufferHead; i++) {
            debugConsoleCmd[i] = debugConsoleBuffer[debugConsoleBufferTail + i];
        }
        debugConsoleBufferTail = debugConsoleBufferHead;
        
        // set flag and exit
        debugConsoleCmdReady = true;
    }
    else {
        // add to buffer
        debugConsoleBuffer[debugConsoleBufferHead++] = c;
        if(sizeof(debugConsoleBuffer) <= debugConsoleBufferHead)
        {
            debugConsoleBufferHead = 0;
        }
    }
}

void main(void) {
    SYSTEM_Initialize();

    UART1_Initialize();
    UART1_SetRxInterruptHandler(&debugConsoleRX);
    
    INTERRUPT_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    
    
    /*OLED_init();
    uint8_t col = 0;
    
    //OLED_cmd(0x80 + col++);
    OLED_data('A');
    //OLED_cmd(0x80 + col++);
    OLED_data('B');
    //OLED_cmd(0x80 + col++);
    OLED_data('C');
    //OLED_cmd(0x80 + col++);
    OLED_data('D');
    //OLED_cmd(0x80 + col++);
    OLED_data('E');*/
    
    
    while (1)
    {
        if(debugConsoleCmdReady) {
            printf("got cmd: %s\r\n", debugConsoleCmd);
            
            __delay_ms(1000);
            
            // clear flag last
            debugConsoleCmdReady = false;
        }
        
        // maybe make this a timer
        //__delay_ms(250);
        //HEARTBEAT_Toggle();
    }
}
