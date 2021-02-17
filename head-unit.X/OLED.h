#ifndef OLED_H_
#define OLED_H_

#include "shared.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"

#define OLED_I2C_ADDR 0x3C
#define OLED_DRAM_ADDR 0x80
#define OLED_DRAM_ROW1_OFFSET 0x00
#define OLED_DRAM_ROW2_OFFSET 0x40
#define OLED_LINE_LENGTH 16
#define OLED_BLANK_LINE "                "

#define OLED_DELAY 25

void OLED_init(void);
void OLED_tick(void);
void OLED_cmd(uint8_t cmd);
void OLED_data(uint8_t data);
void OLED_println(char string[], uint8_t lineNum);
void OLED_setChar(char c, uint8_t pos, uint8_t lineNum);

void OLED_draw(void);
bool OLED_readyToDraw(void);

#endif
