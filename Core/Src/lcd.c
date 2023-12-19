/**
 ****************************************************************************************************
 * @file        lcd.c
 * @author      锟斤拷锟斤拷原锟斤拷锟脚讹拷(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-16
 * @brief       2.8锟斤拷/3.5锟斤拷/4.3锟斤拷/7锟斤拷 TFTLCD(MCU锟斤拷) 锟斤拷锟斤拷锟斤拷锟斤拷
 *              支锟斤拷锟斤拷锟斤拷IC锟酵号帮拷锟斤拷:ILI9341/NT35310/NT35510/SSD1963/ST7789锟斤拷
 *
 * @license     Copyright (c) 2020-2032, 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷涌萍锟斤拷锟斤拷薰锟剿�
 ****************************************************************************************************
 * @attention
 *
 * 实锟斤拷平台:锟斤拷锟斤拷原锟斤拷 探锟斤拷锟斤拷 F407锟斤拷锟斤拷锟斤拷
 * 锟斤拷锟斤拷锟斤拷频:www.yuanzige.com
 * 锟斤拷锟斤拷锟斤拷坛:www.openedv.com
 * 锟斤拷司锟斤拷址:www.alientek.com
 * 锟斤拷锟斤拷锟街�:openedv.taobao.com
 *
 * 锟睫革拷说锟斤拷
 * V1.0 20211016
 * 锟斤拷一锟轿凤拷锟斤拷
 *
 ****************************************************************************************************
 */

#include "stdlib.h"
#include "lcd.h"
#include "lcdfont.h"
#include "stdio.h"
#include "delay.h"

/* lcd_ex.c锟斤拷鸥锟斤拷锟絃CD锟斤拷锟斤拷IC锟侥寄达拷锟斤拷锟斤拷始锟斤拷锟斤拷锟街达拷锟斤拷,锟皆硷拷lcd.c,锟斤拷.c锟侥硷拷
 * 锟斤拷直锟接硷拷锟诫到锟斤拷锟斤拷锟斤拷锟斤拷,只锟斤拷lcd.c锟斤拷锟矫碉拷,锟斤拷锟斤拷通锟斤拷include锟斤拷锟斤拷式锟斤拷锟�.(锟斤拷要锟斤拷
 * 锟斤拷锟斤拷锟侥硷拷锟劫帮拷锟斤拷锟斤拷.c锟侥硷拷!!锟斤拷锟斤拷岜拷锟�!)
 */


SRAM_HandleTypeDef g_sram_handle;   /* SRAM锟斤拷锟�(锟斤拷锟节匡拷锟斤拷LCD) */

/* LCD锟侥伙拷锟斤拷锟斤拷色锟酵憋拷锟斤拷色 */
uint32_t g_point_color = 0xF800;    /* 锟斤拷锟斤拷锟斤拷色 */
uint32_t g_back_color = 0xFFFF;    /* 锟斤拷锟斤拷色 */

/* 锟斤拷锟斤拷LCD锟斤拷要锟斤拷锟斤拷 */
_lcd_dev lcddev;

/**
 * @brief       LCD写锟斤拷锟斤拷
 * @param       data: 要写锟斤拷锟斤拷锟斤拷锟�
 * @retval      锟斤拷
 */
void lcd_wr_data(volatile uint16_t data) {
    data = data;            /* 使锟斤拷-O2锟脚伙拷锟斤拷时锟斤拷,锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷时 */
    LCD->LCD_RAM = data;
}

/**
 * @brief       LCD写锟侥达拷锟斤拷锟斤拷锟�/锟斤拷址锟斤拷锟斤拷
 * @param       regno: 锟侥达拷锟斤拷锟斤拷锟�/锟斤拷址
 * @retval      锟斤拷
 */
void lcd_wr_regno(volatile uint16_t regno) {
    regno = regno;          /* 使锟斤拷-O2锟脚伙拷锟斤拷时锟斤拷,锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷时 */
    LCD->LCD_REG = regno;   /* 写锟斤拷要写锟侥寄达拷锟斤拷锟斤拷锟� */
}

/**
 * @brief       LCD写锟侥达拷锟斤拷
 * @param       regno:锟侥达拷锟斤拷锟斤拷锟�/锟斤拷址
 * @param       data:要写锟斤拷锟斤拷锟斤拷锟�
 * @retval      锟斤拷
 */
void lcd_write_reg(uint16_t regno, uint16_t data) {
    LCD->LCD_REG = regno;   /* 写锟斤拷要写锟侥寄达拷锟斤拷锟斤拷锟� */
    LCD->LCD_RAM = data;    /* 写锟斤拷锟斤拷锟斤拷 */
}

/**
 * @brief       LCD锟斤拷锟斤拷锟斤拷
 * @param       锟斤拷
 * @retval      锟斤拷取锟斤拷锟斤拷锟斤拷锟斤拷
 */
static uint16_t lcd_rd_data(void) {
    volatile uint16_t ram;  /* 锟斤拷止锟斤拷锟脚伙拷 */
    ram = LCD->LCD_RAM;
    return ram;
}

/**
 * @brief       LCD锟斤拷时锟斤拷锟斤拷,锟斤拷锟斤拷锟节诧拷锟斤拷锟斤拷mdk -O1时锟斤拷锟脚伙拷时锟斤拷要锟斤拷锟矫的地凤拷
 * @param       t:锟斤拷时锟斤拷锟斤拷值
 * @retval      锟斤拷
 */
static void lcd_opt_delay(uint32_t i) {
    while (i--); /* 使锟斤拷AC6时锟斤拷循锟斤拷锟斤拷锟杰憋拷锟脚伙拷,锟斤拷使锟斤拷while(1) __asm volatile(""); */
}

/**
 * @brief       准锟斤拷写GRAM
 * @param       锟斤拷
 * @retval      锟斤拷
 */
void lcd_write_ram_prepare(void) {
    LCD->LCD_REG = lcddev.wramcmd;
}

/**
 * @brief       锟斤拷取锟斤拷某锟斤拷锟斤拷锟缴�
 * @param       x,y:锟斤拷锟斤拷
 * @retval      锟剿碉拷锟斤拷锟缴�(32位锟斤拷色,锟斤拷锟斤拷锟斤拷锟絃TDC)
 */
uint32_t lcd_read_point(uint16_t x, uint16_t y) {
    uint16_t r = 0, g = 0, b = 0;

    if (x >= lcddev.width || y >= lcddev.height) {
        return 0;   /* 锟斤拷锟斤拷锟剿凤拷围,直锟接凤拷锟斤拷 */
    }

    lcd_set_cursor(x, y);       /* 锟斤拷锟斤拷锟斤拷锟斤拷 */

    if (lcddev.id == 0x5510) {
        lcd_wr_regno(0x2E00);   /* 5510 锟斤拷锟酵讹拷GRAM指锟斤拷 */
    } else {
        lcd_wr_regno(0x2E);     /* 9341/5310/1963/7789 锟饺凤拷锟酵讹拷GRAM指锟斤拷 */
    }


    r = lcd_rd_data();          /* 锟劫讹拷(dummy read) */

    if (lcddev.id == 0x1963) {
        return r;   /* 1963直锟接讹拷锟酵匡拷锟斤拷 */
    }

    lcd_opt_delay(2);
    r = lcd_rd_data();          /* 实锟斤拷锟斤拷锟斤拷锟斤拷色 */
    /* 9341/NT35310/NT35510要锟斤拷2锟轿讹拷锟斤拷 */
    lcd_opt_delay(2);
    b = lcd_rd_data();
    g = r & 0xFF;               /* 锟斤拷锟斤拷9341/5310/5510/7789,锟斤拷一锟轿讹拷取锟斤拷锟斤拷RG锟斤拷值,R锟斤拷前,G锟节猴拷,锟斤拷占8位 */
    g <<= 8;
    return (((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11));  /* ILI9341/NT35310/NT35510/ST7789锟斤拷要锟斤拷式转锟斤拷一锟斤拷 */
}

/**
 * @brief       LCD锟斤拷锟斤拷锟斤拷示
 * @param       锟斤拷
 * @retval      锟斤拷
 */
void lcd_display_on(void) {
    if (lcddev.id == 0x5510) {
        lcd_wr_regno(0x2900);   /* 锟斤拷锟斤拷锟斤拷示 */
    } else                        /* 9341/5310/1963/7789 锟饺凤拷锟酵匡拷锟斤拷锟斤拷示指锟斤拷 */
    {
        lcd_wr_regno(0x29);     /* 锟斤拷锟斤拷锟斤拷示 */
    }
}

/**
 * @brief       LCD锟截憋拷锟斤拷示
 * @param       锟斤拷
 * @retval      锟斤拷
 */
void lcd_display_off(void) {
    if (lcddev.id == 0x5510) {
        lcd_wr_regno(0x2800);   /* 锟截憋拷锟斤拷示 */
    } else    /* 9341/5310/1963/7789 锟饺凤拷锟酵关憋拷锟斤拷示指锟斤拷 */
    {
        lcd_wr_regno(0x28);     /* 锟截憋拷锟斤拷示 */
    }
}

/**
 * @brief       锟斤拷锟矫癸拷锟轿伙拷锟�(锟斤拷RGB锟斤拷锟斤拷效)
 * @param       x,y: 锟斤拷锟斤拷
 * @retval      锟斤拷
 */
void lcd_set_cursor(uint16_t x, uint16_t y) {
    if (lcddev.id == 0x1963) {
        if (lcddev.dir == 0)    /* 锟斤拷锟斤拷模式, x锟斤拷锟斤拷锟斤拷要锟戒换 */
        {
            x = lcddev.width - 1 - x;
            lcd_wr_regno(lcddev.setxcmd);
            lcd_wr_data(0);
            lcd_wr_data(0);
            lcd_wr_data(x >> 8);
            lcd_wr_data(x & 0xFF);
        } else                    /* 锟斤拷锟斤拷模式 */
        {
            lcd_wr_regno(lcddev.setxcmd);
            lcd_wr_data(x >> 8);
            lcd_wr_data(x & 0xFF);
            lcd_wr_data((lcddev.width - 1) >> 8);
            lcd_wr_data((lcddev.width - 1) & 0xFF);
        }

        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(y >> 8);
        lcd_wr_data(y & 0xFF);
        lcd_wr_data((lcddev.height - 1) >> 8);
        lcd_wr_data((lcddev.height - 1) & 0xFF);

    } else if (lcddev.id == 0x5510) {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(x >> 8);
        lcd_wr_regno(lcddev.setxcmd + 1);
        lcd_wr_data(x & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(y >> 8);
        lcd_wr_regno(lcddev.setycmd + 1);
        lcd_wr_data(y & 0xFF);
    } else    /* 9341/5310/7789 锟斤拷 锟斤拷锟斤拷锟斤拷锟斤拷 */
    {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(x >> 8);
        lcd_wr_data(x & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(y >> 8);
        lcd_wr_data(y & 0xFF);
    }
}

/**
 * @brief       锟斤拷锟斤拷LCD锟斤拷锟皆讹拷扫锟借方锟斤拷(锟斤拷RGB锟斤拷锟斤拷效)
 *   @note
 *              9341/5310/5510/1963/7789锟斤拷IC锟窖撅拷实锟绞诧拷锟斤拷
 *              注锟斤拷:锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟杰伙拷锟杰碉拷锟剿猴拷锟斤拷锟斤拷锟矫碉拷影锟斤拷(锟斤拷锟斤拷锟斤拷9341),
 *              锟斤拷锟斤拷,一锟斤拷锟斤拷锟斤拷为L2R_U2D锟斤拷锟斤拷,锟斤拷锟斤拷锟斤拷锟轿拷锟斤拷锟缴拷璺绞�,锟斤拷锟杰碉拷锟斤拷锟斤拷示锟斤拷锟斤拷锟斤拷.
 *
 * @param       dir:0~7,锟斤拷锟斤拷8锟斤拷锟斤拷锟斤拷(锟斤拷锟藉定锟斤拷锟絣cd.h)
 * @retval      锟斤拷
 */
void lcd_scan_dir(uint8_t dir) {
    uint16_t regval = 0;
    uint16_t dirreg = 0;
    uint16_t temp;

    /* 锟斤拷锟斤拷时锟斤拷锟斤拷1963锟斤拷锟侥憋拷扫锟借方锟斤拷锟斤拷锟斤拷时1963锟侥变方锟斤拷(锟斤拷锟斤拷锟斤拷锟斤拷锟�1963锟斤拷锟斤拷锟解处锟斤拷,锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷IC锟斤拷效) */
    if ((lcddev.dir == 1 && lcddev.id != 0x1963) || (lcddev.dir == 0 && lcddev.id == 0x1963)) {
        switch (dir)   /* 锟斤拷锟斤拷转锟斤拷 */
        {
            case 0:
                dir = 6;
                break;

            case 1:
                dir = 7;
                break;

            case 2:
                dir = 4;
                break;

            case 3:
                dir = 5;
                break;

            case 4:
                dir = 1;
                break;

            case 5:
                dir = 0;
                break;

            case 6:
                dir = 3;
                break;

            case 7:
                dir = 2;
                break;
        }
    }


    /* 锟斤拷锟斤拷扫锟借方式 锟斤拷锟斤拷 0x36/0x3600 锟侥达拷锟斤拷 bit 5,6,7 位锟斤拷值 */
    switch (dir) {
        case L2R_U2D:/* 锟斤拷锟斤拷锟斤拷,锟斤拷锟较碉拷锟斤拷 */
            regval |= (0 << 7) | (0 << 6) | (0 << 5);
            break;

        case L2R_D2U:/* 锟斤拷锟斤拷锟斤拷,锟斤拷锟铰碉拷锟斤拷 */
            regval |= (1 << 7) | (0 << 6) | (0 << 5);
            break;

        case R2L_U2D:/* 锟斤拷锟揭碉拷锟斤拷,锟斤拷锟较碉拷锟斤拷 */
            regval |= (0 << 7) | (1 << 6) | (0 << 5);
            break;

        case R2L_D2U:/* 锟斤拷锟揭碉拷锟斤拷,锟斤拷锟铰碉拷锟斤拷 */
            regval |= (1 << 7) | (1 << 6) | (0 << 5);
            break;

        case U2D_L2R:/* 锟斤拷锟较碉拷锟斤拷,锟斤拷锟斤拷锟斤拷 */
            regval |= (0 << 7) | (0 << 6) | (1 << 5);
            break;

        case U2D_R2L:/* 锟斤拷锟较碉拷锟斤拷,锟斤拷锟揭碉拷锟斤拷 */
            regval |= (0 << 7) | (1 << 6) | (1 << 5);
            break;

        case D2U_L2R:/* 锟斤拷锟铰碉拷锟斤拷,锟斤拷锟斤拷锟斤拷 */
            regval |= (1 << 7) | (0 << 6) | (1 << 5);
            break;

        case D2U_R2L:/* 锟斤拷锟铰碉拷锟斤拷,锟斤拷锟揭碉拷锟斤拷 */
            regval |= (1 << 7) | (1 << 6) | (1 << 5);
            break;
    }

    dirreg = 0x36;  /* 锟皆撅拷锟襟部凤拷锟斤拷锟斤拷IC, 锟斤拷0x36锟侥达拷锟斤拷锟斤拷锟斤拷 */

    if (lcddev.id == 0x5510) {
        dirreg = 0x3600;    /* 锟斤拷锟斤拷5510, 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷ic锟侥寄达拷锟斤拷锟叫诧拷锟斤拷 */
    }

    /* 9341 & 7789 要锟斤拷锟斤拷BGR位 */
    if (lcddev.id == 0x9341 || lcddev.id == 0x7789) {
        regval |= 0x08;
    }

    lcd_write_reg(dirreg, regval);

    if (lcddev.id != 0x1963)                    /* 1963锟斤拷锟斤拷锟斤拷锟疥处锟斤拷 */
    {
        if (regval & 0x20) {
            if (lcddev.width < lcddev.height)   /* 锟斤拷锟斤拷X,Y */
            {
                temp = lcddev.width;
                lcddev.width = lcddev.height;
                lcddev.height = temp;
            }
        } else {
            if (lcddev.width > lcddev.height)   /* 锟斤拷锟斤拷X,Y */
            {
                temp = lcddev.width;
                lcddev.width = lcddev.height;
                lcddev.height = temp;
            }
        }
    }

    /* 锟斤拷锟斤拷锟斤拷示锟斤拷锟斤拷(锟斤拷锟斤拷)锟斤拷小 */
    if (lcddev.id == 0x5510) {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setxcmd + 1);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setxcmd + 2);
        lcd_wr_data((lcddev.width - 1) >> 8);
        lcd_wr_regno(lcddev.setxcmd + 3);
        lcd_wr_data((lcddev.width - 1) & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setycmd + 1);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setycmd + 2);
        lcd_wr_data((lcddev.height - 1) >> 8);
        lcd_wr_regno(lcddev.setycmd + 3);
        lcd_wr_data((lcddev.height - 1) & 0xFF);
    } else {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(0);
        lcd_wr_data(0);
        lcd_wr_data((lcddev.width - 1) >> 8);
        lcd_wr_data((lcddev.width - 1) & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(0);
        lcd_wr_data(0);
        lcd_wr_data((lcddev.height - 1) >> 8);
        lcd_wr_data((lcddev.height - 1) & 0xFF);
    }
}

/**
 * @brief       锟斤拷锟斤拷
 * @param       x,y: 锟斤拷锟斤拷
 * @param       color: 锟斤拷锟斤拷锟缴�(32位锟斤拷色,锟斤拷锟斤拷锟斤拷锟絃TDC)
 * @retval      锟斤拷
 */
void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color) {
    lcd_set_cursor(x, y);       /* 锟斤拷锟矫癸拷锟轿伙拷锟� */
    lcd_write_ram_prepare();    /* 锟斤拷始写锟斤拷GRAM */
    LCD->LCD_RAM = color;
}

