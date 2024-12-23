#include "bsp_dot_matrix.h"
#include "string.h"

////  0 	  0 		 0
////  旋转  左右镜像 	上下镜像
//static uint8_t	dir = 0b0111;
//static uint8_t buff[DM_NUM][8] = {0};

//static uint8_t buff[8][DM_NUM] = {0};

static uint8_t buff[8][DM_NUM * 2] = {0};

static uint8_t table[10][8] = {
	{0x3C,0x42,0x42,0x42,0x42,0x42,0x66,0x38},/*"0",0*/
	{0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x18},/*"1",1*/
	{0x7C,0x42,0x02,0x04,0x08,0x30,0x42,0x7E},/*"2",2*/
	{0x7C,0x46,0x04,0x18,0x06,0x02,0x42,0x3C},/*"3",3*/
	{0x0C,0x14,0x14,0x24,0x44,0x3C,0x04,0x0C},/*"4",4*/
	{0x3E,0x40,0x58,0x64,0x02,0x02,0x42,0x3C},/*"5",5*/
	{0x3E,0x40,0x40,0x7C,0x42,0x42,0x42,0x3C},/*"6",6*/
	{0x7E,0x04,0x04,0x08,0x10,0x10,0x10,0x10},/*"7",7*/
	{0x7C,0x42,0x62,0x3C,0x44,0x42,0x42,0x3C},/*"8",8*/
	{0x7C,0x42,0x42,0x46,0x3A,0x02,0x44,0x38},/*"9",9*/
};

void dm_init() {
	printf("dm init \r\n");
	
	/// 初始化 CS
	bsp_gpio_out(DM_CS_RCU, DM_CS_PIN);
	DM_CS(1); // un select
		
	//译码方式：不进行译码
	DM_CS(0);// 片选
	for(uint8_t i = 0; i < DM_NUM; i++) {
		// 1个点阵
		DM_WR(0x09);
		DM_WR(0x00);
	}
	DM_CS(1);// 取消片选

	//亮度
	DM_CS(0);// 片选
	for(uint8_t i = 0; i < DM_NUM; i++) {
		// 1个数码管
		DM_WR(0x0a);
		DM_WR(0x01);
	}
	DM_CS(1);// 取消片选

	//扫描界限；8个数码管显示
	DM_CS(0);// 片选
	for(uint8_t i = 0; i < DM_NUM; i++) {
		// 1个数码管
		DM_WR(0x0b);
		DM_WR(0x07);
	}
	DM_CS(1);// 取消片选

	//掉电模式：0，普通模式：1
	DM_CS(0);// 片选
	for(uint8_t i = 0; i < DM_NUM; i++) {
		// 1个数码管
		DM_WR(0x0c);
		DM_WR(0x01);
	}
	DM_CS(1);// 取消片选

	 //显示测试：1；测试结束，正常显示：0
	DM_CS(0);// 片选
	for(uint8_t i = 0; i < DM_NUM; i++) {
		// 1个数码管
		DM_WR(0x0f);
		DM_WR(0x00);
	}
	DM_CS(1);// 取消片选	
	
	
	/// 初始化时做默认值
	for(uint8_t i = 0; i < 8; i++) {
		for(uint8_t j = 0; j < DM_NUM; j++) {
			buff[i][2 * j] = i + 1;
			buff[i][2 * j + 1] = 0x00;
		}
	}
	
}
// dat[8] 只可以表达出一个点阵屏幕
// dat[8] 想表达n个点阵 dat[n][8]
//void dm_display() {
////	printf("dm display\r\n");
//	// 交给外设干活
//	
//	uint8_t i = 0;
//    for(i = 1; i < 9; i++ )//1~8行 进行更新
//    {
//		DM_CS(0);// 片选
//		/// TODO：希望交给spi + dma去处理
//		for(uint8_t j = 0; j < DM_NUM; j++) {
//			DM_WR(i);  //写入地址，即行编号1-8
//			DM_WR(buff[j][i-1]);  //第j个点阵
//		}
//		DM_CS(1);// 取消片选
//    }
//}


void dm_display() {	
	uint8_t i = 0;
	// lib_spi0_dma_write
	
//	for(uint8_t i = 1; i < 9; i++) {
//		DM_CS(0);
//		for(uint8_t j = 0; j < DM_NUM; j++) {
//			DM_WR(i);
//			DM_WR(buff[i - 1][j]);// 地址连续
//		}
//		DM_CS(1);
//	}
	
//	for(uint8_t i = 1; i < 9; i++) {
//		
//		DM_CS(0);
//		
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		DM_CS(1);
//	}

//		uint8_t tmp = 1;
//		DM_CS(0);
//		lib_spi0_dma_write((uint32_t)&tmp, 1);	


 //// 8 次
 //		DM_CS(0);	
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		DM_CS(1);

//		DM_CS(0);
//		
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		lib_spi0_dma_write(i);
//		lib_spi0_dma_write(buff[i - 1][j++]);
//		
//		DM_CS(1);


//	for(uint8_t i = 1; i < 9; i++) {
//		DM_CS(0);
//		for(uint8_t j = 0; j < DM_NUM; j++) {
//			DM_WR(i);
//			DM_WR(buff[i - 1][j]);// 地址连续
//		}
//		DM_CS(1);
//	}

//	///// 不采用dma写
//	for(uint8_t i = 0; i < 8; i++) {
//		DM_CS(0);
//		for(uint8_t j = 0; j < DM_NUM; j++) {
//			DM_WR(buff[i][2 * j]);		// 都连续
//			DM_WR(buff[i][2 * j + 1]); // 都连续
//		}
//		DM_CS(1);
//	}

	
//	// 采用dma写
	DM_CS(0);
	lib_spi2_dma_write((uint32_t)(buff[0]), DM_NUM * 2);

}

