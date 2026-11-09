#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>


#define MAX_INVENTORY 10
#define MAX_LENGHT_NAME 30
#define MAX_LENGHT_NAME_FARMER 65
#define MAX_ITEMS 10

#define MAX_RANGE 26

#define MAX_PERCENT 101
#define MAX_PERCENT_R 15
#define MAX_PERCENT_T 30

#define FILE_ITEMS "items_eng.txt"
#define FILE_DIARY "diary.txt"

#define FILE_INPUT "input.txt"
#define FILE_OUTPUT "output.txt"

const int maxTag = 3, maxStat = 8, maxText = 1024;

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
		strcpy(items[0], "<Пусто>\0");
		strcpy(items[1], "Дерево\0");
		strcpy(items[2], "Камень\0");
		strcpy(items[3], "Семена\0");
		strcpy(items[4], "Цветы\0");
		strcpy(items[5], "Стекло\0");
		strcpy(items[6], "Пластик\0");
		strcpy(items[7], "Яйца\0");
		strcpy(items[8], "Мазоль\0");
		strcpy(items[9], "Валидол\0");

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
//  Функции работы с Фермером
//

void printFarmer(char* question, char farmer_name[MAX_LENGHT_NAME_FARMER], FILE* file) {

	fprintf(file, "%s %s\n", question, farmer_name);
}


////////////////////////////////
//
//  Функции работы с Временем
//

void printTime(int current_day, int current_hour, FILE* file) {

	fprintf(file, "Текущее время: День %d, %s%d:00.\n",
		current_day, ((current_hour < 10) ? "0" : ""), current_hour);
}


////////////////////////////////
//
//  Функции работы с Инвентарем (рюкзаком)
//

void printInventory(int inventory[], char items[][MAX_LENGHT_NAME], FILE* file) {

	fprintf(file, "Список инвентаря:\n");
	for (int id_slot = 0; id_slot < MAX_INVENTORY; id_slot++) {
		fprintf(file, "Слот %d: [%d] - %s", id_slot, inventory[id_slot], items[inventory[id_slot]]);
		if (id_slot < MAX_INVENTORY - 1)
			fprintf(file, ", ");
	}

	fprintf(file, "\n");

}


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

int  getSlot(char *question) {

	int id_slot;

	printf("%s", question);
	id_slot = getNumber();

	if (id_slot < 0 || id_slot > MAX_INVENTORY - 1) {
		printf("Номер слота должен быть в интервале от 0 до %d.\n", MAX_INVENTORY - 1);
		return -1;
	}
	return id_slot;
}

