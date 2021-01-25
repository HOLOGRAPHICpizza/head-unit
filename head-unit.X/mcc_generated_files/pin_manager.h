/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC18F26K83
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.30 and above
        MPLAB 	          :  MPLAB X 5.40	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set HEARTBEAT aliases
#define HEARTBEAT_TRIS                 TRISAbits.TRISA0
#define HEARTBEAT_LAT                  LATAbits.LATA0
#define HEARTBEAT_PORT                 PORTAbits.RA0
#define HEARTBEAT_WPU                  WPUAbits.WPUA0
#define HEARTBEAT_OD                   ODCONAbits.ODCA0
#define HEARTBEAT_ANS                  ANSELAbits.ANSELA0
#define HEARTBEAT_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define HEARTBEAT_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define HEARTBEAT_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define HEARTBEAT_GetValue()           PORTAbits.RA0
#define HEARTBEAT_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define HEARTBEAT_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define HEARTBEAT_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define HEARTBEAT_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define HEARTBEAT_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define HEARTBEAT_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define HEARTBEAT_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define HEARTBEAT_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set OLED_RESET aliases
#define OLED_RESET_TRIS                 TRISCbits.TRISC5
#define OLED_RESET_LAT                  LATCbits.LATC5
#define OLED_RESET_PORT                 PORTCbits.RC5
#define OLED_RESET_WPU                  WPUCbits.WPUC5
#define OLED_RESET_OD                   ODCONCbits.ODCC5
#define OLED_RESET_ANS                  ANSELCbits.ANSELC5
#define OLED_RESET_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define OLED_RESET_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define OLED_RESET_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define OLED_RESET_GetValue()           PORTCbits.RC5
#define OLED_RESET_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define OLED_RESET_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define OLED_RESET_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define OLED_RESET_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define OLED_RESET_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define OLED_RESET_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define OLED_RESET_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define OLED_RESET_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/