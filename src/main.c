#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

#include "utils.h"
#include "player.h"
#include "map.h"


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