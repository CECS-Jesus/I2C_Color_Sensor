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
static int num[100];
static float flt[100];
static char letters[100];
/* RGB Color Struct Instance */
RGB_COLOR_HANDLE_t RGB_COLOR;
	
/* MPU6050 Struct Instance */
MPU6050_ACCEL_t Accel_Instance;
MPU6050_GYRO_t 	Gyro_Instance;
MPU6050_ANGLE_t Angle_Instance;

static void Test_Delay(void) {
	LEDs ^= RED;				//Toggle Red Led
	DELAY_1MS(500);				//Delay for 0.5s using millisecond delay
}

static void Test_UART(void) {
	UART0_OutString("This is a test string\r\n");				//Print "This is a test string" with newline and cursor return escape character
	/*DUMMY_FILL*/
	UART0_InString(printBuf, 100);
	sscanf(printBuf, "%s %d %f\r\n", letters, num, flt);
	// 1. Construct a string with letters, decimal numbers and floats using sprintf
	sprintf(printString, "\r\nLetters: %s, Number: %d, Float: %.2f\r\n", letters, *num, *flt);
	// 2. Send the string to PC serial terminal for display	
	UART0_OutString(printString);
	// 3. Delay for 1s using ms delay function
	DELAY_1MS(1000);
}

static void Test_MPU6050(void){
	/* Grab Accelerometer and Gyroscope Raw Data*/
	/*CODE_FILL*/
		
	/* Process Raw Accelerometer and Gyroscope Data */
	/*CODE_FILL*/
		
	/* Calculate Tilt Angle */
	/*CODE_FILL*/
		
	/* Format buffer to print data and angle */
	/*CODE_FILL*/
	
	DELAY_1MS(50);
}

static void Test_TCS34725(void) {
	/* Grab Raw Color Data From Sensor */
	/*CODE_FILL*/
		
	/* Process Raw Color Data to RGB Value */
	/*CODE_FILL*/
		
	/* Change Onboard RGB LED Color to Detected Color */
	switch(CODE_FILL){
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
	/*CODE_FILL*/
		
	/* Print String to Terminal through USB */
	/*CODE_FILL*/
		
	DELAY_1MS(10);
}

static void Test_Servo(void){
	/*
	 * In this test, follow the series of steps below (each step requires a 1s delay after)
	 * 1. Drive Servo to 0 degree
	 * 2. Drive Servo to -45 degree
	 * 3. Drive Servo to 0 degree
	 * 4. Drive Servo to 45 degree
	 * 5. Drive Servo to 0 degree
	 * 6. Drive Servo to -90 degree
	 * 7. Drive Servo to 0 degree
	 * 8. Drive Servo to 90 degree
	 */ 
	
	/*CODE_FILL*/
	
}

static void Test_LCD(void){
	/* Print Name to LCD at Center Location */
	/*CODE_FILL*/
}

static void Test_Full_System(void){
	/* Grab Accelerometer and Gyroscope Raw Data*/
	/*CODE_FILL*/
		
	/* Process Raw Accelerometer and Gyroscope Data */
	/*CODE_FILL*/
		
	/* Calculate Tilt Angle */
	/*CODE_FILL*/
		
	/* Drive Servo Accordingly to Tilt Angle on X-Axis*/
	/*CODE_FILL*/
		
	/* Format buffer to print MPU6050 data and angle */
	/*CODE_FILL*/
		
	/* Grab Raw Color Data From Sensor */
	/*CODE_FILL*/
		
	/* Process Raw Color Data to RGB Value */
	/*CODE_FILL*/
		
	/* Change Onboard RGB LED Color to Detected Color */
	switch(CODE_FILL) {
		case RED_DETECT:
			LEDs = RED;
			strcpy(colorString, "RED");
			break;
		case GREEN_DETECT:
			LEDs = GREEN;
			strcpy(colorString, "GREEN");
			break;
		case BLUE_DETECT:
			LEDs = BLUE;
			strcpy(colorString, "BLUE");
			break;
		case NOTHING_DETECT:
			LEDs = DARK;
			strcpy(colorString, "NA");
			break;
	}
		
	/* Format String to Print RGB value*/
	/*CODE_FILL*/
		
	/* Print String to Terminal through USB */
	/*CODE_FILL*/
		
	/* Update LCD With Current Angle and Color Detected */
//	sprintf(angleBuf, "Angle:%0.2f\0", Angle_Instance.ArX);				//Format String to print angle to 2 Decimal Place
//	sprintf(colorBuf, "Color:%s\0", colorString);									//Format String to print color detected

	sprintf(angleBuf, "Angle:%0.2f", Angle_Instance.ArX);				//Format String to print angle to 2 Decimal Place
	sprintf(colorBuf, "Color:%s", colorString);									//Format String to print color detected
	
	/*CODE_FILL*/						//Clear LCD
	/*CODE_FILL*/						//Safety Delay of 2ms
	/*CODE_FILL*/						//Set Cursor to Row 1 Column 0
	/*CODE_FILL*/						//Print angleBuf String on LCD
	/*CODE_FILL*/						//Safety Delay of 2ms
	/*CODE_FILL*/						//Set Cursor to Row 2 Column 1
	/*CODE_FILL*/						//Print colorBuf String on LCD	
		
	DELAY_1MS(20);
}

void Module_Test(MODULE_TEST_NAME test) {
	
	switch(test){
		case DELAY_TEST:
			Test_Delay();
			break;
		
		case UART_TEST:
			Test_UART();
			break;
		
		case MPU6050_TEST:
			Test_MPU6050();
			break;
		
		case TCS34725_TEST:
			Test_TCS34725();
			break;
		
		case SERVO_TEST:
			Test_Servo();
			break;
		
		case LCD_TEST:
			Test_LCD();
			break;
			
		case FULL_SYSTEM_TEST:
			Test_Full_System();
			break;
		
		default:
			break;
	}
	
}

 