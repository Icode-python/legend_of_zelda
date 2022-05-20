#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <main.h>
#include <string.h>
#include <stdbool.h>

Glyph * initGlyph(int x, int y, int w, int l, float texCoords[2]){
    Glyph * g;
    g = (Glyph *)malloc(sizeof(Glyph));
    g->x = x; g->y = y; g->width = w; g->length = l;
    memcpy(g->textureCoords,texCoords,sizeof(g->textureCoords));
    return g;
}

void drawGlyph(Glyph * g){
    glPointSize(scale);
    glBegin(GL_POINTS);
    for (int y=0;y<g->length/scale;y++){
        for (int x=0;x<g->width/scale;x++){
            int a = y+g->textureCoords[1];
            int z = x+g->textureCoords[0];
            if(font[a][z][0] <= 1){
                glColor3f(font[a][z][0],font[a][z][1],font[a][z][2]);
                glVertex2i(g->x+x*scale,g->y+y*scale);
            }
        }
    }
    glEnd();
    glutPostRedisplay();
}