/**
 * @brief       SSD1963锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟矫猴拷锟斤拷
 * @param       pwm: 锟斤拷锟斤拷燃锟�,0~100.越锟斤拷越锟斤拷.
 * @retval      锟斤拷
 */
void lcd_ssd_backlight_set(uint8_t pwm) {
    lcd_wr_regno(0xBE);         /* 锟斤拷锟斤拷PWM锟斤拷锟� */
    lcd_wr_data(0x05);          /* 1锟斤拷锟斤拷PWM频锟斤拷 */
    lcd_wr_data(pwm * 2.55);    /* 2锟斤拷锟斤拷PWM占锟秸憋拷 */
    lcd_wr_data(0x01);          /* 3锟斤拷锟斤拷C */
    lcd_wr_data(0xFF);          /* 4锟斤拷锟斤拷D */
    lcd_wr_data(0x00);          /* 5锟斤拷锟斤拷E */
    lcd_wr_data(0x00);          /* 6锟斤拷锟斤拷F */
}

/**
 * @brief       锟斤拷锟斤拷LCD锟斤拷示锟斤拷锟斤拷
 * @param       dir:0,锟斤拷锟斤拷; 1,锟斤拷锟斤拷
 * @retval      锟斤拷
 */
void lcd_display_dir(uint8_t dir) {
    lcddev.dir = dir;   /* 锟斤拷锟斤拷/锟斤拷锟斤拷 */

    if (dir == 0)       /* 锟斤拷锟斤拷 */
    {
        lcddev.width = 240;
        lcddev.height = 320;

        if (lcddev.id == 0x5510) {
            lcddev.wramcmd = 0x2C00;
            lcddev.setxcmd = 0x2A00;
            lcddev.setycmd = 0x2B00;
            lcddev.width = 480;
            lcddev.height = 800;
        } else if (lcddev.id == 0x1963) {
            lcddev.wramcmd = 0x2C;  /* 锟斤拷锟斤拷写锟斤拷GRAM锟斤拷指锟斤拷 */
            lcddev.setxcmd = 0x2B;  /* 锟斤拷锟斤拷写X锟斤拷锟斤拷指锟斤拷 */
            lcddev.setycmd = 0x2A;  /* 锟斤拷锟斤拷写Y锟斤拷锟斤拷指锟斤拷 */
            lcddev.width = 480;     /* 锟斤拷锟矫匡拷锟�480 */
            lcddev.height = 800;    /* 锟斤拷锟矫高讹拷800 */
        } else   /* 锟斤拷锟斤拷IC, 锟斤拷锟斤拷: 9341 / 5310 / 7789锟斤拷IC */
        {
            lcddev.wramcmd = 0x2C;
            lcddev.setxcmd = 0x2A;
            lcddev.setycmd = 0x2B;
        }

        if (lcddev.id == 0x5310)    /* 锟斤拷锟斤拷锟�5310 锟斤拷锟绞撅拷锟� 320*480锟街憋拷锟斤拷 */
        {
            lcddev.width = 320;
            lcddev.height = 480;
        }
    }/*dir = 0*/
    else        /* 锟斤拷锟斤拷 */
    {
        lcddev.width = 320;         /* 默锟较匡拷锟� */
        lcddev.height = 240;        /* 默锟较高讹拷 */

        if (lcddev.id == 0x5510) {
            lcddev.wramcmd = 0x2C00;
            lcddev.setxcmd = 0x2A00;
            lcddev.setycmd = 0x2B00;
            lcddev.width = 800;
            lcddev.height = 480;
        } else if (lcddev.id == 0x1963) {
            lcddev.wramcmd = 0x2C;  /* 锟斤拷锟斤拷写锟斤拷GRAM锟斤拷指锟斤拷 */
            lcddev.setxcmd = 0x2A;  /* 锟斤拷锟斤拷写X锟斤拷锟斤拷指锟斤拷 */
            lcddev.setycmd = 0x2B;  /* 锟斤拷锟斤拷写Y锟斤拷锟斤拷指锟斤拷 */
            lcddev.width = 800;     /* 锟斤拷锟矫匡拷锟�800 */
            lcddev.height = 480;    /* 锟斤拷锟矫高讹拷480 */
        } else   /* 锟斤拷锟斤拷IC, 锟斤拷锟斤拷:9341/5310/7789锟斤拷IC */
        {
            lcddev.wramcmd = 0x2C;
            lcddev.setxcmd = 0x2A;
            lcddev.setycmd = 0x2B;
        }

        if (lcddev.id == 0x5310) {
            lcddev.width = 480;
            lcddev.height = 320;
        }
    }

    lcd_scan_dir(DFT_SCAN_DIR);     /* 默锟斤拷扫锟借方锟斤拷 */
}

/**
 * @brief       锟斤拷锟矫达拷锟斤拷(锟斤拷RGB锟斤拷锟斤拷效), 锟斤拷锟皆讹拷锟斤拷锟矫伙拷锟斤拷锟斤拷锟疥到锟斤拷锟斤拷锟斤拷锟较斤拷(sx,sy).
 * @param       sx,sy:锟斤拷锟斤拷锟斤拷始锟斤拷锟斤拷(锟斤拷锟较斤拷)
 * @param       width,height:锟斤拷锟节匡拷群透叨锟�,锟斤拷锟斤拷锟斤拷锟�0!!
 *   @note      锟斤拷锟斤拷锟叫�:width*height.
 *
 * @retval      锟斤拷
 */
