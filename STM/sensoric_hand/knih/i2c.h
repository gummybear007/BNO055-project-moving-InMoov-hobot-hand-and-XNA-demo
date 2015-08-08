
#define	USE_STM32L152_EVAL
#define SLAVE_ADDRESS1 0x28 //address for lsm9ds0 accelerometer + magnetometer
#define SLAVE_ADDRESS2 0x29	//address for lsm9ds0 gyro
#define I2C_SPEED 100000 //100Khz speed for I2C


#define SENSORS_I2C_SCL_GPIO_PORT         GPIOB
#define SENSORS_I2C_SCL_GPIO_CLK          RCC_AHBPeriph_GPIOB
#define SENSORS_I2C_SCL_GPIO_PIN          GPIO_Pin_10
#define SENSORS_I2C_SCL_GPIO_PINSOURCE    GPIO_PinSource10
 
#define SENSORS_I2C_SDA_GPIO_PORT         GPIOB
#define SENSORS_I2C_SDA_GPIO_CLK          RCC_AHBPeriph_GPIOB
#define SENSORS_I2C_SDA_GPIO_PIN          GPIO_Pin_11
#define SENSORS_I2C_SDA_GPIO_PINSOURCE    GPIO_PinSource11

#define SENSORS_I2C_RCC_CLK               RCC_APB1Periph_I2C2
#define SENSORS_I2C_AF                    GPIO_AF_I2C2

extern void I2C1_init(void);
void I2C2_init(void);

unsigned char read_byte_am(unsigned char adr,unsigned char reg);
void write_byte_am(unsigned char adr,unsigned char reg,unsigned char dat);
unsigned char read_byte_am2(unsigned char adr,unsigned char reg);
void write_byte_am2(unsigned char adr, unsigned char reg,unsigned char dat);


