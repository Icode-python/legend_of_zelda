#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern long double wall[2][64*64][3];
long double playerTextureCoords[8][2];
extern long double playerSprite[256*32][3];
extern long double red_moblin[4][2][32*32][3];
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
    int frame;
    int standing;
    int textureCoords[8][2];
    long double sprite[256*32][3];
} entity;

void drawWeapon();
void drawEntity(entity entity);
void drawWall(int wallSprite, int x,int y,int xo,int yo, int mapS, int offset);