void lcd_set_window(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height) {
    uint16_t twidth, theight;
    twidth = sx + width - 1;
    theight = sy + height - 1;


    if (lcddev.id == 0x1963 && lcddev.dir != 1)     /* 1963锟斤拷锟斤拷锟斤拷锟解处锟斤拷 */
    {
        sx = lcddev.width - width - sx;
        height = sy + height - 1;
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(sx >> 8);
        lcd_wr_data(sx & 0xFF);
        lcd_wr_data((sx + width - 1) >> 8);
        lcd_wr_data((sx + width - 1) & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(sy >> 8);
        lcd_wr_data(sy & 0xFF);
        lcd_wr_data(height >> 8);
        lcd_wr_data(height & 0xFF);
    } else if (lcddev.id == 0x5510) {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(sx >> 8);
        lcd_wr_regno(lcddev.setxcmd + 1);
        lcd_wr_data(sx & 0xFF);
        lcd_wr_regno(lcddev.setxcmd + 2);
        lcd_wr_data(twidth >> 8);
        lcd_wr_regno(lcddev.setxcmd + 3);
        lcd_wr_data(twidth & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(sy >> 8);
        lcd_wr_regno(lcddev.setycmd + 1);
        lcd_wr_data(sy & 0xFF);
        lcd_wr_regno(lcddev.setycmd + 2);
        lcd_wr_data(theight >> 8);
        lcd_wr_regno(lcddev.setycmd + 3);
        lcd_wr_data(theight & 0xFF);
    } else    /* 9341/5310/7789/1963锟斤拷锟斤拷 锟斤拷 锟斤拷锟矫达拷锟斤拷 */
    {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(sx >> 8);
        lcd_wr_data(sx & 0xFF);
        lcd_wr_data(twidth >> 8);
        lcd_wr_data(twidth & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(sy >> 8);
        lcd_wr_data(sy & 0xFF);
        lcd_wr_data(theight >> 8);
        lcd_wr_data(theight & 0xFF);
    }
}

///**
// * @brief       SRAM锟阶诧拷锟斤拷锟斤拷锟斤拷时锟斤拷使锟杰ｏ拷锟斤拷锟脚凤拷锟斤拷
// * @note        锟剿猴拷锟斤拷锟结被HAL_SRAM_Init()锟斤拷锟斤拷,锟斤拷始锟斤拷锟斤拷写锟斤拷锟斤拷锟斤拷锟斤拷
// * @param       hsram:SRAM锟斤拷锟�
// * @retval      锟斤拷
// */
//void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram)
//{
//    GPIO_InitTypeDef gpio_init_struct;

//    __HAL_RCC_FSMC_CLK_ENABLE();            /* 使锟斤拷FSMC时锟斤拷 */
//    __HAL_RCC_GPIOD_CLK_ENABLE();           /* 使锟斤拷GPIOD时锟斤拷 */
//    __HAL_RCC_GPIOE_CLK_ENABLE();           /* 使锟斤拷GPIOE时锟斤拷 */

//    /* 锟斤拷始锟斤拷PD0,1, 8,9,10,14,15 */
//    gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 \
//                           | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15;
//    gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* 锟斤拷锟届复锟斤拷 */
//    gpio_init_struct.Pull = GPIO_PULLUP;                /* 锟斤拷锟斤拷 */
//    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* 锟斤拷锟斤拷 */
//    gpio_init_struct.Alternate = GPIO_AF12_FSMC;        /* 锟斤拷锟斤拷为FSMC */

//    HAL_GPIO_Init(GPIOD, &gpio_init_struct);            /* 锟斤拷始锟斤拷 */

//    /* 锟斤拷始锟斤拷PE7,8,9,10,11,12,13,14,15 */
//    gpio_init_struct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 \
//                           | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
//    HAL_GPIO_Init(GPIOE, &gpio_init_struct);
//}



void lcd_ex_st7789_reginit(void) {
    lcd_wr_regno(0x11);

    delay_ms(120);

    lcd_wr_regno(0x36);
    lcd_wr_data(0x00);

    lcd_wr_regno(0x3A);
    lcd_wr_data(0x05);

    lcd_wr_regno(0xB2);
    lcd_wr_data(0x0C);
    lcd_wr_data(0x0C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x33);
    lcd_wr_data(0x33);

    lcd_wr_regno(0xB7);
    lcd_wr_data(0x35);

    lcd_wr_regno(0xBB); /* vcom */
    lcd_wr_data(0x32);  /* 30 */

    lcd_wr_regno(0xC0);
    lcd_wr_data(0x0C);

    lcd_wr_regno(0xC2);
    lcd_wr_data(0x01);

    lcd_wr_regno(0xC3); /* vrh */
    lcd_wr_data(0x10);  /* 17 0D */

    lcd_wr_regno(0xC4); /* vdv */
    lcd_wr_data(0x20);  /* 20 */

    lcd_wr_regno(0xC6);
    lcd_wr_data(0x0f);

    lcd_wr_regno(0xD0);
    lcd_wr_data(0xA4);
    lcd_wr_data(0xA1);

    lcd_wr_regno(0xE0); /* Set Gamma  */
    lcd_wr_data(0xd0);
    lcd_wr_data(0x00);
    lcd_wr_data(0x02);
    lcd_wr_data(0x07);
    lcd_wr_data(0x0a);
    lcd_wr_data(0x28);
    lcd_wr_data(0x32);
    lcd_wr_data(0x44);
    lcd_wr_data(0x42);
    lcd_wr_data(0x06);
    lcd_wr_data(0x0e);
    lcd_wr_data(0x12);
    lcd_wr_data(0x14);
    lcd_wr_data(0x17);


    lcd_wr_regno(0xE1);  /* Set Gamma */
    lcd_wr_data(0xd0);
    lcd_wr_data(0x00);
    lcd_wr_data(0x02);
    lcd_wr_data(0x07);
    lcd_wr_data(0x0a);
    lcd_wr_data(0x28);
    lcd_wr_data(0x31);
    lcd_wr_data(0x54);
    lcd_wr_data(0x47);
    lcd_wr_data(0x0e);
    lcd_wr_data(0x1c);
    lcd_wr_data(0x17);
    lcd_wr_data(0x1b);
    lcd_wr_data(0x1e);


    lcd_wr_regno(0x2A);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0xef);

    lcd_wr_regno(0x2B);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x01);
    lcd_wr_data(0x3f);

    lcd_wr_regno(0x29); /* display on */
}

/**
 * @brief       ILI9341锟侥达拷锟斤拷锟斤拷始锟斤拷锟斤拷锟斤拷
 * @param       锟斤拷
 * @retval      锟斤拷
 */
void lcd_ex_ili9341_reginit(void) {
    lcd_wr_regno(0xCF);
    lcd_wr_data(0x00);
    lcd_wr_data(0xC1);
    lcd_wr_data(0x30);
    lcd_wr_regno(0xED);
    lcd_wr_data(0x64);
    lcd_wr_data(0x03);
    lcd_wr_data(0x12);
    lcd_wr_data(0x81);
    lcd_wr_regno(0xE8);
    lcd_wr_data(0x85);
    lcd_wr_data(0x10);
    lcd_wr_data(0x7A);
    lcd_wr_regno(0xCB);
    lcd_wr_data(0x39);
    lcd_wr_data(0x2C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x34);
    lcd_wr_data(0x02);
    lcd_wr_regno(0xF7);
    lcd_wr_data(0x20);
    lcd_wr_regno(0xEA);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_regno(0xC0); /* Power control */
    lcd_wr_data(0x1B);  /* VRH[5:0] */
    lcd_wr_regno(0xC1); /* Power control */
    lcd_wr_data(0x01);  /* SAP[2:0];BT[3:0] */
    lcd_wr_regno(0xC5); /* VCM control */
    lcd_wr_data(0x30);  /* 3F */
    lcd_wr_data(0x30);  /* 3C */
    lcd_wr_regno(0xC7); /* VCM control2 */
    lcd_wr_data(0xB7);
    lcd_wr_regno(0x36); /*  Memory Access Control */
    lcd_wr_data(0x48);
    lcd_wr_regno(0x3A);
    lcd_wr_data(0x55);
    lcd_wr_regno(0xB1);
    lcd_wr_data(0x00);
    lcd_wr_data(0x1A);
    lcd_wr_regno(0xB6); /*  Display Function Control */
    lcd_wr_data(0x0A);
    lcd_wr_data(0xA2);
    lcd_wr_regno(0xF2); /*  3Gamma Function Disable */
    lcd_wr_data(0x00);
    lcd_wr_regno(0x26); /* Gamma curve selected */
    lcd_wr_data(0x01);
    lcd_wr_regno(0xE0); /* Set Gamma */
    lcd_wr_data(0x0F);
    lcd_wr_data(0x2A);
    lcd_wr_data(0x28);
    lcd_wr_data(0x08);
    lcd_wr_data(0x0E);
    lcd_wr_data(0x08);
    lcd_wr_data(0x54);
    lcd_wr_data(0xA9);
    lcd_wr_data(0x43);
    lcd_wr_data(0x0A);
    lcd_wr_data(0x0F);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_regno(0xE1);    /* Set Gamma */
    lcd_wr_data(0x00);
    lcd_wr_data(0x15);
    lcd_wr_data(0x17);
    lcd_wr_data(0x07);
    lcd_wr_data(0x11);
    lcd_wr_data(0x06);
    lcd_wr_data(0x2B);
    lcd_wr_data(0x56);
    lcd_wr_data(0x3C);
    lcd_wr_data(0x05);
    lcd_wr_data(0x10);
    lcd_wr_data(0x0F);
    lcd_wr_data(0x3F);
    lcd_wr_data(0x3F);
    lcd_wr_data(0x0F);
    lcd_wr_regno(0x2B);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x01);
    lcd_wr_data(0x3f);
    lcd_wr_regno(0x2A);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0xef);
    lcd_wr_regno(0x11); /* Exit Sleep */
    delay_ms(120);
    lcd_wr_regno(0x29); /* display on */
}


/**
 * @brief       NT35310锟侥达拷锟斤拷锟斤拷始锟斤拷锟斤拷锟斤拷
 * @param       锟斤拷
 * @retval      锟斤拷
 */
