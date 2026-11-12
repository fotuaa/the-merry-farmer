#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include "calend.h"
#include "utils.h"


#define MAX_HP 100
#define MAX_STAMINA 50
#define MAX_LENGHT_NAME 30








////////////////////////////////
//
//  Функции работы с Фермером
//

void playerCreate(PLAYER** player);
void playerFree(PLAYER** player);


////////////////////////////////
//
//  Функции работы с Фермером
//

void playerPrintCard(PLAYER** player, char items[][MAX_LENGHT_NAME], FILE* file);

void playerMaxStats(PLAYER** player);
void playerSleep(PLAYER** player);


////////////////////////////////
//
//  Функции работы с Инвентарем (рюкзаком)
//

void playerPrintInventory(PLAYER** player, char items[][MAX_LENGHT_NAME], FILE* file);

void playerPutInSlot(PLAYER** player, char items[][MAX_LENGHT_NAME], FILE* file);

void playerDropItem(PLAYER** player, FILE* file);

void playerСleaningTrash(PLAYER** player, char items[][MAX_LENGHT_NAME], FILE* file);

void playerSearchByName(PLAYER** player, char items[][MAX_LENGHT_NAME], FILE* file);

void playerGarbaging(PLAYER** player, char items[][MAX_LENGHT_NAME], FILE* file);

#endif // !PLAYER_H