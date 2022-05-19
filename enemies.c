#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <main.h>
#include <string.h>
#include <stdbool.h>

void update_enemies(){
    for(int y=0;y<mapSizeY;y++){
        for(int x=0;x<mapSizeX;x++){
            if(enemies[y][x]->alive){
                EntityCollision(enemies[y][x],player);
                int c = staticCollision(map,enemies[y][x]->x+enemies[y][x]->dx,enemies[y][x]->y+enemies[y][x]->dy,enemies[y][x]->width,enemies[y][x]->length);
                int d = collisionBorder(enemies[y][x]->x+enemies[y][x]->dx*enemies[y][x]->speed,enemies[y][x]->y+enemies[y][x]->dy*enemies[y][x]->speed,enemies[y][x]->width,enemies[y][x]->length, false);
                if(c == 0 && d == 0){
                    enemies[y][x]->x+=enemies[y][x]->dx;enemies[y][x]->y+=enemies[y][x]->dy;
                    glutPostRedisplay();
                }
                else{enemies[y][x]->standing=true;}
            }
            updateWeapon(enemies[y][x]->weapon,enemies[y][x]);
        }
    }
}


void allocEnemies(){
    for(int y=0;y<mapSizeY;y++){
        for(int x=0;x<mapSizeX;x++){
            enemies[y][x] = initEntity(64,64,x*mapS,y*mapS,1,0,2,1,redOctorockTextureCoords,1);
            enemies[y][x]->weapon = initWeapon(enemies[y][x],64,64,4,1,false,arrowTextureCoords);
            enemies[y][x]->alive = false;
        }
    }
}

entity * walkCycle(entity * e){
    srand(rand());
    int r = rand()%8;
    if(r>=4){
        e->dx=0;e->dy=0;e->standing=true;
        if(e->weapon->used!=1 && r==4){
            e->weapon->used=1;
            e->weapon->dx=Dir[e->state][0]*e->weapon->speed;
            e->weapon->dy=Dir[e->state][1]*e->weapon->speed;
        }
    }
    else{
        e->state = r;e->standing=false;
        e->dx = Dir[e->state][0];e->dy = Dir[e->state][1];
    }
}

entity * changeEntity(entity * e, int x, int y, int ox, int oy, int health, float textureCoords[8][2], bool alive){
    e->x = x; e->y = y; e->health=health; e->alive=alive; e->ox=ox; e->oy=oy;
    memcpy(e->textureCoords, textureCoords, sizeof(e->textureCoords));
}

void drawEnemyEntity(){
     for(int y=0;y<mapSizeY;y++){
        for(int x=0;x<mapSizeX;x++){
            if(enemies[y][x]->alive){
                glPointSize(scale);
                glBegin(GL_POINTS);
                double modColor;
                if(enemies[y][x]->hurt==true){modColor = rand()%75; modColor = modColor/255;}
                else{modColor=0;}
                for (int l=0;l<enemies[y][x]->length/scale;l++){
                    for (int g=0;g<enemies[y][x]->width/scale;g++){
                        int a = l+enemies[y][x]->textureCoords[enemies[y][x]->state*2+enemies[y][x]->frame][1];
                        int z = g+enemies[y][x]->textureCoords[enemies[y][x]->state*2+enemies[y][x]->frame][0];
                        if(spriteAtlas[a][z][0] <= 1){
                            glColor3f(spriteAtlas[a][z][0]+modColor,spriteAtlas[a][z][1]+modColor,spriteAtlas[a][z][2]+modColor);
                            glVertex2i(enemies[y][x]->x+g*scale,enemies[y][x]->y+l*scale);
                        }
                    }
                }
                glEnd();
            }
        }
     }
}