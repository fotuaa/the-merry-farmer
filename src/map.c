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

	map->row = 0;
	map->col = 0;
	map->cnt = 0;
	map->radius = 5;
	map->stepLight = 0;
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

void mapInit(MAP* map) {

	int percent, i, j;
	char ch;
	for (i = 0; i < map->height; i++) {
		for (j = 0; j < map->width; j++) {
			if (i == map->row && j == map->col) {
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
	j = (rand() % (map->width - 1) + 1 + map->col) % map->width;
	map->ptr[i][j] = '^';

}

int mapIsFire(MAP* map) {
	return (map->ptr[map->row][map->col] == '^') ? 1 : 0;
}

void mapLightOn(MAP* map) {
	map->stepLight = 3;
	map->row_Light = map->row;
	map->col_Light = map->col;
}

void mapPrint(MAP* map) {

	int r = 0;

	printf("\033[2J");   // Очистить экран
	printf("\033[0;0H"); // Позиционируемся в верхний левый угол экрана
	for (int i = 0; i < map->height; i++) {
		for (int j = 0; j < map->width; j++) {
			printf("+---");
		}
		printf("+\n");
		for (int j = 0; j < map->width; j++) {
			if (i == map->row && j == map->col) {
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
	printf("Пройдено локаций: %d, спичка (L) горит: %d\n", map->cnt, map->stepLight);
}

void mapMove(MAP* map, DIRECTIONS arrow) {
	int new = 0, step = 0;
	char ch = 0;


	if (arrow == UP) {
		if (map->row == 0) {
			map->row = map->height - 1;
			mapInit(map);
			map->cnt++;
			step = 1;
		}
		else {
			new = map->row - 1;
			ch = map->ptr[new][map->col];
			if (ch == '.' || ch == '^') {
				map->row = new;
				step = 1;
			}
		}
	}

	if (arrow == DOWN) {
		if (map->row == map->height - 1) {
			map->row = 0;
			mapInit(map);
			map->cnt++;
			step = 1;
		}
		else {
			new = map->row + 1;
			ch = map->ptr[new][map->col];
			if (ch == '.' || ch == '^') {
				map->row = new;
				step = 1;
			}
		}
	}

	if (arrow == RIGHT) {
		if (map->col == map->width - 1) {
			map->col = 0;
			mapInit(map);
			map->cnt++;
			step = 1;
		}
		else {
			new = map->col + 1;
			ch = map->ptr[map->row][new];
			if (ch == '.' || ch == '^') {
				map->col = new;
				step = 1;
			}
		}
	}

	if (arrow == LEFT) {
		if (map->col == 0) {
			map->col = map->width - 1;
			mapInit(map);
			map->cnt++;
			step = 1;
		}
		else {
			new = map->col - 1;
			ch = map->ptr[map->row][new];
			if (ch == '.' || ch == '^') {
				map->col = new;
				step = 1;
			}
		}
	}

	if (map->stepLight > 0 && step == 1) {
		map->stepLight--;
	}
}

void mapPlay() {

	int quit = 0;
	char ch = 0, s[2];
	MAP map;
	mapCreate(&map, (rand() % (MAX_RANGE)) + 5, (rand() % (MAX_RANGE)) + 5);
	mapInit(&map);


	do
	{
		mapPrint(&map);

		scanf("%1s", s);
		ch = toupper(s[0]);

		switch (ch) {
		case 'W':
			mapMove(&map, UP);
			break;

		case 'A':
			mapMove(&map, LEFT);
			break;

		case 'S':
			mapMove(&map, DOWN);
			break;

		case 'D':
			mapMove(&map, RIGHT);
			break;

		case 'Q':
			quit = mapIsFire(&map);
			break;

		case 'L':
			mapLightOn(&map);

			break;
		}

	} while (quit == 0);

	mapFree(&map);
}