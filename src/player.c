#include "player.h"

////////////////////////////////
//
//  Функции работы с Фермером
//

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