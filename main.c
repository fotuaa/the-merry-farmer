#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>

#define MAX_INVENTORY 10
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

int getItem(char *question, char *items[]) {

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

void printInventory(int inventory[], char *items[]) {

	for (int id_slot = 0; id_slot < MAX_INVENTORY; id_slot++) {
		printf("Слот %d: [%d]", id_slot, inventory[id_slot]);
		if (inventory[id_slot] != 0)
			printf(" (%s)", items[inventory[id_slot]]);
		if (id_slot < MAX_INVENTORY - 1)
			printf(", ");
	}
	printf("\n");

}

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	int current_day = 1;
	int current_hour = 8;
	int inventory[MAX_INVENTORY] = { 0 };
	const char* items[MAX_ITEMS] = 
					{"<Пусто>", "Дерево", "Камень", "Семена", "Цветы", "Стекло", "Пластик", "Яйца", "Мазоль", "Валидол" };

	int menu, cnt_hours, id_item, id_slot, cnt;

	do
	{
		printf("Меню:\n");
		printf("[0] Выход\n");
		printf("[1] Посмотреть на часы\n");
		printf("[2] Промотать время (Поработать)\n");
		printf("[3] Посмотреть инвентарь\n");
		printf("[4] Положить предмет в слот\n");
		printf("[5] Выбросить предмет\n");
		printf("[6] Очистка от мусора\n\n");

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
				else {
					current_hour += cnt_hours;
					current_day += (int)(current_hour / 24);
					current_hour = current_hour % 24;
					printf("Поработали, сейчас: День %d, %s%d:00\n",
						current_day, ((current_hour < 10) ? "0" : ""), current_hour);
				}
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

			default:
				printf("Ошибка ввода пункта меню\n");
				break;
		}
		printf("\n");

	} while (menu != 0);

	return 0;
}