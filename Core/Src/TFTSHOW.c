/*
//
// Created by csy on 2023/7/7 0007.
//

#include "TFTSHOW.h"



//function_Num是传入的数组
void TFT_SHOW(uint16_t *function_Num,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t function_Num_Len,uint16_t Y_STEP_ADD,uint16_t X_STEP_ADD){
    uint16_t y_last_POS=0;
    uint16_t function_Num_Max=0;
    uint16_t x_POS=x1;
    uint16_t y_POS=y1;

    for (int j = 0; j < function_Num_Len; ++j) {
        if(function_Num_Max<function_Num[j]){
            function_Num_Max=function_Num[j];
        }
    }


    for (int i = 0; x_POS< x2-X_STEP_ADD; ++i) {
        x_POS+=X_STEP_ADD;
        y_last_POS=y_POS;
        if((function_Num[i])/Y_STEP_ADD<((y1+y2)/2-function_Num_Max/Y_STEP_ADD/2)){
            y_POS=(y1+y2)/2+function_Num_Max/Y_STEP_ADD/2-function_Num[i]/Y_STEP_ADD;
        } else{
            y_POS=0;
        }

        lcd_draw_line(x_POS,y_POS,x_POS-X_STEP_ADD,y_last_POS,BLUE);
        lcd_draw_point(x_POS,y_POS,BLACK);
    }
    y_last_POS=0;

    lcd_draw_line(x1+1,y1+1,x1+1,y2-1,BLACK);
    lcd_draw_line(x1+1,y2-1,x2-1,y2-1,BLACK);
    lcd_draw_line(x2-1,y2-1,x1+1,y2-1,BLACK);
    lcd_draw_line(x2-1,y2-1,x2-1,y1+1,BLACK);

*/
/*    lcd_draw_line(x1,(y1+y2)/2,x2,(y1+y2)/2,BLACK);*//*


};


void Draw_form(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t interval) {
    for (int i = 0;x2<=840&&y1+i<=y2&&y1+i<480;i+=interval) {
        lcd_draw_line(x1,y1+i,x2,y1+i,BLACK);
    }

    for (int i = 0;y2<=480&&x1+i<=x2&&x1+i<800;i+=interval) {
        lcd_draw_line(x1+i,y1,x1+i,y2,BLACK);
    }
}*/
