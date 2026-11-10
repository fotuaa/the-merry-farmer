#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include "calend.h"
#include "utils.h"

#define MAX_INVENTORY 10
#define MAX_LENGHT_NAME_FARMER 65
#define MAX_ITEMS 10
#define MAX_HP 100
#define MAX_STAMINA 50


typedef struct {
	char farmer_name[MAX_LENGHT_NAME_FARMER];
	int curHP, maxHP; // текущее и полное здоровье
	int curStam, maxStam; // текущее и полное стамина
	int gold, row, col;
	int inventory[MAX_INVENTORY];
	CALEND calend;
} PLAYER;


////////////////////////////////
//
//  Функции работы с Фермером
//

void playerCreate(PLAYER* player);
void playerFree(PLAYER* player);


////////////////////////////////
//
//  Функции работы с Фермером
//

void printFarmer(char* question, char farmer_name[MAX_LENGHT_NAME_FARMER], FILE* file);


////////////////////////////////
//
//  Функции работы с Инвентарем (рюкзаком)
//

void printInventory(int inventory[], char items[][MAX_LENGHT_NAME], FILE* file);





#endif // !PLAYER_H