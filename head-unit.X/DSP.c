// TAS3103 DSP Chip Driver

#include "DSP.h"

void _DSP_write(uint8_t addr, uint32_t data) {
    I2C1_Write4ByteRegister(DSP_I2C_ADDR, addr, data);
}

void _DSP_mute(void) {
    _DSP_write(DSP_MUTE_ADDR, DSP_MUTE_ON_VAL);
}

void _DSP_unmute(void) {
    _DSP_write(DSP_MUTE_ADDR, DSP_MUTE_OFF_VAL);
}

void DSP_GPIO_off(void) {
    _DSP_write(DSP_GPIO_DATA_ADDR, 0x00000000);
}

void DSP_GPIO_on(void) {
    _DSP_write(DSP_GPIO_DATA_ADDR, 0x0000000F);
}

void DSP_init(void) {
    /*
    I2C1_Write1ByteRegister(DSP_I2C_ADDR, 0x80, cmd);
    
    Dbuf.SubAddr = I2S_FORMAT_SUB_ADDR;
    Dbuf.Data.B_Data[0] = 0x00;//0x04;
    Dbuf.Data.B_Data[1] = 0x43;//0x40;
    Dbuf.Data.B_Data[2] = 0x24;
    Dbuf.Data.B_Data[3] = 0x33;
    TAS3103_SendData(&Dbuf,4);

    Dbuf.SubAddr = G_TO_Y_SUBADDR;
    Dbuf.Data.B_Data[0] = 0x00;
    Dbuf.Data.B_Data[1] = 0x80;
    Dbuf.Data.B_Data[2] = 0x00;
    Dbuf.Data.B_Data[3] = 0x00;
    TAS3103_SendData(&Dbuf,4);

    Dbuf.SubAddr = H_TO_Z_SUBADDR;
    Dbuf.Data.B_Data[0] = 0x00;
    Dbuf.Data.B_Data[1] = 0x80;
    Dbuf.Data.B_Data[2] = 0x00;
    Dbuf.Data.B_Data[3] = 0x00;
    TAS3103_SendData(&Dbuf,4);
    */
    
    LATrigger();
    _DSP_mute();
    
    // I2S format
    uint32_t config = 0x01031100;
    config |= 0x00000030;           // input I2S
    config ^= 0x00000003;           // output I2S
    config ^= 0x00002000;           // input 24bit
    config ^= 0x00000200;           // output 24bit
    _DSP_write(DSP_I2S_FORMAT_ADDR, config);
    
    // volume
    _DSP_write(DSP_CH1_VOLUME_ADDR, 0x07ECA9CD);
    _DSP_write(DSP_CH2_VOLUME_ADDR, DSP_ONE_VAL);
    
    // GPIO
    _DSP_write(DSP_GPIO_CONFIG_ADDR, DSP_GPIO_CONFIG_VAL);
    uint32_t blarg = I2C1_Read4ByteRegister(DSP_I2C_ADDR, DSP_CH1_VOLUME_ADDR);
    blarg += 1;
//    //DSP_GPIO_off();
    
    _DSP_unmute();
}
