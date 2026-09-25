#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


int getNumber() {
		
	int num;
	while (scanf("%d", &num) != 1)
	{
		printf("Вы ошиблись, введите число: ");
		while (getchar() != '\n');
	}
	return num;
}


int main() {
	system("chcp 1251 > nul");
	//setlocale(LC_ALL, "Rus");
	

	int current_day = 1;
	int current_hour = 8;
	int inventory[10];

	int menu, cnt_hours, cnt_days;

	do
	{
		printf("Меню:\n");
		printf("[0] Выход\n");
		printf("[1] Посмотреть на часы\n");
		printf("[2] Промотать время (Поработать)\n");
		printf("[3] Посмотреть инвентарь\n");
		printf("[4] Положить предмет в слот\n");
		printf("[5] Выбросить предмет\n");
		printf("[6] Выполнить задание по варианту\n\n");

		printf("Выберите пункт меню: ");
		menu = getNumber();
		
		printf("Вы ввели %d\n", menu);

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

			default:
				printf("Ошибка ввода пункта меню\n");
				break;
		}
		printf("\n");

	} while (menu != 0);

	return 0;
}