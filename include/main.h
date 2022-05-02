#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define scale 4

extern int mapSizeX;extern int mapSizeY;extern int mapS;extern int offset;extern int worldX;extern int worldY;extern int screenWidth; extern int screenHeight; extern int yOffset;

extern long double wall[2][64*64][3];
extern long double playerTextureCoords[8][2];
extern long double redMoblinTextureCoords[8][2];
extern long double redOctorockTextureCoords[8][2];
extern long double swordTextureCoords[4][2];
long double arrowTextureCoords[4][2];
extern long double spriteAtlas[48][384][3];
extern int worldMapBlocking[88][256];
extern int worldMapTiles[88][256];
extern int worldMapSpritesTextureCoords[144][2];
extern long double worldMapTilesSprites[136][306][3];
int spriteWorldMap[11][16];
int Dir[4][2];

extern int map[11][16];

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
    int x, y, ox, oy;
    int dx;
    int dy;
    int state;
    int length;
    int width;
    int speed;
    int health;
    int animTimer;
    int animMax;
    bool hurt;
    bool frame;
    bool standing;
    bool alive;
    long double textureCoords[8][2];
    Weapon * weapon;
} entity;

entity * player;
entity * enemies[11][16];

//entity 
void drawWeapon(Weapon * w);
void drawEntity(entity * entity);
void drawWall(int wallSprite, int x,int y,int xo,int yo, int mapS, int offset);
entity * initEntity(int width, int height, int x, int y, int speed, int state, int health, int animMax, long double textureCoords[8][2], int ifWeapon);
Weapon * initWeapon(entity * ep,int width,int length, int speed, int damage, bool changeColor, long double textureCoords[4][2]);
entity * walkCycle(entity * e);
entity * animation(entity * e);
entity * changeEntity(entity * e, int x, int y, int ox, int oy, int health, long double textureCoords[8][2], bool alive);

//math
int staticCollision(int map[11][16], int x1, int y1, int width, int length);
int dynamicCollision(int x1, int width1, int x2, int width2, int y1, int length1, int y2, int length2);
Weapon * updateWeapon(Weapon * weapon, entity * player);
Weapon * resetWeapon(Weapon * weapon,entity * e);
entity * EntityCollision(entity * e, entity * target);
void buttons(unsigned char key, int x, int y);
entity * obstacleCollision(entity * e);
int collisionBorder(int x, int y,int width,int length, bool ifChange);
int scrollMap(entity * e);
void drawWorldSprite(int x, int y, int textureCoords[2]);
void drawWorld();
void update_enemies();
