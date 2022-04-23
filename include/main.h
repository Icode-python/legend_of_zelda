#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern int mapSizeX;extern int mapSizeY;extern int mapS;extern int offset;

extern long double wall[2][64*64][3];
extern long double playerTextureCoords[8][2];
extern long double redMoblinTextureCoords[8][2];
extern long double redOctorockTextureCoords[8][2];
extern long double swordTextureCoords[4][2];
long double arrowTextureCoords[4][2];
extern long double spriteAtlas[96][768][3];
int enemyDir[4][2];

extern int map[];

typedef struct Weapon{
    int x;
    int y;
    int dx;
    int dy;
    int state;
    int length;
    int width;
    int speed;
    int damage;
    bool frame;
    bool used;
    bool changeColor;
    long double textureCoords[4][2];
} Weapon;

typedef struct Entity{
    int x;
    int y;
    int dx;
    int dy;
    int state;
    int length;
    int width;
    int speed;
    int health;
    bool hurt;
    bool frame;
    bool standing;
    bool alive;
    long double textureCoords[8][2];
    Weapon weapon;
} entity;

//entity
void drawWeapon(Weapon w);
void drawEntity(entity entity);
void drawWall(int wallSprite, int x,int y,int xo,int yo, int mapS, int offset);
entity initEntity(entity e, int width, int height, int x, int y, int speed, int state, int health, long double textureCoords[8][2], int ifWeapon);
Weapon initWeapon(Weapon e, entity ep,int width,int length, int speed, int damage, bool changeColor, long double textureCoords[4][2]);
entity walkCycle(entity e);

//math
int staticCollision(int map[], int x1, int y1, int width, int length);
int dynamicCollision(int x1, int width1, int x2, int width2, int y1, int length1, int y2, int length2);
Weapon updateWeapon(Weapon weapon, entity player);
Weapon resetWeapon(Weapon weapon,entity e);
entity EntityCollision(entity e, entity target);