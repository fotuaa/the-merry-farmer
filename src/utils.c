#define _CRT_SECURE_NO_WARNINGS

#include "utils.h"
#include <stdio.h>

////////////////////////////////
//
//  Ввод чисел и строк от пользователя
//

int  getNumber() {

	int num;
	while (scanf("%d", &num) != 1) {
		printf("Вы ошиблись, введите число: ");
		while (getchar() != '\n');
	}
	while (getchar() != '\n');

	return num;
}

int  getString(char* question, char* str) {

	printf("%s", question);

	if (fgets(str, sizeof(str), stdin) != NULL) {
		str[strcspn(str, "\n")] = 0;
	}
	else {
		str[0] = '\0';
	}

	return strlen(str);

}


////////////////////////////////
//
//  Ввод Ид слота и Ид предмета от пользователя
//

int  getSlot(char* question) {

	int id_slot;

	printf("%s", question);
	id_slot = getNumber();

	if (id_slot < 0 || id_slot > MAX_INVENTORY - 1) {
		printf("Номер слота должен быть в интервале от 0 до %d.\n", MAX_INVENTORY - 1);
		return -1;
	}
	return id_slot;
}

int  getItem(char* question, char items[][MAX_LENGHT_NAME]) {

	printItems(items, stdout);
	printf("%s", question);

	int id_item = getNumber();

	if (id_item < 1 || id_item > MAX_ITEMS - 1) {
		printf("Номер предмета должен быть в интервале от 1 до %d.\n", MAX_ITEMS - 1);
		return -1;
	}

	return id_item;
}


////////////////////////////////
//
//  Функции работы с Предметами 
//

/*
 * Печатает список предметов
 * @param items массив предметов
 * @return
 */
void printItems(char items[][MAX_LENGHT_NAME], FILE* file) {

	fprintf(file, "Список предметов:\n");
	for (int id_item = 0; id_item < MAX_ITEMS; id_item++) {
		fprintf(file, "[%d] - %s", id_item, items[id_item]);
		if (id_item < MAX_ITEMS - 1)
			fprintf(file, ", ");
	}
	fprintf(file, "\n");
}

int  findIdByName(char item_name[MAX_LENGHT_NAME], char items[][MAX_LENGHT_NAME]) {

	for (int i = 0; i < MAX_ITEMS; i++) {
		if (strcmp(items[i], item_name) == 0) {
			return i;
		}
	}
	return -1;
}

void initItems(char items[][MAX_LENGHT_NAME]) {

	FILE* file = fopen(FILE_ITEMS, "r");

	if (file == NULL) {
		// Предзаполнение при отсутствии файла
		strcpy(items[0], "<Empty>\0");
		strcpy(items[1], "Tree\0");
		strcpy(items[2], "Stone\0");
		strcpy(items[3], "Seeds\0");
		strcpy(items[4], "Flowers\0");
		strcpy(items[5], "Glass\0");
		strcpy(items[6], "Plastic\0");
		strcpy(items[7], "Eggs\0");
		strcpy(items[8], "Mazol\0");
		strcpy(items[9], "Validol\0");

		// Сообщим об ошибке чтения файла
		printf("Ошибка: не удалось открыть файл %s!\n", FILE_ITEMS);
	}
	else {
		// Читаем
		int i = 0, len = 0;
		char str[MAX_LENGHT_NAME];
		while (fgets(str, sizeof(str), file) != NULL) {
			len = strlen(str);
			if (len > 0 && str[len - 1] == '\n') {
				len--;
				str[len] = '\0';
			}

			if (len > 0) {
				if (i < MAX_ITEMS) {
					strcpy(items[i], str);
					i++;
				}
				else {
					printf("В файле больше %d строк считаны первые %d\n", MAX_ITEMS, MAX_ITEMS);
				}
			}

		}

		fclose(file); // Обязательно закрываем файл после работы!
		printf("Список инвентаря прочитан из файла %s!\n", FILE_ITEMS);
	}
	printf("\n");

}


////////////////////////////////
//
//  Записать состояние в дневник
//

/*void saveDiary(PLAYER* player, char items[MAX_ITEMS][MAX_LENGHT_NAME], PATHOUTTYPE pathOut) {

	FILE* file;

	if (pathOut == TOFILE) {
		file = fopen(FILE_DIARY, "a");
		if (file == NULL) {
			printf("Ошибка: не удалось создать файл %s!\n", FILE_DIARY);
			return;
		}
	}
	else {
		file = stdout;
	}

	// Вывод в дневник
	fprintf(file, "\t*** Новая запись в дневнике:\n");
	playerPrintCard(&player, items, file);
	fprintf(file, "\n\n");

	if (pathOut == 'f') {
		fclose(file);
	}
}
*/

////////////////////////////////
//
//  Анализ логов
//

void analyseLogFile() {

#define maxTag 3
#define maxStat 8
#define maxText 1024

	int i = 0, pos = 0, row = 0;
	char text[1024];
	int tagCnts[maxTag] = { 0 };
	char tagNames[maxTag][maxStat] = { "[INFO]", "[WARN]", "[ERROR]" };
	char* ptr;


	FILE* fIn = fopen(FILE_INPUT, "r");

	if (fIn == NULL) {
		printf("Ошибка: не удалось открыть файл %s!\n", FILE_INPUT);
	}
	else {
		FILE* fOut = fopen(FILE_OUTPUT, "w");
		if (fOut == NULL) {
			printf("Ошибка: не удалось открыть файл %s!\n", FILE_OUTPUT);
		}
		else {

			while (fgets(text, sizeof(text), fIn) != NULL) {
				row++;
				ptr = strstr(text, " "); // Используем адрес в памяти
				if (ptr != NULL) {
					pos = ptr - text;
					if (pos < maxStat) {
						text[pos] = 0;
						ptr++; // Сдвигаем адрес на один чтобы пропустьть 0
						for (i = 0; i < maxTag; i++) {
							if (strcmp(text, tagNames[i]) == 0) {
								tagCnts[i]++;
								if (i > 0) {
									fprintf(fOut, "%d %s", row, ptr);
								}
								break;
							}
						}
					}
				}
			}
			fclose(fOut);
		}
		fclose(fIn);

		printf("Статистика тегов:\n");
		for (i = 0; i < maxTag; i++) {
			printf("%s - %d\n", tagNames[i], tagCnts[i]);
		}
	}

}