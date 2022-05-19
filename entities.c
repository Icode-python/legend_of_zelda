#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <main.h>
#include <string.h>
#include <stdbool.h>

entity * initEntity(int width, int height, int x, int y, int speed, int state, int health, int animMax, float textureCoords[8][2], int ifWeapon){
    entity *e;
    e = (entity *)malloc(sizeof(entity));
    e->x = x; e->y = y;e->animMax=animMax;
    e->width=width;e->length=height;
    e->speed=speed;e->state=state;e->frame=false;e->standing=false;
    e->frame=false;e->health=health;e->hurt=false;e->alive=true;
    e->animTimer=0;
    memcpy(e->textureCoords, textureCoords, sizeof(e->textureCoords));
    return e;
}

entity * animation(entity * e){
    if(e->standing==false && e->alive && !e->hurt){e->frame = !e->frame;}
    if(e->hurt){
        obstacleCollision(e);
        e->animTimer++; 
        if(e->animTimer>=e->animMax){e->dx=0;e->dy=0;}
        if(e->animTimer>=e->animMax+2){e->animTimer=0;e->hurt=false;}
    }
    if(!e->alive){
        e->animTimer++;
    }
    return e;
}

entity * EntityCollision(entity * e, entity * target){
    int d = 0;
    if(target->weapon->used==true){d = dynamicCollision(e->x,e->width,target->weapon->x,target->weapon->width,e->y,e->length,target->weapon->y,target->weapon->length);}
    if(d==1){
        e->dx=target->weapon->dx;e->dy=target->weapon->dy;
        resetWeapon(target->weapon,target);
        e->health--;
        if(e->health<=0){e->alive=false;worldMapBlocking[e->oy][e->ox]=1;}
        else{e->hurt=true;}
    }
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

void drawEntity(entity * e){
    glPointSize(scale);
    glBegin(GL_POINTS);
    double modColor;
    if(e->hurt==true){modColor = rand()%75; modColor = modColor/255;}
    else{modColor=0;}
    for (int y=0;y<e->length/scale;y++){
        for (int x=0;x<e->width/scale;x++){
            int a = y+e->textureCoords[e->state*2+e->frame][1];
            int z = x+e->textureCoords[e->state*2+e->frame][0];
            if(spriteAtlas[a][z][0] <= 1){
                glColor3f(spriteAtlas[a][z][0]+modColor,spriteAtlas[a][z][1]+modColor,spriteAtlas[a][z][2]+modColor);
                glVertex2i(e->x+x*scale,e->y+y*scale);
            }
        }
    }
    glEnd();
}

void drawWorldSprite(int wx, int wy, int textureCoords[2]){
    glPointSize(scale);
    glBegin(GL_POINTS);
    for (int y=0;y<mapS/scale;y++){
        for (int x=0;x<mapS/scale;x++){
            int a = y+textureCoords[1];
            int z = x+textureCoords[0];
            glColor3f(worldMapTilesSprites[a][z][0],worldMapTilesSprites[a][z][1],worldMapTilesSprites[a][z][2]);
            glVertex2i(wx+x*scale,wy+y*scale);
        }
    }
    glEnd();
}

void drawWorld(){
    for (int y=0;y<mapSizeY;y++){
        for (int x=0;x<mapSizeX;x++){
            drawWorldSprite(x*mapS, y*mapS+yOffset, worldMapSpritesTextureCoords[spriteWorldMap[y][x]]);
        }
    }
}