#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <main.h>
#include <string.h>

entity weapon;
entity enemies[2];
entity player;
int mapSizeX=16,mapSizeY=11,mapS=64,offset=0;
int sDir[4][2] = {{0,16},{0,-16},{-16,0},{16,0}};

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

void updateWeapon(){
    if(weapon.state==1){
        int c = staticCollision(map,weapon.x-4,weapon.y-4,0,0);
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
}

void timer(int id){
    if(player.standing==0){
        if(player.frame==0){player.frame=1;}
        else{player.frame=0;}
    }
}

void update_enemies(){
    for(int e=0;e<2;e++){
        int c = staticCollision(map,enemies[e].x+enemies[e].dx,enemies[e].y+enemies[e].dy,enemies[e].width,enemies[e].length);
        if(c == 0){enemies[e].x+=enemies[e].dx;enemies[e].y+=enemies[e].dy;glutPostRedisplay();}
        drawEntity(enemies[e]);
    }
}

void updatePlayer(){
    drawEntity(player);
    for(int e=0;e<2;e++){
        int c = dynamicCollision(enemies[e].x,enemies[e].x,player.x,player.width,enemies[e].y,enemies[e].length,player.y,player.length);
    }
}

void drawMap(){
    int x,y,xo,yo;
    for (y=0;y<mapSizeY;y++){
        for (x=0;x<mapSizeX;x++){
            if (map[y*mapSizeX+x]==1) {drawWall(1,x,y,xo,yo,mapS,offset);} else{drawWall(0,x,y,xo,yo,mapS,offset);}
        }
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glutTimerFunc(1000.0,timer,0);
    drawMap();
    updateWeapon();
    //update_enemies();
    updatePlayer();
    glutSwapBuffers();
}


void buttons(unsigned char key, int x, int y){
    if(key=='a') {player.dx=-player.speed;player.dy=0;player.state=3;player.standing=0;}
    if(key=='d') {player.dx=player.speed;player.dy=0;player.state=1;player.standing=0;}
    if(key=='w') {player.dy=-player.speed;player.dx=0;player.state=2;player.standing=0;}
    if(key=='s') {player.dy=player.speed;player.dx=0;player.state=0;player.standing=0;}
    if(key==32) {
        if(weapon.state==0){weapon.dx=sDir[player.state][0];weapon.dy=sDir[player.state][1];weapon.state=1;}
    }
    if (key=='a' || key=='d' || key=='w' || key=='s'){
        int c = staticCollision(map,player.x+player.dx,player.y+player.dy,player.width,player.length);
        if(c == 0){player.x+=player.dx;player.y+=player.dy;}
        else{player.frame=0;}
    }
    glutPostRedisplay();
}

void readMap(){
    entity enemy;
    int count = 0;
    for (int y=0;y<mapSizeY;y++){
        for (int x=0;x<mapSizeX;x++){
            if (map[y*mapSizeX+x]==3){
                enemies[count]=enemy;
                enemies[count].x = x*mapS;enemies[count].y = y*mapS;
                enemies[count].length=32;enemies[count].width=32;
                enemies[count].state = 0;enemies[count].frame = 1;
                count++;
            }
        }
    }
}

void init(){
    glClearColor(0.3,0.3,0.3,0);
    gluOrtho2D(0,1024,704,0);
    //readMap();
    player.x = 5*mapS; player.y = 5*mapS;
    weapon.x=player.x; weapon.y=player.y; weapon.state=0;player.width=32;player.length=32;
    player.speed = 4;player.state=0;player.frame=0;player.standing=1;
    memcpy(player.textureCoords, playerTextureCoords, sizeof(player.textureCoords));
}

void reshape(int width, int height){
    glutReshapeWindow(1024,704);
}

int main(int argc, char * argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 704);
    glutCreateWindow("legend of zelda");
    glutReshapeFunc(reshape);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(buttons);
    glutMainLoop();
}