//
// Created by csy on 2023/12/6 0006.
//
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "delay.h"
#include "src/lv_api_map.h"
#include "touch.h"

void task_function1(void *pvParameters);

void task_function2(void *pvParameters);

void task_Handel() {
    xTaskCreate(task_function1, "TASK_1", 1024, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(task_function2, "TASK_1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();
}

void task_function1(void *pvParameters) {
    for (;;) {
        lv_task_handler();
        tp_dev.scan(1);
        vTaskDelay(1);
    }
}

void task_function2(void *pvParameters) {
    for (;;) {
        HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9);
        vTaskDelay(200);
    }
}