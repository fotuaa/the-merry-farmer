#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include "utils.h"

#define MAX_RANGE 26

#define MAX_PERCENT 101
#define MAX_PERCENT_R 15
#define MAX_PERCENT_T 30
#define BASE_COEF 2
#define TEMP_RANGE 40
#define PERCENT_MOVE 20



typedef enum {
	SUNNY,
	RAINFALL,
	FOG,
	STORM
} WEATHERTYPE;

typedef struct {
	WEATHERTYPE wt;
	float temperature;
	int windPower;
} WEATHER;

typedef struct {
	int height, width;
	int row_Light, col_Light;
	char** ptr;
	int cnt, radius, stepLight;
	WEATHER weath;
} MAP;


typedef enum {
	UP,
	RIGHT,
	DOWN,
	LEFT
} DIRECTIONS;


////////////////////////////////
//
//  Работа с погодой на карте
//

void weatherInit(MAP* map);
char* weatherName(MAP* map);

////////////////////////////////
//
//  Работа с картой
//

void mapCreate(MAP* map, int height, int width);
void mapFree(MAP* map);
void mapInit(MAP* map, PLAYER** player);
int mapIsFire(MAP* map, PLAYER** player);
void mapLightOn(MAP* map, PLAYER** player);
void mapPrint(MAP* map, PLAYER** player);
void mapMove(MAP* map, PLAYER** player, DIRECTIONS arrow);
void mapPlay(PLAYER** player);

#endif // !MAP_H