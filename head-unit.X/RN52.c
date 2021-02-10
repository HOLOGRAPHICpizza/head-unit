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

static volatile char RN52_title[RX_LINE_LENGTH];
static volatile bool _RN52_titleReady = false;
static volatile char RN52_artist[RX_LINE_LENGTH];
static volatile bool _RN52_artistReady = false;

static volatile uint8_t RN52_buffer[RX_BUFFER_SIZE];
static volatile uint8_t RN52_bufferHead = 0;
static volatile uint8_t RN52_bufferTail = 0;
static volatile uint8_t RN52_bufferCount = 0;


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
        buffer2string(RN52_buffer, &RN52_bufferHead, &RN52_bufferTail, &RN52_bufferCount, line);
        
        // is this title line?
        if(strncmp(line, "Title=", 6) == 0) {
            // check for race condition
            if(_RN52_titleReady) {
                // oh shit we lost the race
                panic(3);
            }
            
            strncpy(RN52_title, line + 6, RX_LINE_LENGTH - 6);
            _RN52_titleReady = true;
        }
        // artist line?
        else if(strncmp(line, "Artist=", 7) == 0) {
            // check for race condition
            if(_RN52_artistReady) {
                // oh shit we lost the race
                panic(4);
            }
            
            strncpy(RN52_artist, line + 7, RX_LINE_LENGTH - 7);
            _RN52_artistReady = true;
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


// Public Methods

void RN52_init(void) {
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

bool RN52_titleReady(void) {
    return _RN52_titleReady;
}

void RN52_getTitle(char destString[]) {
    strncpy(destString, RN52_title, RX_LINE_LENGTH);
    _RN52_titleReady = false;
}

bool RN52_artistReady(void) {
    return _RN52_artistReady;
}

void RN52_getArtist(char destString[]) {
    strncpy(destString, RN52_artist, RX_LINE_LENGTH);
    _RN52_artistReady = false;
}
