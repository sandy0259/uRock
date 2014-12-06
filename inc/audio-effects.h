#ifndef __AUDIO_EFFECT_H__
#define __AUDIO_EFFECT_H__

#include <stdint.h>

#include "stm32f4xx_hal.h"

#define ARM_MATH_CM4
#include "arm_math.h"
#include "core_cmInstr.h"

#define SAMPLE_NUM 256

void NormalizeData(volatile uint8_t * pData, volatile float* tData);

void DenormalizeData(volatile float* tData, volatile uint8_t * pData);

typedef void(*EffectFunc)(volatile float*, float);

struct parameter_t{
    float value;
    float upperBound;
    float lowerBound;
};

struct Effect{
    EffectFunc func;
    struct parameter_t parameter[4];
};

void Gain(volatile float* pData, float g);

#endif //__AUDIO_EFFECT_H__