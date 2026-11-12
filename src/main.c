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

	PLAYER* player = NULL;
	


	int menu, id_item, id_slot, cnt;
	char item_name[MAX_LENGHT_NAME];

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
				
				
				/*printf("Сколько часов хотите поработать? ");
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
					printf("Положительное число\n");*/

				break;

			case 3: // [3] Управление временем
				
				calendDo(&player);
				//playerPrintInventory(inventory, items, stdout);

				break;

/*		case 4: // [4] Положить предмет в слот
				
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
*/
			case 5: // [5] Записать состояние в дневник фермера

				saveDiary(&player, items, TOFILE);
				saveDiary(&player, items, TOSCREEN);

				break;

			case 6: // [6] Анализатор логов

				analyseLogFile();

				break;
/*
			case 10: // [10] Отправиться в приключение 

				mapPlay();

				break;

			case 99: // [99] Замусоревание инвентаря

				for (id_slot = 0; id_slot < MAX_INVENTORY; id_slot++) {
					inventory[id_slot] = rand() % MAX_ITEMS;
				}

				printf("Инвентарь замусорен\n");
				playerPrintInventory(inventory, items, stdout);

				break;

*/

			default:
				printf("Ошибка ввода пункта меню\n");
				break;
		}
		printf("\n");

	} while (menu != 0);
	
	playerFree(&player);

	return 0;
}