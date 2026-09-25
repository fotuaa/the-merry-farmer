#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
//#include <locale.h>
//#include <stdlib.h> 



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
	int menu;

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
		//scanf_s("%c", menu);
		//while 

		printf("Вы ввели %d\n", menu);

		//if (isNumber(menu) == 0)
		switch (menu) {
			case 0:
				break;
			case 1: 
				printf("\n"); 
				break;
			default:
				printf("Ошибка ввода пункта меню\n");
				break;
		}
		
	} while (menu != 0);



	return 0;
}