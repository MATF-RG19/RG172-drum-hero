#include <stdio.h>
//#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "okruzenje.h"
#include "image.h"
#include "main.h"

#define PI 3.1415926535
#define EPSILON 0.01

/*
---------------------------------------
            Game World
---------------------------------------
*/

void pozadina()
{

glPushMatrix();
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, textures[0]);

  glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex3f(10, -2.5, 0);

    glTexCoord2f(0, 1);
    glVertex3f(-10, -2.5, 0);

    glTexCoord2f(1, 1);
    glVertex3f(-10, -2.5, 5.2);

    glTexCoord2f(1, 0);
    glVertex3f(10, -2.5, 5.2);
   glEnd();

glDisable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, 0);
glPopMatrix();
}


void podloga()
{

glPushMatrix();
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, textures[1]);

  glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex3f(-6, 5.5, 0);

    glTexCoord2f(0,1);
    glVertex3f(6, 5.5, 0);

    glTexCoord2f(1, 1);
    glVertex3f(6, -2.5, 0);

    glTexCoord2f(1, 0);
    glVertex3f(-6, -2.5, 0);
   glEnd();

glDisable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, 0);
glPopMatrix();
}

void kolovoz()
{

glPushMatrix();
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, textures[2]);

  glBegin(GL_QUADS);
    glTranslatef(-1.5,0,0);

    glTexCoord2f(0, 0);
    glVertex3f(-1.23, 5.5, 0.1);

    glTexCoord2f(0,1);
    glVertex3f(1.34, 5.5, 0.1);

    glTexCoord2f(1, 1);
    glVertex3f(1.34, -2.3, 0.1);

    glTexCoord2f(1, 0);
    glVertex3f(-1.23, -2.3, 0.1);
   glEnd();

glDisable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, 0);
glPopMatrix();

}

// Pesacki prelaz
void linija(int ind,int p)
{
glDisable(GL_LIGHTING);

    glPushMatrix();

        glColor3f(1,1,1);

        // resetovanje na belu boju posle odredjenog vremena
        if(time(NULL) - vreme[ind] > 0.0001)
        {
            glColor3f(1,1,1);
            vreme[ind]=time(0);
            promasio[ind]=0;
        }

        // zelena boja ako je pogodjena nota
        if(pogodio[ind] || pogodio[ind+4] || pogodio[ind+8] || pogodio[ind+12] || pogodio[ind+16] || pogodio[ind+20] || pogodio[ind+24] || pogodio[ind+28] )
            glColor3f(0,0.9,0);

        // crvena boja ako je promasena
        if(promasio[ind])
            glColor3f(0.9,0,0);

        //kreiranje i pozicioniranje linija
        glTranslatef(1.25 - ((ind*4)+ p)*0.156,4.8,0);
        glScalef(0.156, 0.4, 0.31);
        glutSolidCube(1);

    glPopMatrix();

glEnable(GL_LIGHTING);

}

void prelaz(int ind)
{
    linija(ind,1);
    linija(ind,3);
}

// Bilbord
void bilbord()
{

    glPushMatrix();

    // Okvir
    glPushMatrix();
    glColor3f(0.2, 0.2, 0.2);
    glTranslatef(2.5,1,1);
    glRotatef(40,0,0,1);
    glScalef(1.5, 0.1, 1);

    glutSolidCube(1);
    glPopMatrix();

    // Tabla
    glPushMatrix();
    glColor3f(0.3, 0.3, 0.3);
    glTranslatef(2.49,1,1);
    glRotatef(40,0,0,1);
    glScalef(1.3, 0.2, 0.8);
    glutSolidCube(1);
    glPopMatrix();

    // Stub
    glPushMatrix();
    glColor3f(0.2, 0.2, 0.2);
    glTranslatef(2.5,1,0);
    glScalef(0.1, 0.1, 1.5);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

// Brzinometar (scoreboard)

void brzinometar()
{

glPushMatrix();

// Nogice
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-2.6,-2.4,0);
    glScalef(0.05, 0.05, 1.5);
    glutSolidCube(1);
    glTranslatef(-15,0,0);
    glutSolidCube(1);
    glPopMatrix();

// Tabla
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-3,-2.4,1);
    glScalef(2, 0.05, 0.8);
    glutSolidCube(1);
    glPopMatrix();

