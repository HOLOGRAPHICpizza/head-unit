// TAS3103 DSP Chip Driver

#ifndef DSP_H
#define	DSP_H

#include "shared.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"

#define DSP_I2C_ADDR            0x34

#define DSP_I2S_FORMAT_ADDR     0xF9
#define DSP_MUTE_ADDR           0xF0
#define DSP_CH1_VOLUME_ADDR     0xF2
#define DSP_CH2_VOLUME_ADDR     0xF3
#define DSP_GPIO_CONFIG_ADDR    0xEF
#define DSP_GPIO_DATA_ADDR      0xEE

#define DSP_ONE_VAL             0x00800000
#define DSP_MUTE_ON_VAL         0x00000007
#define DSP_MUTE_OFF_VAL        0x00000000
#define DSP_GPIO_CONFIG_VAL     0x000F6E6D

void DSP_GPIO_off(void);
void DSP_GPIO_on(void);
void DSP_init(void);

#endif
