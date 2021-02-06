// For NHD-0216AW-IB3

#include "OLED.h"

void OLED_cmd(uint8_t cmd) {
    I2C1_Write1ByteRegister(OLED_ADDR, 0x80, cmd);
}

void OLED_data(uint8_t data) {
    I2C1_Write1ByteRegister(OLED_ADDR, 0x40, data);
    __delay_ms(100);
}

void OLED_init(void) {
    OLED_RESET_SetHigh();
    __delay_ms(100);
    OLED_cmd(0x2A);  //function set (extended command set)
    OLED_cmd(0x71);  //function selection A, disable internal Vdd regualtor
    OLED_data(0x00);
    OLED_cmd(0x28);  //function set (fundamental command set)
    OLED_cmd(0x08);  //display off, cursor off, blink off
    OLED_cmd(0x2A);  //function set (extended command set)
    OLED_cmd(0x79);  //OLED command set enabled
    OLED_cmd(0xD5);  //set display clock divide ratio/oscillator frequency
    OLED_cmd(0x70);  //set display clock divide ratio/oscillator frequency
    OLED_cmd(0x78);  //OLED command set disabled
    OLED_cmd(0x08);  //extended function set (2-lines)
    OLED_cmd(0x06);  //COM SEG direction
    OLED_cmd(0x72);  //function selection B, disable internal Vdd regualtor
    OLED_data(0x00);     //ROM CGRAM selection
    OLED_cmd(0x2A);  //function set (extended command set)
    OLED_cmd(0x79);  //OLED command set enabled
    OLED_cmd(0xDA);  //set SEG pins hardware configuration
    OLED_cmd(0x00);  //set SEG pins ... NOTE: When using NHD-0216AW-XB3 or NHD_0216MW_XB3 change to (0x00)
    OLED_cmd(0xDC);  //function selection C
    OLED_cmd(0x00);  //function selection C
    OLED_cmd(0x81);  //set contrast control
    OLED_cmd(0x7F);  //set contrast control
    OLED_cmd(0xD9);  //set phase length
    OLED_cmd(0xF1);  //set phase length
    OLED_cmd(0xDB);  //set VCOMH deselect level
    OLED_cmd(0x40);  //set VCOMH deselect level
    OLED_cmd(0x78);  //OLED command set disabled
    OLED_cmd(0x28);  //function set (fundamental command set)
    OLED_cmd(0x01);  //clear display
    OLED_cmd(0x80);  //set DDRAM address to 0x00
    OLED_cmd(0x0C);  //display ON
    __delay_ms(150);
    OLED_cmd(0x0C);  //display ON
    __delay_ms(150);
    
    OLED_data('H');
    OLED_data('E');
    OLED_data('L');
    OLED_data('L');
    
    OLED_cmd(0xC0);
    OLED_data('Y');
    OLED_data('E');
    OLED_data('S');
}
