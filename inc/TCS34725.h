/*
 * TCS34725.h
 *
 *	Provides functions to interact with TCS34725
 *	RGB color sensor
 *
 *	Datasheet Link: https://cdn-shop.adafruit.com/datasheets/TCS34725.pdf
 *
 * Created on: May 24th, 2023
 *		Author: Jackie Huynh
 *
 */
 
#ifndef TCS34725_H_
#define TCS34725_H_

#include <stdint.h>
#include "util.h"

/* List of Fill In Macros (Not all need to be filled)

IMPORTANT: BEFORE FILLING MACROS READ THE COMMENT BELOW

NOT ALL MACROS NEED TO BE FILLED OUT. REFERENCE TCS34725.c
TO FIGURE OUT WHAT'S NECESSARY (Filling it all out will not
incure any penelties but will be a waste of time)

Comment Out All Macros that are not used

*/

//Macros of TCS34725 Registers Address (Based on Datasheet)
#define TCS34725_ADDR			   		(0x29)

/*************Command Register*************/
#define TCS34725_CMD					(0x80)

/*************Enable Registers*************/
#define TCS34725_ENABLE					(0x00)
#define TCS34725_ENABLE_PON				(0x01)
#define TCS34725_ENABLE_AEN				(0x02)
#define TCS34725_ENABLE_WEN				(0x08)
#define TCS34725_ENABLE_AIEN			(0x10)
		
/**********RGBC Timing Registers***********/
#define TCS34725_RGBC				 (0x01)
#define TCS34725_RGBC_2_4			 (0xFF)
//	#define TCS34725_RGBC_24				()
//	#define TCS34725_RGBC_101				()
//	#define TCS34725_RGBC_154				()
//	#define TCS34725_RGBC_700				()
	
/***********Wait Time Registers************/
//#define TCS34725_WAIT_TIME				(0x00U)
//	#define TCS34725_WAIT_TIME_2_4	(0x00U)
//	#define TCS34725_WAIT_TIME_204	(0x00U)
//	#define TCS34725_WAIT_TIME_614	(0x00U)
	
/****RGBC Interrupt Threshold Registers****/
//#define TCS34725_AILTL						()
//#define TCS34725_AILTH						()
//#define TCS34725_AIHTL						()
//#define TCS34725_AIHTH						()

/**********Persistance Registers***********/
//#define TCS34725_PERSIS						()
//	#define TCS34725_PERSIS_EVERY		()
//	#define TCS34725_PERSIS_1				()
//	#define TCS34725_PERSIS_2				()
//	#define TCS34725_PERSIS_3				()
//	#define TCS34725_PERSIS_5				()
//	#define TCS34725_PERSIS_10			()
//	#define TCS34725_PERSIS_15			()
//	#define TCS34725_PERSIS_20			()
//	#define TCS34725_PERSIS_25			()
//	#define TCS34725_PERSIS_30			()
//	#define TCS34725_PERSIS_35			()
//	#define TCS34725_PERSIS_40			()
//	#define TCS34725_PERSIS_45			()
//	#define TCS34725_PERSIS_50			()
//	#define TCS34725_PERSIS_55			()
//	#define TCS34725_PERSIS_60			()
	
/*************Config Registers*************/
//#define TCS34725_CONFIG						()
//	#define TCS34725_CONFIG_WLONG		()
	
/************Control Registers*************/
#define TCS34725_CTRL				(0x0F)
#define TCS34725_CTRL_AGAIN_1		(0x00)
//	#define TCS34725_CTRL_AGAIN_4		()
//	#define TCS34725_CTRL_AGAIN_16	()
//	#define TCS34725_CTRL_AGAIN_60	()
	
/**************ID Registers****************/
#define TCS34725_ID					(0x12)

/*************Status Registers*************/
//#define TCS34725_STATUS						()
//	#define TCS34725_STATUS_AVALID	()
//	#define TCS34725_STATUS_AINT		()
	
/***********Color Data Registers***********/
#define TCS34725_CDATAL 					(0x14) 
#define TCS34725_CDATAH 					(0x15) 
#define TCS34725_RDATAL 					(0x16) 
#define TCS34725_RDATAH 					(0x17) 
#define TCS34725_GDATAL 					(0x18) 
#define TCS34725_GDATAH 					(0x19) 
#define TCS34725_BDATAL 					(0x1A) 
#define TCS34725_BDATAH 					(0x1B) 

/*************Expected Values**************/
#define TCS34725_EXPECTED_ID			(0x4D)

/* Custom Return Type */
typedef enum{
	RED_DETECT 		= 0,
	GREEN_DETECT 	= 1,
	BLUE_DETECT 	= 2,
	NOTHING_DETECT	= 3
} COLOR_DETECTED;

/* Data Struct to store RGB color values */
typedef struct{
	uint16_t R_RAW;
	uint16_t G_RAW;
	uint16_t B_RAW;
	uint16_t C_RAW;
	
	float R;
	float G;
	float B;
} RGB_COLOR_HANDLE_t;

/*	-------------------TCS34725_Init------------------
 *	Basic Initialization Function for TCS34725 at default settings
 *	Input: none
 *	Output: none
 */
void TCS34725_Init(void);

/*	---------------TCS34725_GET_RAW_CLEAR-------------
 *	Receive RAW clear data reading from the sensor
 *	Input: none
 *	Output: Returns 16-bit RAW clear data
 */
uint16_t TCS34725_GET_RAW_CLEAR(void);

/*	---------------TCS34725_GET_RAW_RED---------------
 *	Receive RAW red data reading from the sensor
 *	Input: none
 *	Output: Returns 16-bit RAW red data
 */
uint16_t TCS34725_GET_RAW_RED(void);

/*	---------------TCS34725_GET_RAW_GREEN-------------
 *	Receive RAW green data reading from the sensor
 *	Input: none
 *	Output: Returns 16-bit RAW green data
 */
uint16_t TCS34725_GET_RAW_GREEN(void);

/*	---------------TCS34725_GET_RAW_BLUE-------------
 *	Receive RAW blue data reading from the sensor
 *	Input: none
 *	Output: Returns 16-bit RAW blue data
 */
uint16_t TCS34725_GET_RAW_BLUE(void);

/*	---------------TCS34725_GET_RGB------------------
 *	Normalize RAW data into RGB range (0-255)
 *	Input: RGB Color User Instance Struct
 *	Output: none
 */
void TCS34725_GET_RGB(RGB_COLOR_HANDLE_t* RGB_COLOR_Instance);

/*	-----------------Detect_Color--------------------
 *	Detect which color is more prominant and returns that color
 *	Input: RGB Color User Instance Struct
 *	Output: COLOR_DETECTED enum value
 */
COLOR_DETECTED Detect_Color(RGB_COLOR_HANDLE_t* RGB_COLOR_Instance);

#endif