glPopMatrix();

}

/*
---------------------------------------
            Teksture
---------------------------------------
*/

 void inicijalizacijaTekstura(void){

    // Iskoriscene funkcije sa sedmog casa

    Image * image;
    glEnable(GL_DEPTH_TEST);

    // Flagovi
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    // Init
    image = image_init(0, 0);
    glGenTextures(4, textures);

    // Pozadina
    image_read(image, "teksture/pozadina.bmp");
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

    // Podloga
    image_read(image, "teksture/hmm.bmp");
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

    // Kolovoz
    image_read(image, "teksture/lane.bmp");
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);


    // Glavni meni
    image_read(image, "teksture/mainMenuFinal.bmp");
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

    // Game over
    image_read(image, "teksture/ss.bmp");
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);


    glBindTexture(GL_TEXTURE_2D, 0);
    image_done(image);
}

/*
---------------------------------------
            Objekti
---------------------------------------
*/



void dobos(double r, double g, double b)
{

glDisable(GL_LIGHTING);

glPushMatrix();

glScalef(0.3,0.3,0.3);

//Koza dobosa
glPushMatrix();
    glColor3f(0.8,0.8,0.8);
    glRotatef(90,1,0,0);
    glTranslatef(0,1.23,0);
    glScalef(0.49,0.001,0.49);
    glutSolidSphere(1,100,100);
glPopMatrix();

//Okvir
glPushMatrix();
    glColor3f(r,g,b);
    glRotatef(90,1,0,0);
    glTranslatef(0,1,0);
    for (double u = 0; u < PI; u += PI / 20) {
        glBegin(GL_TRIANGLE_STRIP);
        for (double v = 0; v <= PI*2 + EPSILON; v += PI / 20) {
        glNormal3f(sin(v)/2, 0, cos(v)/2);
        glVertex3f(sin(v)/2 ,u/20,cos(v)/2);

        glNormal3f(sin(v)/2, 0, cos(v)/2);
        glVertex3f(sin(v)/2 ,u/20+ PI/20,cos(v)/2);
        }
        glEnd();
    }
glPopMatrix();

glPopMatrix();

glEnable(GL_LIGHTING);
}

// Nota

void nota(double traka[],int brz, int indeks, int parametar)
{
    glPushMatrix();

    yKoord[indeks]= -2+ brzine[brz][1]*parr[parametar];
    zKoord[indeks] = 0.4+fabs(sin(2.5*brzine[brz][0]*parr[parametar]));

    glTranslatef(traka[0],yKoord[indeks]-1,zKoord[indeks]);
    glRotatef(-brzine[brz][2]*parr[parametar],0.1,0,0);

    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(traka[1],traka[2],traka[3]);
    glPopMatrix();

    glPopMatrix();

}

void zivoti()
{
    glPushMatrix();

    glTranslatef(2.53,1.5,1.15);
    glRotatef(40,0,0,1);

    // Ukoliko je zivot izgubljen nemoj prikazati odgovarajuci dobos na bilbordu

    for(int i=0;i<5;i++)
    {
        glPushMatrix();
        glPushMatrix();
        glTranslatef(-0.7+i*0.2,0,0);
        glScalef(0.6,0.6,0.6);

        if((brojPromasaja < i+1) && !indZivota[i])
        {
            dobos(0,1/(0.2+i),0);
        }
        else
            indZivota[i]=1;
        glPopMatrix();
        glPopMatrix();
    }

    for(int i=0;i<5;i++)
    {
        glPushMatrix();
        glTranslatef(-0.7+i*0.2,0,-0.4);
        glScalef(0.6,0.6,0.6);

        if((brojPromasaja <= i+5) && !indZivota[i+5])
        {
            dobos(i*0.2,0,0);
        }
        else
            indZivota[i+5]=1;
        glPopMatrix();
    }
    glPopMatrix();
}

