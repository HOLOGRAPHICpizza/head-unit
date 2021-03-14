/* Metadata response example:

Title=Little Pink Plastic Bags
Artist=Gorillaz
Album=The Fall
TrackNumber=1
TrackCount=1
Genre=<unknown>
Time(ms)=189622

 */

#include "RN52.h"

static volatile char _RN52_title[RX_LINE_LENGTH];
static volatile char _RN52_artist[RX_LINE_LENGTH];
static volatile bool _RN52_metadataReady = false;

static volatile struct RXBuffer _RN52_buffer;


// Private Methods

char getch2(void) {
    return UART2_Read();
}

void putch2(char txData) {
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
    
    // newline?
    if(c == '\r') {
        // build string from buffer
        char line[RX_LINE_LENGTH];
        RXBuffer2String(&_RN52_buffer, line);
        
        // is this title line?
        if(strncmp(line, "Title=", 6) == 0) {
            // check for race condition
            if(_RN52_metadataReady) {
                // oh shit we lost the race
                //TODO: gonna just ignore this shit and see what happens
                panic(3);
            }
            
            strncpy(_RN52_title, line + 6, RX_LINE_LENGTH - 6);
            _RN52_metadataReady = true;
        }
        // artist line?
        else if(strncmp(line, "Artist=", 7) == 0) {
            // check for race condition
            if(_RN52_metadataReady) {
                // oh shit we lost the race
                //TODO: gonna just ignore this shit and see what happens
                panic(4);
            }
            
            strncpy(_RN52_artist, line + 7, RX_LINE_LENGTH - 7);
            _RN52_metadataReady = true;
        }
    }
    
    // ignore
    else if(c == '\n') {
        NOP();
    }
    
    else {
        // add to buffer
        RXBufferAppend(&_RN52_buffer, (uint8_t) c);
    }
}


// Public Methods

void RN52_init(void) {
    _RN52_buffer.head = 0;
    _RN52_buffer.tail = 0;
    _RN52_buffer.count = 0;
    
    UART2_Initialize();
    UART2_SetRxInterruptHandler(&RN52_RX);
    
    // the printf commands seems necessary to have a delay between commands
    printf("name\r\n");
    RN52_cmd("SN,Peak15_Labs"); // set device name
    printf("I2S\r\n");
    RN52_cmd("S|,0103");        // I2S 24bit 48kHz
    printf("track change event\r\n");
    RN52_cmd("S%,1000");        // disable all extended features except track change event
    printf("service class\r\n");
    RN52_cmd("SC,240420");      // service class car audio
    printf("A2DP\r\n");
    RN52_cmd("SD,04");          // A2DP protocol only
    printf("A2DP\r\n");
    RN52_cmd("SK,04");          // A2DP protocol only
    printf("auth\r\n");
    RN52_cmd("SA,0");           // open authentication
    printf("discoverable\r\n");
    RN52_cmd("@,1");            // make disoverabe
}

void RN52_cmd(char cmd[]) {
    // send command to RN52
    for(uint8_t i = 0; i < RX_LINE_LENGTH; i++) {
        char c = cmd[i];
        if(c == 0) {
            break;
        }
        putch2(c);
    }
    putch2('\r');
    __delay_ms(25);
}

bool RN52_metadataReady(void) {
    return _RN52_metadataReady;
}

void RN52_getMetadata(char destTitleStr[], char destArtistStr[]) {
    strncpy(destTitleStr, _RN52_title, RX_LINE_LENGTH);
    strncpy(destArtistStr, _RN52_artist, RX_LINE_LENGTH);
    _RN52_metadataReady = false;
}