void lcd_ex_nt35310_reginit(void) {
    lcd_wr_regno(0xED);
    lcd_wr_data(0x01);
    lcd_wr_data(0xFE);

    lcd_wr_regno(0xEE);
    lcd_wr_data(0xDE);
    lcd_wr_data(0x21);

    lcd_wr_regno(0xF1);
    lcd_wr_data(0x01);
    lcd_wr_regno(0xDF);
    lcd_wr_data(0x10);

    /* VCOMvoltage */
    lcd_wr_regno(0xC4);
    lcd_wr_data(0x8F);  /* 5f */

    lcd_wr_regno(0xC6);
    lcd_wr_data(0x00);
    lcd_wr_data(0xE2);
    lcd_wr_data(0xE2);
    lcd_wr_data(0xE2);
    lcd_wr_regno(0xBF);
    lcd_wr_data(0xAA);

    lcd_wr_regno(0xB0);
    lcd_wr_data(0x0D);
    lcd_wr_data(0x00);
    lcd_wr_data(0x0D);
    lcd_wr_data(0x00);
    lcd_wr_data(0x11);
    lcd_wr_data(0x00);
    lcd_wr_data(0x19);
    lcd_wr_data(0x00);
    lcd_wr_data(0x21);
    lcd_wr_data(0x00);
    lcd_wr_data(0x2D);
    lcd_wr_data(0x00);
    lcd_wr_data(0x3D);
    lcd_wr_data(0x00);
    lcd_wr_data(0x5D);
    lcd_wr_data(0x00);
    lcd_wr_data(0x5D);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xB1);
    lcd_wr_data(0x80);
    lcd_wr_data(0x00);
    lcd_wr_data(0x8B);
    lcd_wr_data(0x00);
    lcd_wr_data(0x96);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xB2);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x02);
    lcd_wr_data(0x00);
    lcd_wr_data(0x03);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xB3);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xB4);
    lcd_wr_data(0x8B);
    lcd_wr_data(0x00);
    lcd_wr_data(0x96);
    lcd_wr_data(0x00);
    lcd_wr_data(0xA1);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xB5);
    lcd_wr_data(0x02);
    lcd_wr_data(0x00);
    lcd_wr_data(0x03);
    lcd_wr_data(0x00);
    lcd_wr_data(0x04);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xB6);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xB7);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x3F);
    lcd_wr_data(0x00);
    lcd_wr_data(0x5E);
    lcd_wr_data(0x00);
    lcd_wr_data(0x64);
    lcd_wr_data(0x00);
    lcd_wr_data(0x8C);
    lcd_wr_data(0x00);
    lcd_wr_data(0xAC);
    lcd_wr_data(0x00);
    lcd_wr_data(0xDC);
    lcd_wr_data(0x00);
    lcd_wr_data(0x70);
    lcd_wr_data(0x00);
    lcd_wr_data(0x90);
    lcd_wr_data(0x00);
    lcd_wr_data(0xEB);
    lcd_wr_data(0x00);
    lcd_wr_data(0xDC);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xB8);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xBA);
    lcd_wr_data(0x24);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xC1);
    lcd_wr_data(0x20);
    lcd_wr_data(0x00);
    lcd_wr_data(0x54);
    lcd_wr_data(0x00);
    lcd_wr_data(0xFF);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xC2);
    lcd_wr_data(0x0A);
    lcd_wr_data(0x00);
    lcd_wr_data(0x04);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xC3);
    lcd_wr_data(0x3C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x3A);
    lcd_wr_data(0x00);
    lcd_wr_data(0x39);
    lcd_wr_data(0x00);
    lcd_wr_data(0x37);
    lcd_wr_data(0x00);
    lcd_wr_data(0x3C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x36);
    lcd_wr_data(0x00);
    lcd_wr_data(0x32);
    lcd_wr_data(0x00);
    lcd_wr_data(0x2F);
    lcd_wr_data(0x00);
    lcd_wr_data(0x2C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x29);
    lcd_wr_data(0x00);
    lcd_wr_data(0x26);
    lcd_wr_data(0x00);
    lcd_wr_data(0x24);
    lcd_wr_data(0x00);
    lcd_wr_data(0x24);
    lcd_wr_data(0x00);
    lcd_wr_data(0x23);
    lcd_wr_data(0x00);
    lcd_wr_data(0x3C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x36);
    lcd_wr_data(0x00);
    lcd_wr_data(0x32);
    lcd_wr_data(0x00);
    lcd_wr_data(0x2F);
    lcd_wr_data(0x00);
    lcd_wr_data(0x2C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x29);
    lcd_wr_data(0x00);
    lcd_wr_data(0x26);
    lcd_wr_data(0x00);
    lcd_wr_data(0x24);
    lcd_wr_data(0x00);
    lcd_wr_data(0x24);
    lcd_wr_data(0x00);
    lcd_wr_data(0x23);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xC4);
    lcd_wr_data(0x62);
    lcd_wr_data(0x00);
    lcd_wr_data(0x05);
    lcd_wr_data(0x00);
    lcd_wr_data(0x84);
    lcd_wr_data(0x00);
    lcd_wr_data(0xF0);
    lcd_wr_data(0x00);
    lcd_wr_data(0x18);
    lcd_wr_data(0x00);
    lcd_wr_data(0xA4);
    lcd_wr_data(0x00);
    lcd_wr_data(0x18);
    lcd_wr_data(0x00);
    lcd_wr_data(0x50);
    lcd_wr_data(0x00);
    lcd_wr_data(0x0C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x17);
    lcd_wr_data(0x00);
    lcd_wr_data(0x95);
    lcd_wr_data(0x00);
    lcd_wr_data(0xF3);
    lcd_wr_data(0x00);
    lcd_wr_data(0xE6);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xC5);
    lcd_wr_data(0x32);
    lcd_wr_data(0x00);
    lcd_wr_data(0x44);
    lcd_wr_data(0x00);
    lcd_wr_data(0x65);
    lcd_wr_data(0x00);
    lcd_wr_data(0x76);
    lcd_wr_data(0x00);
    lcd_wr_data(0x88);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xC6);
    lcd_wr_data(0x20);
    lcd_wr_data(0x00);
    lcd_wr_data(0x17);
    lcd_wr_data(0x00);
    lcd_wr_data(0x01);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xC7);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xC8);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xC9);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xE0);
    lcd_wr_data(0x16);
    lcd_wr_data(0x00);
    lcd_wr_data(0x1C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x21);
    lcd_wr_data(0x00);
    lcd_wr_data(0x36);
    lcd_wr_data(0x00);
    lcd_wr_data(0x46);
    lcd_wr_data(0x00);
    lcd_wr_data(0x52);
    lcd_wr_data(0x00);
    lcd_wr_data(0x64);
    lcd_wr_data(0x00);
    lcd_wr_data(0x7A);
    lcd_wr_data(0x00);
    lcd_wr_data(0x8B);
    lcd_wr_data(0x00);
    lcd_wr_data(0x99);
    lcd_wr_data(0x00);
    lcd_wr_data(0xA8);
    lcd_wr_data(0x00);
    lcd_wr_data(0xB9);
    lcd_wr_data(0x00);
    lcd_wr_data(0xC4);
    lcd_wr_data(0x00);
    lcd_wr_data(0xCA);
    lcd_wr_data(0x00);
    lcd_wr_data(0xD2);
    lcd_wr_data(0x00);
    lcd_wr_data(0xD9);
    lcd_wr_data(0x00);
    lcd_wr_data(0xE0);
    lcd_wr_data(0x00);
    lcd_wr_data(0xF3);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xE1);
    lcd_wr_data(0x16);
    lcd_wr_data(0x00);
    lcd_wr_data(0x1C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x22);
    lcd_wr_data(0x00);
    lcd_wr_data(0x36);
    lcd_wr_data(0x00);
    lcd_wr_data(0x45);
    lcd_wr_data(0x00);
    lcd_wr_data(0x52);
    lcd_wr_data(0x00);
    lcd_wr_data(0x64);
    lcd_wr_data(0x00);
    lcd_wr_data(0x7A);
    lcd_wr_data(0x00);
    lcd_wr_data(0x8B);
    lcd_wr_data(0x00);
    lcd_wr_data(0x99);
    lcd_wr_data(0x00);
    lcd_wr_data(0xA8);
    lcd_wr_data(0x00);
    lcd_wr_data(0xB9);
    lcd_wr_data(0x00);
    lcd_wr_data(0xC4);
    lcd_wr_data(0x00);
    lcd_wr_data(0xCA);
    lcd_wr_data(0x00);
    lcd_wr_data(0xD2);
    lcd_wr_data(0x00);
    lcd_wr_data(0xD8);
    lcd_wr_data(0x00);
    lcd_wr_data(0xE0);
    lcd_wr_data(0x00);
    lcd_wr_data(0xF3);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xE2);
    lcd_wr_data(0x05);
    lcd_wr_data(0x00);
    lcd_wr_data(0x0B);
    lcd_wr_data(0x00);
    lcd_wr_data(0x1B);
    lcd_wr_data(0x00);
    lcd_wr_data(0x34);
    lcd_wr_data(0x00);
    lcd_wr_data(0x44);
    lcd_wr_data(0x00);
    lcd_wr_data(0x4F);
    lcd_wr_data(0x00);
    lcd_wr_data(0x61);
    lcd_wr_data(0x00);
    lcd_wr_data(0x79);
    lcd_wr_data(0x00);
    lcd_wr_data(0x88);
    lcd_wr_data(0x00);
    lcd_wr_data(0x97);
    lcd_wr_data(0x00);
    lcd_wr_data(0xA6);
    lcd_wr_data(0x00);
    lcd_wr_data(0xB7);
    lcd_wr_data(0x00);
    lcd_wr_data(0xC2);
    lcd_wr_data(0x00);
    lcd_wr_data(0xC7);
    lcd_wr_data(0x00);
    lcd_wr_data(0xD1);
    lcd_wr_data(0x00);
    lcd_wr_data(0xD6);
    lcd_wr_data(0x00);
    lcd_wr_data(0xDD);
    lcd_wr_data(0x00);
    lcd_wr_data(0xF3);
    lcd_wr_data(0x00);
    lcd_wr_regno(0xE3);
    lcd_wr_data(0x05);
    lcd_wr_data(0x00);
    lcd_wr_data(0xA);
    lcd_wr_data(0x00);
    lcd_wr_data(0x1C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x33);
    lcd_wr_data(0x00);
    lcd_wr_data(0x44);
    lcd_wr_data(0x00);
    lcd_wr_data(0x50);
    lcd_wr_data(0x00);
    lcd_wr_data(0x62);
    lcd_wr_data(0x00);
    lcd_wr_data(0x78);
    lcd_wr_data(0x00);
    lcd_wr_data(0x88);
    lcd_wr_data(0x00);
    lcd_wr_data(0x97);
    lcd_wr_data(0x00);
    lcd_wr_data(0xA6);
    lcd_wr_data(0x00);
    lcd_wr_data(0xB7);
    lcd_wr_data(0x00);
    lcd_wr_data(0xC2);
    lcd_wr_data(0x00);
    lcd_wr_data(0xC7);
    lcd_wr_data(0x00);
    lcd_wr_data(0xD1);
    lcd_wr_data(0x00);
    lcd_wr_data(0xD5);
    lcd_wr_data(0x00);
    lcd_wr_data(0xDD);
    lcd_wr_data(0x00);
    lcd_wr_data(0xF3);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xE4);
    lcd_wr_data(0x01);
    lcd_wr_data(0x00);
    lcd_wr_data(0x01);
    lcd_wr_data(0x00);
    lcd_wr_data(0x02);
    lcd_wr_data(0x00);
    lcd_wr_data(0x2A);
    lcd_wr_data(0x00);
    lcd_wr_data(0x3C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x4B);
    lcd_wr_data(0x00);
    lcd_wr_data(0x5D);
    lcd_wr_data(0x00);
    lcd_wr_data(0x74);
    lcd_wr_data(0x00);
    lcd_wr_data(0x84);
    lcd_wr_data(0x00);
    lcd_wr_data(0x93);
    lcd_wr_data(0x00);
    lcd_wr_data(0xA2);
    lcd_wr_data(0x00);
    lcd_wr_data(0xB3);
    lcd_wr_data(0x00);
    lcd_wr_data(0xBE);
    lcd_wr_data(0x00);
    lcd_wr_data(0xC4);
    lcd_wr_data(0x00);
    lcd_wr_data(0xCD);
    lcd_wr_data(0x00);
    lcd_wr_data(0xD3);
    lcd_wr_data(0x00);
    lcd_wr_data(0xDD);
    lcd_wr_data(0x00);
    lcd_wr_data(0xF3);
    lcd_wr_data(0x00);
    lcd_wr_regno(0xE5);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x02);
    lcd_wr_data(0x00);
    lcd_wr_data(0x29);
    lcd_wr_data(0x00);
    lcd_wr_data(0x3C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x4B);
    lcd_wr_data(0x00);
    lcd_wr_data(0x5D);
    lcd_wr_data(0x00);
    lcd_wr_data(0x74);
    lcd_wr_data(0x00);
    lcd_wr_data(0x84);
    lcd_wr_data(0x00);
    lcd_wr_data(0x93);
    lcd_wr_data(0x00);
    lcd_wr_data(0xA2);
    lcd_wr_data(0x00);
    lcd_wr_data(0xB3);
    lcd_wr_data(0x00);
    lcd_wr_data(0xBE);
    lcd_wr_data(0x00);
    lcd_wr_data(0xC4);
    lcd_wr_data(0x00);
    lcd_wr_data(0xCD);
    lcd_wr_data(0x00);
    lcd_wr_data(0xD3);
    lcd_wr_data(0x00);
    lcd_wr_data(0xDC);
    lcd_wr_data(0x00);
    lcd_wr_data(0xF3);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xE6);
    lcd_wr_data(0x11);
    lcd_wr_data(0x00);
    lcd_wr_data(0x34);
    lcd_wr_data(0x00);
    lcd_wr_data(0x56);
    lcd_wr_data(0x00);
    lcd_wr_data(0x76);
    lcd_wr_data(0x00);
    lcd_wr_data(0x77);
    lcd_wr_data(0x00);
    lcd_wr_data(0x66);
    lcd_wr_data(0x00);
    lcd_wr_data(0x88);
    lcd_wr_data(0x00);
    lcd_wr_data(0x99);
    lcd_wr_data(0x00);
    lcd_wr_data(0xBB);
    lcd_wr_data(0x00);
    lcd_wr_data(0x99);
    lcd_wr_data(0x00);
    lcd_wr_data(0x66);
    lcd_wr_data(0x00);
    lcd_wr_data(0x55);
    lcd_wr_data(0x00);
    lcd_wr_data(0x55);
    lcd_wr_data(0x00);
    lcd_wr_data(0x45);
    lcd_wr_data(0x00);
    lcd_wr_data(0x43);
    lcd_wr_data(0x00);
    lcd_wr_data(0x44);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xE7);
    lcd_wr_data(0x32);
    lcd_wr_data(0x00);
    lcd_wr_data(0x55);
    lcd_wr_data(0x00);
    lcd_wr_data(0x76);
    lcd_wr_data(0x00);
    lcd_wr_data(0x66);
    lcd_wr_data(0x00);
    lcd_wr_data(0x67);
    lcd_wr_data(0x00);
    lcd_wr_data(0x67);
    lcd_wr_data(0x00);
    lcd_wr_data(0x87);
    lcd_wr_data(0x00);
    lcd_wr_data(0x99);
    lcd_wr_data(0x00);
    lcd_wr_data(0xBB);
    lcd_wr_data(0x00);
    lcd_wr_data(0x99);
    lcd_wr_data(0x00);
    lcd_wr_data(0x77);
    lcd_wr_data(0x00);
    lcd_wr_data(0x44);
    lcd_wr_data(0x00);
    lcd_wr_data(0x56);
    lcd_wr_data(0x00);
    lcd_wr_data(0x23);
    lcd_wr_data(0x00);
    lcd_wr_data(0x33);
    lcd_wr_data(0x00);
    lcd_wr_data(0x45);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xE8);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x99);
    lcd_wr_data(0x00);
    lcd_wr_data(0x87);
    lcd_wr_data(0x00);
    lcd_wr_data(0x88);
    lcd_wr_data(0x00);
    lcd_wr_data(0x77);
    lcd_wr_data(0x00);
    lcd_wr_data(0x66);
    lcd_wr_data(0x00);
    lcd_wr_data(0x88);
    lcd_wr_data(0x00);
    lcd_wr_data(0xAA);
    lcd_wr_data(0x00);
    lcd_wr_data(0xBB);
    lcd_wr_data(0x00);
    lcd_wr_data(0x99);
    lcd_wr_data(0x00);
    lcd_wr_data(0x66);
    lcd_wr_data(0x00);
    lcd_wr_data(0x55);
    lcd_wr_data(0x00);
    lcd_wr_data(0x55);
    lcd_wr_data(0x00);
    lcd_wr_data(0x44);
    lcd_wr_data(0x00);
    lcd_wr_data(0x44);
    lcd_wr_data(0x00);
    lcd_wr_data(0x55);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xE9);
    lcd_wr_data(0xAA);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);

    lcd_wr_regno(0x00);
    lcd_wr_data(0xAA);

    lcd_wr_regno(0xCF);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xF0);
    lcd_wr_data(0x00);
    lcd_wr_data(0x50);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xF3);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xF9);
    lcd_wr_data(0x06);
    lcd_wr_data(0x10);
    lcd_wr_data(0x29);
    lcd_wr_data(0x00);

    lcd_wr_regno(0x3A);
    lcd_wr_data(0x55);  /* 66 */

    lcd_wr_regno(0x11);
    delay_ms(100);
    lcd_wr_regno(0x29);
    lcd_wr_regno(0x35);
    lcd_wr_data(0x00);

    lcd_wr_regno(0x51);
    lcd_wr_data(0xFF);
    lcd_wr_regno(0x53);
    lcd_wr_data(0x2C);
    lcd_wr_regno(0x55);
    lcd_wr_data(0x82);
    lcd_wr_regno(0x2c);
}

/**
 * @brief       NT35510锟侥达拷锟斤拷锟斤拷始锟斤拷锟斤拷锟斤拷
 * @param       锟斤拷
 * @retval      锟斤拷
 */
