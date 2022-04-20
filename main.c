#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <main.h>
#include <string.h>
#include <stdbool.h>

entity weapon;
entity enemies[100];
entity player;
int mapSizeX=16,mapSizeY=11,mapS=64,offset=0,nEnemies=0;
int sDir[4][2] = {{0,16},{16,0},{0,-16},{-16,0}};

void timer(int id){
    if(!player.standing){player.frame=!player.frame;}
    player.standing=true;
    glutTimerFunc(300, timer, 0);
}

void readMap(){
    entity enemy;
    nEnemies = 0;
    for (int y=0;y<mapSizeY;y++){
        for (int x=0;x<mapSizeX;x++){
            if (map[y*mapSizeX+x]==3){
                enemies[nEnemies]=enemy;
                enemies[nEnemies] = initEntity(enemies[nEnemies],32,32,x*mapS,y*mapS,4,0,redMoblinTextureCoords);
                nEnemies++;
            }
        }
    }
}

void update_enemies(){
    for(int e=0;e<nEnemies;e++){
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
    drawMap();
    weapon = updateWeapon(weapon,player);
    updatePlayer();
    update_enemies();
    glutSwapBuffers();
}


void buttons(unsigned char key, int x, int y){
    if(key=='a') {player.dx=-player.speed;player.dy=0;player.state=3;}
    if(key=='d') {player.dx=player.speed;player.dy=0;player.state=1;}
    if(key=='w') {player.dy=-player.speed;player.dx=0;player.state=2;}
    if(key=='s') {player.dy=player.speed;player.dx=0;player.state=0;}
    if(key==32) {
        if(weapon.state==0){weapon.dx=sDir[player.state][0];weapon.dy=sDir[player.state][1];weapon.state=1;}
        player.standing=true;
    }
    if (key=='a' || key=='d' || key=='w' || key=='s'){
        player.standing=false;
        int c = staticCollision(map,player.x+player.dx,player.y+player.dy,player.width,player.length);
        if(c == 0){player.x+=player.dx;player.y+=player.dy;}
        else{player.frame=0;player.standing=true;}
    }
    glutPostRedisplay();
}

void init(){
    glClearColor(0.3,0.3,0.3,0);
    gluOrtho2D(0,1024,704,0);
    readMap();
    player = initEntity(player,32,32,5*mapS,5*mapS,4,0,playerTextureCoords);
    weapon = initEntity(weapon,4,4,player.x,player.y,6,0,playerTextureCoords);
    timer(0);
}

int main(int argc, char * argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 704);
    glutCreateWindow("legend of zelda");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(buttons);
    glutMainLoop();
}