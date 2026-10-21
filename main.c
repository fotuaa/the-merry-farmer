#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_INVENTORY 10
#define MAX_LENGHT_NAME 30
#define MAX_LENGHT_NAME_FARMER 65
#define MAX_ITEMS 10

int getNumber() {
		
	int num;
	while (scanf("%d", &num) != 1)
	{
		printf("Вы ошиблись, введите число: ");
		while (getchar() != '\n');
	}
	return num;
}

int getSlot(char *question) {

	int id_slot;

	printf("%s", question);
	id_slot = getNumber();

	if (id_slot < 0 || id_slot > MAX_INVENTORY - 1) {
		printf("Номер слота должен быть в интервале от 0 до %d.\n", MAX_INVENTORY - 1);
		return -1;
	}
	return id_slot;
}

int getItem(char *question, char items[][MAX_LENGHT_NAME]) {

	int id_item;

	printf("%s (", question);
	for (id_item = 1; id_item < MAX_ITEMS; id_item++) {
		printf("[%d] %s", id_item, items[id_item]);
		if (id_item < MAX_ITEMS - 1)
			printf(", ");
		else
			printf(")? ");
	}
	id_item = getNumber();

	if (id_item < 1 || id_item > MAX_ITEMS - 1) {
		printf("Номер предмета должен быть в интервале от 1 до %d.\n", MAX_ITEMS - 1);
		return -1;
	}

	return id_item;
}

void printInventory(int inventory[], char items[][MAX_LENGHT_NAME]) {
	
	printf("Список инвентаря:\n");
	for (int id_slot = 0; id_slot < MAX_INVENTORY; id_slot++) {
		printf("Слот %d: [%d] - %s", id_slot, inventory[id_slot], items[inventory[id_slot]]);
		if (id_slot < MAX_INVENTORY - 1)
			printf(", "); 
	}

	printf("\n");

}

void getItems(char items[][MAX_LENGHT_NAME]) {

	FILE* file = fopen("items.txt", "r");

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
		printf("Ошибка: не удалось открыть файл items.txt!\n");
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
		printf("Список инвентаря прочитан из файла items.txt!\n");
	}
	printf("\n");

}

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	int current_day = 1;
	int current_hour = 8;
	int inventory[MAX_INVENTORY] = { 0 };
	
	// Инициализация датчика случайных чисел
	srand(time(NULL));

	char items[MAX_ITEMS][MAX_LENGHT_NAME]; // = { "<Пусто>", "Дерево", "Камень", "Семена", "Цветы", "Стекло", "Пластик", "Яйца", "Мазоль", "Валидол" };
	getItems(items);

	int menu, cnt_hours, id_item, id_slot, cnt;
	char farmer_name[MAX_LENGHT_NAME_FARMER];

	printf("Как вас зовут? ");
	if (fgets(farmer_name, sizeof(farmer_name), stdin) != NULL) {
		farmer_name[strcspn(farmer_name, "\n")] = 0;
	} else {
		farmer_name[0] = '\0';
	}
	


	do
	{
		printf("Здраствуйте, %s\n", farmer_name);
		printf("Меню:\n");
		printf("[0] Выход\n");
		printf("[1] Посмотреть на часы\n");
		printf("[2] Промотать время (Поработать)\n");
		printf("[3] Посмотреть инвентарь\n");
		printf("[4] Положить предмет в слот\n");
		printf("[5] Выбросить предмет\n");
		printf("[6] Очистка от мусора\n"); 
		printf("[10] Замусоревание инвентаря\n\n");

		printf("Выберите пункт меню: ");
		menu = getNumber();
		
		switch (menu) {
			case 0:
				break;

			case 1: // [1] Посмотреть на часы
				printf("Текущее время: День %d, %s%d:00\n", 
						current_day, ((current_hour < 10) ? "0" : ""), current_hour);

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

				printInventory(inventory, items);

				break;

			case 4: // [4] Положить предмет в слот
				
				id_slot = getSlot("В какой слот кладём? ");
				if (id_slot == - 1) 
					break;

				id_item = getItem("Какой предмет кладём", items);
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

				id_item = getItem("Какой предмет ищем", items);
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


			case 10: // [10] Замусоревание инвентаря

				for (int id_slot = 0; id_slot < MAX_INVENTORY; id_slot++) {
					inventory[id_slot] = rand() % MAX_ITEMS;
				}

				printf("Инвентарь замусорен\n");
				printInventory(inventory, items);
			
				break;

			default:
				printf("Ошибка ввода пункта меню\n");
				break;
		}
		printf("\n");

	} while (menu != 0);
 
	return 0;
}