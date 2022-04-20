#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern int mapSizeX;extern int mapSizeY;extern int mapS;extern int offset;

extern long double wall[2][64*64][3];
extern long double playerTextureCoords[8][2];
extern long double spriteAtlas[96][768][3];
extern int map[];

typedef struct Entity{
    int x;
    int y;
    int dx;
    int dy;
    int state;
    int length;
    int width;
    int speed;
    bool frame;
    bool standing;
    long double textureCoords[8][2];
} entity;

//entity
void drawWeapon();
void drawEntity(entity entity);
void drawWall(int wallSprite, int x,int y,int xo,int yo, int mapS, int offset);
entity initEntity(entity e, int width, int height, int x, int y, int speed, int state, long double textureCoords[8][2]);

//math
int staticCollision(int map[], int x1, int y1, int width, int length);
int dynamicCollision(int x1, int width1, int x2, int width2, int y1, int length1, int y2, int length2);
void readMap(entity enemies[]);
entity updateWeapon(entity weapon, entity player);