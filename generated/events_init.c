/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "main.h"

static void screen_1_chart_1_event_handler(lv_event_t *e) {

}

void events_init_screen_1(lv_ui *ui) {
    lv_obj_add_event_cb(ui->screen_1_chart_1, screen_1_chart_1_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui) {
}