void lcd_ex_nt35510_reginit(void) {
    lcd_write_reg(0xF000, 0x55);
    lcd_write_reg(0xF001, 0xAA);
    lcd_write_reg(0xF002, 0x52);
    lcd_write_reg(0xF003, 0x08);
    lcd_write_reg(0xF004, 0x01);
    /* AVDD Set AVDD 5.2V */
    lcd_write_reg(0xB000, 0x0D);
    lcd_write_reg(0xB001, 0x0D);
    lcd_write_reg(0xB002, 0x0D);
    /* AVDD ratio */
    lcd_write_reg(0xB600, 0x34);
    lcd_write_reg(0xB601, 0x34);
    lcd_write_reg(0xB602, 0x34);
    /* AVEE -5.2V */
    lcd_write_reg(0xB100, 0x0D);
    lcd_write_reg(0xB101, 0x0D);
    lcd_write_reg(0xB102, 0x0D);
    /* AVEE ratio */
    lcd_write_reg(0xB700, 0x34);
    lcd_write_reg(0xB701, 0x34);
    lcd_write_reg(0xB702, 0x34);
    /* VCL -2.5V */
    lcd_write_reg(0xB200, 0x00);
    lcd_write_reg(0xB201, 0x00);
    lcd_write_reg(0xB202, 0x00);
    /* VCL ratio */
    lcd_write_reg(0xB800, 0x24);
    lcd_write_reg(0xB801, 0x24);
    lcd_write_reg(0xB802, 0x24);
    /* VGH 15V (Free pump) */
    lcd_write_reg(0xBF00, 0x01);
    lcd_write_reg(0xB300, 0x0F);
    lcd_write_reg(0xB301, 0x0F);
    lcd_write_reg(0xB302, 0x0F);
    /* VGH ratio */
    lcd_write_reg(0xB900, 0x34);
    lcd_write_reg(0xB901, 0x34);
    lcd_write_reg(0xB902, 0x34);
    /* VGL_REG -10V */
    lcd_write_reg(0xB500, 0x08);
    lcd_write_reg(0xB501, 0x08);
    lcd_write_reg(0xB502, 0x08);
    lcd_write_reg(0xC200, 0x03);
    /* VGLX ratio */
    lcd_write_reg(0xBA00, 0x24);
    lcd_write_reg(0xBA01, 0x24);
    lcd_write_reg(0xBA02, 0x24);
    /* VGMP/VGSP 4.5V/0V */
    lcd_write_reg(0xBC00, 0x00);
    lcd_write_reg(0xBC01, 0x78);
    lcd_write_reg(0xBC02, 0x00);
    /* VGMN/VGSN -4.5V/0V */
    lcd_write_reg(0xBD00, 0x00);
    lcd_write_reg(0xBD01, 0x78);
    lcd_write_reg(0xBD02, 0x00);
    /* VCOM */
    lcd_write_reg(0xBE00, 0x00);
    lcd_write_reg(0xBE01, 0x64);
    /* Gamma Setting */
    lcd_write_reg(0xD100, 0x00);
    lcd_write_reg(0xD101, 0x33);
    lcd_write_reg(0xD102, 0x00);
    lcd_write_reg(0xD103, 0x34);
    lcd_write_reg(0xD104, 0x00);
    lcd_write_reg(0xD105, 0x3A);
    lcd_write_reg(0xD106, 0x00);
    lcd_write_reg(0xD107, 0x4A);
    lcd_write_reg(0xD108, 0x00);
    lcd_write_reg(0xD109, 0x5C);
    lcd_write_reg(0xD10A, 0x00);
    lcd_write_reg(0xD10B, 0x81);
    lcd_write_reg(0xD10C, 0x00);
    lcd_write_reg(0xD10D, 0xA6);
    lcd_write_reg(0xD10E, 0x00);
    lcd_write_reg(0xD10F, 0xE5);
    lcd_write_reg(0xD110, 0x01);
    lcd_write_reg(0xD111, 0x13);
    lcd_write_reg(0xD112, 0x01);
    lcd_write_reg(0xD113, 0x54);
    lcd_write_reg(0xD114, 0x01);
    lcd_write_reg(0xD115, 0x82);
    lcd_write_reg(0xD116, 0x01);
    lcd_write_reg(0xD117, 0xCA);
    lcd_write_reg(0xD118, 0x02);
    lcd_write_reg(0xD119, 0x00);
    lcd_write_reg(0xD11A, 0x02);
    lcd_write_reg(0xD11B, 0x01);
    lcd_write_reg(0xD11C, 0x02);
    lcd_write_reg(0xD11D, 0x34);
    lcd_write_reg(0xD11E, 0x02);
    lcd_write_reg(0xD11F, 0x67);
    lcd_write_reg(0xD120, 0x02);
    lcd_write_reg(0xD121, 0x84);
    lcd_write_reg(0xD122, 0x02);
    lcd_write_reg(0xD123, 0xA4);
    lcd_write_reg(0xD124, 0x02);
    lcd_write_reg(0xD125, 0xB7);
    lcd_write_reg(0xD126, 0x02);
    lcd_write_reg(0xD127, 0xCF);
    lcd_write_reg(0xD128, 0x02);
    lcd_write_reg(0xD129, 0xDE);
    lcd_write_reg(0xD12A, 0x02);
    lcd_write_reg(0xD12B, 0xF2);
    lcd_write_reg(0xD12C, 0x02);
    lcd_write_reg(0xD12D, 0xFE);
    lcd_write_reg(0xD12E, 0x03);
    lcd_write_reg(0xD12F, 0x10);
    lcd_write_reg(0xD130, 0x03);
    lcd_write_reg(0xD131, 0x33);
    lcd_write_reg(0xD132, 0x03);
    lcd_write_reg(0xD133, 0x6D);
    lcd_write_reg(0xD200, 0x00);
    lcd_write_reg(0xD201, 0x33);
    lcd_write_reg(0xD202, 0x00);
    lcd_write_reg(0xD203, 0x34);
    lcd_write_reg(0xD204, 0x00);
    lcd_write_reg(0xD205, 0x3A);
    lcd_write_reg(0xD206, 0x00);
    lcd_write_reg(0xD207, 0x4A);
    lcd_write_reg(0xD208, 0x00);
    lcd_write_reg(0xD209, 0x5C);
    lcd_write_reg(0xD20A, 0x00);

    lcd_write_reg(0xD20B, 0x81);
    lcd_write_reg(0xD20C, 0x00);
    lcd_write_reg(0xD20D, 0xA6);
    lcd_write_reg(0xD20E, 0x00);
    lcd_write_reg(0xD20F, 0xE5);
    lcd_write_reg(0xD210, 0x01);
    lcd_write_reg(0xD211, 0x13);
    lcd_write_reg(0xD212, 0x01);
    lcd_write_reg(0xD213, 0x54);
    lcd_write_reg(0xD214, 0x01);
    lcd_write_reg(0xD215, 0x82);
    lcd_write_reg(0xD216, 0x01);
    lcd_write_reg(0xD217, 0xCA);
    lcd_write_reg(0xD218, 0x02);
    lcd_write_reg(0xD219, 0x00);
    lcd_write_reg(0xD21A, 0x02);
    lcd_write_reg(0xD21B, 0x01);
    lcd_write_reg(0xD21C, 0x02);
    lcd_write_reg(0xD21D, 0x34);
    lcd_write_reg(0xD21E, 0x02);
    lcd_write_reg(0xD21F, 0x67);
    lcd_write_reg(0xD220, 0x02);
    lcd_write_reg(0xD221, 0x84);
    lcd_write_reg(0xD222, 0x02);
    lcd_write_reg(0xD223, 0xA4);
    lcd_write_reg(0xD224, 0x02);
    lcd_write_reg(0xD225, 0xB7);
    lcd_write_reg(0xD226, 0x02);
    lcd_write_reg(0xD227, 0xCF);
    lcd_write_reg(0xD228, 0x02);
    lcd_write_reg(0xD229, 0xDE);
    lcd_write_reg(0xD22A, 0x02);
    lcd_write_reg(0xD22B, 0xF2);
    lcd_write_reg(0xD22C, 0x02);
    lcd_write_reg(0xD22D, 0xFE);
    lcd_write_reg(0xD22E, 0x03);
    lcd_write_reg(0xD22F, 0x10);
    lcd_write_reg(0xD230, 0x03);
    lcd_write_reg(0xD231, 0x33);
    lcd_write_reg(0xD232, 0x03);
    lcd_write_reg(0xD233, 0x6D);
    lcd_write_reg(0xD300, 0x00);
    lcd_write_reg(0xD301, 0x33);
    lcd_write_reg(0xD302, 0x00);
    lcd_write_reg(0xD303, 0x34);
    lcd_write_reg(0xD304, 0x00);
    lcd_write_reg(0xD305, 0x3A);
    lcd_write_reg(0xD306, 0x00);
    lcd_write_reg(0xD307, 0x4A);
    lcd_write_reg(0xD308, 0x00);
    lcd_write_reg(0xD309, 0x5C);
    lcd_write_reg(0xD30A, 0x00);

    lcd_write_reg(0xD30B, 0x81);
    lcd_write_reg(0xD30C, 0x00);
    lcd_write_reg(0xD30D, 0xA6);
    lcd_write_reg(0xD30E, 0x00);
    lcd_write_reg(0xD30F, 0xE5);
    lcd_write_reg(0xD310, 0x01);
    lcd_write_reg(0xD311, 0x13);
    lcd_write_reg(0xD312, 0x01);
    lcd_write_reg(0xD313, 0x54);
    lcd_write_reg(0xD314, 0x01);
    lcd_write_reg(0xD315, 0x82);
    lcd_write_reg(0xD316, 0x01);
    lcd_write_reg(0xD317, 0xCA);
    lcd_write_reg(0xD318, 0x02);
    lcd_write_reg(0xD319, 0x00);
    lcd_write_reg(0xD31A, 0x02);
    lcd_write_reg(0xD31B, 0x01);
    lcd_write_reg(0xD31C, 0x02);
    lcd_write_reg(0xD31D, 0x34);
    lcd_write_reg(0xD31E, 0x02);
    lcd_write_reg(0xD31F, 0x67);
    lcd_write_reg(0xD320, 0x02);
    lcd_write_reg(0xD321, 0x84);
    lcd_write_reg(0xD322, 0x02);
    lcd_write_reg(0xD323, 0xA4);
    lcd_write_reg(0xD324, 0x02);
    lcd_write_reg(0xD325, 0xB7);
    lcd_write_reg(0xD326, 0x02);
    lcd_write_reg(0xD327, 0xCF);
    lcd_write_reg(0xD328, 0x02);
    lcd_write_reg(0xD329, 0xDE);
    lcd_write_reg(0xD32A, 0x02);
    lcd_write_reg(0xD32B, 0xF2);
    lcd_write_reg(0xD32C, 0x02);
    lcd_write_reg(0xD32D, 0xFE);
    lcd_write_reg(0xD32E, 0x03);
    lcd_write_reg(0xD32F, 0x10);
    lcd_write_reg(0xD330, 0x03);
    lcd_write_reg(0xD331, 0x33);
    lcd_write_reg(0xD332, 0x03);
    lcd_write_reg(0xD333, 0x6D);
    lcd_write_reg(0xD400, 0x00);
    lcd_write_reg(0xD401, 0x33);
    lcd_write_reg(0xD402, 0x00);
    lcd_write_reg(0xD403, 0x34);
    lcd_write_reg(0xD404, 0x00);
    lcd_write_reg(0xD405, 0x3A);
    lcd_write_reg(0xD406, 0x00);
    lcd_write_reg(0xD407, 0x4A);
    lcd_write_reg(0xD408, 0x00);
    lcd_write_reg(0xD409, 0x5C);
    lcd_write_reg(0xD40A, 0x00);
    lcd_write_reg(0xD40B, 0x81);

    lcd_write_reg(0xD40C, 0x00);
    lcd_write_reg(0xD40D, 0xA6);
    lcd_write_reg(0xD40E, 0x00);
    lcd_write_reg(0xD40F, 0xE5);
    lcd_write_reg(0xD410, 0x01);
    lcd_write_reg(0xD411, 0x13);
    lcd_write_reg(0xD412, 0x01);
    lcd_write_reg(0xD413, 0x54);
    lcd_write_reg(0xD414, 0x01);
    lcd_write_reg(0xD415, 0x82);
    lcd_write_reg(0xD416, 0x01);
    lcd_write_reg(0xD417, 0xCA);
    lcd_write_reg(0xD418, 0x02);
    lcd_write_reg(0xD419, 0x00);
    lcd_write_reg(0xD41A, 0x02);
    lcd_write_reg(0xD41B, 0x01);
    lcd_write_reg(0xD41C, 0x02);
    lcd_write_reg(0xD41D, 0x34);
    lcd_write_reg(0xD41E, 0x02);
    lcd_write_reg(0xD41F, 0x67);
    lcd_write_reg(0xD420, 0x02);
    lcd_write_reg(0xD421, 0x84);
    lcd_write_reg(0xD422, 0x02);
    lcd_write_reg(0xD423, 0xA4);
    lcd_write_reg(0xD424, 0x02);
    lcd_write_reg(0xD425, 0xB7);
    lcd_write_reg(0xD426, 0x02);
    lcd_write_reg(0xD427, 0xCF);
    lcd_write_reg(0xD428, 0x02);
    lcd_write_reg(0xD429, 0xDE);
    lcd_write_reg(0xD42A, 0x02);
    lcd_write_reg(0xD42B, 0xF2);
    lcd_write_reg(0xD42C, 0x02);
    lcd_write_reg(0xD42D, 0xFE);
    lcd_write_reg(0xD42E, 0x03);
    lcd_write_reg(0xD42F, 0x10);
    lcd_write_reg(0xD430, 0x03);
    lcd_write_reg(0xD431, 0x33);
    lcd_write_reg(0xD432, 0x03);
    lcd_write_reg(0xD433, 0x6D);
    lcd_write_reg(0xD500, 0x00);
    lcd_write_reg(0xD501, 0x33);
    lcd_write_reg(0xD502, 0x00);
    lcd_write_reg(0xD503, 0x34);
    lcd_write_reg(0xD504, 0x00);
    lcd_write_reg(0xD505, 0x3A);
    lcd_write_reg(0xD506, 0x00);
    lcd_write_reg(0xD507, 0x4A);
    lcd_write_reg(0xD508, 0x00);
    lcd_write_reg(0xD509, 0x5C);
    lcd_write_reg(0xD50A, 0x00);
    lcd_write_reg(0xD50B, 0x81);

    lcd_write_reg(0xD50C, 0x00);
    lcd_write_reg(0xD50D, 0xA6);
    lcd_write_reg(0xD50E, 0x00);
    lcd_write_reg(0xD50F, 0xE5);
    lcd_write_reg(0xD510, 0x01);
    lcd_write_reg(0xD511, 0x13);
    lcd_write_reg(0xD512, 0x01);
    lcd_write_reg(0xD513, 0x54);
    lcd_write_reg(0xD514, 0x01);
    lcd_write_reg(0xD515, 0x82);
    lcd_write_reg(0xD516, 0x01);
    lcd_write_reg(0xD517, 0xCA);
    lcd_write_reg(0xD518, 0x02);
    lcd_write_reg(0xD519, 0x00);
    lcd_write_reg(0xD51A, 0x02);
    lcd_write_reg(0xD51B, 0x01);
    lcd_write_reg(0xD51C, 0x02);
    lcd_write_reg(0xD51D, 0x34);
    lcd_write_reg(0xD51E, 0x02);
    lcd_write_reg(0xD51F, 0x67);
    lcd_write_reg(0xD520, 0x02);
    lcd_write_reg(0xD521, 0x84);
    lcd_write_reg(0xD522, 0x02);
    lcd_write_reg(0xD523, 0xA4);
    lcd_write_reg(0xD524, 0x02);
    lcd_write_reg(0xD525, 0xB7);
    lcd_write_reg(0xD526, 0x02);
    lcd_write_reg(0xD527, 0xCF);
    lcd_write_reg(0xD528, 0x02);
    lcd_write_reg(0xD529, 0xDE);
    lcd_write_reg(0xD52A, 0x02);
    lcd_write_reg(0xD52B, 0xF2);
    lcd_write_reg(0xD52C, 0x02);
    lcd_write_reg(0xD52D, 0xFE);
    lcd_write_reg(0xD52E, 0x03);
    lcd_write_reg(0xD52F, 0x10);
    lcd_write_reg(0xD530, 0x03);
    lcd_write_reg(0xD531, 0x33);
    lcd_write_reg(0xD532, 0x03);
    lcd_write_reg(0xD533, 0x6D);
    lcd_write_reg(0xD600, 0x00);
    lcd_write_reg(0xD601, 0x33);
    lcd_write_reg(0xD602, 0x00);
    lcd_write_reg(0xD603, 0x34);
    lcd_write_reg(0xD604, 0x00);
    lcd_write_reg(0xD605, 0x3A);
    lcd_write_reg(0xD606, 0x00);
    lcd_write_reg(0xD607, 0x4A);
    lcd_write_reg(0xD608, 0x00);
    lcd_write_reg(0xD609, 0x5C);
    lcd_write_reg(0xD60A, 0x00);
    lcd_write_reg(0xD60B, 0x81);

    lcd_write_reg(0xD60C, 0x00);
    lcd_write_reg(0xD60D, 0xA6);
    lcd_write_reg(0xD60E, 0x00);
    lcd_write_reg(0xD60F, 0xE5);
    lcd_write_reg(0xD610, 0x01);
    lcd_write_reg(0xD611, 0x13);
    lcd_write_reg(0xD612, 0x01);
    lcd_write_reg(0xD613, 0x54);
    lcd_write_reg(0xD614, 0x01);
    lcd_write_reg(0xD615, 0x82);
    lcd_write_reg(0xD616, 0x01);
    lcd_write_reg(0xD617, 0xCA);
    lcd_write_reg(0xD618, 0x02);
    lcd_write_reg(0xD619, 0x00);
    lcd_write_reg(0xD61A, 0x02);
    lcd_write_reg(0xD61B, 0x01);
    lcd_write_reg(0xD61C, 0x02);
    lcd_write_reg(0xD61D, 0x34);
    lcd_write_reg(0xD61E, 0x02);
    lcd_write_reg(0xD61F, 0x67);
    lcd_write_reg(0xD620, 0x02);
    lcd_write_reg(0xD621, 0x84);
    lcd_write_reg(0xD622, 0x02);
    lcd_write_reg(0xD623, 0xA4);
    lcd_write_reg(0xD624, 0x02);
    lcd_write_reg(0xD625, 0xB7);
    lcd_write_reg(0xD626, 0x02);
    lcd_write_reg(0xD627, 0xCF);
    lcd_write_reg(0xD628, 0x02);
    lcd_write_reg(0xD629, 0xDE);
    lcd_write_reg(0xD62A, 0x02);
    lcd_write_reg(0xD62B, 0xF2);
    lcd_write_reg(0xD62C, 0x02);
    lcd_write_reg(0xD62D, 0xFE);
    lcd_write_reg(0xD62E, 0x03);
    lcd_write_reg(0xD62F, 0x10);
    lcd_write_reg(0xD630, 0x03);
    lcd_write_reg(0xD631, 0x33);
    lcd_write_reg(0xD632, 0x03);
    lcd_write_reg(0xD633, 0x6D);
    /* LV2 Page 0 enable */
    lcd_write_reg(0xF000, 0x55);
    lcd_write_reg(0xF001, 0xAA);
    lcd_write_reg(0xF002, 0x52);
    lcd_write_reg(0xF003, 0x08);
    lcd_write_reg(0xF004, 0x00);
    /* Display control */
    lcd_write_reg(0xB100, 0xCC);
    lcd_write_reg(0xB101, 0x00);
    /* Source hold time */
    lcd_write_reg(0xB600, 0x05);
    /* Gate EQ control */
    lcd_write_reg(0xB700, 0x70);
    lcd_write_reg(0xB701, 0x70);
    /* Source EQ control (Mode 2) */
    lcd_write_reg(0xB800, 0x01);
    lcd_write_reg(0xB801, 0x03);
    lcd_write_reg(0xB802, 0x03);
    lcd_write_reg(0xB803, 0x03);
    /* Inversion mode (2-dot) */
    lcd_write_reg(0xBC00, 0x02);
    lcd_write_reg(0xBC01, 0x00);
    lcd_write_reg(0xBC02, 0x00);
    /* Timing control 4H w/ 4-delay */
    lcd_write_reg(0xC900, 0xD0);
    lcd_write_reg(0xC901, 0x02);
    lcd_write_reg(0xC902, 0x50);
    lcd_write_reg(0xC903, 0x50);
    lcd_write_reg(0xC904, 0x50);
    lcd_write_reg(0x3500, 0x00);
    lcd_write_reg(0x3A00, 0x55); /* 16-bit/pixel */
    lcd_wr_regno(0x1100);
    delay_us(120);
    lcd_wr_regno(0x2900);
}

