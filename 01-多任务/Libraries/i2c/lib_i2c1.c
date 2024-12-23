#include "lib_I2C1.h"

#if USE_LIB_I2C1

#define I2C1_SCL_AF					GPIO_AF_4
#define I2C1_SDA_AF					GPIO_AF_4


#if I2C1_SOFT
////////////////////////////////// SOFT ///////////////////////////////////////

#define SCL(BIT) 			gpio_bit_write(I2C1_SCL_PORT, I2C1_SCL_PIN, BIT?SET:RESET)
#define SDA(BIT) 			gpio_bit_write(I2C1_SDA_PORT, I2C1_SDA_PIN, BIT?SET:RESET)
#define SDA_STATE() 	gpio_input_bit_get(I2C1_SDA_PORT, I2C1_SDA_PIN)

#define SDA_IN()  		gpio_mode_set(I2C1_SDA_PORT, GPIO_MODE_INPUT,  GPIO_PUPD_NONE, I2C1_SDA_PIN)
#define SDA_OUT() 		gpio_mode_set(I2C1_SDA_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, I2C1_SDA_PIN)

#define DELAY()				delay_1us(5)
#define AWAIT()				delay_1us(1)

static void start();
static void stop();
static void send(uint8_t data);
static uint8_t recv();
static uint8_t wait_ack();
static void send_ack();
static void send_nack(); 


void lib_I2C1_init() {
    // ʱ������
    rcu_periph_clock_enable(I2C1_SCL_PORT_RCU);
    // �������ģʽ
    gpio_mode_set(I2C1_SCL_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, I2C1_SCL_PIN);
    gpio_output_options_set(I2C1_SCL_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, I2C1_SCL_PIN);

    // ʱ������
    rcu_periph_clock_enable(I2C1_SDA_PORT_RCU);
    // �������ģʽ
    gpio_mode_set(I2C1_SDA_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, I2C1_SDA_PIN);
    gpio_output_options_set(I2C1_SDA_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, I2C1_SDA_PIN);
}

uint8_t lib_I2C1_write(uint8_t addr, uint8_t reg, uint8_t* data, uint32_t len) {
    start();

    send(addr << 1);			//�����豸д��ַ
    if(wait_ack()) return 1;	//�ȴ���Ӧ

    send(reg);					//���ͼĴ�����ַ
    if(wait_ack()) return 2;	//�ȴ���Ӧ

    do {
        send(*data++);
        if(wait_ack()) return 3;
    } while(--len);

    stop();
    return 0;
}

uint8_t lib_I2C1_write2(uint8_t addr, uint8_t reg, uint8_t* data, uint32_t offset, uint32_t len) {
    start();

    send(addr << 1);			//�����豸д��ַ
    if(wait_ack()) return 1;	//�ȴ���Ӧ

    send(reg);					//���ͼĴ�����ַ
    if(wait_ack()) return 2;	//�ȴ���Ӧ

    do {
        send(*data);
        data += offset;
        if(wait_ack()) return 3;
    } while(--len);

    stop();
    return 0;
}

uint8_t lib_I2C1_read(uint8_t addr, uint8_t reg, uint8_t* data, uint32_t len) {
    start();

    send(addr << 1);				//�����豸д��ַ
    if(wait_ack()) return 1;		//�ȴ���Ӧ

    send(reg);						//���ͼĴ�����ַ
    if(wait_ack()) return 2;		//�ȴ���Ӧ

    start();
    send((addr << 1) | 0x01);		//�����豸����ַ
    if(wait_ack()) return 3;		//�ȴ���Ӧ

    do {
        *data = recv();
        data++;
        if(len != 1) send_ack();	// ���� NACK
    } while(--len);
    send_nack();					// ���� NACK
    stop();

    return 0;
}

void lib_I2C1_deinit() {
}

static void start() {
    SDA_OUT();

    SDA(1);
		DELAY();
    SCL(1);
    DELAY();

    SDA(0);
    DELAY();
    SCL(0);
    DELAY();
}

static void stop() {
    SDA_OUT();

    SCL(0);
    SDA(0);

    SCL(1);
    DELAY();
    SDA(1);
    DELAY();
}

static void send(uint8_t data) {
    uint8_t i;
    SDA_OUT();

    for(i = 0; i < 8; i++) {
        if(data & 0x80) {
            SDA(1);
        } else {
            SDA(0);
        }
				AWAIT();
        SCL(1);
        DELAY();
        SCL(0);
        DELAY();
        data <<= 1;
    }
}

static uint8_t recv() {
    uint8_t i, data;
    SDA_IN();
    data = 0;
    for(i = 0; i < 8; i++) {
        SCL(0);
        DELAY();
        SCL(1);
        DELAY();

        data <<= 1;

        data |= SDA_STATE();

        DELAY();
    }
    SCL(0);
    return data;
}

