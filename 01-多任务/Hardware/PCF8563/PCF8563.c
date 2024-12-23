#include "PCF8563.h"

// PCF8563初始化
void PCF8563_init() {
}

// 设置时间
void PCF8563_set_clock(Clock_t temp) {
	u8 p[7] = {0}; 
	
	// =========================== 日期、时间设置 ===========================
	//  十进制  转换为   16进制 格式存储  BCD
    // 秒的寄存器地址为： 0x02
    // 秒:  第0~3位记录个位，第4~6位记录十位   
	p[0] = WRITE_BCD(temp.second);
    // 分: 第0~3位，保存个数，第4到6位，保存十位
	p[1] = WRITE_BCD(temp.minute);
    // 时：第0~3位，保存个数，第4到5位，保存十位
	p[2] = WRITE_BCD(temp.hour);
    // 日：第0~3位，保存个数，第4到5位，保存十位
	p[3] = WRITE_BCD(temp.day);
    // 周：第0~2位，保存个数
	p[4] = WRITE_BCD(temp.weekday);// 星期天为0   其它正常表示
    // 月_世纪:  第0~3位记录个位，第4位记录十位，第7位为0，世纪数为20xx，为1，世纪数为21xx
	p[5] = WRITE_BCD(temp.month);
	// 假如  年份为20xx 往后的
	if (temp.year < 2100 ) { // 2000 ~ 2099 < 2100
		// 第7位为0，世纪数为20xx
		
		p[5] &= ~(1 << 7);
		
	} else {
		// 第7位为1，世纪数为21xx
		p[5] |= (1 << 7);
		
	}
    // 年：第0~3位，保存个数，第4到7位，保存十位
	// 假如年为 2024   存储的是  24      计算出 2  和  4
	//   2024  %  10 ===   4    个位
	//   2024  % 100 / 10  === 2   十位
	p[6] = WRITE_BCD(temp.year  % 100); // 24作为参数
	
	// I2C 写
	I2C_WriteNbyte(PCF8563_DEV_ADDR, PCF8563_REG_SECOND, p, 7);
}

// 获取时间
void PCF8563_get_clock(Clock_t * p) {
	u8 temp[7] = {0};
	u8 flag;
	
	// I2C 读,  读操作也是用写的地址，因为内部根据写地址，转换为读地址
	I2C_ReadNbyte(PCF8563_DEV_ADDR, PCF8563_REG_SECOND, temp, 7);

	// 秒的寄存器地址为： 0x02
	// 秒:  第0~3位记录个位，第4~6位记录十位
	p->second = READ_BCD(temp[0]);
	// 分: 第0~3位，保存个数，第4到6位，保存十位
	p->minute = READ_BCD(temp[1]);
	// 时：第0~3位，保存个数，第4到5位，保存十位
	p->hour = READ_BCD(temp[2]);
	// 日：第0~3位，保存个数，第4到5位，保存十位
	p->day = READ_BCD(temp[3]);
	// 周：第0~2位，保存个数
	p->weekday = READ_BCD(temp[4]); // 星期天为0   其它正常表示
	// 月_世纪:  第0~3位记录个位，第4位记录十位，第7位为0，世纪数为20xx，为1，世纪数为21xx
	// 取出标志位后，把标志位置0
	flag = (temp[5] >> 7) & 1;
	temp[5] &= ~(1 << 7);
	p->month = READ_BCD(temp[5]);

	// 年：第0~3位，保存个数，第4到7位，保存十位
	p->year = READ_BCD(temp[6]); // 得到24
	if (flag == 0) {
		p->year = 2000 + p->year;
	} else {
		p->year = 2100 + p->year;
	}

}

// ==================闹钟=====================
// 设置闹钟
void PCF8563_set_alarm(Alarm_t alarm) {
	u8 p[4];
	
	// ======================= 第7位 不做处理，默认就是0
    // 分: 第0~3位,记录个数, 第4~6位记录十位, 第7位：置0启动, 置1禁用
	if (alarm.minute != -1) {
		p[0] = WRITE_BCD(alarm.minute);
	} else {
		p[0] = 0x80; // 第7位：置1禁用
		// p[0] |= (1 << 7);
	}
    // 时: 第0~3位,记录个数, 第4~5位记录十位, 第7位：置0启动, 置1禁用
	p[1] = alarm.hour != -1 ? WRITE_BCD(alarm.hour) : 0x80;
    // 日: 第0~3位,记录个数, 第4~5位记录十位, 第7位：置0启动, 置1禁用
	p[2] = alarm.day != -1 ? WRITE_BCD(alarm.day) : 0x80;  
    // 周: 第0~2位,记录个数, 第7位：置0启动, 置1禁用
	p[3] = alarm.weekday != -1 ? WRITE_BCD(alarm.weekday) : 0x80;
	
	// I2C 写
	I2C_WriteNbyte(PCF8563_DEV_ADDR, 0x09, p, 4);
}

// 启用闹钟
void PCF8563_enable_alarm() {
	u8 cfg;
    //a) 读原来的配置(不要乱改配置，只改自己的位，其它维持不变)
	I2C_ReadNbyte(PCF8563_DEV_ADDR, 0x01, &cfg, 1);
    //b) 在原来配置的基础上，清除标志位  第3位：置0清除标志位，置1维持不变
	cfg	&= ~(1 << 3); // 第3位置0清除标志位
    //c) 在原来配置基础上，启动闹钟，第1位：置0禁用，置1启动 
	cfg	|= (1 << 1);	// 第1位 置1启动 
    //d) 重新写入配置
	I2C_WriteNbyte(PCF8563_DEV_ADDR, 0x01, &cfg, 1);

}

