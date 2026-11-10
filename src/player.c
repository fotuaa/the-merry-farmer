#include "player.h"


////////////////////////////////
//
//  Функции работы с Фермером
//

void playerCreate(PLAYER* player) {

	char farmer_name[MAX_LENGHT_NAME_FARMER];
	
	if (player != NULL) {
		if (getString("Игрок уже создан. Пересоздать? (Y/N) ", farmer_name) == 0 || toupper(farmer_name[0]) != 'Y') {
			printf("Фермер не пересоздан");
			return;
		}
		playerFree(player);
	}

	player = malloc(sizeof(PLAYER));

	if (getString("Введите имя фермера ", farmer_name) == 0) {
		strcpy(farmer_name, "Инкогнито\0");
	}

	strcpy(player->farmer_name, farmer_name);
	player->curHP = MAX_HP;
	player->maxHP = MAX_HP; 
	player->curStam = MAX_STAMINA;
	player->maxStam = MAX_STAMINA; 
	player->gold = 0;
	player->row = 0;
	player->col = 0;
	for (int i = 0; i <= MAX_INVENTORY; i++)
		player->inventory[i] = 0;
	calendStart(&player->calend);

}

void playerFree(PLAYER* player) {

	if (player != NULL) {
		free(player);
		player = NULL;
	}
}

void printFarmer(char* question, char farmer_name[MAX_LENGHT_NAME_FARMER], FILE* file) {

	fprintf(file, "%s %s\n", question, farmer_name);
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