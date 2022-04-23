#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <main.h>
#include <string.h>
#include <stdbool.h>

int staticCollision(int map[], int x1, int y1, int width, int length){
    for (int y=0;y<mapSizeY;y++){
        for (int x=0;x<mapSizeX;x++){
            if (map[y*mapSizeX+x]==1){
                if(x1+width>x*mapS && x1<x*mapS+mapS && y1+length>y*mapS && y1<y*mapS+mapS){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int dynamicCollision(int x1, int width1, int x2, int width2, int y1, int length1, int y2, int length2){
    if(x1+width1>x2 && x1<x2+width2 && y1+length1>y2 && y1<y2+length2){
        return 1;
    }
    else {return 0;}

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
        if(c==0){
            drawWeapon(weapon);
            weapon->x+=weapon->dx; weapon->y+=weapon->dy;
        }
        else if(c==1){resetWeapon(weapon,e);}
    }
    else{
        weapon->state = e->state;
        weapon->x=e->x+e->width-weapon->width;weapon->y=e->y+e->length-weapon->length;;
    }
    return weapon;
}

entity * walkCycle(entity * e){
    srand(rand());
    int r = rand()%8;
    if(r>=4){
        e->dx=0;e->dy=0;e->standing=true;
        if(e->weapon->used!=1 && r==4){
            e->weapon->used=1;
            e->weapon->dx=enemyDir[e->state][0]*e->weapon->speed;
            e->weapon->dy=enemyDir[e->state][1]*e->weapon->speed;
        }
    }
    else{
        e->state = r;e->standing=false;
        e->dx = enemyDir[e->state][0];e->dy = enemyDir[e->state][1];
    }
    return e;
}

void buttons(unsigned char key, int x, int y){
    if(!player->hurt){
        if(key=='a' && !player->hurt) {player->dx=-player->speed;player->dy=0;player->state=3;}
        if(key=='d' && !player->hurt) {player->dx=player->speed;player->dy=0;player->state=1;}
        if(key=='w' && !player->hurt) {player->dy=-player->speed;player->dx=0;player->state=2;}
        if(key=='s' && !player->hurt) {player->dy=player->speed;player->dx=0;player->state=0;}
        if(key==32) {
            if(player->weapon->used==0){
                player->weapon->used=1;
                player->weapon->dx=sDir[player->state][0]*player->weapon->speed; player->weapon->dy=sDir[player->state][1]*player->weapon->speed;
            }
            player->standing=true;
        }
        if (key=='a' || key=='d' || key=='w' || key=='s'){
            player->standing=false;
            int c = staticCollision(map,player->x+player->dx,player->y+player->dy,player->width,player->length);
            if(c == 0){player->x+=player->dx;player->y+=player->dy;}
            else{player->frame=0;player->standing=true;}
        }
        glutPostRedisplay();
    }
}