static uint8_t wait_ack() {
    int8_t retry = 10;

    SCL(0);
    SDA(1);
    SDA_IN();
    DELAY();
    SCL(1);
    DELAY();

    while(SDA_STATE() == 1 && retry > 0) {
        retry --;
        DELAY();
    }

    if(retry <= 0) {
        stop();
        return 1;
    } else {
        SCL(0);
        SDA_OUT();
    }
    return 0;
}

static void send_ack() {
    SDA_OUT();
    SCL(0);
    SDA(0);
    DELAY();

    SDA(0);

    SCL(1);
    DELAY();
    SCL(0);
    SDA(1);
}

static void send_nack() {
    SDA_OUT();
    SCL(0);
    SDA(0);
    DELAY();

    SDA(1);

    SCL(1);
    DELAY();
    SCL(0);
    SDA(1);
}


#else

////////////////////////////////// HARD ///////////////////////////////////////

#define I2Cx 			I2C1
#define I2Cx_RCU	RCU_I2C1

void lib_I2C1_init() {
    /****************** GPIO config **********************/
    // ʱ������
    rcu_periph_clock_enable(I2C1_SCL_PORT_RCU);
		// ���ø��ù���
    gpio_af_set(I2C1_SCL_PORT, I2C1_SDA_AF, I2C1_SCL_PIN);
		// �������ģʽ
    gpio_mode_set(I2C1_SCL_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, I2C1_SCL_PIN);
    gpio_output_options_set(I2C1_SCL_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_MAX, I2C1_SCL_PIN);
    
    // ʱ������
    rcu_periph_clock_enable(I2C1_SDA_PORT_RCU);
    // ���ø��ù���
    gpio_af_set(I2C1_SDA_PORT, I2C1_SDA_AF, I2C1_SDA_PIN);
		// �������ģʽ
    gpio_mode_set(I2C1_SDA_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, I2C1_SDA_PIN);
    gpio_output_options_set(I2C1_SDA_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_MAX, I2C1_SDA_PIN);
    
    /****************** I2C config  **********************/
    i2c_deinit(I2Cx);
    // ʱ������
    rcu_periph_clock_enable(I2Cx_RCU);
    // I2C��������
    i2c_clock_config(I2Cx, I2C1_SPEED, I2C_DTCY_2);

    // ʹ��i2c
    i2c_mode_addr_config(I2Cx, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, 0x00);
    i2c_enable(I2Cx);

    // i2c ack enable
		i2c_ack_config(I2Cx, I2C_ACK_ENABLE);	
}

static uint8_t I2C_wait(uint32_t flag) {
    uint16_t TIMEOUT = 50000;
    uint16_t cnt = 0;

    while(!i2c_flag_get(I2Cx, flag)) {
        cnt++;
        if(cnt > TIMEOUT) return 1;
    }
    return 0;
}

static uint8_t I2C_waitn(uint32_t flag) {
    uint16_t TIMEOUT = 50000;
    uint16_t cnt = 0;

    while(i2c_flag_get(I2Cx, flag)) {
        cnt++;
        if(cnt > TIMEOUT) return 1;
    }
		return 0;
}


uint8_t lib_I2C1_write(uint8_t addr, uint8_t reg, uint8_t* data, uint32_t data_len) {
    uint8_t address = addr << 1;
		
		/************* start ***********************/
		// �ȴ�I2C����
    if(I2C_waitn(I2C_FLAG_I2CBSY)) return 1;
	
    // start
    i2c_start_on_bus(I2Cx);
		
		 // �ȴ�I2C���豸�ɹ�������ʼ�ź�
    if(I2C_wait(I2C_FLAG_SBSEND)) return 2;
	
		/************* device address **************/
    // �����豸��ַ
    i2c_master_addressing(I2Cx, address, I2C_TRANSMITTER);
		 // �ȴ���ַ�������
    if(I2C_wait(I2C_FLAG_ADDSEND)) return 3;
    i2c_flag_clear(I2Cx, I2C_FLAG_ADDSEND);
	
		/************ register address ************/
    // �Ĵ�����ַ
    // �ȴ��������ݻ�����Ϊ��
    if(I2C_wait(I2C_FLAG_TBE)) return 4;
		
		// ��������
    i2c_data_transmit(I2Cx, reg);

    // �ȴ����ݷ������
    if(I2C_wait(I2C_FLAG_BTC)) return 5;
		
		/***************** data ******************/
    // ��������
    uint32_t i;
    for(i = 0; i < data_len; i++) {
        uint32_t d = data[i];

        // �ȴ��������ݻ�����Ϊ��
        if(I2C_wait(I2C_FLAG_TBE)) return 6;

        // ��������
        i2c_data_transmit(I2Cx, d);

        // �ȴ����ݷ������
        if(I2C_wait(I2C_FLAG_BTC)) return 7;
    }
		
		/***************** stop ********************/
    // stop
    i2c_stop_on_bus(I2Cx);
	
		return 0;
}

