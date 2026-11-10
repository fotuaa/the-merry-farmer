#ifndef CALEND_H
#define CALEND_H

#include <stdio.h>

typedef struct {
	int current_day;
	int current_hour;
} CALEND;


////////////////////////////////
//
//  Функции работы с Временем
//

void calendStart(CALEND* calend);
void calendPrint(CALEND* calend, FILE* file);
int calendMove(CALEND* calend, int cntHours);
int calendIsNight(CALEND* calend);
void calendNextDay(CALEND* calend);

#endif // !CALEND_H