void lib_spi2_dma_write_on_finish() {
	static uint8_t i = 1;
	
	DM_CS(1);

	if(i >= 8) {
		i = 0;
	}
	
	DM_CS(0);
	lib_spi2_dma_write((uint32_t)(buff[i]), DM_NUM * 2);
	
	i++;
	
}

//void lib_spi0_dma_write_on_finish() {
//	static uint8_t i = 1;
//	static uint8_t j = 0;
//	static uint8_t state = 0;
//	if(state == 0) {
//		lib_spi0_dma_write((uint32_t)&buff[i - 1][j++], 1);
//		state = 1;
//		if(j >= DM_NUM) {
//			j = 0;
//			i++;

//			DM_CS(1);
//			if(i >= 9) {
//				i = 1;
//			}
//		}
//	} else if(state == 1) {
//		if(j == 0) {
//			DM_CS(0);
//		}
//		lib_spi0_dma_write((uint32_t)&i, 1);
//		state = 0;
//	}
//}

void dm_set_data(uint8_t index, uint8_t dat[8]) {
	
	uint8_t tmp[8];
//	// dat[8] 存到什么位置
//	// buff[8][列]
//	for(uint8_t i = 0; i < 8; i++) {
//		buff[i][index] = dat[i];
//	}
	
//	uint8_t tmp[8];
//	// dat[8] 存到什么位置
//	// buff[8][列]
	for(uint8_t i = 0; i < 8; i++) {
		buff[i][2 * index + 1] = dat[i];
	}
	
	/****************** 旋转 180度 ************************/
	/*
	///// 反转
	// 上下镜像
	for(uint8_t i = 0; i < 8; i++) {
		tmp[i] = dat[7 - i];
	}
	
	// 左右镜像
	for(uint8_t i = 0; i < 8; i++) {
		// tmp[i] 高位变低位
		tmp[i] = (tmp[i] & 0xF0) >> 4 | (tmp[i] & 0x0F) << 4;
		tmp[i] = (tmp[i] & 0xCC) >> 2 | (tmp[i] & 0x33) << 2;
		tmp[i] = (tmp[i] & 0xAA) >> 1 | (tmp[i] & 0x55) << 1;		
	}
	memcpy(buff[index], tmp, 8);
	*/


	/****************** 顺时针旋转 90度 ************************/
/*
	for(uint8_t i = 0; i < 8; i++) {
		//	data[i] b7 ---> tmp[0] b[7 - i]
		//	data[i] b6 ---> tmp[1] b[7 - i]
		//	data[i] b5 ---> tmp[2] b[7 - i]
		//	data[i] b4 ---> tmp[3] b[7 - i]
		//	data[i] b3 ---> tmp[4] b[7 - i]
		//	data[i] b2 ---> tmp[5] b[7 - i]
		//	data[i] b1 ---> tmp[6] b[7 - i]
		//	data[i] b0 ---> tmp[7] b[7 - i]
		
		for(uint8_t j = 0; j < 8; j++) {
			//	data[i] b[7-j] ---> tmp[j] b[7 - i]
			// tmp[j] b[7 - i] = 	data[i] b[7-j]
			
			if((dat[i] & (1 << (7-j))) == (1 << (7-j))) {
				tmp[j] |= (1 << (7 - i));
			} else {
				tmp[j] &= ~(1 << (7 - i));
			}
		}
	}
	
	//	// 左右镜像
	for(uint8_t i = 0; i < 8; i++) {
		// tmp[i] 高位变低位
		tmp[i] = (tmp[i] & 0xF0) >> 4 | (tmp[i] & 0x0F) << 4;
		tmp[i] = (tmp[i] & 0xCC) >> 2 | (tmp[i] & 0x33) << 2;
		tmp[i] = (tmp[i] & 0xAA) >> 1 | (tmp[i] & 0x55) << 1;
	}
	memcpy(buff[index], tmp, 8);
*/	
	
	/****************** 逆时针旋转 90度 ************************/
	/*
	for(uint8_t i = 0; i < 8; i++) {		
		for(uint8_t j = 0; j < 8; j++) {
			//	data[i] b[7-j] ---> tmp[j] b[7 - i]
			// tmp[j] b[7 - i] = 	data[i] b[7-j]
			
			if((dat[i] & (1 << (7-j))) == (1 << (7-j))) {
				tmp[j] |= (1 << (7 - i));
			} else {
				tmp[j] &= ~(1 << (7 - i));
			}
		}
	}
	
	// 上下镜像
	uint8_t tmp2[8];
	for(uint8_t i = 0; i < 8; i++) {
		tmp2[i] = tmp[7 - i];
	}
	memcpy(buff[index], tmp2, 8);
	*/
}

void dm_set_num(uint8_t index, uint8_t num) {
	if(num > 9) return;
	dm_set_data(index, table[num]);
}
