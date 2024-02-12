/*
 * I2C.h
 *
 *	Main implementation of the I2C Init, Read, and Write Function
 *
 * Created on: May 24th, 2023
 *		Author: Jackie Huynh
 *
 */
 
#include "I2C.h"
#include "tm4c123gh6pm.h"

/*
 *	-------------------I2C0_Init------------------
 *	Basic I2C Initialization function for master mode @ 100kHz
 *	Input: None
 *	Output: None
 */
void I2C0_Init(void){
	
	/* Enable Required System Clock */
	SYSCTL_RCGC1_R |= EN_I2C0_CLOCK;		//Enable I2C0 System Clock
	SYSCTL_RCGC2_R |= EN_GPIOB_CLOCK;		//Enable GPIOB System Clock
	
	//Wait Until GPIOx System Clock is enabled
	while((SYSCTL_RCGC2_R&EN_GPIOB_CLOCK)!= EN_GPIOB_CLOCK);
	
	/* GPIOx I2C Alternate Function Setup	*/
	GPIO_PORTB_DEN_R |= I2C0_PINS;			//Enable Digital I/O
	GPIO_PORTB_AFSEL_R |= I2C0_PINS;		//Enable Alternate Function Selection
	
	//Select I2C0 as the alternate function 
	GPIO_PORTB_PCTL_R |= (GPIO_PORTB_PCTL_R & 0xFFFF00FF) + I2C0_ALT_FUNC_SET;
	GPIO_PORTB_ODR_R |= I2C0_SDA_PIN;		//Enable Open Drain for SDA pin
	GPIO_PORTB_AMSEL_R &= I2C0_PINS;		//Disable Analog Mode
	
	/*	I2C0 Setup as Master Mode @ 100kBits	*/
	I2C0_MCR_R |= EN_I2C0_MASTER;			//Configure I2C0 as Master 
	
	/* Configuring I2C Clock Frequency to 100KHz
		
		TPR = (System Clock / (2*(SCL_LP + SCL_HP) * SCL_CLK)) - 1
		SCL_LP and SCL_HP are fixed
		SCL_LP = 6 & SCL_HP = 4
		
		Example if we want to configure I2C speed to 100kHz for 40MHz system clock
		TPR = (40MHz / ((2*(6+4)) * 100kHz)) - 1 		(Convert Everything to Hz)
		TPR = 19
		
	*/
	
	I2C0_MTPR_R = I2C0_CLOCK_VALUE;
}

/*
 *	-------------------I2C0_Receive------------------
 *	Polls to receive data from specified peripheral
 *	Input: Slave address & Slave Register Address
 *	Output: Returns 8-bit data that has been received
 */
uint8_t I2C0_Receive(uint8_t slave_addr, uint8_t slave_reg_addr){

	char error;						//Temp Variable to hold errors

	/* Check if I2C0 is busy */
	while((I2C0_MCS_R&I2C_MCS_BUSY) == I2C_MCS_BUSY);

	/* Configure I2C0 Slave Address and Read Mode */
	I2C0_MSA_R = (slave_addr << 1);		//Slave Address is the 7 MSB
	I2C0_MDR_R = slave_reg_addr;		//Set Data Register to which register needs to be read

	/* Initiate I2C by generating a START & RUN cmd */
	I2C0_MCS_R = I2C_MCS_START | I2C_MCS_RUN;

	/* Wait until write is done*/
	while((I2C0_MCS_R&I2C_MCS_BUSY) == I2C_MCS_BUSY);

	/* Set I2C to Receive with Slave Address */
	I2C0_MSA_R = (slave_addr << 1) + I2C_MSA_RS;

	/* Initiate I2C by generating a repeated START, STOP, & RUN cmd */
	I2C0_MCS_R = I2C_MCS_START | I2C_MCS_STOP | I2C_MCS_RUN;

	/* Wait until I2C bus is not busy */
	while((I2C0_MCS_R&I2C_MCS_BUSY) == I2C_MCS_BUSY);

	/* Check for any error: read the error flag */
	error = I2C0_MCS_R & I2C_MCS_ERROR;
	if(error != 0)
		return error;
	
	return I2C0_MDR_R & I2C_MDR_DATA_M;
}

