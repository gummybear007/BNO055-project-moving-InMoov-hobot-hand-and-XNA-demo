
//#include "main.h"
#include "stm32l1xx_i2c.h"
#include "i2c.h"
#include "stm32l1xx.h"
#include "main.h"

//-------------------------------------------



void I2C1_init(void){


	
	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;

	// enable APB1 peripheral clock for I2C1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	// enable clock for SCL and SDA pins
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	/* setup SCL and SDA pins
	 * You can connect the I2C1 functions to two different
	 * pins:
	 * 1. SCL on PB6 or PB8  
	 * 2. SDA on PB7 or PB9
	 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // we are going to use PB6 and PB9
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;			// set pins to alternate function
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;		// set GPIO speed
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;			// set output to open drain --> the line has to be only pulled low, not driven high
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;			// enable pull up resistors
						// init GPIOB

	// Connect I2C1 pins to AF  
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);	// SCL
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1); // SDA
	
	

	// configure I2C1 
	I2C_InitStruct.I2C_ClockSpeed = I2C_SPEED; 		// 100kHz
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;			// I2C mode
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;	// 50% duty cycle --> standard
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;			// own address, not relevant in master mode
	I2C_InitStruct.I2C_Ack = I2C_Ack_Disable;		// disable acknowledge when reading (can be changed later on)
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; // set address length to 7 bit addresses
	// init I2C1

	// enable I2C1
	I2C_Cmd(I2C1, ENABLE);
  I2C_Init(I2C1, &I2C_InitStruct);
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void I2C2_init(void){


	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;

	// enable APB1 peripheral clock for I2C1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	// enable clock for SCL and SDA pins
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	/* setup SCL and SDA pins
	 * You can connect the I2C1 functions to two different
	 * pins:
	 * 1. SCL on PB10  
	 * 2. SDA on PB11
	 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; // we are going to use PB6 and PB9
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;							// set pins to alternate function
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;		// set GPIO speed
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;			// set output to open drain --> the line has to be only pulled low, not driven high
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;			// enable pull up resistors
						// init GPIOB

	// Connect I2C1 pins to AF  
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);	// SCL
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2); // SDA

	// configure I2C1 
	I2C_InitStruct.I2C_ClockSpeed = I2C_SPEED; 		// 100kHz
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;			// I2C mode
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;	// 50% duty cycle --> standard
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;			// own address, not relevant in master mode
	I2C_InitStruct.I2C_Ack = I2C_Ack_Disable;		// disable acknowledge when reading (can be changed later on)
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; // set address length to 7 bit addresses
					// init I2C1

	// enable I2C1
	I2C_Cmd(I2C2, ENABLE);
  I2C_Init(I2C2, &I2C_InitStruct);
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/* This function issues a start condition and 
 * transmits the slave address + R/W bit
 * 
 * Parameters:
 * 		I2Cx --> the I2C peripheral e.g. I2C1
 * 		address --> the 7 bit slave address
 * 		direction --> the transmission direction can be:
 * 						I2C_Direction_Tranmitter for Master transmitter mode
 * 						I2C_Direction_Receiver for Master receiver
 */
void I2C_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction){
	// wait until I2C1 is not busy any more
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
  
	// Send I2C1 START condition 
	I2C_GenerateSTART(I2Cx, ENABLE);

	// wait for I2C1 EV5 --> Slave has acknowledged start condition
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

	// Send slave Address for write 
	I2C_Send7bitAddress(I2Cx, address, direction);

	/* wait for I2Cx EV6, check if 
	 * either Slave has acknowledged Master transmitter or
	 * Master receiver mode, depending on the transmission
	 * direction
	 */ 
	if(direction == I2C_Direction_Transmitter){
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	}
	else if(direction == I2C_Direction_Receiver){
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}
}


/* This function transmits one byte to the slave device
 * Parameters:
 *		I2Cx --> the I2C peripheral e.g. I2C1 
 *		data --> the data byte to be transmitted
 */
void I2C_write(I2C_TypeDef* I2Cx, uint8_t data)
{
	// wait for I2C1 EV8 --> last byte is still being transmitted (last byte in SR, buffer empty), next byte can already be written
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
	I2C_SendData(I2Cx, data);
}

/* This function reads one byte from the slave device 
 * and acknowledges the byte (requests another byte)
 */
uint8_t I2C_read_ack(I2C_TypeDef* I2Cx){
	// enable acknowledge of received data
	uint8_t data;
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	// wait until one byte has been received
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
	// read data from I2C data register and return data byte
	data = I2C_ReceiveData(I2Cx);
	return data;
}

/* This function reads one byte from the slave device
 * and doesn't acknowledge the received data 
 * after that a STOP condition is transmitted
 */
uint8_t I2C_read_nack(I2C_TypeDef* I2Cx){
	// disable acknowledge of received data
	// nack also generates stop condition after last byte received
	// see reference manual for more info
	uint8_t data;
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	I2C_GenerateSTOP(I2Cx, ENABLE);
	// wait until one byte has been received
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
	// read data from I2C data register and return data byte
	data = I2C_ReceiveData(I2Cx);
	return data;
}

/* This function issues a stop condition and therefore
 * releases the bus
 */
void I2C_stop(I2C_TypeDef* I2Cx){
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
	// Send I2C1 STOP Condition after last byte has been transmitted
	I2C_GenerateSTOP(I2Cx, ENABLE);
	// wait for I2C1 EV8_2 --> byte has been transmitted
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}


unsigned char read_byte_am(unsigned char adr,unsigned char reg)
{
	unsigned char dat;
	I2C_start(I2C1,(uint8_t)(adr <<1), I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
	I2C_write(I2C1, reg); // write one byte to the slave
	I2C_stop(I2C1); // stop the transmission
	delay(2);
	I2C_start(I2C1, adr <<1, I2C_Direction_Receiver); // start a transmission in Master receiver mode
	dat = I2C_read_nack(I2C1); // read one byte and don't request another byte, stop transmissio
	return dat;
}

void write_byte_am(unsigned char adr, unsigned char reg,unsigned char dat)
{

	I2C_start(I2C1,(uint8_t) (adr <<1), I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
	I2C_write(I2C1, reg); // write one byte to the slave
	I2C_write(I2C1, dat); // write one byte to the slave
	I2C_stop(I2C1); // stop the transmission

}

unsigned char read_byte_am2(unsigned char adr,unsigned char reg)
{
	unsigned char dat;
	I2C_start(I2C2,(uint8_t)(adr <<1), I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
	I2C_write(I2C2, reg); // write one byte to the slave
	I2C_stop(I2C2); // stop the transmission
	delay(2);
	I2C_start(I2C2, adr <<1, I2C_Direction_Receiver); // start a transmission in Master receiver mode
	dat = I2C_read_nack(I2C2); // read one byte and don't request another byte, stop transmissio
	return dat;
}

void write_byte_am2(unsigned char adr, unsigned char reg,unsigned char dat)
{

	I2C_start(I2C2,(uint8_t) (adr <<1), I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
	I2C_write(I2C2, reg); // write one byte to the slave
	I2C_write(I2C2, dat); // write one byte to the slave
	I2C_stop(I2C2); // stop the transmission

}
