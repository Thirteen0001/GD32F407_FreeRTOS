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

// ����-1����ȡ����ʧ�ܣ� ����0����ȡ���ݳɹ�
char DHT11_get_humidity_temperature(int *humidity, float *temperature) {
    u16 cnt;
    u8 i, j;
    u8 dat[5] = {0}; // 5���ֽڣ�1���ֽ�8λ
    float temp;
    DHT_OUT(); // ���ģʽ
    // 1. ����(stc8h) ����  18ms ~ 30ms (Ĭ��Ϊ�ߵ�ƽ)
    DHT(0);
    delay_1ms(20);
    DHT(1);

    DHT_IN(); // ����ģʽ
    // 2. �����ͷ���ʱ�� 10us ~ 35us
    cnt = 0;
    do {
        delay_1us(1);
        cnt++;
        //   ��50���ڣ��Ž��룬����50�Σ�˵����DHT11����
    } while(DHT_VAL() == 1 && cnt < 50);

    if (cnt < 10 || cnt > 35) {
        printf("%s err: %d\n", "�����ͷ���ʱ��", (int)cnt);
        return -1; // ��������
    }

    // 3. ��Ӧ�͵�ƽʱ�� 78us ~ 88us
    wait_level_change(0, 78, 88, "��Ӧ�͵�ƽʱ��");

    // 4. ��Ӧ�ߵ�ƽʱ�� 80us ~ 92us
    wait_level_change(1, 80, 92, "��Ӧ�ߵ�ƽʱ��");

    // 5. �յ�������ʼ�źź󣬴�����һ���Դ��������ߣ�SDA)����40λ���ݣ���λ�ȳ�
    // 40λ���ݣ�1�ֽ�8λ����Ҫ5���ֽ�
    for(i = 0; i < 5; i++) { // i = 0~ 4
        for(j = 0; j < 8; j++) { // j = 0~7
            // 5.1 �źŵ͵�ƽʱ�� 50us ~ 58us
            wait_level_change(0, 50, 58, "�źŵ͵�ƽʱ��");

            // 5.2 ������0��1���� 23us ~74 us
            // �ź�0 �ߵ�ƽʱ��  23us ~ 27us
            // �ź�1 �ߵ�ƽʱ��  68us ~ 74us
            cnt = 0;
            do {
                delay_1us(1);
                cnt++;
            } while(DHT_VAL() == 1);

            // ����1λ����һ��λ�÷�����
            dat[i] <<= 1;

            // cnt >= 68  ����1����������0
            if (cnt >= 68) {
                // ����1
                dat[i] |= 0x01;
            } // else���ô���Ĭ�Ͼ���0

        }
    }

    // 6. ����У��
    // ʪ�ȸ� 8 λ    ʪ�ȵ� 8 λ        �¶ȸ� 8 λ    �¶ȵ� 8 λ    У��λ
    //   dat[0]        dat[1]              dat[2]         dat[3]        dat[4]
    // printf("%#x, %#x, %#x, %#x, %#x\n", (int)dat[0], (int)dat[1], (int)dat[2], (int)dat[3], (int)dat[4]);

    // 6.1 У��λ��ʪ�ȸ�λ+ʪ�ȵ�λ+�¶ȸ�λ+�¶ȵ�λ
    if (dat[0] + dat[1] + dat[2] + dat[3] != dat[4]) {
        printf("����У��ʧ��\n");
        return -1; // ��������
    }

    // 6.2 ʪ�ȸ�λΪʪ�������������ݣ�ʪ�ȵ�λΪʪ��С���������ݣ�����ʪ��С������Ϊ 0
    // 2��%���1��%
    // printf("ʪ�ȣ�%d %%\n", (int)dat[0]);
    *humidity = dat[0];

    // 6.3 �¶ȸ�λΪ�¶������������ݣ��¶ȵ�λΪ�¶�С����������(1λС����)
    temp = dat[2] + (dat[3] & 0x7f) * 0.1;
    // ���¶ȵ�λ Bit7 (���λ) Ϊ 1 ���ʾ���¶ȣ�����Ϊ���¶�
    if (dat[3] & 0x80) { // ����
        temp = temp * -1;
    }
    // printf("�¶ȣ�%.1f ��\n", temp);

    *temperature = temp;

    return 0;
}