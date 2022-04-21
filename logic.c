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

entity updateWeapon(entity weapon, entity player){
    if(weapon.state==1){
        int c = staticCollision(map,weapon.x,weapon.y,4,4);
        if(c==0){
            drawWeapon(weapon);
            weapon.x+=weapon.dx; weapon.y+=weapon.dy;
        }
        else if(c==1){
            weapon.state=0;weapon.dx=0;weapon.dy=0;weapon.x=player.x+player.width/2;weapon.y=player.y+player.length/2;
        }
    }
    else{
        weapon.x=player.x+player.width/2;weapon.y=player.y+player.length/2; 
    }
    return weapon;
}