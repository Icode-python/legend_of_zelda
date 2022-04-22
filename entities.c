#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <main.h>
#include <string.h>
#include <stdbool.h>

void drawWeapon(Weapon w){
    glPointSize(1);
    glBegin(GL_POINTS);
    double modColor = rand()%75; modColor = modColor/255;
    for (int y=0;y<w.length;y++){
        for (int x=0;x<w.width;x++){
            int a = y+w.textureCoords[w.state][1];
            int z = x+w.textureCoords[w.state][0];
            if(spriteAtlas[a][z][0] <= 1){
                glColor3f(spriteAtlas[a][z][0]+modColor,spriteAtlas[a][z][1]+modColor,spriteAtlas[a][z][2]+modColor);
                glVertex2i(w.x+x,w.y+y);
            }
        }
    }
    glEnd();
}

entity initEntity(entity e, int width, int height, int x, int y, int speed, int state, long double textureCoords[8][2], int ifWeapon){
    e.x = x; e.y = y;
    e.width=width;e.length=height;
    e.speed=speed;e.state=state;e.frame=false;e.standing=false;
    e.frame=false;
    if(ifWeapon==1){Weapon weapon;e.weapon=weapon;}
    memcpy(e.textureCoords, textureCoords, sizeof(e.textureCoords));
    return e;
}


Weapon initWeapon(Weapon e, entity ep,int width,int length, int speed,long double textureCoords[4][2]){
    e.x=ep.x; e.y=ep.y;e.dx=0;e.dy=0;
    e.width=width; e.length=length;
    e.used=0;e.state=0;e.speed=speed;
    memcpy(e.textureCoords,textureCoords,sizeof(e.textureCoords));
    return e;
}

void drawWall(int wallSprite, int x,int y,int xo,int yo, int mapS, int offset){
    glPointSize(1);
    glBegin(GL_POINTS);
    xo=x*mapS; yo=y*mapS;
    for (y=0;y<mapS;y++){
        for (x=0;x<mapS;x++){
            glColor3f(wall[wallSprite][y*mapS+x][0],wall[wallSprite][y*mapS+x][1],wall[wallSprite][y*mapS+x][2]);
            glVertex2i(xo+offset+x,yo+offset+y);
        }
    }
    glEnd();
}

void drawEntity(entity e){
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int y=0;y<e.length;y++){
        for (int x=0;x<e.width;x++){
            int a = y+e.textureCoords[e.state*2+e.frame][1];
            int z = x+e.textureCoords[e.state*2+e.frame][0];
            if(spriteAtlas[a][z][0] <= 1){
                glColor3f(spriteAtlas[a][z][0],spriteAtlas[a][z][1],spriteAtlas[a][z][2]);
                glVertex2i(e.x+x,e.y+y);
            }
        }
    }
    glEnd();
}