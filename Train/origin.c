#include "model.h"
#include "draw.h"
#include "camera.h"

#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

int mouse_x, mouse_y;

double rotateX;
double rotateY;

float metro_PosX = 15.0f;
float metro_PosY = 0.0f;
int last_time = 0;
int acc = 0;
int timer;
int inTheStation = 1;
int inTheEnd = 0;
int arrive = 0;
float metroSpeed = 0.0f;
float light = 0.4f;
float lightm = 0.4f;
int menu = 0;
struct Camera camera;
struct Model metro;
struct Model bench;
struct Model lamp;
struct Model wolf;
//struct Model benchb;

//typedef GLubyte Pixel[3];
GLuint textures[11];

void initialize_texture()
{
    textures[0] = SOIL_load_OGL_texture
	(
		"textures/floor3.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA
	);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	textures[1] = SOIL_load_OGL_texture
	(
		"textures/wall4.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA
	);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	textures[2] = SOIL_load_OGL_texture
	(
		"textures/rail.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA
	);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	textures[3] = SOIL_load_OGL_texture
	(
		"textures/stairs.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA
	);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	textures[4] = SOIL_load_OGL_texture
	(
		"textures/dark.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA
	);

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	textures[5] = SOIL_load_OGL_texture
	(
		"textures/train1.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA
	);

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	textures[6] = SOIL_load_OGL_texture
	(
		"textures/metal.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA
	);

	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	textures[7] = SOIL_load_OGL_texture
	(
		"textures/plafon.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA
	);

	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	textures[8] = SOIL_load_OGL_texture
	(
		"textures/stone2.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA
	);

	
	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	textures[9] = SOIL_load_OGL_texture
	(
		"textures/lamp.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA
	);

	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

void floor()
{
    //PADLÓ eleje

    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-10.0f, -30.0f, -2.0f);
        glTexCoord2f(4.0f,0.0f);glVertex3f(10.0f, -30.0f, -2.0f);
        glTexCoord2f(4.0f,8.0f);glVertex3f(10.0f, 25.0f, -2.0f);
        glTexCoord2f(0.0f,8.0f);glVertex3f(-10.0f, 25.0f, -2.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-10.0f, -10.0f, -2.0f);
        glTexCoord2f(2.0f,0.0f);glVertex3f(-20.0f, -10.0f, -2.0f);
        glTexCoord2f(2.0f,2.3f);glVertex3f(-20.0f, 6.0f, -2.0f);
        glTexCoord2f(0.0f,2.3f);glVertex3f(-10.0f, 6.0f, -2.0f);
    glEnd();

        //felsőszint
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-35.0f, -10.0f, 6.0f);
        glTexCoord2f(1.0f,0.0f);glVertex3f(-60.0f, -10.0f, 6.3f);
        glTexCoord2f(1.0f,1.0f);glVertex3f(-60.0f, 6.0f, 6.3f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(-35.0f, 6.0f, 6.0f);
    glEnd();

    //PADLÓ vége

    //SÍN eleje
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    float i;
     for(i=0.0f;i<395.0f; i += 5.0f){
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(9.0f, -200.0f+i, -3.5f);
        glTexCoord2f(1.0f,0.0f);glVertex3f(21.0f, -200.0f+i, -3.5f);
        glTexCoord2f(1.0f,1.0f);glVertex3f(21.0f, -195.0f+i, -3.5f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(9.0f, -195.0f+i, -3.5f);
    glEnd();}
    //SÍN vége


}

void walls()
{
    //FALAK eleje

    //HÁTSÓ FAL eleje
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-10.0f, -30.0f, -2.0f);
        glTexCoord2f(2.0f,0.0f);glVertex3f(-10.0f, -10.0f, -2.0f);
        glTexCoord2f(2.0f,1.0f);glVertex3f(-10.0f, -10.0f, 8.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(-10.0f, -30.0f, 8.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-10.0f, 6.0f, -2.0f);
        glTexCoord2f(2.0f,0.0f);glVertex3f(-10.0f, 25.0f, -2.0f);
        glTexCoord2f(2.0f,1.0f);glVertex3f(-10.0f, 25.0f, 8.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(-10.0f, 6.0f, 8.0f);
    glEnd();

    //HÁTSÓ FAL vége

    //ELSŐ FAL eleje
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(20.0f, -200.0f, -2.0f);
        glTexCoord2f(15.0f,0.0f);glVertex3f(20.0f, 195.0f, -2.0f);
        glTexCoord2f(15.0f,1.0f);glVertex3f(20.0f, 195.0f, 8.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(20.0f, -200.0f, 8.0f);
    glEnd();
    //ELSŐ FAL vége

    //BAL FAL ELEJE
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-10.0f, 25.0f, -2.0f);
        glTexCoord2f(2.0f,0.0f);glVertex3f(10.0f, 25.0f, -2.0f);
        glTexCoord2f(2.0f,1.0f);glVertex3f(10.0f, 25.0f, 8.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(-10.0f, 25.0f, 8.0f);
    glEnd();
    //BAL FAL VÉGE

    //JOBB FAL ELEJE
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-10.0f, -30.0f, -2.0f);
        glTexCoord2f(2.0f,0.0f);glVertex3f(10.0f, -30.0f, -2.0f);
        glTexCoord2f(2.0f,1.0f);glVertex3f(10.0f, -30.0f, 8.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(-10.0f, -30.0f, 8.0f);
    glEnd();
    //JOBB FAL VÉGE

    //PLAFON eleje
        //VÁRÓTEREM FÖLÖTT
    glBindTexture(GL_TEXTURE_2D, textures[7]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-10.0f, -30.0f, 8.0f);
        glTexCoord2f(2.0f,0.0f);glVertex3f(10.0f, -30.0f, 8.0f);
        glTexCoord2f(2.0f,2.0f);glVertex3f(10.0f, 25.0f, 8.0f);
        glTexCoord2f(0.0f,2.0f);glVertex3f(-10.0f, 25.0f, 8.0f);
    glEnd();
                //lépcső előtt
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-10.0f, -10.0f, 8.0f);
        glTexCoord2f(1.0f,0.0f);glVertex3f(-20.0f, -10.0f, 8.0f);
        glTexCoord2f(1.0f,1.0f);glVertex3f(-20.0f, 6.0f, 8.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(-10.0f, 6.0f, 8.0f);
    glEnd();

            //felsőszint

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-20.0f, -10.0f, 14.0f);
        glTexCoord2f(1.0f,0.0f);glVertex3f(-60.0f, -10.0f, 14.0f);
        glTexCoord2f(1.0f,1.0f);glVertex3f(-60.0f, 6.0f, 14.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(-20.0f, 6.0f, 14.0f);
    glEnd();

        //lépcső előtt és felett összeköt
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-20.0f, -10.0f, 8.0f);
        glTexCoord2f(1.4f,0.0f);glVertex3f(-20.0f, 6.0f, 8.0f);
        glTexCoord2f(1.4f,0.6f);glVertex3f(-20.0f, 6.0f, 14.0f);
        glTexCoord2f(0.0f,0.6f);glVertex3f(-20.0f, -10.0f, 14.0f);
    glEnd();


        //SÍN FÖLÖTT
    glBindTexture(GL_TEXTURE_2D, textures[7]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(10.0f, -200.0f, 8.0f);
        glTexCoord2f(1.0f,0.0f);glVertex3f(20.0f, -200.0f, 8.0f);
        glTexCoord2f(1.0f,20.0f);glVertex3f(20.0f, 195.0f, 8.0f);
        glTexCoord2f(0.0f,20.0f);glVertex3f(10.0f, 195.0f, 8.0f);
    glEnd();
    //PLAFON vége

    //ALAGÚT FALA
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(10.0f, -30.0f, -2.0f);
        glTexCoord2f(10.0f,0.0f);glVertex3f(10.0f, -200.0f, -2.0f);
        glTexCoord2f(10.0f,1.0f);glVertex3f(10.0f, -200.0f, 8.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(10.0f, -30.0f, 8.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(10.0f, 195.0f, -2.0f);
        glTexCoord2f(10.0f,0.0f);glVertex3f(10.0f, 25.0f, -2.0f);
        glTexCoord2f(10.0f,1.0f);glVertex3f(10.0f, 25.0f, 8.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(10.0f, 195.0f, 8.0f);
    glEnd();
    //ALAGÚT FALA vége

    //FOLYOSÓ eleje
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-20.0f, -10.0f, -2.0f);
        glTexCoord2f(1.0f,0.0f);glVertex3f(-10.0f, -10.0f, -2.0f);
        glTexCoord2f(1.0f,1.0f);glVertex3f(-10.0f, -10.0f, 8.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(-20.0f, -10.0f, 8.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-20.0f, 6.0f, -2.0f);
        glTexCoord2f(1.0f,0.0f);glVertex3f(-10.0f, 6.0f, -2.0f);
        glTexCoord2f(1.0f,1.0f);glVertex3f(-10.0f, 6.0f, 8.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(-20.0f, 6.0f, 8.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-20.0f, 6.0f, -2.0f);
        glTexCoord2f(0.1f,0.0f);glVertex3f(-20.0f, 4.0f, -2.0f);
        glTexCoord2f(0.1f,1.0f);glVertex3f(-20.0f, 4.0f, 8.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(-20.0f, 6.0f, 8.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-20.0f, -10.0f, -2.0f);
        glTexCoord2f(0.1f,0.0f);glVertex3f(-20.0f, -8.0f, -2.0f);
        glTexCoord2f(0.1f,1.0f);glVertex3f(-20.0f, -8.0f, 8.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(-20.0f, -10.0f, 8.0f);
    glEnd();


    //FOLYOSÓ vége

    //FAL A LÉPCSŐ MELLETT
        //jobb
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-20.0f, -8.0f, -2.0f);
        glTexCoord2f(4.2f,0.0f);glVertex3f(-60.0f, -8.0f, -2.0f);
        glTexCoord2f(4.2f,1.6f);glVertex3f(-60.0f, -8.0f, 14.0f);
        glTexCoord2f(0.0f,1.6f);glVertex3f(-20.0f, -8.0f, 14.0f);
    glEnd();

        //bal
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-20.0f, 4.0f, -2.0f);
        glTexCoord2f(4.2f,0.0f);glVertex3f(-60.0f, 4.0f, -2.0f);
        glTexCoord2f(4.2f,1.6f);glVertex3f(-60.0f, 4.0f, 14.0f);
        glTexCoord2f(0.0f,1.6f);glVertex3f(-20.0f, 4.0f, 14.0f);
    glEnd();

        //hátul
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(-60.0f, -10.0f, 6.0f);
        glTexCoord2f(1.4f,0.0f);glVertex3f(-60.0f, 6.0f, 6.0f);
        glTexCoord2f(1.4f,0.80f);glVertex3f(-60.0f, 6.0f, 14.0f);
        glTexCoord2f(0.0f,0.80f);glVertex3f(-60.0f, -10.0f, 14.0f);
    glEnd();



    //FAL A LÉPCSŐ MELLETT vége
    //FALAK vége
}

void stairs()
{


    float i;
    int j = -20;
    for(i = -2; i<6; i+=0.5f){

     glBindTexture(GL_TEXTURE_2D, textures[3]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(j, -8.0f, i);
        glTexCoord2f(0.07f,0.0f);glVertex3f(j, 4.0f, i);
        glTexCoord2f(0.07f,0.07f);glVertex3f(j, 4.0f, i+0.5f);
        glTexCoord2f(0.0f,0.07f);glVertex3f(j, -8.0f, i+0.5f);
    glEnd();

       glBindTexture(GL_TEXTURE_2D, textures[3]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(j, -8.0f, i+0.5f);
        glTexCoord2f(0.07f,0.0f);glVertex3f(j, 4.0f, i+0.5f);
        glTexCoord2f(0.07f,0.07f);glVertex3f(j-1, 4.0f, i+0.5f);
        glTexCoord2f(0.0f,0.07f);glVertex3f(j-1, -8.0f, i+0.5f);
    glEnd();

    j -= 1;
    }

    //LÉPCSŐ vége
}
void limit()
{
    //FEKETE falak
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(10.0f, -200.0f, -2.0f);
        glTexCoord2f(1.0f,0.0f);glVertex3f(10.0f, -200.0f, -2.0f);
        glTexCoord2f(1.0f,1.0f);glVertex3f(10.0f, -200.0f, 8.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(10.0f, -200.0f, 8.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(10.0f, 195.0f, -2.0f);
        glTexCoord2f(1.0f,0.0f);glVertex3f(10.0f, 195.0f, -2.0f);
        glTexCoord2f(1.0f,1.0f);glVertex3f(10.0f, 195.0f, 8.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(10.0f, 195.0f, 8.0f);
    glEnd();
    //FEKETE FALAK vége
}
void border()
{

    //SZEGÉLY ELŐL eleje
  glBindTexture(GL_TEXTURE_2D, textures[8]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(19.5f, -200.0f, -2.0f);
        glTexCoord2f(80.0f,0.0f);glVertex3f(19.5f, 195.0f, -2.0f);
        glTexCoord2f(80.0f,1.0f);glVertex3f(20.0f, 195.0f, -2.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(20.0f, -200.0f, -2.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[8]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(19.5f, -200.0f, -2.0f);
        glTexCoord2f(80.0f,0.0f);glVertex3f(19.5f, 195.0f, -2.0f);
        glTexCoord2f(80.0f,1.0f);glVertex3f(19.5f, 195.0f, -3.5f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(19.5f, -200.0f, -3.5f);
    glEnd();
    //SZEGÉLY ELŐL vége

    //SZEGÉLY HÁTUL eleje
    glBindTexture(GL_TEXTURE_2D, textures[8]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(10.5f, -200.0f, -2.0f);
        glTexCoord2f(60.0f,0.0f);glVertex3f(10.5f, 195.0f, -2.0f);
        glTexCoord2f(60.0f,1.0f);glVertex3f(10.5f, 195.0f, -3.5f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(10.5f, -200.0f, -3.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[8]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);glVertex3f(10.5f, -200.0f, -2.0f);
        glTexCoord2f(60.0f,0.0f);glVertex3f(10.5f, 195.0f, -2.0f);
        glTexCoord2f(60.0f,1.0f);glVertex3f(10.0f, 195.0f, -2.0f);
        glTexCoord2f(0.0f,1.0f);glVertex3f(10.0f, -200.0f, -2.0f);
    glEnd();

    //SZEGÉLY HÁTUL vége
}

void draw_metro()
{
    glMatrixMode(GL_MODELVIEW);
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glPushMatrix();

    glTranslatef(metro_PosX,metro_PosY, -3.5f);
    glRotatef(90.0f, 1.0f, 0.0f   , 0.0f );
    glRotatef(90.0f, 0.0f, 1.0f   , 0.0f );
    glScalef(0.05f, 0.05f, 0.05f);

    draw_model(&metro);

	glPopMatrix();

}


void draw_bench()
{

	float ambient_material_color[] = {0.0, 0.0, 0.0, 1.0};
	
    float diffuse_material_color[] = {0.0, 1.0, 0.0, 1.0};

    float specular_material_color[] = {1.0, 1.0, 1.0, 1.0};
	
	float shadow[] = {60.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shadow);

    glMatrixMode(GL_MODELVIEW);

    glBindTexture(GL_TEXTURE_2D, textures[6]);
    glPushMatrix();

    glTranslatef(-9.0f, 10.0f, -2.0f);
     glRotatef(90.0f, 1.0f, 0.0f , 0.0f );
     glRotatef(90.0f, 0.0f, 1.0f , 0.0f );
    glScalef(1.3f, 1.3f, 1.3f);

    draw_model(&bench);

	glPopMatrix();
}

void draw_bench2()
{

    glMatrixMode(GL_MODELVIEW);

    glBindTexture(GL_TEXTURE_2D, textures[6]);
    glPushMatrix();

    glTranslatef(-9.0f, -15.0f, -2.0f);
     glRotatef(90.0f, 1.0f, 0.0f , 0.0f );
     glRotatef(90.0f, 0.0f, 1.0f , 0.0f );
     glScalef(1.3f, 1.3f, 1.3f);

    draw_model(&bench);

	glPopMatrix();
}

void draw_wolf()
{
	
    glMatrixMode(GL_MODELVIEW);

    //glBindTexture(GL_TEXTURE_2D, textures[1]);
    glPushMatrix();

    glTranslatef(-15.0f, 4.0f, -2.0f);
     glRotatef(90.0f, 1.0f, 0.0f , 0.0f );
     glRotatef(0.0f, 0.0f, 1.0f , 0.0f );
     glScalef(0.01f, 0.01f, 0.01);

    draw_model(&wolf);

	glPopMatrix();
}

void draw_lamp()
{
	
    glMatrixMode(GL_MODELVIEW);

    glBindTexture(GL_TEXTURE_2D, textures[9]);
    glPushMatrix();

    glTranslatef(-15.0f, -8.0f, -2.0f);
     glRotatef(90.0f, 1.0f, 0.0f , 0.0f );
     glRotatef(0.0f, 0.0f, 1.0f , 0.0f );
     glScalef(0.3f, 0.3f, 0.3);

    draw_model(&lamp);

	glPopMatrix();
}

void idle()
{
    int curr_time = glutGet(GLUT_ELAPSED_TIME);
    int diff = curr_time - last_time;
    last_time = curr_time;



    const int time_step = 5;
    int i;
    float dt;
     for( i= 0; i < diff; i += time_step) {

    if(diff-i <time_step ){
        dt = (diff-i) /1000.0f;
        }
    else {
        dt = time_step / 1000.0f;
        }

    if( metroSpeed ==0 && arrive == 0 && acc ==0){
        if(inTheStation == 1){
            inTheStation =0;
            timer= curr_time;
            }
       else if(inTheStation == 0){
            if ((timer+3000) < curr_time){
            acc = 1;
            metroSpeed += 0.05f;}
        }
    }

    if (metro_PosY > -10.5f && acc==1 && inTheStation ==0 && arrive ==0){
        if(metro_PosY < 70.0f){
            metroSpeed += 0.05f;
        } else if(metro_PosY >= 70.0f){
        acc = 0;
        metroSpeed = metroSpeed;}

    }

    if (metro_PosY >= 195.0f && acc ==0 && arrive == 0) {
            metro_PosY = -200.0f;

            metroSpeed=0;
            inTheEnd =1;
            arrive =1;

    }



    if(arrive == 1){
            if(inTheEnd == 1){
            inTheEnd = 0;
            timer = curr_time;

            }
            if(inTheEnd ==0 && metro_PosY < -100){
            if((timer+1000) < curr_time)
            {
                    acc = 1;
            metroSpeed +=0.1f;}
            }

            if(metro_PosY > -100.0f){
            acc=0;
            metroSpeed -= 0.1f;

            }

            if(metro_PosY >= 0.0f){
            metroSpeed =0.0f;
            arrive=0;
            inTheStation =1;
            }
        }
    if(metroSpeed < 0.0f){
        metroSpeed =0.0f;
        if(metro_PosY > -10.0f){
        inTheStation =1;
         arrive = 0;   }

    }

    metro_PosY += metroSpeed * dt;

  }

  glutPostRedisplay();
}

void bitmap_output(float x, float y, char *string, void *font) //menühöz kiíratás
{
  int len, i;
  glRasterPos3f(x, y,-1.0f);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }

}


void help(){

	//menüpontok kiírása

	glPushMatrix();
	glLoadIdentity();
	bitmap_output(-0.1f, 0.28f, "[ W ] 'Kamera mozgatasa elore' ",
    GLUT_BITMAP_HELVETICA_12);
	bitmap_output(-0.1f, 0.26f, "[ S ] 'Kamera mozgatasa hatra' ",
    GLUT_BITMAP_HELVETICA_12);
	bitmap_output(-0.1f, 0.24f, "[ D ] 'Kamera mozgatasa jobbra' ",
    GLUT_BITMAP_HELVETICA_12);
	bitmap_output(-0.1f, 0.22f, "[ A ] 'Kamera mozgatasa balra' ",
    GLUT_BITMAP_HELVETICA_12);
	bitmap_output(-0.1f, 0.20f, "[ - ] 'Feny csokkentese' ",
    GLUT_BITMAP_HELVETICA_12);
	bitmap_output(-0.1f, 0.18f, "[ + ] 'Feny novelese' ",
    GLUT_BITMAP_HELVETICA_12);
	bitmap_output(-0.1f, 0.16f, "[ Eger ] 'Eger' ",
    GLUT_BITMAP_HELVETICA_12);

	glPopMatrix();
	glFlush();

	}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);

	set_view_point(&camera);
	//set_lighting();
    float light_diffuse[]    = { light, light, light, 1.0 };
	float light_position[]  = { -15.0, -8.0, 5.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    set_view_point(&camera);
	//set_lighting();
	float light_diffusem[]    = { lightm, lightm, lightm, 1.0 };
	float light_positionm[]  = { -15.0, -8.0, 5.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffusem);
	glLightfv(GL_LIGHT1, GL_POSITION, light_positionm);

    if (menu == 1)help();
	floor();
    walls();
    border();
    limit();
    stairs();
    draw_metro();
    draw_bench();
    draw_bench2();
	draw_wolf();
	draw_lamp();
	glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport (x, y, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.01, 10000.0);
}

void mouse_handler(int button, int state, int x, int y)
{
	mouse_x = x;
	mouse_y = y;
}

void motion_handler(int x, int y)
{
	double horizontal, vertical;

	horizontal = mouse_x - x;
	vertical = mouse_y - y;

	rotate_camera(&camera, horizontal, vertical);

	mouse_x = x;
	mouse_y = y;

    glutPostRedisplay();
}

void collisionDetection(){
    //elől

    if(camera.position.x > 9.5f){
        if((metro_PosY + 20.5) > camera.position.y && camera.position.y > (metro_PosY - 20.5) ){
            camera.position.x = 9.5f;
            camera.position.z = 2;
            }
          else
                camera.position.z = 0;
          if(camera.position.x > 19.5f)
             camera.position.x = 19.5f;
}

    if(camera.position.z == 0 && camera.position.x < 9.5)
        camera.position.z =2;


    //hátul
    if(camera.position.x < -19.5f ){
        if(camera.position.x < -59.5f)
            camera.position.x = -59.5f;
        //lépcső
        if(camera.position.x <= -20.0f)
            camera.position.z = 2;

         if(camera.position.x <= -21.0f)
            camera.position.z = 2.5f;

        if(camera.position.x <= -22.0f)
            camera.position.z = 3.0;

        if(camera.position.x <= -23.0f)
            camera.position.z = 3.5f;

        if(camera.position.x <= -24.0f)
            camera.position.z = 4.0;

        if(camera.position.x <= -25.0f)
            camera.position.z = 4.5f;

        if(camera.position.x <= -26.0f)
            camera.position.z = 5.0;

        if(camera.position.x <= -27.0f)
            camera.position.z = 5.5f;

        if(camera.position.x <= -28.0f)
            camera.position.z = 6;

        if(camera.position.x <= -29.0f)
            camera.position.z = 6.5f;

        if(camera.position.x <= -30.0f)
            camera.position.z = 7;

        if(camera.position.x <= -31.0f)
            camera.position.z = 7.5f;

        if(camera.position.x <= -32.0f)
            camera.position.z = 8;

        if(camera.position.x <= -33.0f)
            camera.position.z = 8.5f;

         if(camera.position.x <= -34.0f)
            camera.position.z = 9.0f;
    }
    //jobb hátul lépcső mellett
    if(camera.position.x < -19.5f && camera.position.y < -7.5f){
       if( camera.position.x < -20.0f)
            camera.position.y = -7.5f;
            else
                camera.position.x = -19.5f;
         }

    //bal hátul lépcső mellett
    if(camera.position.x < -19.5f && camera.position.y > 3.5f){
       if( camera.position.x < -20.0f)
            camera.position.y = 3.5f;
            else
                camera.position.x = -19.5f;
         }

    //jobb oldal
    if(camera.position.y < -29.5f)
            camera.position.y =-29.5f;

    //bal oldal
    if(camera.position.y > 24.5f)
        camera.position.y = 24.5f;

    //jobb összekötő
    if(camera.position.x < -9.5f && camera.position.y < -9.5f){
       if( camera.position.x < -10.0f)
            camera.position.y = -9.5f;
            else
                camera.position.x= -9.5f;
         }

    //bal összekötő
    if(camera.position.x < -9.5f && camera.position.y > 5.5f){
       if( camera.position.x < -10.0f)
            camera.position.y = 5.5f;
            else
                camera.position.x= -9.5f;
         }

        // jobb pad
     if(camera.position.x < -8.2f && camera.position.y < -12.0f && camera.position.y > -17.5f){
            if( camera.position.x < -9.0f && camera.position.y == -12.0f){
                camera.position.y = -12.0f;
                }
            if( camera.position.x < -9.0f && camera.position.y == -17.5f){
                camera.position.y = -17.5f;
                }
        else
            camera.position.x= -8.2f;
         }

        //bal pad
     if(camera.position.x < -8.2f && camera.position.y < 12.5f && camera.position.y > 7.0f){
            if( camera.position.x < -9.0f && camera.position.y == 12.5f){
                camera.position.y = 12.5f;
                }
            if( camera.position.x < -9.0f && camera.position.y == 7.0f){
                camera.position.y = 7.0f;
                }
        else
            camera.position.x= -8.2f;
        }

    printf("%f %f \n   ", camera.position.y, metro_PosY);
}

void key_handler(int key, int x, int y)
{
	switch (key) {
	case 'w':

        move_camera_forward(&camera);
        collisionDetection();
		break;
	case 's':
		move_camera_backward(&camera);
		collisionDetection();
		break;
	case 'a':
		step_camera_left(&camera);
        collisionDetection();
		break;
	case 'd':
		step_camera_right(&camera);
		collisionDetection();
		break;

    case '-':

			if(light>0.0 && lightm>0.0){
			light=light-0.05;
			lightm=lightm-0.05;
			}
		break;

	case '+':
		if(light<0.8 && lightm<0.8){
		light=light+0.05;
		lightm=lightm+0.05;
		}
	break;
	}

	glutPostRedisplay();
}

void special (int key, int x, int y)
{
switch (key)
{
case GLUT_KEY_F1:
	if(menu == 0)
        menu = 1;
    else menu =0;
break;

}
}

void initialize()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

	
    glClearDepth(1.0);

    initialize_texture();

}

void set_lighting()
{
    float ambient_light[] = { 0.1f, 0.1f, 0.1f, 0.1f };
    float diffuse_light[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    float specular_light[] = { 0.8f, 0.8f, 0.8f, 0.8f };
    float position[] = { -4.0f, -2.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}


/**
 * Main function
 */
int main(int argc, char* argv[])
{
    rotateX = 0.0;
    rotateY = 0.0;

    load_model("train1.obj", &metro);
    print_bounding_box(&metro);

    load_model("bench.obj", &bench);
    print_bounding_box(&bench);
	
	load_model("wolf.obj", &wolf);
    print_bounding_box(&wolf);
	
	load_model("lamp.obj", &lamp);
    print_bounding_box(&lamp);


    glutInit(&argc, argv);

	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	int window = glutCreateWindow("GLUT Window");
	glutSetWindow(window);

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key_handler);
    glutSpecialFunc(special);
    glutMouseFunc(mouse_handler);
    glutMotionFunc(motion_handler);
    glutIdleFunc(idle);
    init_camera(&camera);

    glutMainLoop();

    return 0;
}

