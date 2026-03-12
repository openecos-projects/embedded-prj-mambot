#ifndef __EMO_DATA_H__
#define __EMO_DATA_H__

#include <stdint.h>

// 表情数量
#define EMO_COUNT  9

// 128x64 全屏表情 (1024 字节/个)
extern const uint8_t emo_0[1024];
extern const uint8_t emo_1[1024];
extern const uint8_t emo_2[1024];
extern const uint8_t emo_3[1024];
extern const uint8_t emo_4[1024];
extern const uint8_t emo_5[1024];
extern const uint8_t emo_6[1024];
extern const uint8_t emo_7[1024];
extern const uint8_t emo_8[1024];

// 表情指针数组，方便索引访问
extern const uint8_t* const emo_list[EMO_COUNT];

#endif // __EMO_DATA_H__
