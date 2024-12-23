#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>

#include "lib_usart.h"
#include "lib_exti.h"

#include "FreeRTOS.h"
#include "task.h"

/// 两个任务
/// 1. 打印任务
/// 2. 按键扫描任务(软实现)，PA0 按键，
/// 如果按下， 挂起任务，再按 恢复任务
/// 3. 硬件实现 PC0 按键
/// 如果按下， 挂起任务，再按 恢复任务

TaskHandle_t start_Handle;
TaskHandle_t task1_Handle;
TaskHandle_t task2_Handle;

void lib_usart0_on_recv(uint8_t *data, uint32_t len) {
    printf("\r\n");
    // 中断函数

//	 // 临界区 开始
//	portENTER_CRITICAL();
//
//	 // 临界区 结束
//	portEXIT_CRITICAL();
}

void GPIO_config(void) {
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_0);
}


void task1() {
    // 打印
    uint8_t cnt = 0;
    while(1) {
        printf("task1 %d\r\n", cnt++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    vTaskDelete(NULL);
}

void task2() {
    // 打印
    uint8_t cnt = 0;
    while(1) {
        printf("task2 %d\r\n", cnt++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}

void start_task() {
    // 外设
    lib_usart_init();
    lib_exti_init();
    GPIO_config();

    printf("mcu start\r\n");

    //taskENTER_CRITICAL(); // 临界区 开始

    // 创建任务 print
    xTaskCreate(task1, "task1", 128, NULL, 3, &task1_Handle);

    // 创建任务 key
    xTaskCreate(task2, "task2", 128, NULL, 4, &task2_Handle);

    vTaskDelete(start_Handle);

    //taskEXIT_CRITICAL(); // 临界区 结束
}


int main(void) {
//	// 解决小内存设备运行FreeRTOS的问题的
//	xTaskCreateStatic
	
    xTaskCreate(start_task, "start_task", 128, NULL, 3, &start_Handle);
    vTaskStartScheduler(); // 开启任务

    // while不再做任何操作
    while(1) {
    }

}
