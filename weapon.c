#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <main.h>
#include <string.h>
#include <stdbool.h>

void drawWeapon(Weapon * w){
    glPointSize(scale);
    glBegin(GL_POINTS);
    double modColor;
    if(w->changeColor==true){modColor = rand()%75; modColor = modColor/255;}
    else{modColor=0;}
    for (int y=0;y<w->length/scale;y++){
        for (int x=0;x<w->width/scale;x++){
            int a = y+w->textureCoords[w->state][1];
            int z = x+w->textureCoords[w->state][0];
            if(spriteAtlas[a][z][0] <= 1){
                glColor3f(spriteAtlas[a][z][0]+modColor,spriteAtlas[a][z][1]+modColor,spriteAtlas[a][z][2]+modColor);
                glVertex2i(w->x+x*scale,w->y+y*scale);
            }
        }
    }
    glEnd();
    glutPostRedisplay();
}

Weapon * initWeapon(entity * ep,int width,int length, int speed, int damage, bool changeColor, float textureCoords[4][2]){
    Weapon *e;
    e = (Weapon *)malloc(sizeof(Weapon));
    e->x=ep->x; e->y=ep->y;e->dx=0;e->dy=0;
    e->width=width; e->length=length;
    e->used=0;e->state=0;e->speed=speed;
    e->damage = damage; e->changeColor = changeColor;
    memcpy(e->textureCoords,textureCoords,sizeof(e->textureCoords));
    return e;
}

Weapon * resetWeapon(Weapon * weapon,entity * e){
    weapon->used=0;
    weapon->dx=0;weapon->dy=0;
    weapon->x=e->x+e->width-weapon->width;weapon->y=e->y+e->length-weapon->length;
    return weapon;
}

Weapon * updateWeapon(Weapon * weapon, entity * e){
    if(weapon->used==1){
        int c = staticCollision(map,weapon->x,weapon->y,weapon->width,weapon->length);
        int d = collisionBorder(weapon->x,weapon->y,weapon->width/2,weapon->length/2,false);
        if(c==0 && d==0){
            drawWeapon(weapon);
            weapon->x+=weapon->dx; weapon->y+=weapon->dy;
        }
        else if(c==1 || d==1){resetWeapon(weapon,e);}
    }
    else{
        weapon->state = e->state;
        weapon->x=e->x+e->width-weapon->width;weapon->y=e->y+e->length-weapon->length;;
    }
    return weapon;
}