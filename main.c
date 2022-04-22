#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <main.h>
#include <string.h>
#include <stdbool.h>

entity enemies[100];
entity player;
int mapSizeX=16,mapSizeY=11,mapS=64,offset=0,nEnemies=0;
int sDir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
int enemyDir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};

void frameTimer(int id){
    for(int e=0;e<nEnemies;e++){
        if(enemies[e].standing==false){enemies[e].frame = !enemies[e].frame;}
    }
    if(!player.standing){player.frame=!player.frame;}
    player.standing=true;
    glutTimerFunc(200, frameTimer, 0);
}

void gameEvents(int id){
    for(int e=0;e<nEnemies;e++){enemies[e] = walkCycle(enemies[e]);}
    glutTimerFunc(1000, gameEvents, 0);
}

void readMap(){
    entity enemy;
    nEnemies = 0;
    for (int y=0;y<mapSizeY;y++){
        for (int x=0;x<mapSizeX;x++){
            if (map[y*mapSizeX+x]==3){
                enemies[nEnemies] = initEntity(enemy,32,32,x*mapS,y*mapS,4,0,redMoblinTextureCoords,1);
                enemies[nEnemies].weapon = initWeapon(enemies[nEnemies].weapon, enemies[nEnemies],32,32,4,arrowTextureCoords);
                nEnemies++;
            }
        }
    }
}

void update_enemies(){
    for(int e=0;e<nEnemies;e++){
        int c = staticCollision(map,enemies[e].x+enemies[e].dx,enemies[e].y+enemies[e].dy,enemies[e].width,enemies[e].length);
        if(c == 0){
            enemies[e].x+=enemies[e].dx;enemies[e].y+=enemies[e].dy;
            glutPostRedisplay();
        }
        else{enemies[e].standing=true;}
        enemies[e].weapon=updateWeapon(enemies[e].weapon,enemies[e]);
        drawEntity(enemies[e]);
    }
}

void updatePlayer(){
    player.weapon = updateWeapon(player.weapon,player);
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
        if(player.weapon.used==0){
            player.weapon.used=1;
            player.weapon.dx=sDir[player.state][0]*player.weapon.speed; player.weapon.dy=sDir[player.state][1]*player.weapon.speed;
        }
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
    player = initEntity(player,32,32,5*mapS,5*mapS,4,0,playerTextureCoords,1);
    player.weapon = initWeapon(player.weapon,player,32,32,4,swordTextureCoords);
    frameTimer(0);
    gameEvents(0);
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