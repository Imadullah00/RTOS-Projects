/*
 * RTC.c
 *
 *  Created on: Sep 29, 2024
 *      Author: ImadF
 */
#include "main.h"
#include "string.h"
#include <stdio.h>

extern RTC_HandleTypeDef hrtc;
extern QueueHandle_t q_print;

void show_time_date()
{
	static char showtime[40];
	static char showdate[40];

	RTC_DateTypeDef rtc_date;
	RTC_TimeTypeDef rtc_time;

	static char* time = showtime;
	static char* date = showdate;

	memset(&rtc_date,0,sizeof(rtc_date));
	memset(&rtc_time,0,sizeof(rtc_time));

	//get the RTC current time
	HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);

	//get the RTC current date
	HAL_RTC_GetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN);

	char* format;
	format = (rtc_time.TimeFormat == RTC_HOURFORMAT12_AM) ? "AM" : "PM";

	//display the time --> hh:mm:ss [AM/PM]
	sprintf((char*)showtime, "%s: \t%02d:%02d:%02d [%s]", "\n Current time & date", rtc_time.Hours, rtc_time.Minutes, rtc_time.Seconds, format);
	xQueueSend(q_print,&time,portMAX_DELAY);

	//display the date---> dd/mm/yyyy
	sprintf((char*)showdate, "\t%02d-%02d-%02d\n", rtc_date.Date, rtc_date.Month, 2000 + rtc_date.Year);
	xQueueSend(q_print,&date, portMAX_DELAY );
}

void show_time_date_itm()
{


	RTC_DateTypeDef rtc_date;
	RTC_TimeTypeDef rtc_time;

	memset(&rtc_date,0,sizeof(rtc_date));
	memset(&rtc_time,0,sizeof(rtc_time));

	//get the RTC current time
	HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);

	//get the RTC current date
	HAL_RTC_GetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN);

	char* format;
	format = (rtc_time.TimeFormat == RTC_HOURFORMAT12_AM) ? "AM" : "PM";

	printf("%02d:%02d:%02d [%s]", rtc_time.Hours, rtc_time.Minutes, rtc_time.Seconds, format);
	printf("\t%02d-%02d-%02d\n", rtc_date.Date, rtc_date.Month, 2000 + rtc_date.Year);

}


void rtc_configure_time(RTC_TimeTypeDef* time)
{
	time->TimeFormat = RTC_HOURFORMAT12_AM;
	HAL_RTC_SetTime(&hrtc, time, RTC_FORMAT_BIN);
}

void rtc_configure_date(RTC_DateTypeDef* date)
{
	HAL_RTC_SetDate(&hrtc, date, RTC_FORMAT_BIN);
}


uint8_t rtc_validate_info(RTC_TimeTypeDef* time,RTC_DateTypeDef* date )
{
	if(time)
	{
		if(time->Hours>12 || time->Minutes >59 || time->Seconds>59)
		{
			return 1;
		}

	}
	if(date)
	{
		if(date->Date>31 || date->Month >12 || date->WeekDay>7 || date->Year>99)
		{
			return 1;
		}
	}

	return 0;

}
