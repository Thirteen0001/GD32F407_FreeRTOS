#include "DHT11.h"

#define	DHT_OUT()	gpio_mode_set(DHT_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, DHT_PIN)
#define DHT_IN()  	gpio_mode_set(DHT_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, DHT_PIN)


#define DHT(bit)	gpio_bit_write(DHT_PORT, DHT_PIN, bit ? SET : RESET)
#define DHT_VAL()	gpio_input_bit_get(DHT_PORT, DHT_PIN)

#define wait_level_change(level, min, max, desc)  	cnt = 0; \
												do {  \
													delay_1us(1); \
													cnt++;  \
												}while(DHT_VAL() == level); \
												if (cnt < min || cnt > max) { \
													printf("%s err: %d\n", desc, (int)cnt); \
													return -1; \
												}


static void GPIO_config(rcu_periph_enum rcu, uint32_t port, uint32_t pin) {
    rcu_periph_clock_enable(DHT_RCU);
    gpio_output_options_set(DHT_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, DHT_PIN);
}


void DHT11_init() {
    GPIO_config(DHT_RCU, DHT_PORT, DHT_PIN);
    DHT_OUT();
}

// 返回-1：获取数据失败， 返回0：获取数据成功
char DHT11_get_humidity_temperature(int *humidity, float *temperature) {
    u16 cnt;
    u8 i, j;
    u8 dat[5] = {0}; // 5个字节，1个字节8位
    float temp;
    DHT_OUT(); // 输出模式
    // 1. 主机(stc8h) 拉低  18ms ~ 30ms (默认为高电平)
    DHT(0);
    delay_1ms(20);
    DHT(1);

    DHT_IN(); // 输入模式
    // 2. 主机释放总时间 10us ~ 35us
    cnt = 0;
    do {
        delay_1us(1);
        cnt++;
        //   在50次内，才进入，超过50次，说明，DHT11坏了
    } while(DHT_VAL() == 1 && cnt < 50);

    if (cnt < 10 || cnt > 35) {
        printf("%s err: %d\n", "主机释放总时间", (int)cnt);
        return -1; // 结束函数
    }

    // 3. 响应低电平时间 78us ~ 88us
    wait_level_change(0, 78, 88, "响应低电平时间");

    // 4. 响应高电平时间 80us ~ 92us
    wait_level_change(1, 80, 92, "响应高电平时间");

    // 5. 收到主机起始信号后，传感器一次性从数据总线（SDA)串出40位数据，高位先出
    // 40位数据，1字节8位，需要5个字节
    for(i = 0; i < 5; i++) { // i = 0~ 4
        for(j = 0; j < 8; j++) { // j = 0~7
            // 5.1 信号低电平时间 50us ~ 58us
            wait_level_change(0, 50, 58, "信号低电平时间");

            // 5.2 真正的0、1数据 23us ~74 us
            // 信号0 高电平时间  23us ~ 27us
            // 信号1 高电平时间  68us ~ 74us
            cnt = 0;
            do {
                delay_1us(1);
                cnt++;
            } while(DHT_VAL() == 1);

            // 左移1位，留一个位置放内容
            dat[i] <<= 1;

            // cnt >= 68  数字1，其它数字0
            if (cnt >= 68) {
                // 数字1
                dat[i] |= 0x01;
            } // else不用处理，默认就是0

        }
    }

    // 6. 数据校验
    // 湿度高 8 位    湿度低 8 位        温度高 8 位    温度低 8 位    校验位
    //   dat[0]        dat[1]              dat[2]         dat[3]        dat[4]
    // printf("%#x, %#x, %#x, %#x, %#x\n", (int)dat[0], (int)dat[1], (int)dat[2], (int)dat[3], (int)dat[4]);

    // 6.1 校验位＝湿度高位+湿度低位+温度高位+温度低位
    if (dat[0] + dat[1] + dat[2] + dat[3] != dat[4]) {
        printf("数据校验失败\n");
        return -1; // 结束函数
    }

    // 6.2 湿度高位为湿度整数部分数据，湿度低位为湿度小数部分数据，其中湿度小数部分为 0
    // 2个%输出1个%
    // printf("湿度：%d %%\n", (int)dat[0]);
    *humidity = dat[0];

    // 6.3 温度高位为温度整数部分数据，温度低位为温度小数部分数据(1位小数点)
    temp = dat[2] + (dat[3] & 0x7f) * 0.1;
    // 且温度低位 Bit7 (最高位) 为 1 则表示负温度，否则为正温度
    if (dat[3] & 0x80) { // 负数
        temp = temp * -1;
    }
    // printf("温度：%.1f °\n", temp);

    *temperature = temp;

    return 0;
}