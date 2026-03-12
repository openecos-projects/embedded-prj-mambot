#ifndef __SG90_H
#define __SG90_H

#include <stdint.h>

typedef enum {
    SG90_CH0 = 0,
    SG90_CH1, SG90_CH2, SG90_CH3
} SG90_channel_t;

/* 定义微调角度，用于控制步幅大小
 * STEP_AMP 越大，腿抬得越高/划得越远，但也越容易翻车
 */
#define STEP_AMP  30  // 步幅幅度 (30度)

// 基准角度 (站立状态)
#define CENTER    90

void init_sg90(void);
void set_sg90_degree(SG90_channel_t sg90_channel, int degree);
void set_all_sg90_degree(int fr, int fl, int bl, int br);
void action_laydown(void);
void action_test_which_is_which(void);
void action_test_which_is_which2(void);
int deg_pos_neg(int deg);

// Placeholder functions mentioned in original header but not implemented in main.c snippet
// If they were implemented elsewhere, they should be moved too.
// Assuming they were not implemented or used in main.c based on grep.
// void sg90_motion_0(void);
// void sg90_motion_1(void);
// void sg90_motion_2(int steps, int speed_delay_ms);

#endif
