#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <math.h>

#include "map.h"

////////////////////////////////
//
//  Работа с картой
//


void mapCreate(MAP* map, int height, int width) {

	map->height = height;
	map->width = width;
	map->ptr = (char**)malloc(height * sizeof(char*));
	for (int i = 0; i < height; i++) {
		map->ptr[i] = (char*)malloc(width * sizeof(char));
	}

	//map->row = 0;
	//map->col = 0;
	map->cnt = 0;
	map->radius = 5;
	map->stepLight = 0;
	map->row_Light = 0;
	map->col_Light = 0;
}

void mapFree(MAP* map) {

	for (int i = 0; i < map->height; i++) {
		free(map->ptr[i]);
		map->ptr[i] = NULL;
	}
	free(map->ptr);
	map->ptr = NULL;

	map->height = 0;
	map->width = 0;
}

void mapInit(MAP* map, PLAYER** player) {

	int percent, i, j;
	char ch;
	for (i = 0; i < map->height; i++) {
		for (j = 0; j < map->width; j++) {
			if (i == (*player)->row && j == (*player)->col) {
				ch = '.';
			}
			else {
				percent = rand() % MAX_PERCENT;
				if (percent < MAX_PERCENT_R) {
					ch = 'R';
				}
				else if (percent < MAX_PERCENT_T) {
					ch = 'T';
				}
				else {
					ch = '.';
				}
			}

			map->ptr[i][j] = ch;
		}
	}

	i = rand() % map->height;
	j = (rand() % (map->width - 1) + 1 + (*player)->col) % map->width;
	map->ptr[i][j] = '^';

}

int mapIsFire(MAP* map, PLAYER** player) {
	return (map->ptr[(*player)->row][(*player)->col] == '^') ? 1 : 0;
}

void mapLightOn(MAP* map, PLAYER** player) {
	map->stepLight = 3;
	map->row_Light = (*player)->row;
	map->col_Light = (*player)->col;
}

void mapPrint(MAP* map, PLAYER** player) {

	int r = 0;

	printf("\033[2J");   // Очистить экран
	printf("\033[0;0H"); // Позиционируемся в верхний левый угол экрана
	for (int i = 0; i < map->height; i++) {
		for (int j = 0; j < map->width; j++) {
			printf("+---");
		}
		printf("+\n");
		for (int j = 0; j < map->width; j++) {
			if (i == (*player)->row && j == (*player)->col) {
				printf("| \x1B[32m@\x1B[0m ");
			}
			else {
				if (map->stepLight == 0) {
					printf("| \x1B[36m?\x1B[0m ");
				}
				else {
					r = (int)sqrt((map->row_Light - i) * (map->row_Light - i) + (map->col_Light - j) * (map->col_Light - j));
					if (r > map->radius) {
						printf("| \x1B[36m?\x1B[0m ");
					}
					else {
						if (map->ptr[i][j] == '^') {
							printf("| \x1B[31m^\x1B[0m ");
						}
						else {
							printf("| %c ", map->ptr[i][j]);
						}
					}
				}
			}
		}
		printf("|\n");
	}
	for (int j = 0; j < map->width; j++) {
		printf("+---");
	}
	printf("+\n");
	printf("HP: %d / %d | Выносливость: %d / %d | Золото: %d | Этаж: %d | Время: %d:00\n", 
		(*player)->curHP, (*player)->maxHP, (*player)->curStam, (*player)->maxStam, (*player)->gold, map->cnt, (*player)->calend.current_hour);
	//printf("Пройдено локаций: %d, спичка (L) горит: %d\n", map->cnt, map->stepLight);
}

void mapMove(MAP* map, PLAYER** player, DIRECTIONS arrow) {
	int new = 0, step = 0, newForest =0;
	char ch = 0;


	if (arrow == UP) {
		if ((*player)->row == 0) {
			(*player)->row = map->height - 1;
			step = 1;
			newForest = 1;
		}
		else {
			new = (*player)->row - 1;
			ch = map->ptr[new][(*player)->col];
			if (ch == '.' || ch == '^') {
				(*player)->row = new;
				step = 1;
			}
		}
	}

	if (arrow == DOWN) {
		if ((*player)->row == map->height - 1) {
			(*player)->row = 0;
			step = 1;
			newForest = 1;
		}
		else {
			new = (*player)->row + 1;
			ch = map->ptr[new][(*player)->col];
			if (ch == '.' || ch == '^') {
				(*player)->row = new;
				step = 1;
			}
		}
	}

	if (arrow == RIGHT) {
		if ((*player)->col == map->width - 1) {
			(*player)->col = 0;
			step = 1;
			newForest = 1;
		}
		else {
			new = (*player)->col + 1;
			ch = map->ptr[(*player)->row][new];
			if (ch == '.' || ch == '^') {
				(*player)->col = new;
				step = 1;
			}
		}
	}

	if (arrow == LEFT) {
		if ((*player)->col == 0) {
			(*player)->col = map->width - 1;
			step = 1;
			newForest = 1;
		}
		else {
			new = (*player)->col - 1;
			ch = map->ptr[(*player)->row][new];
			if (ch == '.' || ch == '^') {
				(*player)->col = new;
				step = 1;
			}
		}
	}

	if (newForest == 1) {
		mapInit(map, &(*player));
		map->cnt++;
		(*player)->curStam = ((*player)->curStam <= 4) ? 0 : (*player)->curStam - 4;
		
		calendMove(&(*player)->calend, 1);
		(*player)->gold += BASE_COEF * map->cnt;
		map->stepLight = 0;
	}

	if (step == 1) {
		(*player)->curStam = ((*player)->curStam <= 1) ? 0 : (*player)->curStam - 1;
		if (map->stepLight > 0) {
			map->stepLight--;
		}
	}
}

void mapPlay(PLAYER** player) {

	if ((*player) == NULL) {
		printf("Игрок не создан\n");
		return;
	}
	if (calendIsNight(&(*player)->calend) == 1) {
		printf("Уже ночь\n");
		return;
	}
	if ((&(*player)->curStam) == 0) {
		printf("Вы устали (стамина на нуле)\n");
		return;
	}

	(*player)->row = 0;
	(*player)->col = 0;

	int quit = 0;
	char ch = 0, s[2];
	MAP map;
	mapCreate(&map, (rand() % (MAX_RANGE)) + 5, (rand() % (MAX_RANGE)) + 5);
	mapInit(&map, &(*player));


	do
	{
		mapPrint(&map, &(*player));

		scanf("%1s", s);
		ch = toupper(s[0]);

		switch (ch) {
		case 'W':
			mapMove(&map, &(*player), UP);
			break;

		case 'A':
			mapMove(&map, &(*player), LEFT);
			break;

		case 'S':
			mapMove(&map, &(*player), DOWN);
			break;

		case 'D':
			mapMove(&map, &(*player), RIGHT);
			break;

		case 'Q':
			quit = mapIsFire(&map, &(*player));
			break;

		case 'L':
			mapLightOn(&map, &(*player));

			break;
		}

		if ((calendIsNight(&(*player)->calend) == 1) || ((*player)->curStam <= 0)) {
			printf("Вы упали в обморок и возвращаетесь домой\n");
			(*player)->gold = (int)((*player)->gold / 2);
			printf("Выносливость: %d | Золото: %d | Время: %d:00\n",
				(*player)->curStam, (*player)->gold, (*player)->calend.current_hour);
			
			break;
		}
		

	} while (quit == 0);

	mapFree(&map);
}