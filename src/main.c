//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "utils.h"
#include "player.h"

#include "map.h"
#include "calend.h"


int  main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);


	// Инициализация датчика случайных чисел
	srand(time(NULL));

	char items[MAX_ITEMS][MAX_LENGHT_NAME]; 
	initItems(items);

	int menu = 0;
	PLAYER* player = NULL;
	
	char menuMain[8][MAX_LENGHT_MENU_ITEM] = {"Выход\0", "Создать/пересоздать игрока\0", "Карточка персонажа\0", "Управление временем\0", "Управление инвентарем\0", 
										   "Записать состояние в дневник фермера\0", "Анализатор логов\0", "Отправиться в приключение\0"};

	do
	{
		menu = menuChoice(menuMain, 8);
		
		switch (menu) {
			case 0:
				break;

			case 1: // [1] Создать/пересоздать игрока
				playerCreate(&player);

				break;

			case 2: // [2] Карточка персонажа
				
				playerPrintCard(&player, items, stdout);

				break;

			case 3: // [3] Управление временем
				
				calendDo(&player);

				break;

		case 4: // [4] Положить предмет в слот

			inventoryDo(&player, items);

			break;

			case 5: // [5] Записать состояние в дневник фермера

				saveDiary(&player, items, TOFILE);
				saveDiary(&player, items, TOSCREEN);

				break;

			case 6: // [6] Анализатор логов

				analyseLogFile();

				break;

			case 7: // [7] Отправиться в приключение 

				mapPlay(&player);

				break;

			default:
				printf("Ошибка ввода пункта меню\n");
				break;
		}
		printf("\n");

	} while (menu != 0);
	
	playerFree(&player);

	return 0;
}