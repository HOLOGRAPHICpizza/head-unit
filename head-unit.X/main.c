// Peak 15 Labs Head Unit
// for PIC18F26K83

// RN52 Firmware must be V1.16
// Firmware update tool must be run in win7 compatibility mode,
// and visual c++ 2005 must be installed.
// Then you must connect UART at 115200 baud and issue command
// "SU,01" to permanently set to 9600 baud.
// What GPIO7 does is unclear.

#include "shared.h"
#include "OLED.h"
#include "RN52.h"
#include "DebugConsole.h"

static volatile char lineCopy[RX_LINE_LENGTH];

void main(void) {
    SYSTEM_Initialize();
    
    DebugConsole_init();
    
    OLED_init();
    
    INTERRUPT_Initialize();
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();
    
    __delay_ms(10);
    printf("\r\n\r\nPeak 15 Labs Head Unit\r\n");
    __delay_ms(10);
    
    RN52_init();
    
    while (true)
    {
        if(DebugConsole_cmdReady()) {
            //printf("got cmd: %s\r\n", debugConsoleCmd);
            
            /*char first = debugConsoleCmd[0];
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
            }*/
            
            DebugConsole_getCmd(lineCopy);
            
            // send command straight to RN52
            RN52_cmd(lineCopy);
        }
        
        if(RN52_titleReady()) {
            RN52_getTitle(lineCopy);
            
            OLED_println(lineCopy, 1);
        }
        
        if(RN52_artistReady()) {
            RN52_getArtist(lineCopy);
            
            OLED_println(lineCopy, 2);
        }
    }
}
