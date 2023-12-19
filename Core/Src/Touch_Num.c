//
// Created by csy on 2023/7/17 0017.
//

#include "Touch_Num.h"

void Touch_Num(uint16_t TOUCH[5][2]) {
    for (int i = 0; i < 5; ++i) {
        tp_dev.x[i] = 0;
        tp_dev.y[i] = 0;
    }
    if (tp_dev.touchtype & 0X80) {
        tp_dev.scan(0);
        for (int t = 0; t < 5; ++t) {
            if (tp_dev.sta) {
                if (tp_dev.x[t] < lcddev.width && tp_dev.y[t] < lcddev.height) {
                    TOUCH[t][0] = tp_dev.x[t];
                    TOUCH[t][1] = tp_dev.y[t];
                }
            } else {
                TOUCH[t][0] = 0XFFFF;
            }
        }
    }
}