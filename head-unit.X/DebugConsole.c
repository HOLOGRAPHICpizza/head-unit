#include "DebugConsole.h"

static volatile char debugConsoleCmd[RX_LINE_LENGTH];
static volatile bool debugConsoleCmdReady = false;
static volatile uint8_t debugConsoleBuffer[RX_BUFFER_SIZE];
static volatile uint8_t debugConsoleBufferHead = 0;
static volatile uint8_t debugConsoleBufferTail = 0;
static volatile uint8_t debugConsoleBufferCount = 0;


// Private Methods

// UART1 RX ISR
// debug console
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
            panic(1);
        }
        
        // build string from buffer
        buffer2string(
                debugConsoleBuffer,
                &debugConsoleBufferHead,
                &debugConsoleBufferTail,
                &debugConsoleBufferCount,
                debugConsoleCmd);
        
        // set flag and exit
        debugConsoleCmdReady = true;
    }
    
    // panic character
    else if(c == '^') {
        panic(2);
    }
    
    // ignore
    else if(c == '\n') {
        NOP();
    }
    
    else {
        // add to buffer
        bufferAppend(debugConsoleBuffer, &debugConsoleBufferHead, &debugConsoleBufferCount, c);
    }
}


// Public Methods

void DebugConsole_init(void) {
    UART1_Initialize();
    UART1_SetRxInterruptHandler(&debugConsoleRX);
}

bool DebugConsole_cmdReady(void) {
    return debugConsoleCmdReady;
}

void DebugConsole_getCmd(char destString[]) {
    strncpy(destString, debugConsoleCmd, RX_LINE_LENGTH);
    debugConsoleCmdReady = false;
}
