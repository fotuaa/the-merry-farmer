#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include "player.h"


////////////////////////////////
//
//  Функции работы с Фермером
//

void playerCreate(PLAYER** player) {

	char farmer_name[MAX_LENGHT_NAME_FARMER];
	
	if ((*player) != NULL) {
		if (getString("Игрок уже создан. Пересоздать? (Y/N) ", farmer_name) == 0 || toupper(farmer_name[0]) != 'Y') {
			printf("Фермер не пересоздан");
			return;
		}
		playerFree(&(*player));

	}

	(*player) = (PLAYER*) malloc(sizeof(PLAYER));

	if (getString("Введите имя фермера ", farmer_name) == 0) {
		strcpy(farmer_name, "Incognito\0");
	}

	strcpy((*player)->farmer_name, farmer_name);
	(*player)->curHP = MAX_HP;
	(*player)->maxHP = MAX_HP;
	(*player)->curStam = MAX_STAMINA;
	(*player)->maxStam = MAX_STAMINA;
	(*player)->gold = 0;
	(*player)->row = 0;
	(*player)->col = 0;
	for (int i = 0; i < MAX_INVENTORY; i++)
		(*player)->inventory[i] = 0;
	calendStart(&(*player)->calend);

}

void playerFree(PLAYER** player) {

	if ((*player) == NULL) {
		return;
	}

	free((*player));
	(*player) = NULL;
	printf("Память игрока освобождена\n\n");
}

void playerPrintCard(PLAYER** player, char items[][MAX_LENGHT_NAME], FILE* file) {

	if ((*player) == NULL) {
		fprintf(file, "Игрок не создан\n");
		return;
	}

	fprintf(file, "Имя: %s\n", (*player)->farmer_name);
	fprintf(file, "HP: %d / %d | Выносливость: %d / %d | Золото: %d ", (*player)->curHP, (*player)->maxHP, (*player)->curStam, (*player)->maxStam, (*player)->gold);
	calendPrint(&(*player)->calend, file);
	playerPrintInventory(&(*player), items, file);

}

void playerMaxStats(PLAYER** player) {
	
	if ((*player) == NULL) {
		printf("Игрок не создан\n");
		return;
	}

	(*player)->curHP = (*player)->maxHP;
	(*player)->curStam = (*player)->maxStam;
}

void playerSleep(PLAYER** player) {

	if ((*player) == NULL) {
		printf("Игрок не создан\n");
		return;
	}

	calendNextDay(&(*player)->calend);
	playerMaxStats(&(*player));
}


////////////////////////////////
//
//  Функции работы с Инвентарем (рюкзаком)
//

void playerPrintInventory(PLAYER** player, char items[][MAX_LENGHT_NAME], FILE* file) {

	if ((*player) == NULL) {
		fprintf(file, "Игрок не создан\n");
		return;
	}
	
	fprintf(file, "Список инвентаря:\n");
	for (int id_slot = 0; id_slot < MAX_INVENTORY; id_slot++) {
		fprintf(file, "Слот %d: [%d] - %s", id_slot, (*player)->inventory[id_slot], items[(*player)->inventory[id_slot]]);
		if (id_slot < MAX_INVENTORY - 1)
			fprintf(file, ", ");
	}

	fprintf(file, "\n");


}


void playerPutInSlot(PLAYER** player, char items[][MAX_LENGHT_NAME], FILE* file) {

	if ((*player) == NULL) {
		fprintf(file, "Игрок не создан\n");
		return;
	}

	int idSlot = 0, idItem = 0;

	idSlot = getSlot("В какой слот кладём? ");
	if (idSlot == -1)
		return;

	idItem = getItem("Какой предмет кладём (введите ID)? ", items);
	if (idItem == -1)
		return;

	(*player)->inventory[idSlot] = idItem;

}

void playerDropItem(PLAYER** player, FILE* file) {

	if ((*player) == NULL) {
		fprintf(file, "Игрок не создан\n");
		return;
	}

	int idSlot = 0;

	idSlot = getSlot("Какой слот очищаем? ");
	if (idSlot == -1)
		return;

	(*player)->inventory[idSlot] = 0;
}

void playerСleaningTrash(PLAYER** player, char items[][MAX_LENGHT_NAME], FILE* file) {

	if ((*player) == NULL) {
		fprintf(file, "Игрок не создан\n");
		return;
	}

	int idSlot = 0, idItem = 0, cnt = 0;

	idItem = getItem("Какой предмет ищем (введите ID)? ", items);
	if (idItem == -1)
		return;

	cnt = 0;
	for (int idSlot = 0; idSlot < MAX_INVENTORY; idSlot++) {
		if ((*player)->inventory[idSlot] == idItem) {
			(*player)->inventory[idSlot] = 0;
			cnt++;
		}
	}
	printf("Очищено: %d", cnt);
	printf("\n");
}

void playerSearchByName(PLAYER** player, char items[][MAX_LENGHT_NAME], FILE* file) {

	if ((*player) == NULL) {
		fprintf(file, "Игрок не создан\n");
		return;
	}

	int idSlot = 0, idItem = 0, cnt = 0;
	char item_name[MAX_LENGHT_NAME];

	printItems(items, stdout);
	if (getString("Какой предмет ищем (введите название)? ", item_name) == 0) {
		printf("Название не введено. Поиск прерван");
		return;
	}

	idItem = findIdByName(item_name, items);
	if (idItem == -1) {
		printf("Такого предмета не существует");
		return;
	}

	cnt = 0;
	for (idSlot = 0; idSlot < MAX_INVENTORY; idSlot++) {
		if ((*player)->inventory[idSlot] == idItem) {
			cnt++;
			if (cnt == 1) {
				printf("Слот %d", idSlot);
			}
			else if (cnt > 1) {
				printf(", %d", idSlot);
			}

		}
	}
	if (cnt == 0)
		printf("Такого предмета нет в инвентаре");

	printf("\n");
}

void playerGarbaging(PLAYER** player, char items[][MAX_LENGHT_NAME], FILE* file) {

	// Инициализация датчика случайных чисел
	srand(time(NULL));

	if ((*player) == NULL) {
		fprintf(file, "Игрок не создан\n");
		return;
	}

	int idSlot = 0;

	for (idSlot = 0; idSlot < MAX_INVENTORY; idSlot++) {
		(*player)->inventory[idSlot] = rand() % MAX_ITEMS;
	}

	printf("Инвентарь замусорен\n");
	playerPrintInventory(&(*player), items, stdout);
}