/**
 * @brief       SSD1963锟侥达拷锟斤拷锟斤拷始锟斤拷锟斤拷锟斤拷
 * @param       锟斤拷
 * @retval      锟斤拷
 */
void lcd_ex_ssd1963_reginit(void) {
    lcd_wr_regno(
            0xE2); /* Set PLL with OSC = 10MHz (hardware),	Multiplier N = 35, 250MHz < VCO < 800MHz = OSC*(N+1), VCO = 300MHz */
    lcd_wr_data(0x1D);  /* 锟斤拷锟斤拷1 */
    lcd_wr_data(0x02);  /* 锟斤拷锟斤拷2 Divider M = 2, PLL = 300/(M+1) = 100MHz */
    lcd_wr_data(0x04);  /* 锟斤拷锟斤拷3 Validate M and N values */
    delay_us(100);
    lcd_wr_regno(0xE0); /*  Start PLL command */
    lcd_wr_data(0x01);  /*  enable PLL */
    delay_ms(10);
    lcd_wr_regno(0xE0); /*  Start PLL command again */
    lcd_wr_data(0x03);  /*  now, use PLL output as system clock */
    delay_ms(12);
    lcd_wr_regno(0x01); /* 锟斤拷位 */
    delay_ms(10);

    lcd_wr_regno(0xE6); /* 锟斤拷锟斤拷锟斤拷锟斤拷频锟斤拷,33Mhz */
    lcd_wr_data(0x2F);
    lcd_wr_data(0xFF);
    lcd_wr_data(0xFF);

    lcd_wr_regno(0xB0); /* 锟斤拷锟斤拷LCD模式 */
    lcd_wr_data(0x20);  /* 24位模式 */
    lcd_wr_data(0x00);  /* TFT 模式 */

    lcd_wr_data((SSD_HOR_RESOLUTION - 1) >> 8); /* 锟斤拷锟斤拷LCD水平锟斤拷锟斤拷 */
    lcd_wr_data(SSD_HOR_RESOLUTION - 1);
    lcd_wr_data((SSD_VER_RESOLUTION - 1) >> 8); /* 锟斤拷锟斤拷LCD锟斤拷直锟斤拷锟斤拷 */
    lcd_wr_data(SSD_VER_RESOLUTION - 1);
    lcd_wr_data(0x00);  /* RGB锟斤拷锟斤拷 */

    lcd_wr_regno(0xB4); /* Set horizontal period */
    lcd_wr_data((SSD_HT - 1) >> 8);
    lcd_wr_data(SSD_HT - 1);
    lcd_wr_data(SSD_HPS >> 8);
    lcd_wr_data(SSD_HPS);
    lcd_wr_data(SSD_HOR_PULSE_WIDTH - 1);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_regno(0xB6); /* Set vertical perio */
    lcd_wr_data((SSD_VT - 1) >> 8);
    lcd_wr_data(SSD_VT - 1);
    lcd_wr_data(SSD_VPS >> 8);
    lcd_wr_data(SSD_VPS);
    lcd_wr_data(SSD_VER_FRONT_PORCH - 1);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);

    lcd_wr_regno(0xF0); /* 锟斤拷锟斤拷SSD1963锟斤拷CPU锟接匡拷为16bit */
    lcd_wr_data(0x03);  /* 16-bit(565 format) data for 16bpp */

    lcd_wr_regno(0x29); /* 锟斤拷锟斤拷锟斤拷示 */
    /* 锟斤拷锟斤拷PWM锟斤拷锟�  锟斤拷锟斤拷通锟斤拷占锟秸比可碉拷 */
    lcd_wr_regno(0xD0); /* 锟斤拷锟斤拷锟皆讹拷锟斤拷平锟斤拷DBC */
    lcd_wr_data(0x00);  /* disable */

    lcd_wr_regno(0xBE); /* 锟斤拷锟斤拷PWM锟斤拷锟� */
    lcd_wr_data(0x05);  /* 1锟斤拷锟斤拷PWM频锟斤拷 */
    lcd_wr_data(0xFE);  /* 2锟斤拷锟斤拷PWM占锟秸憋拷 */
    lcd_wr_data(0x01);  /* 3锟斤拷锟斤拷C */
    lcd_wr_data(0x00);  /* 4锟斤拷锟斤拷D */
    lcd_wr_data(0x00);  /* 5锟斤拷锟斤拷E */
    lcd_wr_data(0x00);  /* 6锟斤拷锟斤拷F */

    lcd_wr_regno(0xB8); /* 锟斤拷锟斤拷GPIO锟斤拷锟斤拷 */
    lcd_wr_data(0x03);  /* 2锟斤拷IO锟斤拷锟斤拷锟矫筹拷锟斤拷锟� */
    lcd_wr_data(0x01);  /* GPIO使锟斤拷锟斤拷锟斤拷锟斤拷IO锟斤拷锟斤拷 */
    lcd_wr_regno(0xBA);
    lcd_wr_data(0x01);  /* GPIO[1:0]=01,锟斤拷锟斤拷LCD锟斤拷锟斤拷 */
}

/**
 * @brief       锟斤拷始锟斤拷LCD
 *   @note      锟矫筹拷始锟斤拷锟斤拷锟斤拷锟斤拷锟皆筹拷始锟斤拷锟斤拷锟斤拷锟酵号碉拷LCD(锟斤拷锟斤拷锟�.c锟侥硷拷锟斤拷前锟斤拷锟斤拷锟斤拷锟�)
 *
 * @param       锟斤拷
 * @retval      锟斤拷
 */
