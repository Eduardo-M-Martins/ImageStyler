#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <omp.h>

#include <GL/glut.h> 

#include "SOIL.h"

typedef struct {
    unsigned char r, g, b;
} Pixel;

typedef struct {
    int width, height;
    Pixel *img;
} Img;

GLuint tex[3];
Img pic[3];

int width, height;
int sel;

void load(char *name, Img *pic);
void draw();
void keyboard(unsigned char key, int x, int y);

void load(char *name, Img *pic) {
    int chan;
    pic->img = (Pixel *)SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if (!pic->img) {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

int main(int argc, char **argv) {
    if (argc < 1) {
        printf("artistic [im. entrada]\n");
        exit(1);
    }
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    load(argv[1], &pic[0]);

    width = pic[0].width;
    height = pic[0].height;
    pic[1].width = pic[0].width;
    pic[1].height = pic[0].height;
    pic[1].img = calloc(pic[1].width * pic[1].height, 3);
    pic[2].width = pic[0].width;
    pic[2].height = pic[0].height;
    pic[2].img = calloc(pic[2].width * pic[2].height, 3);

    glutInitWindowSize(width, height);
    glutCreateWindow("Art");
    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);

    printf("Origin  : %s %d x %d\n", argv[1], pic[0].width, pic[0].height);
    sel = 0;

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, width, height, 0.0);
    glMatrixMode(GL_MODELVIEW);

    Pixel(*in)[width] = (Pixel(*)[width])pic[0].img;
    Pixel(*out)[width] = (Pixel(*)[width])pic[1].img;
    Pixel(*auxImg)[width] = (Pixel(*)[width])pic[2].img;

    typedef struct{
        int y, x;
        Pixel px;
    } Seeds;

    Seeds s[height * width]; 

    int rgb = 55, seg = 12; 
    int inc = 0;           

     for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1){ 
                continue;
            }
            else if ((abs((in[y][x].b - in[y - 1][x - 1].b)) > rgb) && (abs((in[y][x].r - in[y - 1][x - 1].r)) > rgb) && (abs((in[y][x].g - in[y - 1][x - 1].g)) > rgb)){
                s[inc].y = y;
                s[inc].x = x;
                s[inc].px = in[y][x];
                auxImg[s[inc].y][s[inc].x].b=255; 
                auxImg[s[inc].y][s[inc].x].r=255; 
                auxImg[s[inc].y][s[inc].x].g=255; 
                inc++;
                continue;
            }
            else if ((abs((in[y][x].b - in[y - 1][x].b)) > rgb) && (abs((in[y][x].r - in[y - 1][x].r)) > rgb) && (abs((in[y][x].g - in[y - 1][x].g)) > rgb)){
                s[inc].y = y;
                s[inc].x = x;
                s[inc].px = in[y][x];
                auxImg[s[inc].y][s[inc].x].b=255; 
                auxImg[s[inc].y][s[inc].x].r=255; 
                auxImg[s[inc].y][s[inc].x].g=255; 
                inc++;
                continue;
            }
            else if ((abs((in[y][x].b - in[y - 1][x + 1].b)) > rgb) && (abs((in[y][x].r - in[y - 1][x + 1].r)) > rgb) && (abs((in[y][x].g - in[y - 1][x + 1].g)) > rgb)){
                s[inc].y = y;
                s[inc].x = x;
                s[inc].px = in[y][x];
                auxImg[s[inc].y][s[inc].x].b=255;
                auxImg[s[inc].y][s[inc].x].r=255; 
                auxImg[s[inc].y][s[inc].x].g=255; 
                inc++;
                continue;
            }
            else if ((abs((in[y][x].b - in[y][x - 1].b)) > rgb) && (abs((in[y][x].r - in[y][x - 1].r)) > rgb) && (abs((in[y][x].g - in[y][x - 1].g)) > rgb)){
                s[inc].y = y;
                s[inc].x = x;
                s[inc].px = in[y][x];
                auxImg[s[inc].y][s[inc].x].b=255; 
                auxImg[s[inc].y][s[inc].x].r=255; 
                auxImg[s[inc].y][s[inc].x].g=255; 
                inc++;
                continue;
            }
            else if ((abs((in[y][x].b - in[y][x + 1].b)) > rgb) && (abs((in[y][x].r - in[y][x + 1].r)) > rgb) && (abs((in[y][x].g - in[y][x + 1].g)) > rgb)){
                s[inc].y = y;
                s[inc].x = x;
                s[inc].px = in[y][x];
                auxImg[s[inc].y][s[inc].x].b=255; 
                auxImg[s[inc].y][s[inc].x].r=255; 
                auxImg[s[inc].y][s[inc].x].g=255; 
                inc++;
                continue;
            }
            else if ((abs((in[y][x].b - in[y + 1][x - 1].b)) > rgb) && (abs((in[y][x].r - in[y + 1][x - 1].r)) > rgb) && (abs((in[y][x].g - in[y + 1][x - 1].g)) > rgb)){
                s[inc].y = y;
                s[inc].x = x;
                s[inc].px = in[y][x];
                auxImg[s[inc].y][s[inc].x].b=255; 
                auxImg[s[inc].y][s[inc].x].r=255; 
                auxImg[s[inc].y][s[inc].x].g=255; 
                inc++;
                continue;
            }
            else if ((abs((in[y][x].b - in[y + 1][x].b)) > rgb) && (abs((in[y][x].r - in[y + 1][x].r)) > rgb) && (abs((in[y][x].g - in[y + 1][x].g)) > rgb)){
                s[inc].y = y;
                s[inc].x = x;
                s[inc].px = in[y][x];
                auxImg[s[inc].y][s[inc].x].b=255; 
                auxImg[s[inc].y][s[inc].x].r=255; 
                auxImg[s[inc].y][s[inc].x].g=255; 
                inc++;
                continue;
            }
            else if ((abs((in[y][x].b - in[y + 1][x + 1].b)) > rgb) && (abs((in[y][x].r - in[y + 1][x + 1].r)) > rgb) && (abs((in[y][x].g - in[y + 1][x + 1].g)) > rgb)){
                s[inc].y = y;
                s[inc].x = x;
                s[inc].px = in[y][x];
                auxImg[s[inc].y][s[inc].x].b=255; 
                auxImg[s[inc].y][s[inc].x].r=255; 
                auxImg[s[inc].y][s[inc].x].g=255; 
                inc++;
                continue;
            }
            else if (x % seg == 0 && y % seg == 0){
                s[inc].y = y;
                s[inc].x = x;
                s[inc].px = in[y][x];
                auxImg[s[inc].y][s[inc].x].b=255; 
                auxImg[s[inc].y][s[inc].x].r=255; 
                auxImg[s[inc].y][s[inc].x].g=255; 
                inc++;
                continue;
            }
        }
    }

    int aux = -1;
    #pragma omp parallel for private(aux) schedule(dynamic, 8) 
    for (int y = 0; y < height; y++){
        Pixel px;
        for (int x = 0; x < width; x++){
            for (int i = 0; i < inc; i++){
                if (abs(x - s[i].x < 28) || abs(y - s[i].y < 28)){
                    int dist = maxy(abs(y - s[i].y), abs(x - s[i].x));
                    if (dist < aux||aux==-1){
                        aux = dist;
                        px = s[i].px;
                    }
                }
            }
            out[y][x].b = px.b;
            out[y][x].r = px.r;
            out[y][x].g = px.g;
            aux = -1;
        }
        if (y == height - 1)
            printf("Number of seeds: %d\n", inc);
    }

    tex[0] = SOIL_create_OGL_texture((unsigned char *)pic[0].img, width, height, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
    tex[1] = SOIL_create_OGL_texture((unsigned char *)pic[1].img, width, height, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
    tex[2] = SOIL_create_OGL_texture((unsigned char *)pic[2].img, width, height, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);

    glutMainLoop();
}

int maxy(int a, int b){
    return a > b ? a : b;
}

void keyboard(unsigned char key, int x, int y){
    if (key == 27){
        free(pic[0].img);
        free(pic[1].img);
        free(pic[2].img);
        exit(1);
    }
    if (key == '1')sel =0;
    if (key == '2')sel =1;
    if (key == '3')sel =2;

    glutPostRedisplay();
}

void draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3ub(255, 255, 255); 
    glBindTexture(GL_TEXTURE_2D, tex[sel]);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex2f(0, 0);

    glTexCoord2f(1, 0);
    glVertex2f(pic[sel].width, 0);

    glTexCoord2f(1, 1);
    glVertex2f(pic[sel].width, pic[sel].height);

    glTexCoord2f(0, 1);
    glVertex2f(0, pic[sel].height);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}