uint8_t lib_I2C1_write2(uint8_t addr, uint8_t reg, uint8_t* data, uint32_t offset, uint32_t len) {
    uint8_t address = addr << 1;
		
		/************* start ***********************/
		// �ȴ�I2C����
    if(I2C_waitn(I2C_FLAG_I2CBSY)) return 1;
	
    // start
    i2c_start_on_bus(I2Cx);
		
		 // �ȴ�I2C���豸�ɹ�������ʼ�ź�
    if(I2C_wait(I2C_FLAG_SBSEND)) return 2;
	
		/************* device address **************/
    // �����豸��ַ
    i2c_master_addressing(I2Cx, address, I2C_TRANSMITTER);
		 // �ȴ���ַ�������
    if(I2C_wait(I2C_FLAG_ADDSEND)) return 3;
    i2c_flag_clear(I2Cx, I2C_FLAG_ADDSEND);
	
		/************ register address ************/
    // �Ĵ�����ַ
    // �ȴ��������ݻ�����Ϊ��
    if(I2C_wait(I2C_FLAG_TBE)) return 4;
		
		// ��������
    i2c_data_transmit(I2Cx, reg);

    // �ȴ����ݷ������
    if(I2C_wait(I2C_FLAG_BTC)) return 5;
		
		/***************** data ******************/
    // ��������
		do {
        // �ȴ��������ݻ�����Ϊ��
        if(I2C_wait(I2C_FLAG_TBE)) return 6;

        // ��������
        i2c_data_transmit(I2Cx, *data);
				data += offset;

        // �ȴ����ݷ������
        if(I2C_wait(I2C_FLAG_BTC)) return 7;
    } while(--len);
		
		/***************** stop ********************/
    // stop
    i2c_stop_on_bus(I2Cx);
	
		return 0;
}


void lib_I2C1_deinit() {
		i2c_deinit(I2Cx);
}


uint8_t lib_I2C1_read(uint8_t addr, uint8_t reg, uint8_t* data, uint32_t len) {
		uint8_t address = addr << 1;
		
		/************* start ***********************/
    // �ȴ�I2C����
		if(I2C_waitn(I2C_FLAG_I2CBSY)) return 1;

    // ���������ź�
    i2c_start_on_bus(I2Cx);
		if(I2C_wait(I2C_FLAG_SBSEND)) return 2;

		/************* device address **************/
    // ���ʹ��豸��ַ
    i2c_master_addressing(I2Cx, address, I2C_TRANSMITTER);
		
		if(I2C_wait(I2C_FLAG_ADDSEND)) return 3;
		i2c_flag_clear(I2Cx, I2C_FLAG_ADDSEND);

		/********** register address **************/
		// �ȴ����ͻ�����	
    if(I2C_wait(I2C_FLAG_TBE)) return 4;
    
		// ���ͼĴ�����ַ
    i2c_data_transmit(I2Cx, reg);
		
		// �ȴ������������	
    if(I2C_wait(I2C_FLAG_BTC)) return 5;	
		if(I2C_wait(I2C_FLAG_TBE)) return 6;

		/************* start ***********************/
    // �����������ź�
    i2c_start_on_bus(I2Cx);
		
		if(I2C_wait(I2C_FLAG_SBSEND)) return 7;

		/************* device address **************/
    // ���ʹ��豸��ַ
    i2c_master_addressing(I2Cx, address, I2C_RECEIVER);
		if(I2C_wait(I2C_FLAG_ADDSEND)) return 8;
		i2c_flag_clear(I2Cx, I2C_FLAG_ADDSEND);


		/************* data **************/
		//ack
		i2c_ack_config(I2Cx, I2C_ACK_ENABLE);
		i2c_ackpos_config(I2Cx, I2C_ACKPOS_CURRENT);
		
    // ��ȡ����
		uint8_t i;
    for (i = 0; i < len; i++) {
				if(i != len - 1) {
						// �ȴ�ACK�������	
						if(I2C_wait(I2C_FLAG_BTC)) return 9;
				}
			
				// �ȴ�ACK���ݷ������
				// �ȴ����ջ�����	
				if(I2C_wait(I2C_FLAG_RBNE)) return 10;
        data[i] = i2c_data_receive(I2Cx);
			
        if (i == len - 1) {
            // �ڶ�ȡ���һ���ֽ�֮ǰ������ACK��������ֹͣ�ź�
						// �����Զ�NACK
						i2c_ack_config(I2Cx, I2C_ACK_DISABLE);
        }
    }
		
		/***************** stop ********************/
		i2c_stop_on_bus(I2Cx);
    return 0;
}

#endif

#endif