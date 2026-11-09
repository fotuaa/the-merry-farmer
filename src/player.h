#ifndef PLAYER_H
#define PLAYER_H


#define MAX_INVENTORY 10
#define MAX_LENGHT_NAME_FARMER 65
#define MAX_ITEMS 10


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