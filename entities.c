#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <main.h>
#include <string.h>
#include <stdbool.h>

void drawWeapon(entity weapon){
    glColor3f(0.3,0.3,0.3);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(weapon.x,weapon.y);
    glEnd();
    glutPostRedisplay();
}

entity initEntity(entity e, int width, int height, int x, int y, int speed, int state, long double textureCoords[8][2]){
    e.x = x; e.y = y;
    e.width=width;e.length=height;
    e.speed=speed;e.state=state;e.frame=false;e.standing=true;
    e.frame=false;
    memcpy(e.textureCoords, textureCoords, sizeof(e.textureCoords));
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
            if(spriteAtlas[a][z][2] <= 1){
                glColor3f(spriteAtlas[a][z][0],spriteAtlas[a][z][1],spriteAtlas[a][z][2]);
                glVertex2i(e.x+x,e.y+y);
            }
        }
    }
    glEnd();
}