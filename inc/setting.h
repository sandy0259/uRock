#ifndef __SETTING_H__
#define __SETTING_H__

#define BUFFER_NUM 4
#define STAGE_NUM 4
#define SAMPLE_NUM 256

#define SAMPLING_RATE 200 /* In Kilo Hz, Make Sure it can divide 45000*/

#define DELAY_BANK(x) DELAY_BANK_##x

#define DELAY_BANK_0 0xD0200000 
#define DELAY_BANK_1 0xD0300000
#define DELAY_BANK_2 0xD0400000
#define DELAY_BANK_3 0xD0500000
#define DELAY_BANK_4 0xD0600000

#endif //__SETTING_H__