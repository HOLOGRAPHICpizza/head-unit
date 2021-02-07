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
#include <string.h>

#define RX_BUFFER_SIZE 64
#define RX_LINE_LENGTH 64

static volatile uint8_t debugConsoleBuffer[RX_BUFFER_SIZE];
static volatile uint8_t debugConsoleBufferHead = 0;
static volatile uint8_t debugConsoleBufferTail = 0;
static volatile uint8_t debugConsoleBufferCount = 0;
static volatile bool debugConsoleCmdReady = false;
static volatile char debugConsoleCmd[RX_LINE_LENGTH];

static volatile uint8_t RN52_buffer[RX_BUFFER_SIZE];
static volatile uint8_t RN52_bufferHead = 0;
static volatile uint8_t RN52_bufferTail = 0;
static volatile uint8_t RN52_bufferCount = 0;
static volatile char RN52_title[RX_LINE_LENGTH];
static volatile bool RN52_titleReady = false;
static volatile char RN52_artist[RX_LINE_LENGTH];
static volatile bool RN52_artistReady = false;

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

char getch2(void)
{
    return UART2_Read();
}

void putch2(char txData)
{
    UART2_Write(txData);
}

/* Metadata response example:

Title=Little Pink Plastic Bags
Artist=Gorillaz
Album=The Fall
TrackNumber=1
TrackCount=1
Genre=<unknown>
Time(ms)=189622

 */

// UART2 RX ISR
// RN52
void RN52_RX(void) {
    // call default ISR
    UART2_Receive_ISR();
    
    // get character and echo
    char c = getch2();
    //putch(c);
    
    // newline?
    if(c == '\r') {
        // build string from buffer
        char line[RX_LINE_LENGTH];
        buffer2string(RN52_buffer, &RN52_bufferHead, &RN52_bufferTail, &RN52_bufferCount, line);
        
        // is this title line?
        if(strncmp(line, "Title=", 6) == 0) {
            // check for race condition
            if(RN52_titleReady) {
                // oh shit we lost the race
                panic(3);
            }
            
            strncpy(RN52_title, line + 6, RX_LINE_LENGTH - 6);
            RN52_titleReady = true;
        }
        // artist line?
        else if(strncmp(line, "Artist=", 7) == 0) {
            // check for race condition
            if(RN52_artistReady) {
                // oh shit we lost the race
                panic(4);
            }
            
            strncpy(RN52_artist, line + 7, RX_LINE_LENGTH - 7);
            RN52_artistReady = true;
        }
    }
    
    // ignore
    else if(c == '\n') {
        NOP();
    }
    
    else {
        // add to buffer
        bufferAppend(RN52_buffer, &RN52_bufferHead, &RN52_bufferCount, (uint8_t) c);
    }
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
    printf("\r\n\r\nBOOT\r\n");
    __delay_ms(10);
    
    // get RN52 firmware version
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
            else if(first == 'M') {
                putch2('A');
                putch2('D');
                putch2('\r');
                putch2('\n');
            }
            else if(first == 'V') {
                putch2('V');
                putch2('\r');
                putch2('\n');
            }
            
            // release lock on cmd string
            debugConsoleCmdReady = false;
        }
        
        if(RN52_titleReady) {
            char lineCopy[RX_LINE_LENGTH];
            strncpy(lineCopy, RN52_title, RX_LINE_LENGTH);
            // release lock on string
            RN52_titleReady = false;
            
            //printf("got title: %s\r\n", lineCopy);
            OLED_println(lineCopy, 1);
        }
        
        if(RN52_artistReady) {
            char lineCopy[RX_LINE_LENGTH];
            strncpy(lineCopy, RN52_artist, RX_LINE_LENGTH);
            // release lock on string
            RN52_artistReady = false;
            
            //printf("got artist: %s\r\n", lineCopy);
            OLED_println(lineCopy, 2);
        }
        
        // maybe make this a timer
        //__delay_ms(250);
        //HEARTBEAT_Toggle();
    }
}
