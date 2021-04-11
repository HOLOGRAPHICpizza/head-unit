// Peak 15 Labs Head Unit
// for PIC18F26K83

// RN52 Firmware must be V1.16
// Firmware update tool must be run in win7 compatibility mode,
// and visual c++ 2005 must be installed.
// Then you must connect UART at 115200 baud and issue command
// "SU,01" to permanently set to 9600 baud.
// What GPIO7 does is unclear.

// disable function never called warnings
#pragma warning disable 520
#pragma warning disable 2053

#include "shared.h"
#include "OLED.h"
#include "RN52.h"
#include "DebugConsole.h"
#include "Knobs.h"
#include "DSP.h"

static volatile char _Main_scratchLine1[RX_LINE_LENGTH];
static volatile char _Main_scratchLine2[RX_LINE_LENGTH];
static volatile uint8_t _Main_tickCount = 0;
static volatile uint8_t _Main_lastTickCount = 0;
static volatile uint8_t _Main_restoreOLEDTick = 0;   // the tick to restore the OLED on

void _Main_tick(void) {
    _Main_tickCount++;
}

void main(void) {
    SYSTEM_Initialize();
    
    DebugConsole_init();
    
    INTERRUPT_Initialize();
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();
    
    OLED_init();
    
    __delay_ms(10);
    printf("\r\n\r\nPeak 15 Labs Head Unit\r\n");
    __delay_ms(10);
    
    RN52_init();
    
    Knobs_init();
    
    TMR0_Initialize();
    TMR0_SetInterruptHandler(&_Main_tick);
    TMR0_StartTimer();
    
    DSP_init();
    
    while (true)
    {
        if(DebugConsole_cmdReady()) {
            DebugConsole_getCmd(_Main_scratchLine1);
            
            // OLED Commands
            char first = _Main_scratchLine1[0];
            if(first == 'C' || first == 'D') {
                char hex[2];
                hex[0] = _Main_scratchLine1[1];
                hex[1] = _Main_scratchLine1[2];
                uint8_t byte = (uint8_t) strtoul(hex, NULL, 16);
                
                if(first == 'C') {
                    OLED_cmd(byte);
                }
                else if(first == 'D') {
                    OLED_data(byte);
                }
            }
            else if(first == 'G') {
                DSP_GPIO_on();
            }
            else if(first == 'H') {
                DSP_GPIO_off();
            }
            else {
                // send command straight to RN52
                RN52_cmd(_Main_scratchLine1);
            }
        }
        
        if(RN52_metadataReady()) {
            RN52_getMetadata(_Main_scratchLine1, _Main_scratchLine2);
            
            OLED_println(_Main_scratchLine1, 1);
            OLED_println(_Main_scratchLine2, 2);
        }
        
        if(Knobs_volumeChanged()) {
            uint8_t volume = Knobs_getVolume();
            //printf("volume: %u\r\n", volume);
            char volStr[16];
            snprintf(volStr, 16, "Volume: %u", volume);
            OLED_save();
            OLED_println(volStr, 1);
            OLED_println("", 2);
            _Main_restoreOLEDTick = _Main_tickCount + (INFO_DISPLAY_MS / TICK_MS);
        }
        
        // time to stop displaying info?
        if(_Main_tickCount == _Main_restoreOLEDTick) {
            OLED_restore();
        }
        
        if(OLED_readyToDraw()) {
            OLED_draw();
        }
        
        // Do a tick
        if(_Main_tickCount != _Main_lastTickCount) {
            Knobs_tick();
            OLED_tick();
            
            _Main_lastTickCount = _Main_tickCount;
        }
    }
}
