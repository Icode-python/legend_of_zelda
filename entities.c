#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <main.h>
#include <string.h>

void drawWeapon(entity weapon){
    glColor3f(0.3,0.3,0.3);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(weapon.x,weapon.y);
    glEnd();
    glutPostRedisplay();
}

void drawWall(int wallSprite, int x,int y,int xo,int yo, int mapS, int offset){
    xo=x*mapS; yo=y*mapS;
    for (y=0;y<mapS;y++){
        for (x=0;x<mapS;x++){
            glColor3f(wall[wallSprite][y*mapS+x][0],wall[wallSprite][y*mapS+x][1],wall[wallSprite][y*mapS+x][2]);
            glPointSize(1);
            glBegin(GL_POINTS);
            glVertex2i(xo+offset+x,yo+offset+y);
            glEnd();
        }
    }
}

void drawEntity(entity e){
    for (int y=0;y<e.length;y++){
        for (int x=0;x<e.width;x++){
            
        }
    }
}

/*
void drawEntity(entity e){
    entity entity = e;
    for (int y=0;y<entity.length;y++){
        for (int x=0;x<entity.width;x++){
            if(entity.sprite[entity.state][entity.frame][y*entity.length+x][0] <= 1){
                glColor3f(entity.sprite[entity.state][entity.frame][y*entity.length+x][0],entity.sprite[entity.state][entity.frame][y*entity.length+x][1],entity.sprite[entity.state][entity.frame][y*entity.length+x][2]);
                glPointSize(1);
                glBegin(GL_POINTS);
                glVertex2i(entity.x+x,entity.y+y);
                glEnd();
            }
        }
    }
}
*/