int  getItem(char *question, char items[][MAX_LENGHT_NAME]) {

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
//  Записать состояние в дневник
//

void saveDiary(char farmer_name[MAX_LENGHT_NAME_FARMER], 
				int current_day, int current_hour, 
				int inventory[MAX_INVENTORY], char items[MAX_ITEMS][MAX_LENGHT_NAME],
				char pathOut) {

	FILE* file;

	if (pathOut == 'f') {
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
	printFarmer("Имя фермера:", farmer_name, file);
	printTime(current_day, current_hour, file);
	printInventory(inventory, items, file);
	fprintf(file, "\n\n");

	if (pathOut == 'f') {
		fclose(file);
	}
}


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
	int tagCnts[maxTag] = {0};
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
		} else {

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


////////////////////////////////
//
//  Работа с картой
//

typedef struct {
	int height, width;
	int row, col;
	int row_Light, col_Light;
	char** ptr;
	int cnt, radius, stepLight;
} MAP;

typedef enum {
	UP,
	RIGHT,
	DOWN,
	LEFT
} DIRECTIONS;

void mapCreate(MAP* map, int height, int width) {

	map->height = height;
	map->width = width;
	map->ptr = (char**)malloc(height * sizeof(char*));
	for (int i = 0; i < height; i++) {
		map->ptr[i] = (char*)malloc(width * sizeof(char));
	}

	map->row = 0;
	map->col = 0;
	map->cnt = 0;
	map->radius = 5;
	map->stepLight = 0;
}

void mapFree(MAP *map) {

	for (int i = 0; i < map->height; i++) {
		free(map->ptr[i]);
		map->ptr[i] = NULL;
	}
	free(map->ptr);
	map->ptr = NULL;

	map->height = 0;
	map->width = 0;
}

void mapInit(MAP* map) {

	int percent, i, j;
	char ch;
	for (i = 0; i < map->height; i++) {
		for (j = 0; j < map->width; j++) {
			if (i == map->row && j == map->col) {
				ch = '.';
			}
			else {
				percent = rand() % MAX_PERCENT;
				if (percent < MAX_PERCENT_R) {
					ch = 'R';
				}
				else if (percent < MAX_PERCENT_T) {
					ch = 'T';
				}
				else {
					ch = '.';
				}
			}

			map->ptr[i][j] = ch;
		}
	}

	i = rand() % map->height;
	j = (rand() % (map->width - 1) + 1 + map->col) % map->width;
	map->ptr[i][j] = '^';

}

int mapIsFire(MAP* map) {
	return (map->ptr[map->row][map->col] == '^') ? 1 : 0;
}

void mapLightOn(MAP* map) {
	map->stepLight = 3;
	map->row_Light = map->row;
	map->col_Light = map->col;
}

void mapPrint(MAP* map) {

	int r = 0;

	printf("\033[2J");   // Очистить экран
	printf("\033[0;0H"); // Позиционируемся в верхний левый угол экрана
	for (int i = 0; i < map->height; i++) {
		for (int j = 0; j < map->width; j++) {
			printf("+---");
		}
		printf("+\n");
		for (int j = 0; j < map->width; j++) {
			if (i == map->row && j == map->col) {
				printf("| \x1B[32m@\x1B[0m ");
			}
			else {
				if (map->stepLight == 0) {
					printf("| \x1B[36m?\x1B[0m ");
				}
				else {
					r = (int)sqrt((map->row_Light - i) * (map->row_Light - i) + (map->col_Light - j) * (map->col_Light - j));
					if (r > map->radius) {
						printf("| \x1B[36m?\x1B[0m ");
					}
					else {
						if (map->ptr[i][j] == '^') {
							printf("| \x1B[31m^\x1B[0m ");
						}
						else {
							printf("| %c ", map->ptr[i][j]);
						}
					}
				} 
			}
		}
		printf("|\n");
	}
	for (int j = 0; j < map->width; j++) {
		printf("+---");
	}
	printf("+\n");
	printf("Пройдено локаций: %d, спичка (L) горит: %d\n", map->cnt, map->stepLight);
}

void mapMove(MAP* map, DIRECTIONS arrow) {
	int new = 0, step = 0;
	char ch = 0;
	

	if (arrow == UP) {
		if (map->row == 0) {
			map->row = map->height - 1;
			mapInit(map);
			map->cnt++;
			step = 1;
		}
		else {
			new = map->row - 1;
			ch = map->ptr[new][map->col];
			if (ch == '.' || ch == '^') {
				map->row = new;
				step = 1;
			}
		}
	}

	if (arrow == DOWN) {
		if (map->row == map->height - 1) {
			map->row = 0;
			mapInit(map);
			map->cnt++;
			step = 1;
		}
		else {
			new = map->row + 1;
			ch = map->ptr[new][map->col];
			if (ch == '.' || ch == '^') {
				map->row = new;
				step = 1;
			}
		}
	}

	if (arrow == RIGHT) {
		if (map->col == map->width - 1) {
			map->col = 0;
			mapInit(map);
			map->cnt++;
			step = 1;
		}
		else {
			new = map->col + 1;
			ch = map->ptr[map->row][new];
			if (ch == '.' || ch == '^') {
				map->col = new;
				step = 1;
			}
		}
	}

	if (arrow == LEFT) {
		if (map->col == 0) {
			map->col = map->width - 1;
			mapInit(map);
			map->cnt++;
			step = 1;
		}
		else {
			new = map->col - 1;
			ch = map->ptr[map->row][new];
			if (ch == '.' || ch == '^') {
				map->col = new;
				step = 1;
			}
		}
	}

	if (map->stepLight > 0 && step == 1) {
		map->stepLight--;
	}
}

void mapPlay() {

	int quit = 0;
	char ch = 0, s[2];
	MAP map;
	mapCreate(&map, (rand() % (MAX_RANGE)) + 5, (rand() % (MAX_RANGE)) + 5);
	mapInit(&map);
	

	do
	{
		mapPrint(&map);

		scanf("%1s", s);
		ch = toupper(s[0]);

		switch (ch) {
		case 'W': 
			mapMove(&map, UP);
			break;
			
		case 'A': 
			mapMove(&map, LEFT);
			break;
			
		case 'S': 
			mapMove(&map, DOWN);
			break;

		case 'D': 
			mapMove(&map, RIGHT);
			break;

		case 'Q': 
			quit = mapIsFire(&map);
			break;

		case 'L': 
			mapLightOn(&map);

			break;
		}

	} while (quit == 0);

	mapFree(&map);
}

int  main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	int current_day = 1;
	int current_hour = 8;
	int inventory[MAX_INVENTORY] = { 0 };

	// Инициализация датчика случайных чисел
	srand(time(NULL));

	char items[MAX_ITEMS][MAX_LENGHT_NAME]; 
	initItems(items);

	int menu, cnt_hours, id_item, id_slot, cnt;
	char farmer_name[MAX_LENGHT_NAME_FARMER], item_name[MAX_LENGHT_NAME];


	if (getString("Как вас зовут? ", farmer_name) == 0) {
		strcpy(farmer_name, "Инкогнито\0");
	}


	do
	{
		printFarmer("Здраствуйте,", farmer_name, stdout);

		printf("\tМеню:\n");
		printf("[0] Выход\n");
		printf("[1] Посмотреть на часы\n");
		printf("[2] Промотать время (Поработать)\n");
		printf("[3] Посмотреть инвентарь\n");
		printf("[4] Положить предмет в слот\n");
		printf("[5] Выбросить предмет\n");
		printf("[6] Очистка от мусора\n"); 
		printf("[7] Поиск предмета в рюкзаке по названию\n");
		printf("[8] Записать состояние в дневник фермера\n");
		printf("[9] Анализатор логов\n");
		printf("[10] Отправиться в приключение\n");
		printf("[99] Замусоревание инвентаря\n\n");

		printf("Выберите пункт меню: ");
		menu = getNumber();
		
		switch (menu) {
			case 0:
				break;

			case 1: // [1] Посмотреть на часы
				printTime(current_day, current_hour, stdout);

				break;

			case 2: // [2] Промотать время (Поработать)
				printf("Сколько часов хотите поработать? ");
				cnt_hours = getNumber();
				if (cnt_hours == 0)
					printf("Да Вы работяга! Время прежнее.\n");
				else if (cnt_hours > 0) {
					current_hour += cnt_hours;
					current_day += (int)(current_hour / 24);
					current_hour = current_hour % 24;
					printf("Поработали, сейчас: День %d, %s%d:00\n",
						current_day, ((current_hour < 10) ? "0" : ""), current_hour);
				}
				else 
					printf("Положительное число\n");

				break;

			case 3: // [3] Посмотреть инвентарь

				printInventory(inventory, items, stdout);

				break;

			case 4: // [4] Положить предмет в слот
				
				id_slot = getSlot("В какой слот кладём? ");
				if (id_slot == - 1) 
					break;

				id_item = getItem("Какой предмет кладём (введите ID)?", items);
				if (id_item == -1)
					break;

				inventory[id_slot] = id_item;

				break;

			case 5: // [5] Выбросить предмет

				id_slot = getSlot("Какой слот очищаем? ");
				if (id_slot == -1)
					break;

				inventory[id_slot] = 0;

				break;

			case 6: // [6] Очистка от мусора

				id_item = getItem("Какой предмет ищем (введите ID)?", items);
				if (id_item == -1)
					break;

				cnt = 0;
				for (int id_slot = 0; id_slot < MAX_INVENTORY; id_slot++) {
					if (inventory[id_slot] == id_item) {
						inventory[id_slot] = 0;
						cnt++;
					}
				}
				printf("Очищено: %d", cnt);
				printf("\n");

				break;

			case 7: // [7] Поиск предмета в рюкзаке по названию

				printItems(items, stdout);
				if (getString("Какой предмет ищем (введите название)? ", item_name) == 0) {
					printf("Название не введено. Поиск прерван");
					break;
				}

				id_item = findIdByName(item_name, items);
				if (id_item == -1) {
					printf("Такого предмета не существует");
					break;
				}

				cnt = 0;
				for (id_slot = 0; id_slot < MAX_INVENTORY; id_slot++) {
					if (inventory[id_slot] == id_item) {
						cnt++;
						if (cnt == 1) {
							printf("Слот %d", id_slot);
						}
						else if (cnt > 1) {
							printf(", %d", id_slot);
						}
						
					}
				}
				if (cnt == 0)
					printf("Такого предмета нет в инвентаре");
				
				printf("\n");
				
				break;

			case 8: // [8] Записать состояние в дневник фермера

				saveDiary(farmer_name, current_day, current_hour, inventory, items, 'f');
				saveDiary(farmer_name, current_day, current_hour, inventory, items, 'm');

				break;

			case 9: // [9] Анализатор логов

				analyseLogFile();

				break;

			case 10: // [10] Отправиться в приключение 

				mapPlay();

				break;

			case 99: // [99] Замусоревание инвентаря

				for (id_slot = 0; id_slot < MAX_INVENTORY; id_slot++) {
					inventory[id_slot] = rand() % MAX_ITEMS;
				}

				printf("Инвентарь замусорен\n");
				printInventory(inventory, items, stdout);

				break;

			default:
				printf("Ошибка ввода пункта меню\n");
				break;
		}
		printf("\n");

	} while (menu != 0);
 
	return 0;
}