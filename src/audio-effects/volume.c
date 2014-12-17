#include "volume.h"
#include "helper.h"
#include "math.h"

#include "arm_math.h"

void Volume(q31_t* pData, void *opaque){
    struct Volume_t *tmp = (struct Volume_t*)opaque;

    arm_scale_q31(pData, tmp->cache, 15, pData, SAMPLE_NUM);

    return;
}

void delete_Volume(void *opaque){
    return;
}

void adjust_Volume(void *opaque, uint8_t* values){
    struct Volume_t *tmp = (struct Volume_t*)opaque;

    LinkPot(&(tmp->gain), values[0]); 
    tmp->cache = (q31_t)(powf(10, (tmp->gain.value * 0.1f)) * 131072);

    return;
}

struct Effect_t* new_Volume(struct Volume_t* opaque){
    strcpy(opaque->parent.name, "Volume");
    opaque->parent.func = Volume;
    opaque->parent.del = delete_Volume;
    opaque->parent.adj = adjust_Volume;

    opaque->gain.upperBound = 0.0f;
    opaque->gain.lowerBound = -30.0f;
    opaque->gain.value = 0.0f;

    return (struct Effect_t*)opaque;
}

