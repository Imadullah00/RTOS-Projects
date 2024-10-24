/*
 * led_effect.c
 *
 *  Created on: Sep 29, 2024
 *      Author: ImadF
 */

#include "main.h"

void turnON_all();
void turnOFF_all();
void turnON_even();
void turnON_odd();
void led_effect_1();		// toggle all LEDs together
void led_effect_2();
void led_effect_3();
void led_effect_4();

extern TimerHandle_t sw_timer_handles [4];

void led_effect_stop()
{
	for(int i = 0; i<4; i++)
	{
		xTimerStop(sw_timer_handles[i],portMAX_DELAY);
	}

}

void led_effect(int n)
{
	led_effect_stop();
	xTimerStart(sw_timer_handles[n-1], portMAX_DELAY);

}

void LED_control(int value)
{
	for(int i = 0; i<4; i++)
	{
		HAL_GPIO_WritePin(GPIOD, (LED1 << i), ((value >> i)& 0x1));
	}
}
void led_effect_1()		// toggle all LEDs together
{
	static int flag = 1;
	(flag ^= 1) ? turnOFF_all() : turnON_all();
}

void led_effect_2()
{
	static int flag = 1;
	(flag ^= 1) ? turnON_even() : turnON_odd();
}

void led_effect_3()
{
	static int i = 0;
	LED_control(0x1 <<  (i++%4));
}

void led_effect_4()
{
	static int i =0;
	LED_control(0x08 >> (i++%4));
}


void turnON_all()
{
	HAL_GPIO_WritePin(GPIOD, LED1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, LED2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, LED3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, LED4, GPIO_PIN_SET);
}

void turnOFF_all()
{
	HAL_GPIO_WritePin(GPIOD, LED1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, LED2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, LED3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, LED4, GPIO_PIN_RESET);
}

void turnON_even()
{
	HAL_GPIO_WritePin(GPIOD, LED1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, LED2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, LED3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, LED4, GPIO_PIN_SET);
}

void turnON_odd()
{
	HAL_GPIO_WritePin(GPIOD, LED1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, LED2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, LED3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, LED4, GPIO_PIN_RESET);
}



