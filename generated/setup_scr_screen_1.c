/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/



#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"
#include "main.h"

void setup_scr_screen_1(lv_ui *ui) {
    //Write codes screen_1
    ui->screen_1 = lv_obj_create(NULL);
    ui->g_kb_screen_1 = lv_keyboard_create(ui->screen_1);
    lv_obj_add_event_cb(ui->g_kb_screen_1, kb_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui->g_kb_screen_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_font(ui->g_kb_screen_1, &lv_font_simsun_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui->screen_1, 800, 480);

    //Write style for screen_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes screen_1_chart_1
    ui->screen_1_chart_1 = lv_chart_create(ui->screen_1);
    lv_chart_set_type(ui->screen_1_chart_1, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(ui->screen_1_chart_1, 30, 50);
    lv_chart_set_point_count(ui->screen_1_chart_1, 5);
    lv_chart_set_range(ui->screen_1_chart_1, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    lv_chart_set_range(ui->screen_1_chart_1, LV_CHART_AXIS_SECONDARY_Y, 0, 100);
    lv_chart_set_zoom_x(ui->screen_1_chart_1, 256);
    lv_chart_set_zoom_y(ui->screen_1_chart_1, 256);
    lv_obj_set_style_size(ui->screen_1_chart_1, 0, LV_PART_INDICATOR);


    lv_obj_set_pos(ui->screen_1_chart_1, 5, 5);
    lv_obj_set_size(ui->screen_1_chart_1, 800, 480);
    lv_obj_set_scrollbar_mode(ui->screen_1_chart_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_1_chart_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_chart_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_chart_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_chart_1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_chart_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_chart_1, lv_color_hex(0xe8e8e8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_chart_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_chart_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->screen_1_chart_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->screen_1_chart_1, lv_color_hex(0xe8e8e8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->screen_1_chart_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_chart_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write style for screen_1_chart_1, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_1_chart_1, lv_color_hex(0x151212), LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_chart_1, &lv_font_montserratMedium_12, LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->screen_1_chart_1, 2, LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->screen_1_chart_1, lv_color_hex(0xe8e8e8), LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->screen_1_chart_1, 255, LV_PART_TICKS | LV_STATE_DEFAULT);

    //Update current screen layout.
    lv_obj_update_layout(ui->screen_1);


}
