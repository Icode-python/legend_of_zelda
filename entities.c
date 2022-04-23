#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <main.h>
#include <string.h>
#include <stdbool.h>

void drawWeapon(Weapon * w){
    glPointSize(1);
    glBegin(GL_POINTS);
    double modColor;
    if(w->changeColor==true){modColor = rand()%75; modColor = modColor/255;}
    else{modColor=0;}
    for (int y=0;y<w->length;y++){
        for (int x=0;x<w->width;x++){
            int a = y+w->textureCoords[w->state][1];
            int z = x+w->textureCoords[w->state][0];
            if(spriteAtlas[a][z][0] <= 1){
                glColor3f(spriteAtlas[a][z][0]+modColor,spriteAtlas[a][z][1]+modColor,spriteAtlas[a][z][2]+modColor);
                glVertex2i(w->x+x,w->y+y);
            }
        }
    }
    glEnd();
}


entity * initEntity(int width, int height, int x, int y, int speed, int state, int health, long double textureCoords[8][2], int ifWeapon){
    entity *e;
    e = (entity *)malloc(sizeof(entity));
    e->x = x; e->y = y;
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
        e->x+=e->dx;e->y+=e->dy;
        e->animTimer++; 
        if(e->animTimer>=1){e->dx=0;e->dy=0;}
        if(e->animTimer>=5){e->animTimer=0;e->hurt=false;}
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
        if(e->health<=0){e->alive=false;}
        else{e->hurt=true;}
    }
    return e;
}


Weapon * initWeapon(entity * ep,int width,int length, int speed, int damage, bool changeColor, long double textureCoords[4][2]){
    Weapon *e;
    e = (Weapon *)malloc(sizeof(Weapon));
    e->x=ep->x; e->y=ep->y;e->dx=0;e->dy=0;
    e->width=width; e->length=length;
    e->used=0;e->state=0;e->speed=speed;
    e->damage = damage; e->changeColor = changeColor;
    memcpy(e->textureCoords,textureCoords,sizeof(e->textureCoords));
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
    glPointSize(1);
    glBegin(GL_POINTS);
    double modColor;
    if(e->hurt==true){modColor = rand()%75; modColor = modColor/255;}
    else{modColor=0;}
    for (int y=0;y<e->length;y++){
        for (int x=0;x<e->width;x++){
            int a = y+e->textureCoords[e->state*2+e->frame][1];
            int z = x+e->textureCoords[e->state*2+e->frame][0];
            if(spriteAtlas[a][z][0] <= 1){
                glColor3f(spriteAtlas[a][z][0]+modColor,spriteAtlas[a][z][1]+modColor,spriteAtlas[a][z][2]+modColor);
                glVertex2i(e->x+x,e->y+y);
            }
        }
    }
    glEnd();
}