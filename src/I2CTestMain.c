#include "tm4c123gh6pm.h"
#include "I2C.h"
#include "UART0.h"
#include "TCS34725.h"
#include "MPU6050.h"
#include "ButtonLED.h"
#include "util.h"
#include "Servo.h"
#include "LCD.h"
#include <stdio.h>
#include <string.h>
#include "ModuleTest.h"

/* List of Predefined Macros for individual Peripheral Testing */
//#define DELAY
#define UART
#define TCS34725
//#define MPU6050
//#define SERVO
//#define LCD
//#define FULL_SYSTEM

int main(void){
	
	/* Peripheral Initialization */
	UART0_Init();
	LED_Init();
	BTN_Init();
	WTIMER0_Init();
	
	#if defined(TCS34725) || defined(MPU6050) || defined(LCD) || defined(FULL_SYSTEM)
	I2C0_Init();
	#endif
	
	#if defined(TCS34725) || defined(FULL_SYSTEM)
	/* Color Sensor Initialization */
	TCS34725_Init();
	#endif
	
	#if defined(MPU6050) || defined(FULL_SYSTEM)
	/* MPU6050 Initialization */
	MPU6050_Init();
	#endif
	
	#if defined(SERVO) || defined(FULL_SYSTEM)
	/* Servo Initialization */
	Servo_Init();
	#endif
	
	#if defined(LCD) || defined(FULL_SYSTEM)
	/* LCD Initialization */
	LCD_Init();
	#endif
	
	while(1){
		
		#ifdef DELAY
		Module_Test(DELAY_TEST);
		#endif
		
		#ifdef UART
		Module_Test(UART_TEST);
		#endif
		
		#ifdef TCS34725
		Module_Test(TCS34725_TEST);
		#endif	
		
	}
	
	return 0;
}
