#ifndef UTILS_H
#define UTILS_H


#define MAX_LENGHT_NAME 30

#define FILE_ITEMS "items_eng.txt"
#define FILE_DIARY "diary.txt"

#define FILE_INPUT "input.txt"
#define FILE_OUTPUT "output.txt"


typedef struct {
	int current_day;
	int current_hour;
} CALEND;


////////////////////////////////
//
//  Ввод чисел и строк от пользователя
//

int  getNumber();
int  getString(char* question, char* str);



////////////////////////////////
//
//  Ввод Ид слота и Ид предмета от пользователя
//

int  getSlot(char* question);
int  getItem(char* question, char items[][MAX_LENGHT_NAME]);


////////////////////////////////
//
//  Функции работы с Предметами 
//

/*
 * Печатает список предметов
 * @param items массив предметов
 * @return
 */
void printItems(char items[][MAX_LENGHT_NAME], FILE* file);
int  findIdByName(char item_name[MAX_LENGHT_NAME], char items[][MAX_LENGHT_NAME]);
void initItems(char items[][MAX_LENGHT_NAME]);


////////////////////////////////
//
//  Функции работы с Временем
//

void calendStart(CALEND* calend);
void calendPrint(CALEND* calend, FILE* file);
int calendMove(CALEND* calend, int cntHours);
int calendIsNight(CALEND* calend);
void calendNextDay(CALEND* calend);


////////////////////////////////
//
//  Записать состояние в дневник
//

void saveDiary(char farmer_name[MAX_LENGHT_NAME_FARMER],
	int current_day, int current_hour,
	int inventory[MAX_INVENTORY], char items[MAX_ITEMS][MAX_LENGHT_NAME],
	char pathOut);


////////////////////////////////
//
//  Анализ логов
//

void analyseLogFile();

#endif // !UTILS_H
