/*
 * TCS34725.c
 *
 *	Main implementation of the functions to interact with
 *	the TCS34725 RGB Color Sensor
 *
 */

#include "TCS34725.h"
#include "I2C.h"
#include "UART0.h"
#include "util.h"
#include <stdio.h>
#include "tm4c123gh6pm.h"

/*	-------------------TCS34725_Init------------------
 *	Basic Initialization Function for TCS34725 at default settings
 *	Input: none
 *	Output: none
 */
void TCS34725_Init(void){
	uint8_t ret;																//Temp Variable to hold return values
	char printBuf[20];													//String buffer to print
	
	/* Check if RGB Color Sensor has been detected */
	ret = I2C0_Receive(TCS34725_ADDR, TCS34725_CMD|TCS34725_ID);
	
	//Print ID or Error to Terminal
	sprintf(printBuf, "ID: %x\r\n", ret);
	UART0_OutString(printBuf);
	
	if(ret != TCS34725_EXPECTED_ID){
		UART0_OutString("TCS34725 has not been Detected\r\n");
		return;
	}
	UART0_OutString("TCS34725 has been Detected\r\n");
	
	/* Setting Integration Time */
	ret = I2C0_Transmit(TCS34725_ADDR, TCS34725_CMD|TCS34725_RGBC, TCS34725_RGBC_2_4);
	if(ret != 0)
		UART0_OutString("Error on Transmit\r\n");
	else
		UART0_OutString("TCS34725 Integration Time Set\r\n");
	
	//Necessary Delay when setting integration time. This varies for which integration time is choosen
	DELAY_1MS(3);
	
	/* Setting Gain */
	ret = I2C0_Transmit(TCS34725_ADDR, TCS34725_CMD|TCS34725_CTRL, TCS34725_CTRL_AGAIN_1);
	if(ret != 0)
		UART0_OutString("Error on Transmit\r\n");
	else
		UART0_OutString("TCS34725 Gain Set\r\n");
	
	/* Powering On Sensor */
	ret = I2C0_Transmit(TCS34725_ADDR, TCS34725_CMD|TCS34725_ENABLE, TCS34725_ENABLE_PON);
	if(ret != 0)
		UART0_OutString("Error on Transmit\r\n");
	else
		UART0_OutString("TCS34725 Power On\r\n");

	//Nessessary Delay When Powering On Module
	DELAY_1MS(3);
	
	/* Enabling RGBC 2-Channel ADC */
	ret = I2C0_Transmit(TCS34725_ADDR, TCS34725_CMD|TCS34725_ENABLE, TCS34725_ENABLE_PON |TCS34725_ENABLE_AEN);
	if(ret != 0)
		UART0_OutString("Error on Transmit\r\n");
	else
		UART0_OutString("TCS34725 RGBC On\r\n");
	
	//Integration Time Delay when Activating. Varies with Integration Time Choosen by User
	DELAY_1MS(3);
	
	UART0_OutString("TCS34725 Color Sensor Initialized\r\n");
	
}

/*	---------------TCS34725_GET_RAW_CLEAR-------------
 *	Receive RAW clear data reading from the sensor
 *	Input: none
 *	Output: Returns 16-bit RAW clear data
 */
uint16_t TCS34725_GET_RAW_CLEAR(void){
	uint8_t CLEAR_LOW;
	uint8_t CLEAR_HIGH;
	uint16_t CLEAR_DATA;
	
	/* Use I2C to grab both HIGH and LOW data */
	CLEAR_LOW = I2C0_Receive(TCS34725_ADDR, TCS34725_CMD|TCS34725_CDATAL);
	CLEAR_HIGH = I2C0_Receive(TCS34725_ADDR, TCS34725_CMD|TCS34725_CDATAH);
	
	/* Concatanate into 16-bit value */
	CLEAR_DATA = ((uint16_t)CLEAR_HIGH << 8) | CLEAR_LOW;
	
	//Integration Time Delay
	DELAY_1MS(3);
	
	return CLEAR_DATA;
}

/*	---------------TCS34725_GET_RAW_RED---------------
 *	Receive RAW red data reading from the sensor
 *	Input: none
 *	Output: Returns 16-bit RAW red data
 */
uint16_t TCS34725_GET_RAW_RED(void){
	uint8_t RED_LOW;
	uint8_t RED_HIGH;
	uint16_t RED_DATA;
	
	/* Use I2C to grab both HIGH and LOW data */
	RED_LOW = I2C0_Receive(TCS34725_ADDR, TCS34725_CMD|TCS34725_RDATAL);
	RED_HIGH = I2C0_Receive(TCS34725_ADDR, TCS34725_CMD|TCS34725_RDATAH);
	
	/* Concatanate into 16-bit value */
	RED_DATA = ((uint16_t)RED_HIGH << 8) | RED_LOW;
	
	//Integration Time Delay
	DELAY_1MS(3);
	
	return RED_DATA;
}