void lcd_init(void) {
    GPIO_InitTypeDef gpio_init_struct;
    FSMC_NORSRAM_TimingTypeDef fsmc_read_handle;
    FSMC_NORSRAM_TimingTypeDef fsmc_write_handle;

    LCD_CS_GPIO_CLK_ENABLE();   /* LCD_CS锟斤拷时锟斤拷使锟斤拷 */
    LCD_WR_GPIO_CLK_ENABLE();   /* LCD_WR锟斤拷时锟斤拷使锟斤拷 */
    LCD_RD_GPIO_CLK_ENABLE();   /* LCD_RD锟斤拷时锟斤拷使锟斤拷 */
    LCD_RS_GPIO_CLK_ENABLE();   /* LCD_RS锟斤拷时锟斤拷使锟斤拷 */
    LCD_BL_GPIO_CLK_ENABLE();   /* LCD_BL锟斤拷时锟斤拷使锟斤拷 */

    gpio_init_struct.Pin = LCD_CS_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* 锟斤拷锟届复锟斤拷 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 锟斤拷锟斤拷 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 锟斤拷锟斤拷 */
    gpio_init_struct.Alternate = GPIO_AF12_FSMC;            /* 锟斤拷锟斤拷为FSMC */
    HAL_GPIO_Init(LCD_CS_GPIO_PORT, &gpio_init_struct);     /* 锟斤拷始锟斤拷LCD_CS锟斤拷锟斤拷 */

    gpio_init_struct.Pin = LCD_WR_GPIO_PIN;
    HAL_GPIO_Init(LCD_WR_GPIO_PORT, &gpio_init_struct);     /* 锟斤拷始锟斤拷LCD_WR锟斤拷锟斤拷 */

    gpio_init_struct.Pin = LCD_RD_GPIO_PIN;
    HAL_GPIO_Init(LCD_RD_GPIO_PORT, &gpio_init_struct);     /* 锟斤拷始锟斤拷LCD_RD锟斤拷锟斤拷 */

    gpio_init_struct.Pin = LCD_RS_GPIO_PIN;
    HAL_GPIO_Init(LCD_RS_GPIO_PORT, &gpio_init_struct);     /* 锟斤拷始锟斤拷LCD_RS锟斤拷锟斤拷 */

    gpio_init_struct.Pin = LCD_BL_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 锟斤拷锟斤拷锟斤拷锟� */
    HAL_GPIO_Init(LCD_BL_GPIO_PORT, &gpio_init_struct);     /* LCD_BL锟斤拷锟斤拷模式锟斤拷锟斤拷(锟斤拷锟斤拷锟斤拷锟�) */

    g_sram_handle.Instance = FSMC_NORSRAM_DEVICE;
    g_sram_handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
    g_sram_handle.Init.NSBank = FSMC_NORSRAM_BANK4;                        /*使锟斤拷NE4*/
    g_sram_handle.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;     /*锟斤拷址/锟斤拷锟斤拷锟竭诧拷锟斤拷锟斤拷*/
    g_sram_handle.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;    /*16位锟斤拷锟捷匡拷锟�*/
    g_sram_handle.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;   /*锟角凤拷使锟斤拷突锟斤拷锟斤拷锟斤拷,锟斤拷锟斤拷同锟斤拷突锟斤拷锟芥储锟斤拷锟斤拷效,锟剿达拷未锟矫碉拷*/
    g_sram_handle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW; /*锟饺达拷锟脚号的硷拷锟斤拷,锟斤拷锟斤拷突锟斤拷模式锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷*/
    g_sram_handle.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;      /* 锟芥储锟斤拷锟斤拷锟节等达拷锟斤拷锟斤拷之前锟斤拷一锟斤拷时锟斤拷锟斤拷锟节伙拷锟角等达拷锟斤拷锟斤拷锟节硷拷使锟斤拷NWAIT */
    g_sram_handle.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;       /* 锟芥储锟斤拷写使锟斤拷 */
    g_sram_handle.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;              /* 锟饺达拷使锟斤拷位,锟剿达拷未锟矫碉拷 */
    g_sram_handle.Init.ExtendedMode = FSMC_EXTENDED_MODE_ENABLE;           /* 锟斤拷写使锟矫诧拷同锟斤拷时锟斤拷 */
    g_sram_handle.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;  /* 锟角凤拷使锟斤拷同锟斤拷锟斤拷锟斤拷模式锟铰的等达拷锟脚猴拷,锟剿达拷未锟矫碉拷 */
    g_sram_handle.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;              /* 锟斤拷止突锟斤拷写 */

    /* FSMC锟斤拷时锟斤拷锟斤拷萍拇锟斤拷锟� */
    fsmc_read_handle.AddressSetupTime = 0x0F;           /* 锟斤拷址锟斤拷锟斤拷时锟斤拷(ADDSET)为15锟斤拷fmc_ker_ck 1/168=6*16=96ns */
    fsmc_read_handle.AddressHoldTime = 0x00;
    fsmc_read_handle.DataSetupTime = 60;                /* 锟斤拷锟捷憋拷锟斤拷时锟斤拷(DATAST)为60锟斤拷fmc_ker_ck=6*60=360ns */
    /* 锟斤拷为液锟斤拷锟斤拷锟斤拷IC锟侥讹拷锟斤拷锟捷碉拷时锟斤拷,锟劫度诧拷锟斤拷太锟斤拷,锟斤拷锟斤拷锟角革拷锟斤拷锟斤拷锟斤拷芯片 */
    fsmc_read_handle.AccessMode = FSMC_ACCESS_MODE_A;   /* 模式A */
    /* FSMC写时锟斤拷锟斤拷萍拇锟斤拷锟� */
    fsmc_write_handle.BusTurnAroundDuration = 0;
    fsmc_write_handle.AddressSetupTime = 9;             /* 锟斤拷址锟斤拷锟斤拷时锟斤拷(ADDSET)为9锟斤拷fmc_ker_ck=6*9=54ns */
    fsmc_write_handle.AddressHoldTime = 0x00;
    fsmc_write_handle.DataSetupTime = 9;                /* 锟斤拷锟捷憋拷锟斤拷时锟斤拷(DATAST)为9锟斤拷fmc_ker_ck=6*8=54ns */
    /* 9锟斤拷fmc_ker_ck锟斤拷fmc_ker_ck=168Mhz锟斤拷,某些液锟斤拷锟斤拷锟斤拷IC锟斤拷写锟脚猴拷锟斤拷锟斤拷锟斤拷锟斤拷也锟斤拷50ns */
    fsmc_write_handle.AccessMode = FSMC_ACCESS_MODE_A;  /* 模式A */

    HAL_SRAM_Init(&g_sram_handle, &fsmc_read_handle, &fsmc_write_handle);
    delay_ms(50);

    /* 锟斤拷锟斤拷9341 ID锟侥讹拷取 */
    lcd_wr_regno(0xD3);
    lcddev.id = lcd_rd_data();  /* dummy read */
    lcddev.id = lcd_rd_data();  /* 锟斤拷锟斤拷0x00 */
    lcddev.id = lcd_rd_data();  /* 锟斤拷取93 */
    lcddev.id <<= 8;
    lcddev.id |= lcd_rd_data(); /* 锟斤拷取41 */

    if (lcddev.id != 0x9341)    /* 锟斤拷锟斤拷 9341 , 锟斤拷锟皆匡拷锟斤拷锟角诧拷锟斤拷 ST7789 */
    {
        lcd_wr_regno(0x04);
        lcddev.id = lcd_rd_data();      /* dummy read */
        lcddev.id = lcd_rd_data();      /* 锟斤拷锟斤拷0x85 */
        lcddev.id = lcd_rd_data();      /* 锟斤拷取0x85 */
        lcddev.id <<= 8;
        lcddev.id |= lcd_rd_data();     /* 锟斤拷取0x52 */

        if (lcddev.id == 0x8552)        /* 锟斤拷8552锟斤拷ID转锟斤拷锟斤拷7789 */
        {
            lcddev.id = 0x7789;
        }

        if (lcddev.id != 0x7789)        /* 也锟斤拷锟斤拷ST7789, 锟斤拷锟斤拷锟角诧拷锟斤拷 NT35310 */
        {
            lcd_wr_regno(0xD4);
            lcddev.id = lcd_rd_data();  /* dummy read */
            lcddev.id = lcd_rd_data();  /* 锟斤拷锟斤拷0x01 */
            lcddev.id = lcd_rd_data();  /* 锟斤拷锟斤拷0x53 */
            lcddev.id <<= 8;
            lcddev.id |= lcd_rd_data(); /* 锟斤拷锟斤拷锟斤拷锟�0x10 */

            if (lcddev.id != 0x5310)    /* 也锟斤拷锟斤拷NT35310,锟斤拷锟皆匡拷锟斤拷锟角诧拷锟斤拷NT35510 */
            {
                /* 锟斤拷锟斤拷锟斤拷钥锟斤拷锟斤拷锟斤拷锟结供锟斤拷 */
                lcd_write_reg(0xF000, 0x0055);
                lcd_write_reg(0xF001, 0x00AA);
                lcd_write_reg(0xF002, 0x0052);
                lcd_write_reg(0xF003, 0x0008);
                lcd_write_reg(0xF004, 0x0001);

                lcd_wr_regno(0xC500);       /* 锟斤拷取ID锟酵帮拷位 */
                lcddev.id = lcd_rd_data();  /* 锟斤拷锟斤拷0x80 */
                lcddev.id <<= 8;

                lcd_wr_regno(0xC501);       /* 锟斤拷取ID锟竭帮拷位 */
                lcddev.id |= lcd_rd_data(); /* 锟斤拷锟斤拷0x00 */
                delay_ms(
                        5);                /* 锟饺达拷5ms, 锟斤拷为0XC501指锟斤拷锟�1963锟斤拷说锟斤拷锟斤拷锟斤拷锟斤拷锟轿恢革拷锟�, 锟饺达拷5ms锟斤拷1963锟斤拷位锟斤拷锟斤拷俨锟斤拷锟� */

                if (lcddev.id != 0x5510)        /* 也锟斤拷锟斤拷NT5510,锟斤拷锟皆匡拷锟斤拷锟角诧拷锟斤拷SSD1963 */
                {
                    lcd_wr_regno(0xA1);
                    lcddev.id = lcd_rd_data();
                    lcddev.id = lcd_rd_data();  /* 锟斤拷锟斤拷0x57 */
                    lcddev.id <<= 8;
                    lcddev.id |= lcd_rd_data(); /* 锟斤拷锟斤拷0x61 */

                    if (lcddev.id == 0x5761)
                        lcddev.id = 0x1963; /* SSD1963锟斤拷锟截碉拷ID锟斤拷5761H,为锟斤拷锟斤拷锟斤拷锟斤拷,锟斤拷锟斤拷强锟斤拷锟斤拷锟斤拷为1963 */
                }
            }
        }
    }

    /* 锟截憋拷注锟斤拷, 锟斤拷锟斤拷锟絤ain锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟轿达拷锟斤拷1锟斤拷始锟斤拷, 锟斤拷峥拷锟斤拷锟絧rintf
     * 锟斤拷锟斤拷(锟斤拷锟斤拷锟斤拷f_putc锟斤拷锟斤拷), 锟斤拷锟斤拷, 锟斤拷锟斤拷锟绞硷拷锟斤拷锟斤拷锟�1, 锟斤拷锟斤拷锟斤拷锟轿碉拷锟斤拷锟斤拷
     * 锟斤拷锟斤拷 printf 锟斤拷锟� !!!!!!!
     */
    //printf("LCD ID:%x\r\n", lcddev.id); /* 锟斤拷印LCD ID */

    if (lcddev.id == 0x7789) {
        lcd_ex_st7789_reginit();        /* 执锟斤拷ST7789锟斤拷始锟斤拷 */
    } else if (lcddev.id == 0x9341) {
        lcd_ex_ili9341_reginit();       /* 执锟斤拷ILI9341锟斤拷始锟斤拷 */
    } else if (lcddev.id == 0x5310) {
        lcd_ex_nt35310_reginit();       /* 执锟斤拷NT35310锟斤拷始锟斤拷 */
    } else if (lcddev.id == 0x5510) {
        lcd_ex_nt35510_reginit();       /* 执锟斤拷NT35510锟斤拷始锟斤拷 */
    } else if (lcddev.id == 0x1963) {
        lcd_ex_ssd1963_reginit();       /* 执锟斤拷SSD1963锟斤拷始锟斤拷 */
        lcd_ssd_backlight_set(100);     /* 锟斤拷锟斤拷锟斤拷锟斤拷为锟斤拷锟斤拷 */
    }

    /* 锟斤拷始锟斤拷锟斤拷锟斤拷院锟�,锟斤拷锟斤拷 */
    if (lcddev.id == 0x9341 || lcddev.id == 0x1963 || lcddev.id == 0x7789)  /* 锟斤拷锟斤拷锟斤拷饧革拷锟絀C, 锟斤拷锟斤拷锟斤拷WR时锟斤拷为锟斤拷锟� */
    {
        /* 锟斤拷锟斤拷锟斤拷锟斤拷写时锟斤拷锟斤拷萍拇锟斤拷锟斤拷锟绞憋拷锟� */
        fsmc_write_handle.AddressSetupTime = 3;
        fsmc_write_handle.DataSetupTime = 3;
        FSMC_NORSRAM_Extended_Timing_Init(g_sram_handle.Extended, &fsmc_write_handle, g_sram_handle.Init.NSBank,
                                          g_sram_handle.Init.ExtendedMode);
    }

    if (lcddev.id == 0x5310 || lcddev.id == 0x5510)  /* 锟斤拷锟斤拷锟斤拷饧革拷锟絀C, 锟斤拷锟斤拷锟斤拷WR时锟斤拷为锟斤拷锟� */
    {
        /* 锟斤拷锟斤拷锟斤拷锟斤拷写时锟斤拷锟斤拷萍拇锟斤拷锟斤拷锟绞憋拷锟� */
        fsmc_write_handle.AddressSetupTime = 2;
        fsmc_write_handle.DataSetupTime = 2;
        FSMC_NORSRAM_Extended_Timing_Init(g_sram_handle.Extended, &fsmc_write_handle, g_sram_handle.Init.NSBank,
                                          g_sram_handle.Init.ExtendedMode);
    }

    lcd_display_dir(0); /* 默锟斤拷为锟斤拷锟斤拷 */
    LCD_BL(1);          /* 锟斤拷锟斤拷锟斤拷锟斤拷 */
    lcd_clear(WHITE);
}

/**
 * @brief       锟斤拷锟斤拷锟斤拷锟斤拷
 * @param       color: 要锟斤拷锟斤拷锟斤拷锟斤拷色
 * @retval      锟斤拷
 */
void lcd_clear(uint16_t color) {
    uint32_t index = 0;
    uint32_t totalpoint = lcddev.width;

    totalpoint *= lcddev.height;    /* 锟矫碉拷锟杰碉拷锟斤拷 */
    lcd_set_cursor(0x00, 0x0000);   /* 锟斤拷锟矫癸拷锟轿伙拷锟� */
    lcd_write_ram_prepare();        /* 锟斤拷始写锟斤拷GRAM */

    for (index = 0; index < totalpoint; index++) {
        LCD->LCD_RAM = color;
    }
}

/**
 * @brief       锟斤拷指锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷涞ワ拷锟斤拷锟缴�
 * @param       (sx,sy),(ex,ey):锟斤拷锟斤拷锟轿对斤拷锟斤拷锟斤拷,锟斤拷锟斤拷锟叫∥�:(ex - sx + 1) * (ey - sy + 1)
 * @param       color:  要锟斤拷锟斤拷锟斤拷色(32位锟斤拷色,锟斤拷锟斤拷锟斤拷锟絃TDC)
 * @retval      锟斤拷
 */
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color) {
    uint16_t i, j;
    uint16_t xlen = 0;
    xlen = ex - sx + 1;

    for (i = sy; i <= ey; i++) {
        lcd_set_cursor(sx, i);      /* 锟斤拷锟矫癸拷锟轿伙拷锟� */
        lcd_write_ram_prepare();    /* 锟斤拷始写锟斤拷GRAM */

        for (j = 0; j < xlen; j++) {
            LCD->LCD_RAM = color;   /* 锟斤拷示锟斤拷色 */
        }
    }
}

/**
 * @brief       锟斤拷指锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟街革拷锟斤拷锟缴拷锟�
 * @param       (sx,sy),(ex,ey):锟斤拷锟斤拷锟轿对斤拷锟斤拷锟斤拷,锟斤拷锟斤拷锟叫∥�:(ex - sx + 1) * (ey - sy + 1)
 * @param       color: 要锟斤拷锟斤拷锟斤拷色锟斤拷锟斤拷锟阶碉拷址
 * @retval      锟斤拷
 */
void lcd_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color) {
    uint16_t height, width;
    uint16_t i, j;

    width = ex - sx + 1;            /* 锟矫碉拷锟斤拷锟侥匡拷锟� */
    height = ey - sy + 1;           /* 锟竭讹拷 */

    for (i = 0; i < height; i++) {
        lcd_set_cursor(sx, sy + i); /* 锟斤拷锟矫癸拷锟轿伙拷锟� */
        lcd_write_ram_prepare();    /* 锟斤拷始写锟斤拷GRAM */

        for (j = 0; j < width; j++) {
            LCD->LCD_RAM = color[i * width + j]; /* 写锟斤拷锟斤拷锟斤拷 */
        }
    }
}

/**
 * @brief       锟斤拷锟斤拷
 * @param       x1,y1: 锟斤拷锟斤拷锟斤拷锟�
 * @param       x2,y2: 锟秸碉拷锟斤拷锟斤拷
 * @param       color: 锟竭碉拷锟斤拷色
 * @retval      锟斤拷
 */
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, row, col;
    delta_x = x2 - x1;      /* 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷 */
    delta_y = y2 - y1;
    row = x1;
    col = y1;

    if (delta_x > 0) {
        incx = 1;       /* 锟斤拷锟矫碉拷锟斤拷锟斤拷锟斤拷 */
    } else if (delta_x == 0) {
        incx = 0;       /* 锟斤拷直锟斤拷 */
    } else {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0) {
        incy = 1;
    } else if (delta_y == 0) {
        incy = 0;       /* 水平锟斤拷 */
    } else {
        incy = -1;
        delta_y = -delta_y;
    }

    if (delta_x > delta_y) {
        distance = delta_x;  /* 选取锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷 */
    } else {
        distance = delta_y;
    }

    for (t = 0; t <= distance + 1; t++)    /* 锟斤拷锟斤拷锟斤拷锟� */
    {
        lcd_draw_point(row, col, color);    /* 锟斤拷锟斤拷 */
        xerr += delta_x;
        yerr += delta_y;

        if (xerr > distance) {
            xerr -= distance;
            row += incx;
        }

        if (yerr > distance) {
            yerr -= distance;
            col += incy;
        }
    }
}

/**
 * @brief       锟斤拷水平锟斤拷
 * @param       x,y   : 锟斤拷锟斤拷锟斤拷锟�
 * @param       len   : 锟竭筹拷锟斤拷
 * @param       color : 锟斤拷锟轿碉拷锟斤拷色
 * @retval      锟斤拷
 */
