#include "shared.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"

#define OLED_ADDR 0x3C
#define OLED_DELAY 25

void OLED_init(void);
void OLED_cmd(uint8_t cmd);
void OLED_data(uint8_t data);
void OLED_println(char string[], uint8_t lineNum);