/*	---------------TCS34725_GET_RAW_GREEN-------------
 *	Receive RAW green data reading from the sensor
 *	Input: none
 *	Output: Returns 16-bit RAW green data
 */
uint16_t TCS34725_GET_RAW_GREEN(void){
	uint8_t GREEN_LOW;
	uint8_t GREEN_HIGH;
	uint16_t GREEN_DATA;
	
	/* Use I2C to grab both HIGH and LOW data */
	GREEN_LOW = I2C0_Receive(TCS34725_ADDR, TCS34725_CMD|TCS34725_GDATAL);
	GREEN_HIGH = I2C0_Receive(TCS34725_ADDR, TCS34725_CMD|TCS34725_GDATAH);
	
	/* Concatanate into 16-bit value */
	GREEN_DATA = ((uint16_t)GREEN_HIGH << 8) | GREEN_LOW;
	
	//Integration Time Delay
	DELAY_1MS(3);
	
	return GREEN_DATA;
}

/*	---------------TCS34725_GET_RAW_BLUE-------------
 *	Receive RAW blue data reading from the sensor
 *	Input: none
 *	Output: Returns 16-bit RAW blue data
 */
uint16_t TCS34725_GET_RAW_BLUE(void){
	uint8_t BLUE_LOW;
	uint8_t BLUE_HIGH;
	uint16_t BLUE_DATA;
	
	/* Use I2C to grab both HIGH and LOW data */
	BLUE_LOW = I2C0_Receive(TCS34725_ADDR, TCS34725_CMD|TCS34725_BDATAL);
	BLUE_HIGH = I2C0_Receive(TCS34725_ADDR, TCS34725_CMD|TCS34725_BDATAH);
	
	/* Concatanate into 16-bit value*/
	BLUE_DATA = ((uint16_t)BLUE_HIGH << 8) | BLUE_LOW;
	
	//Integration Time Delay
	DELAY_1MS(3);
	
	return BLUE_DATA;
}

/*	---------------TCS34725_GET_RGB------------------
 *	Normalize RAW data into RGB range (0-255)
 *	Input: RGB Color Struct User Instance
 *	Output: none
 */
void TCS34725_GET_RGB(RGB_COLOR_HANDLE_t* RGB_COLOR_Instance){
	
	/* Prevent Dividing by 0 by checking if the C_RAW value from struct is equal to 0 */
	if (RGB_COLOR_Instance->C_RAW == 0){
		RGB_COLOR_Instance->R = RGB_COLOR_Instance->G = RGB_COLOR_Instance->B = 0;
		return;
	}
	
	/*
	Divide all RGB value with their (RAW Value / Clear Raw Value) and multiple everything with 255.0
	Store in RGB Color Instance Struct
	*/ 
	RGB_COLOR_Instance->R = ((float)RGB_COLOR_Instance->R_RAW / (float)RGB_COLOR_Instance->C_RAW) * 255.0;
  RGB_COLOR_Instance->G = ((float)RGB_COLOR_Instance->G_RAW / (float)RGB_COLOR_Instance->C_RAW) * 255.0;
  RGB_COLOR_Instance->B = ((float)RGB_COLOR_Instance->B_RAW / (float)RGB_COLOR_Instance->C_RAW) * 255.0;
	
}

/*	-----------------Detect_Color--------------------
 *	Detect which color is more prominant and returns that color
 *	Input: RGB Color User Instance Struct
 *	Output: COLOR_DETECTED enum value
 */
COLOR_DETECTED Detect_Color(RGB_COLOR_HANDLE_t* RGB_COLOR_Instance){
	
	/* Compare all values with eachother and return which color is prominent using enum type */
	if(RGB_COLOR_Instance->R > RGB_COLOR_Instance->G && RGB_COLOR_Instance->R > RGB_COLOR_Instance->B)
		return RED_DETECT;
	else if(RGB_COLOR_Instance->G > RGB_COLOR_Instance->R && RGB_COLOR_Instance->G > RGB_COLOR_Instance->B)
		return GREEN_DETECT;
	else if(RGB_COLOR_Instance->B > RGB_COLOR_Instance->R && RGB_COLOR_Instance->B > RGB_COLOR_Instance->G)
		return BLUE_DETECT;
	
	/* Otherwise no color is being detected */
	return NOTHING_DETECT;
}
