#include <stdio.h>
#include <locale.h>
#include <stdlib.h> 

int isNumber(char num) {
	if (num >= '0' && num <= '9')
		return 1;
	else
		return 0;
}


int main() {
	system("chcp 1251 > nul");
	setlocale(LC_ALL, "Rus");
	

	int current_day = 1;
	int current_hour = 8;
	int inventory[10];
	char menu;

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

		printf("Выберите пункт меню:");
		menu = getchar();
		//scanf("%c", &menu);
		//if (isNumber(menu) == 0)
		switch (menu) {
			case '0':
				break;
			case '1': 
				printf("1"); 
				break;
			default:
				printf("Ошибка ввода пункта меню");
				break;
		}
		
	} while (menu != '0');



	return 0;
}