#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>

#include "lib_usart.h"
#include "lib_exti.h"

#include "FreeRTOS.h"
#include "task.h"

/// ��������
/// 1. ��ӡ����
/// 2. ����ɨ������(��ʵ��)��PA0 ������
/// ������£� ���������ٰ� �ָ�����
/// 3. Ӳ��ʵ�� PC0 ����
/// ������£� ���������ٰ� �ָ�����

TaskHandle_t start_Handle;
TaskHandle_t task1_Handle;
TaskHandle_t task2_Handle;

void lib_usart0_on_recv(uint8_t *data, uint32_t len) {
    printf("\r\n");
    // �жϺ���

//	 // �ٽ��� ��ʼ
//	portENTER_CRITICAL();
//
//	 // �ٽ��� ����
//	portEXIT_CRITICAL();
}

void GPIO_config(void) {
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_0);
}


void task1() {
    // ��ӡ
    uint8_t cnt = 0;
    while(1) {
        printf("task1 %d\r\n", cnt++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    vTaskDelete(NULL);
}

void task2() {
    // ��ӡ
    uint8_t cnt = 0;
    while(1) {
        printf("task2 %d\r\n", cnt++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}

void start_task() {
    // ����
    lib_usart_init();
    lib_exti_init();
    GPIO_config();

    printf("mcu start\r\n");

    //taskENTER_CRITICAL(); // �ٽ��� ��ʼ

    // �������� print
    xTaskCreate(task1, "task1", 128, NULL, 3, &task1_Handle);

    // �������� key
    xTaskCreate(task2, "task2", 128, NULL, 4, &task2_Handle);

    vTaskDelete(start_Handle);

    //taskEXIT_CRITICAL(); // �ٽ��� ����
}


int main(void) {
//	// ���С�ڴ��豸����FreeRTOS�������
//	xTaskCreateStatic
	
    xTaskCreate(start_task, "start_task", 128, NULL, 3, &start_Handle);
    vTaskStartScheduler(); // ��������

    // while�������κβ���
    while(1) {
    }

}
