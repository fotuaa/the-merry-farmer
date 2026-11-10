#include "calend.h"
#include <stdio.h>

////////////////////////////////
//
//  Функции работы с Временем
//

void calendStart(CALEND* calend) {

	calend->current_day = 1;
	calend->current_hour = 8;
}

void calendPrint(CALEND* calend, FILE* file) {

	fprintf(file, "Текущее время: День %d, %s%d:00.\n",
		calend->current_day, ((calend->current_hour < 10) ? "0" : ""), calend->current_hour);
}

int calendMove(CALEND* calend, int cntHours) {

	int maxHours = 0;

	// не летаем в прошлое и по ночам
	if ((cntHours <= 0) || (calend->current_hour >= 2 && calend->current_hour < 8))
		return 0;

	maxHours = (calend->current_hour >= 8) ? 26 - calend->current_hour : 2 - calend->current_hour;

	if (maxHours > cntHours) {
		maxHours = cntHours;
	}


	calend->current_hour += maxHours;
	calend->current_day += (int)(calend->current_hour / 24);
	calend->current_hour = calend->current_hour % 24;
	return maxHours;

}

int calendIsNight(CALEND* calend) {
	return (calend->current_hour >= 2 && calend->current_hour < 8) ? 1 : 0;
}

void calendNextDay(CALEND* calend) {
	calend->current_day++;
	calend->current_hour = 8;
}
