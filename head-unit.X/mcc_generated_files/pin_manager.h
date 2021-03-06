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

// get/set HEARTBEAT_OUT aliases
#define HEARTBEAT_OUT_TRIS                 TRISAbits.TRISA0
#define HEARTBEAT_OUT_LAT                  LATAbits.LATA0
#define HEARTBEAT_OUT_PORT                 PORTAbits.RA0
#define HEARTBEAT_OUT_WPU                  WPUAbits.WPUA0
#define HEARTBEAT_OUT_OD                   ODCONAbits.ODCA0
#define HEARTBEAT_OUT_ANS                  ANSELAbits.ANSELA0
#define HEARTBEAT_OUT_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define HEARTBEAT_OUT_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define HEARTBEAT_OUT_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define HEARTBEAT_OUT_GetValue()           PORTAbits.RA0
#define HEARTBEAT_OUT_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define HEARTBEAT_OUT_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define HEARTBEAT_OUT_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define HEARTBEAT_OUT_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define HEARTBEAT_OUT_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define HEARTBEAT_OUT_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define HEARTBEAT_OUT_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define HEARTBEAT_OUT_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set VOLUME_IN aliases
#define VOLUME_IN_TRIS                 TRISAbits.TRISA1
#define VOLUME_IN_LAT                  LATAbits.LATA1
#define VOLUME_IN_PORT                 PORTAbits.RA1
#define VOLUME_IN_WPU                  WPUAbits.WPUA1
#define VOLUME_IN_OD                   ODCONAbits.ODCA1
#define VOLUME_IN_ANS                  ANSELAbits.ANSELA1
#define VOLUME_IN_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define VOLUME_IN_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define VOLUME_IN_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define VOLUME_IN_GetValue()           PORTAbits.RA1
#define VOLUME_IN_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define VOLUME_IN_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define VOLUME_IN_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define VOLUME_IN_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define VOLUME_IN_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define VOLUME_IN_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define VOLUME_IN_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define VOLUME_IN_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set RB0 procedures
#define RB0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()              PORTBbits.RB0
#define RB0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define RB0_SetPullup()             do { WPUBbits.WPUB0 = 1; } while(0)
#define RB0_ResetPullup()           do { WPUBbits.WPUB0 = 0; } while(0)
#define RB0_SetAnalogMode()         do { ANSELBbits.ANSELB0 = 1; } while(0)
#define RB0_SetDigitalMode()        do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()              PORTBbits.RB1
#define RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()             do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()           do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode()         do { ANSELBbits.ANSELB1 = 1; } while(0)
#define RB1_SetDigitalMode()        do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set LATRIGGER_OUT aliases
#define LATRIGGER_OUT_TRIS                 TRISCbits.TRISC2
#define LATRIGGER_OUT_LAT                  LATCbits.LATC2
#define LATRIGGER_OUT_PORT                 PORTCbits.RC2
#define LATRIGGER_OUT_WPU                  WPUCbits.WPUC2
#define LATRIGGER_OUT_OD                   ODCONCbits.ODCC2
#define LATRIGGER_OUT_ANS                  ANSELCbits.ANSELC2
#define LATRIGGER_OUT_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define LATRIGGER_OUT_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define LATRIGGER_OUT_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define LATRIGGER_OUT_GetValue()           PORTCbits.RC2
#define LATRIGGER_OUT_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define LATRIGGER_OUT_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define LATRIGGER_OUT_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define LATRIGGER_OUT_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define LATRIGGER_OUT_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define LATRIGGER_OUT_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define LATRIGGER_OUT_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define LATRIGGER_OUT_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

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

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSELC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSELC7 = 0; } while(0)

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




#endif // PIN_MANAGER_H
/**
 End of File
*/