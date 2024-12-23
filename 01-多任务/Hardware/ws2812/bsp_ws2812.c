#include "bsp_ws2812.h"
#include <string.h>


// ��ɫֵ TODO:

///// 1. SPI1 42MHZ -> 4��Ƶ -> 10.5MHZ
///// MOSI
///// CLK Ҫ���գ����ܸ������Ĺ���ʹ��


// 1������Ҫ 30��byte
//static uint8_t buff[30] = {0};
// G R B
//static uint8_t buff[WS2812_NUM][30] = {
//	0xE0, 0x38, 0x0E, 0x03, 0x80, 0xE0, 0x38, 0x0E, 0x03, 0x80, // 0x00	
//	0xE0, 0x38, 0x0E, 0x03, 0x80, 0xE0, 0x38, 0x0E, 0x03, 0x80, // 0x00
//	0xE0, 0x38, 0x0E, 0x03, 0x80, 0xE0, 0x38, 0x0E, 0x03, 0x80, // 0x00
////	0xFE, 0x3F, 0x8F, 0xE3, 0xF8, 0xFE, 0x3F, 0x8F, 0xE3, 0xF8, // 0xFF
//};

static uint8_t buff[WS2812_NUM][30];


// ������ұ���ǰ�洢 0 �� 1 ��ӳ����
const uint16_t lookup_table[2] = {0b1110000000, 0b1111111000};


void ws2812_init() {
	printf("ws2812 init\r\n");
	
//	ws2812_set_color(0, 0xFF0000);
//	ws2812_set_color(1, 0x00FF00);
//	ws2812_set_color(2, 0x0000FF);
//	ws2812_set_color(3, 0xFFFFFF);
	ws2812_set_color(0, 0x000000);
	ws2812_set_color(1, 0x000000);
	ws2812_set_color(2, 0x000000);
	ws2812_set_color(3, 0x000000);
}

// ��1��byteת��Ϊ10��byte
void convert_1byte_to_10byte(uint8_t byte, uint8_t output[10]) {
    uint8_t temp[80];  // ��ʱ�洢80λ

    // Step 1: ʹ�ò��ұ�1��byteת��Ϊ80λ
    for (int i = 0; i < 8; i++) {
        // ʹ�ò��ұ�ֱ�Ӳ���ӳ��
        uint16_t mapping = lookup_table[(byte >> (7 - i)) & 1];
        
        // ��10λ��ӳ��ֵ����temp����
        for (int j = 0; j < 10; j++) {
            temp[i * 10 + j] = (mapping >> (9 - j)) & 1;
        }
    }

    // Step 2: ��80λ�����ư�8λһ�飬�����10��byte
    for (int i = 0; i < 10; i++) {
        output[i] = 0;  // ��ʼ�������ÿ��byte
        for (int j = 0; j < 8; j++) {
            // ��ÿ��8λ��������ϳ�һ��byte
            output[i] |= (temp[i * 8 + j] << (7 - j));
        }
    }
}



// 8bit(����) + 8bit(RED) + 8bit(GREEN) + 8bit(BLUE)
//void ws2812_set_color(uint16_t index, uint32_t color) {
//	/// �ı� ״̬
//	
//	// RGB -> 3��byte ת�� �� 30��byte
//	// RGB -> 1��byte ת�� �� 10��byte
//	
//	// printf("ws2812 set color\r\n");
//	
//	uint8_t red 	= (color >> 16) & 0xFF;
//	uint8_t green 	= (color >> 8) & 0xFF;
//	uint8_t blue 	= (color >> 0) & 0xFF;
//	
//	uint8_t dst[10];
//	// ת��red
//	convert_1byte_to_10byte(red, dst);
////	for(uint8_t i = 0; i < 10; i++) {
////		buff[i+ 10] = dst[i];
////	}
//	// �ڴ濽��, 
//	/// 1. Ŀ���ַ
//	/// 2. Դͷ��ַ
//	/// 3. �����ĳ���
//	memcpy(&buff[10], dst, 10);
//	
//	// ת��green
//	convert_1byte_to_10byte(green, dst);
////	for(uint8_t i = 0; i < 10; i++) {
////		buff[i] = dst[i];
////	}
//	memcpy(buff, dst, 10);
//	
//	// ת��blue
//	convert_1byte_to_10byte(blue, dst);
////	for(uint8_t i = 0; i < 10; i++) {
////		buff[i + 20] = dst[i];
////	}
//	memcpy(&buff[20], dst, 10);
//	
//}

// index ��һ����
void ws2812_set_color(uint16_t index, uint32_t color) {
	/// �ı� ״̬
	
	uint8_t red 	= (color >> 16) & 0xFF;
	uint8_t green 	= (color >> 8) & 0xFF;
	uint8_t blue 	= (color >> 0) & 0xFF;
	
	uint8_t dst[10];
	// ת��red
	convert_1byte_to_10byte(red, dst);

	memcpy(&buff[index][10], dst, 10);
	
	// ת��green
	convert_1byte_to_10byte(green, dst);

	memcpy(&buff[index][0], dst, 10);
	
	// ת��blue
	convert_1byte_to_10byte(blue, dst);

	memcpy(&buff[index][20], dst, 10);
	
}


void ws2812_display() {
	/// ����״̬����ʾ
//	printf("ws2812 display\r\n");

//	for(uint8_t j = 0; j < WS2812_NUM; j++) {
//		// mosi����30��byteд��
//		for(uint8_t i = 0; i < 30; i++) {
//			lib_spi1_write(buff[j][i]);
//		}
//	}
//	// reset
//	lib_spi1_write(0x80);
//	for(uint16_t i = 0; i < 112; i++) {
//		lib_spi1_write(0x00);
//	}
	
	// д�Ƶ�����
	lib_spi1_dma_write((uint32_t)buff, WS2812_NUM * 30);
}

void lib_spi1_dma_write_on_finish() {
	// �������
	static uint8_t state = 0;
	static uint8_t cnt = 0;
	
	if(state == 0) {
		// reset
		uint8_t tmp = 0x80;
		lib_spi1_dma_write((uint32_t)&tmp, 1);
		
		state++;
	} else if(state == 1) {
		uint8_t tmp = 0x00;
		lib_spi1_dma_write((uint32_t)&tmp, 1);
		
		cnt++;
		if(cnt >= 112) {
			state++;
			cnt = 0;
		}
	} else if(state == 2) {
		lib_spi1_dma_write((uint32_t)buff, WS2812_NUM * 30);
		state = 0;
	}
}