void lcd_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint16_t color) {
    if ((len == 0) || (x > lcddev.width) || (y > lcddev.height)) {
        return;
    }

    lcd_fill(x, y, x + len - 1, y, color);
}

/**
 * @brief       锟斤拷锟斤拷锟斤拷
 * @param       x1,y1: 锟斤拷锟斤拷锟斤拷锟�
 * @param       x2,y2: 锟秸碉拷锟斤拷锟斤拷
 * @param       color: 锟斤拷锟轿碉拷锟斤拷色
 * @retval      锟斤拷
 */
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    lcd_draw_line(x1, y1, x2, y1, color);
    lcd_draw_line(x1, y1, x1, y2, color);
    lcd_draw_line(x1, y2, x2, y2, color);
    lcd_draw_line(x2, y1, x2, y2, color);
}

/**
 * @brief       锟斤拷圆
 * @param       x0,y0 : 圆锟斤拷锟斤拷锟斤拷锟斤拷
 * @param       r     : 锟诫径
 * @param       color : 圆锟斤拷锟斤拷色
 * @retval      锟斤拷
 */
void lcd_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color) {
    int a, b;
    int di;

    a = 0;
    b = r;
    di = 3 - (r << 1);       /* 锟叫讹拷锟铰革拷锟斤拷位锟矫的憋拷志 */

    while (a <= b) {
        lcd_draw_point(x0 + a, y0 - b, color);  /* 5 */
        lcd_draw_point(x0 + b, y0 - a, color);  /* 0 */
        lcd_draw_point(x0 + b, y0 + a, color);  /* 4 */
        lcd_draw_point(x0 + a, y0 + b, color);  /* 6 */
        lcd_draw_point(x0 - a, y0 + b, color);  /* 1 */
        lcd_draw_point(x0 - b, y0 + a, color);
        lcd_draw_point(x0 - a, y0 - b, color);  /* 2 */
        lcd_draw_point(x0 - b, y0 - a, color);  /* 7 */
        a++;

        /* 使锟斤拷Bresenham锟姐法锟斤拷圆 */
        if (di < 0) {
            di += 4 * a + 6;
        } else {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}

/**
 * @brief       锟斤拷锟绞碉拷锟皆�
 * @param       x,y  : 圆锟斤拷锟斤拷锟斤拷锟斤拷
 * @param       r    : 锟诫径
 * @param       color: 圆锟斤拷锟斤拷色
 * @retval      锟斤拷
 */
void lcd_fill_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color) {
    uint32_t i;
    uint32_t imax = ((uint32_t) r * 707) / 1000 + 1;
    uint32_t sqmax = (uint32_t) r * (uint32_t) r + (uint32_t) r / 2;
    uint32_t xr = r;

    lcd_draw_hline(x - r, y, 2 * r, color);

    for (i = 1; i <= imax; i++) {
        if ((i * i + xr * xr) > sqmax) {
            /* draw lines from outside */
            if (xr > imax) {
                lcd_draw_hline(x - i + 1, y + xr, 2 * (i - 1), color);
                lcd_draw_hline(x - i + 1, y - xr, 2 * (i - 1), color);
            }

            xr--;
        }

        /* draw lines from inside (center) */
        lcd_draw_hline(x - xr, y + i, 2 * xr, color);
        lcd_draw_hline(x - xr, y - i, 2 * xr, color);
    }
}

/**
 * @brief       锟斤拷指锟斤拷位锟斤拷锟斤拷示一锟斤拷锟街凤拷
 * @param       x,y  : 锟斤拷锟斤拷
 * @param       chr  : 要锟斤拷示锟斤拷锟街凤拷:" "--->"~"
 * @param       size : 锟斤拷锟斤拷锟叫� 12/16/24/32
 * @param       mode : 锟斤拷锟接凤拷式(1); 锟角碉拷锟接凤拷式(0);
 * @retval      锟斤拷
 */
void lcd_show_char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color) {
    uint8_t temp, t1, t;
    uint16_t y0 = y;
    uint8_t csize = 0;
    uint8_t * pfont = 0;

    csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2); /* 锟矫碉拷锟斤拷锟斤拷一锟斤拷锟街凤拷锟斤拷应锟斤拷锟斤拷锟斤拷占锟斤拷锟街斤拷锟斤拷 */
    chr = chr - ' ';    /* 锟矫碉拷偏锟狡猴拷锟街碉拷锟紸SCII锟街匡拷锟角从空革拷始取模锟斤拷锟斤拷锟斤拷-' '锟斤拷锟角讹拷应锟街凤拷锟斤拷锟街库） */

    switch (size) {
        case 12:
            pfont = (uint8_t *) asc2_1206[chr];  /* 锟斤拷锟斤拷1206锟斤拷锟斤拷 */
            break;

        case 16:
            pfont = (uint8_t *) asc2_1608[chr];  /* 锟斤拷锟斤拷1608锟斤拷锟斤拷 */
            break;

        case 24:
            pfont = (uint8_t *) asc2_2412[chr];  /* 锟斤拷锟斤拷2412锟斤拷锟斤拷 */
            break;

        case 32:
            pfont = (uint8_t *) asc2_3216[chr];  /* 锟斤拷锟斤拷3216锟斤拷锟斤拷 */
            break;

        default:
            return;
    }

    for (t = 0; t < csize; t++) {
        temp = pfont[t];                            /* 锟斤拷取锟街凤拷锟侥碉拷锟斤拷锟斤拷锟斤拷 */

        for (t1 = 0; t1 < 8; t1++)                  /* 一锟斤拷锟街斤拷8锟斤拷锟斤拷 */
        {
            if (temp & 0x80)                        /* 锟斤拷效锟斤拷,锟斤拷要锟斤拷示 */
            {
                lcd_draw_point(x, y, color);        /* 锟斤拷锟斤拷锟斤拷锟�,要锟斤拷示锟斤拷锟斤拷锟� */
            } else if (mode == 0)                     /* 锟斤拷效锟斤拷,锟斤拷锟斤拷示 */
            {
                lcd_draw_point(x, y, g_back_color); /* 锟斤拷锟斤拷锟斤拷色,锟洁当锟斤拷锟斤拷锟斤拷悴伙拷锟绞�(注锟解背锟斤拷色锟斤拷全锟街憋拷锟斤拷锟斤拷锟斤拷) */
            }

            temp <<= 1;                             /* 锟斤拷位, 锟皆憋拷锟饺★拷锟揭伙拷锟轿伙拷锟阶刺� */
            y++;

            if (y >= lcddev.height)return;          /* 锟斤拷锟斤拷锟斤拷锟斤拷 */

            if ((y - y0) == size)                   /* 锟斤拷示锟斤拷一锟斤拷锟斤拷? */
            {
                y = y0; /* y锟斤拷锟疥复位 */
                x++;    /* x锟斤拷锟斤拷锟斤拷锟� */

                if (x >= lcddev.width) {
                    return;       /* x锟斤拷锟疥超锟斤拷锟斤拷锟斤拷 */
                }

                break;
            }
        }
    }
}

/**
 * @brief       平锟斤拷锟斤拷锟斤拷, m^n
 * @param       m: 锟斤拷锟斤拷
 * @param       n: 指锟斤拷
 * @retval      m锟斤拷n锟轿凤拷
 */
static uint32_t lcd_pow(uint8_t m, uint8_t n) {
    uint32_t result = 1;

    while (n--) {
        result *= m;
    }

    return result;
}

/**
 * @brief       锟斤拷示len锟斤拷锟斤拷锟斤拷
 * @param       x,y : 锟斤拷始锟斤拷锟斤拷
 * @param       num : 锟斤拷值(0 ~ 2^32)
 * @param       len : 锟斤拷示锟斤拷锟街碉拷位锟斤拷
 * @param       size: 选锟斤拷锟斤拷锟斤拷 12/16/24/32
 * @retval      锟斤拷
 */
void lcd_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint16_t color) {
    uint8_t t, temp;
    uint8_t enshow = 0;

    for (t = 0; t < len; t++)   /* 锟斤拷锟斤拷锟斤拷示位锟斤拷循锟斤拷 */
    {
        temp = (num / lcd_pow(10, len - t - 1)) % 10;   /* 锟斤拷取锟斤拷应位锟斤拷锟斤拷锟斤拷 */

        if (enshow == 0 && t < (len - 1))               /* 没锟斤拷使锟斤拷锟斤拷示,锟揭伙拷锟斤拷位要锟斤拷示 */
        {
            if (temp == 0) {
                lcd_show_char(x + (size / 2) * t, y, ' ', size, 0, color);    /* 锟斤拷示锟秸革拷,占位 */
                continue;       /* 锟斤拷锟斤拷锟铰革拷一位 */
            } else {
                enshow = 1;     /* 使锟斤拷锟斤拷示 */
            }
        }

        lcd_show_char(x + (size / 2) * t, y, temp + '0', size, 0, color);     /* 锟斤拷示锟街凤拷 */
    }
}

/**
 * @brief       锟斤拷展锟斤拷示len锟斤拷锟斤拷锟斤拷(锟斤拷位锟斤拷0也锟斤拷示)
 * @param       x,y : 锟斤拷始锟斤拷锟斤拷
 * @param       num : 锟斤拷值(0 ~ 2^32)
 * @param       len : 锟斤拷示锟斤拷锟街碉拷位锟斤拷
 * @param       size: 选锟斤拷锟斤拷锟斤拷 12/16/24/32
 * @param       mode: 锟斤拷示模式
 *              [7]:0,锟斤拷锟斤拷锟�;1,锟斤拷锟�0.
 *              [6:1]:锟斤拷锟斤拷
 *              [0]:0,锟角碉拷锟斤拷锟斤拷示;1,锟斤拷锟斤拷锟斤拷示.
 *
 * @retval      锟斤拷
 */
void lcd_show_xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode, uint16_t color) {
    uint8_t t, temp;
    uint8_t enshow = 0;

    for (t = 0; t < len; t++)       /* 锟斤拷锟斤拷锟斤拷示位锟斤拷循锟斤拷 */
    {
        temp = (num / lcd_pow(10, len - t - 1)) % 10;    /* 锟斤拷取锟斤拷应位锟斤拷锟斤拷锟斤拷 */

        if (enshow == 0 && t < (len - 1))   /* 没锟斤拷使锟斤拷锟斤拷示,锟揭伙拷锟斤拷位要锟斤拷示 */
        {
            if (temp == 0) {
                if (mode & 0x80)    /* 锟斤拷位锟斤拷要锟斤拷锟�0 */
                {
                    lcd_show_char(x + (size / 2) * t, y, '0', size, mode & 0x01, color);  /* 锟斤拷0占位 */
                } else {
                    lcd_show_char(x + (size / 2) * t, y, ' ', size, mode & 0x01, color);  /* 锟矫空革拷占位 */
                }

                continue;
            } else {
                enshow = 1;     /* 使锟斤拷锟斤拷示 */
            }

        }

        lcd_show_char(x + (size / 2) * t, y, temp + '0', size, mode & 0x01, color);
    }
}

/**
 * @brief       锟斤拷示锟街凤拷锟斤拷
 * @param       x,y         : 锟斤拷始锟斤拷锟斤拷
 * @param       width,height: 锟斤拷锟斤拷锟叫�
 * @param       size        : 选锟斤拷锟斤拷锟斤拷 12/16/24/32
 * @param       p           : 锟街凤拷锟斤拷锟阶碉拷址
 * @retval      锟斤拷
 */
void lcd_show_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color) {
    uint8_t x0 = x;

    width += x;
    height += y;

    while ((*p <= '~') && (*p >= ' '))   /* 锟叫讹拷锟角诧拷锟角非凤拷锟街凤拷! */
    {
        if (x >= width) {
            x = x0;
            y += size;
        }

        if (y >= height) {
            break;      /* 锟剿筹拷 */
        }

        lcd_show_char(x, y, *p, size, 0, color);
        x += size / 2;
        p++;
    }
}


/**
 * @brief       锟斤拷锟斤拷锟斤拷
 * @param       x1,y1: 锟斤拷锟斤拷锟斤拷锟�
 * @param       x2,y2: 锟秸碉拷锟斤拷锟斤拷
 * @param       size : 锟斤拷锟斤拷锟斤拷细锟教讹拷
 * @param       color: 锟竭碉拷锟斤拷色
 * @retval      锟斤拷
 */
void lcd_draw_bline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size, uint16_t color) {
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, row, col;

    if (x1 < size || x2 < size || y1 < size || y2 < size)
        return;

    delta_x = x2 - x1; /* 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷 */
    delta_y = y2 - y1;
    row = x1;
    col = y1;

    if (delta_x > 0) {
        incx = 1; /* 锟斤拷锟矫碉拷锟斤拷锟斤拷锟斤拷 */
    } else if (delta_x == 0) {
        incx = 0; /* 锟斤拷直锟斤拷 */
    } else {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0) {
        incy = 1;
    } else if (delta_y == 0) {
        incy = 0; /* 水平锟斤拷 */
    } else {
        incy = -1;
        delta_y = -delta_y;
    }

    if (delta_x > delta_y)
        distance = delta_x; /* 选取锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷 */
    else
        distance = delta_y;

    for (t = 0; t <= distance + 1; t++) /* 锟斤拷锟斤拷锟斤拷锟� */
    {
        lcd_fill_circle(row, col, size, color); /* 锟斤拷锟斤拷 */
        xerr += delta_x;
        yerr += delta_y;

        if (xerr > distance) {
            xerr -= distance;
            row += incx;
        }

        if (yerr > distance) {
            yerr -= distance;
            col += incy;
        }
    }
}


void lcd_show_float(uint16_t x, uint16_t y, float num, uint8_t size, uint16_t color) {
    char temp[64];
    sprintf(temp, "%f   ", num);
    lcd_show_string(x, y, 200, 200, size, temp, color);//VPP锟斤拷锟街�
}
