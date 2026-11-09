#ifndef MAP_H
#define MAP_H


#define MAX_RANGE 26

#define MAX_PERCENT 101
#define MAX_PERCENT_R 15
#define MAX_PERCENT_T 30


////////////////////////////////
//
//  Работа с картой
//

typedef struct {
	int height, width;
	int row, col;
	int row_Light, col_Light;
	char** ptr;
	int cnt, radius, stepLight;
} MAP;

typedef enum {
	UP,
	RIGHT,
	DOWN,
	LEFT
} DIRECTIONS;


void mapCreate(MAP* map, int height, int width);
void mapFree(MAP* map);
void mapInit(MAP* map);
int mapIsFire(MAP* map);
void mapLightOn(MAP* map);
void mapPrint(MAP* map);
void mapMove(MAP* map, DIRECTIONS arrow);
void mapPlay();

#endif // !MAP_H