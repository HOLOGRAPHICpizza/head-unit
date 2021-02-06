// Peak 15 Labs Head Unit
// for PIC18F26K83

// RN52 Firmware must be V1.16
// Firmware update tool must be run in win7 compatibility mode,
// and visual c++ 2005 must be installed.
// Then you must connect UART at 115200 baud and issue command
// "SU,01" to permanently set to 9600 baud.
// What GPIO7 does is unclear.

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
    
    // panic character
    else if(c == '^') {
        panic();
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

char getch2(void)
{
    return UART2_Read();
}

void putch2(char txData)
{
    UART2_Write(txData);
}

// UART2 RX ISR
// RN52
void RN52_RX(void) {
    // call default ISR
    UART2_Receive_ISR();
    
    // get character and echo
    char c = getch2();
    putch(c);
}

void main(void) {
    SYSTEM_Initialize();
    
    // debug console
    UART1_Initialize();
    UART1_SetRxInterruptHandler(&debugConsoleRX);
    
    // RN52
    UART2_Initialize();
    UART2_SetRxInterruptHandler(&RN52_RX);
    
    OLED_init();
    
    INTERRUPT_Initialize();
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();
    
    __delay_ms(10);
    printf("\r\nBOOT\r\n");
    __delay_ms(10);
    
    putch2('V');
    putch2('\r');
    putch2('\n');
    
    while (true)
    {
        if(debugConsoleCmdReady) {
            //printf("got cmd: %s\r\n", debugConsoleCmd);
            
            char first = debugConsoleCmd[0];
            if(first == 'C' || first == 'D') {
                char hex[2];
                hex[0] = debugConsoleCmd[1];
                hex[1] = debugConsoleCmd[2];
                uint8_t byte = (uint8_t) strtoul(hex, NULL, 16);
                
                if(first == 'C') {
                    OLED_cmd(byte);
                }
                else if(first == 'D') {
                    OLED_data(byte);
                }
            }
            else if(first == 'V') {
                putch2('V');
                putch2('\r');
                putch2('\n');
            }
            
            // release lock on cmd string
            debugConsoleCmdReady = false;
        }
        
        // maybe make this a timer
        //__delay_ms(250);
        //HEARTBEAT_Toggle();
    }
}
