#include "Knobs.h"

volatile static uint8_t lastVolume = 0;
volatile static uint8_t volume = 0;
volatile static bool volumeChanged = false;

void ADC_ISR(void) {
    uint32_t result = (uint32_t) ADCC_GetConversionResult();
    uint32_t vol32 = (result * 200) / 4095;
    volume = (uint8_t) vol32 / 2;
    if((volume > lastVolume  + 1) || (volume < lastVolume  - 1)) {
        lastVolume = volume;
        volumeChanged = true;
    }
}

void Knobs_init(void) {
    ADCC_Initialize();
    ADCC_SetADIInterruptHandler(&ADC_ISR);
    ADCC_StartConversion(VOLUME_IN);
}

bool Knobs_volumeChanged(void) {
    return volumeChanged;
}

uint8_t Knobs_getVolume(void) {
    volumeChanged = false;
    while(!ADCC_IsConversionDone()) {
        NOP();
    }
    ADCC_StartConversion(VOLUME_IN);
    return volume;
}
