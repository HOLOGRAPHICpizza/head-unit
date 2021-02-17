#include "Knobs.h"

volatile static uint8_t _Knobs_lastVolume = 0;
volatile static uint8_t _Knobs_volume = 0;
volatile static bool _Knobs_volumeChanged = false;

void _Knobs_TMR0_ISR(void) {
    if(ADCC_IsConversionDone()) {
        ADCC_StartConversion(VOLUME_IN);
    }
}

void _Knobs_ADC_ISR(void) {
    uint32_t result = (uint32_t) ADCC_GetConversionResult();
    uint32_t vol32 = (result * 200) / 4095;
    _Knobs_volume = (uint8_t) vol32 / 2;
    if((_Knobs_volume > _Knobs_lastVolume  + 1) || (_Knobs_volume < _Knobs_lastVolume  - 1)) {
        _Knobs_lastVolume = _Knobs_volume;
        _Knobs_volumeChanged = true;
    }
}

void Knobs_init(void) {
    ADCC_Initialize();
    ADCC_SetADIInterruptHandler(&_Knobs_ADC_ISR);
    
    TMR0_Initialize();
    TMR0_StartTimer();
    TMR0_SetInterruptHandler(&_Knobs_TMR0_ISR);
}

bool Knobs_volumeChanged(void) {
    return _Knobs_volumeChanged;
}

uint8_t Knobs_getVolume(void) {
    _Knobs_volumeChanged = false;
    return _Knobs_volume;
}
