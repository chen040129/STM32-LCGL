//
// Created by csy on 2023/7/7 0007.
//

#ifndef PROJECT_TFTSHOW_H
#define PROJECT_TFTSHOW_H

#include "lcd.h"
#include "main.h"
#include "stdio.h"
#include "math.h"

void TFT_SHOW(uint16_t *function_Num, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t function_Num_Len,
              uint16_t Y_STEP_ADD, uint16_t X_STEP_ADD);

void Draw_form(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t interval);

#endif //PROJECT_TFTSHOW_H