/*
 *	-------------------I2C0_Transmit------------------
 *	Transmit a byte of data to specified peripheral
 *	Input: Slave address, Slave Register Address, Data to Transmit
 *	Output: Any Errors if detected, otherwise 0
 */
uint8_t I2C0_Transmit(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t data){

	char error;							//Temp Variable to hold errors

	/* Check if I2C0 is busy */
	while(CODE_FILL);

	/* Configure I2C Slave Address, R/W Mode, and what to transmit */
	I2C0_MSA_R = CONSTANT_FILL;			//Slave Address is the first 7 MSB
	I2C0_MSA_R &= ~I2C0_RW_PIN;			//Clear LSB to write
	I2C0_MDR_R = CONSTANT_FILL;			//Transmit register addr to interact

	/* Initiate I2C by generate a START bit and RUN cmd */
	I2C0_MCS_R = CODE_FILL;

	/* Wait until write has been completed */
	while(CODE_FILL);

	/* Set Data Reg to desired transmission */
	I2C0_MDR_R = CONSTANT_FILL; 

	/* Initiate I2C by generating a STOP & RUN cmd */
	I2C0_MCS_R = CODE_FILL;

	/* Wait until write has been completed */
	while(CODE_FILL);

	/* Wait until bus isn't busy */
	while(CODE_FILL);

	/* Check for any error */
	error = CODE_FILL;
	if(error != 0)
		return error;
	else
		return 0;
	
}

//Has Yet to be Implemented
/*
 *	----------------I2C0_Burst_Receive-----------------
 *	Polls to receive multiple bytes of data from specified
 *  peripheral by incrementing starting slave register address
 *	Input: Slave address, Slave Register Address, Data Buffer
 *	Output: None
 */
void I2C0_Burst_Receive(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t* data, uint32_t size){
	
}

/*
 *	----------------I2C0_Burst_Transmit-----------------
 *	Transmit multiple bytes of data to specified peripheral
 *  by incrementing starting slave address
 *	Input: Slave address, Slave Register Address, Data Buffer to transmit
 *	Output: None
 */
uint8_t I2C0_Burst_Transmit(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t* data, uint32_t size){

	char error;							//Temp Error Variable

	/* Asserting Param */
	if(size <= 0)
		return 0;

	/* Check if I2C0 is busy */
	while(CODE_FILL);

	/* Configure I2C Slave Address, R/W Mode, and what to transmit */
	I2C0_MSA_R = CONSTANT_FILL;				//Slave Address is the first 7 MSB
	I2C0_MSA_R &= CONSTANT_FILL;			//Clear LSB to write
	I2C0_MDR_R = CONSTANT_FILL;				//Transmit register addr to interact

	/* Initiate I2C by generate a START bit and RUN cmd */
	I2C0_MCS_R = CODE_FILL;

	/* Wait until write has been completed */
	while(CODE_FILL);

	/* Loop to Burst Transmit what is stored in data buffer */
	while(size > 1){
		
		I2C0_MDR_R = CONSTANT_FILL;			//Deference Pointer from data array and load into data reg. Post-Increment the pointer after
		I2C0_MCS_R = RUN_CMD;				//Initiate I2C RUN CMD
		while(CODE_FILL);					//Wait until transmit is complete
		size--;								//Reduce size until 1 is left
		
	}

	I2C0_MDR_R = CONSTANT_FILL;				//Deference Pointer from data array and load into data reg
	I2C0_MCS_R = CODE_FILL;					//Initiate I2C STOP condition and RUN CMD

	/* Wait until write has been completed */
	while(CODE_FILL);

	/* Wait until bus isn't busy */
	while(CODE_FILL);

	/* Check for any error */
	error = CODE_FILL;
	if(error != 0)
		return error;
	else
		return 0;
}
