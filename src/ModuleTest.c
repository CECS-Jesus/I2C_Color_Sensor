/*
 * ModuleTest.c
 *
 *	Provides the testing functions all of individual peripheral testing
 *	and full system testing
 *
 * Created on: September 3rd, 2023
 *		Author: Jackie Huynh
 *
 */
 
#include "ModuleTest.h"
#include "TCS34725.h"
#include "MPU6050.h"
#include "UART0.h"
#include "Servo.h"
#include "LCD.h"
#include "I2C.h"
#include "util.h"
#include "ButtonLED.h"
#include "tm4c123gh6pm.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static char printBuf[100];
static char angleBuf[LCD_ROW_SIZE];
static char colorBuf[LCD_ROW_SIZE];
static char colorString[6];
static char printString[100];
static char printColor[100];
static int num[100];
static float flt[100];
static char letters[100];
/* RGB Color Struct Instance */
RGB_COLOR_HANDLE_t RGB_COLOR;
	
static void Test_Delay(void) {
	LEDs ^= RED;	//Toggle Red Led
	DELAY_1MS(500);	//Delay for 0.5s using millisecond delay
}

static void Test_UART(void) {
	UART0_OutString("This is a test string\r\n");	//Print "This is a test string" with newline and cursor return escape character
	UART0_InString(printBuf, 100);
	sscanf(printBuf, "%s %d %f\r\n", letters, num, flt);
	// 1. Construct a string with letters, decimal numbers and floats using sprintf
	sprintf(printString, "\r\nLetters: %s, Number: %d, Float: %.2f\r\n", letters, *num, *flt);
	// 2. Send the string to PC serial terminal for display	
	UART0_OutString(printString);
	// 3. Delay for 1s using ms delay function
	DELAY_1MS(1000);
}

static void Test_TCS34725(void) {
	/* Grab Raw Color Data From Sensor */
	RGB_COLOR_HANDLE_t color_data;
	
	color_data.C_RAW = TCS34725_GET_RAW_CLEAR();
	color_data.R_RAW = TCS34725_GET_RAW_RED();
	color_data.G_RAW = TCS34725_GET_RAW_GREEN();
	color_data.B_RAW = TCS34725_GET_RAW_BLUE();
		
	/* Process Raw Color Data to RGB Value */
	TCS34725_GET_RGB(&color_data);
	
	COLOR_DETECTED color = Detect_Color(&color_data);
	
	/* Change Onboard RGB LED Color to Detected Color */
	switch(color){
		case RED_DETECT:
			LEDs = RED;
			break;
		case GREEN_DETECT:
			LEDs = GREEN;
			break;
		case BLUE_DETECT:
			LEDs = BLUE;
			break;
		case NOTHING_DETECT:
			LEDs = DARK;
			break;
		}
		
	/* Format String to Print */
	sprintf(printColor, "R: %0.2f, G: %0.2f, B: %0.2f/r/n", color_data.R, color_data.G, color_data.B);
		
	/* Print String to Terminal through USB */
	UART0_OutString(printColor);
		
	DELAY_1MS(10);
}

void Module_Test(MODULE_TEST_NAME test) {
	switch(test){
		case DELAY_TEST:
			Test_Delay();
			break;
		
		case UART_TEST:
			Test_UART();
			break;
		
		case TCS34725_TEST:
			Test_TCS34725();
			break;
		
		default:
			break;
	}
}

 
