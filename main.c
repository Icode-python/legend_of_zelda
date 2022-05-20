#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <main.h>
#include <string.h>
#include <stdbool.h>

int mapSizeX=16,mapSizeY=11,mapS=64,offset=0,worldX=7,worldY=7,screenWidth=1024,screenHeight=768,yOffset=128;
int Dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};

void frameTimer(int id){
    for(int y=0;y<mapSizeY;y++){for(int x=0;x<mapSizeX;x++){animation(enemies[y][x]);}}
    animation(player);
    player->standing=true;
    glutTimerFunc(100, frameTimer, 0);
}

void updateEnemyLoop(int id){
    update_enemies();
    glutTimerFunc(10, updateEnemyLoop, 0);
}

void gameEvents(int id){
    for(int y=0;y<mapSizeY;y++){for(int x=0;x<mapSizeX;x++){if(enemies[y][x]->alive && !enemies[y][x]->hurt){walkCycle(enemies[y][x]);}}}
    glutTimerFunc(1000, gameEvents, 0);
    glutPostRedisplay();
}

void readMap(){
    for (int y=0;y<mapSizeY;y++){
        for (int x=0;x<mapSizeX;x++){
            map[y][x] = worldMapBlocking[worldY*11+y][worldX*16+x];
            spriteWorldMap[y][x] = worldMapTiles[worldY*11+y][worldX*16+x];
            if (map[y][x]==2){
                changeEntity(enemies[y][x], x*mapS, y*mapS+yOffset, worldX*16+x, worldY*11+y, 2, redOctorockTextureCoords,true);
            }
            else{changeEntity(enemies[y][x],0,0,x,y,1,redOctorockTextureCoords,false);}
        }
    }
    drawWorld();
}

void updatePlayer(){
    if(collisionBorder(player->x,player->y,player->width,player->length,true)==1){readMap();scrollMap(player);}
    updateWeapon(player->weapon,player);
    drawEntity(player);
    for(int y=0;y<mapSizeY;y++){
        for(int x=0;x<mapSizeX;x++){
            if(enemies[y][x]->alive){
                EntityCollision(player,enemies[y][x]);
            }
        }
    }
}

void drawMap(){
    int x,y,xo,yo;
    for (y=0;y<mapSizeY;y++){
        for (x=0;x<mapSizeX;x++){
            if (map[y][x]==0) {drawWall(1,x,y,xo,yo,mapS,offset);} else{drawWall(0,x,y,xo,yo,mapS,offset);}
        }
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawWorld();
    drawEnemyEntity();
    drawGlyph(A);
    updatePlayer(player);
    glutSwapBuffers();
}


void init(){
    glClearColor(0.1,0.1,0.1,0);
    gluOrtho2D(0,screenWidth,screenHeight,0);
    allocEnemies();
    updateEnemyLoop(0);
    readMap();
    A = initGlyph(100,50,7,7,fontTextureCoords[0]);
    player = initEntity(64,64,5*mapS,5*mapS+yOffset,8,0,6,2,playerTextureCoords,1);
    player->weapon = initWeapon(player,64,64,4,1,true,swordTextureCoords);
    frameTimer(0);
    gameEvents(0);
}

int main(int argc, char * argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("legend of zelda");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(buttons);
    glutMainLoop();
}