// 禁用闹钟Alarm
void PCF8563_disable_alarm() {
	u8 cfg;
    //a) 读原来的配置(不要乱改配置，只改自己的位，其它维持不变)
	I2C_ReadNbyte(PCF8563_DEV_ADDR, 0x01, &cfg, 1);
    //b) 在原来配置的基础上，清除标志位  第3位：置0清除标志位，置1维持不变
	cfg	&= ~(1 << 3); // 第3位置0清除标志位
    //c) 在原来配置基础上，启动闹钟，第1位：置0禁用，置1启动 
	cfg	&= ~(1 << 1);	// 第1位 置0禁用 
    //d) 重新写入配置
	I2C_WriteNbyte(PCF8563_DEV_ADDR, 0x01, &cfg, 1);
}

// 清理闹钟标记
void PCF8563_alarm_clear_flag() {
	u8 cfg;
	
	//a) 读原来的配置(不要乱改配置，只改自己的位，其它维持不变)
	I2C_ReadNbyte(PCF8563_DEV_ADDR, 0x01, &cfg, 1);
    //b) 在原来配置的基础上，清除标志位  第3位：置0清除标志位，置1维持不变
	cfg	&= ~(1 << 3); // 第3位置0清除标志位
    //c) 重新写入配置
	I2C_WriteNbyte(PCF8563_DEV_ADDR, 0x01, &cfg, 1);
}

//=============================定时器
// 启动定时器
void PCF8563_enable_timer() {
	u8 cfg;
    //a) 读原来的配置(不要乱改配置，只改自己的位，其它维持不变)
	I2C_ReadNbyte(PCF8563_DEV_ADDR, 0x01, &cfg, 1);
    //b) 在原来配置的基础上，清除标志位，第2位：置0清除标志位，置1维持不变 
	cfg	&= ~(1 << 2); // 第2位置0清除标志位
    //c) 在原来配置基础上，启动定时器，第0位：置0禁用，置1启用 
	cfg	|= (1 << 0);	// 第0位 置1启动 
    //d) 重新写入配置
	I2C_WriteNbyte(PCF8563_DEV_ADDR, 0x01, &cfg, 1);
}

// 禁用定时器
void PCF8563_disable_timer() {
	u8 cfg;
    //a) 读原来的配置(不要乱改配置，只改自己的位，其它维持不变)
	I2C_ReadNbyte(PCF8563_DEV_ADDR, 0x01, &cfg, 1);
    //b) 在原来配置的基础上，清除标志位，第2位：置0清除标志位，置1维持不变 
	cfg	&= ~(1 << 2); // 第2位置0清除标志位
    //c) 在原来配置基础上，启动定时器，第0位：置0禁用，置1启用 
	cfg	&= ~(1 << 0);	// 第0位 置0禁用 
    //d) 重新写入配置
	I2C_WriteNbyte(PCF8563_DEV_ADDR, 0x01, &cfg, 1);
}

// 清除定时器标志位
void PCF8563_clear_timer() {
	u8 cfg;
	
    //a) 读原来的配置(不要乱改配置，只改自己的位，其它维持不变)
	I2C_ReadNbyte(PCF8563_DEV_ADDR, 0x01, &cfg, 1);
    //b) 在原来配置的基础上，清除标志位，第2位：置0清除标志位，置1维持不变 
	cfg	&= ~(1 << 2); // 第2位置0清除标志位
    //c) 重新写入配置
	I2C_WriteNbyte(PCF8563_DEV_ADDR, 0x01, &cfg, 1);
}

// 设置定时器，参数1：时钟频率 参数2：倒计时计算值，时间为：参数2/参数1
void PCF8563_set_timer(TimerFreq freq, u8 countdown) {
	u8 p[2];
    //a) 时钟频率
    // 第7位为0，定时器禁用，第七位为1，定时器启用
	p[0] = freq + 0x80;
    //b) 计数值(0~255) ===》时间为： 计数值/时钟频率 
	p[1] = countdown;
	// I2C 写
	I2C_WriteNbyte(PCF8563_DEV_ADDR, 0x0e, p, 2);
}

// EXTI5_on_trig 在EXTI.h里面有声明
void EXTI5_on_trig(void) {
	u8 cfg;
	// 读取原来的配置
	I2C_ReadNbyte(PCF8563_DEV_ADDR, 0x01, &cfg, 1);
	
	// 如果是闹钟，第1位和第3位是1    非0就是真 
	if ((cfg & 0x02) && (cfg & 0x08)) {
	
		#if USE_ALARM
		PCF8563_on_alarm(); // 函数调用
		#endif
		
		// ============闹钟清除标志位，才可以重复使用==============
		PCF8563_alarm_clear_flag();
	}
	
	// 如果是定时器，第0位和第2位是1 
	// if ((cfg >> 0 & 1) && (cfg >> 2 & 1)) { 
	if ((cfg & 0x01) && (cfg & 0x04)) {
		#if USE_TIMER
		PCF8563_on_timer(); // 函数调用
		#endif
		
		// ============定时器清除标志位，才可以重复使用==============
		PCF8563_clear_timer();
	}
}