#include <stdio.h>
//#include <windows.h>
#include <GL/glut.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "okruzenje.h"
#include "image.h"
#include "main.h"

#define PI 3.1415926535
#define EPSILON 0.01


/*
---------------------------------------
            Display
---------------------------------------
*/


void glavniMeni()
{


glDisable(GL_LIGHTING);


glPushMatrix();
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, textures[3]);

  glBegin(GL_QUADS);

    glTexCoord2f(1, 0);
    glVertex3f(3,14.3, 1);

    glTexCoord2f(1,1);
    glVertex3f(-3, 14.3, 1);

    glTexCoord2f(0, 1);
    glVertex3f(-3, 5.62, 1);

    glTexCoord2f(0, 0);
    glVertex3f(3, 5.62 , 1);
   glEnd();

glDisable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, 0);
glPopMatrix();

glPushMatrix();
glRotatef(-0.15,0,1,0);

// Semafor - biranje tezine

// Crvena - Hard - 3
glPushMatrix();
glTranslatef(1.65,8.52,2);
if(izabranaBrzina==2)
    glColor3f(0.9,0,0);
else
    glColor3f(0.2,0.2,0.2);
glutSolidSphere(0.197,32,32);

glPopMatrix();

// Zuta - Medium - 2
glPushMatrix();
glTranslatef(1.65,8.06,2);
if(izabranaBrzina==1)
    glColor3f(0.9,0.9,0);
else
    glColor3f(0.2,0.2,0.2);
glutSolidSphere(0.197,32,32);
glPopMatrix();

// Zelena - Easy - 1
glPushMatrix();
glTranslatef(1.65,7.6,2);
if(!izabranaBrzina)
    glColor3f(0,0.9,0);
else
    glColor3f(0.2,0.2,0.2);
glutSolidSphere(0.197,32,32);
glPopMatrix();

glPopMatrix();

glEnable(GL_LIGHTING);

}


void prikaziRezultat()
{

  // Projekcija
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0,window_width,0,window_height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

  // Ispis
    glPushMatrix();

        glPushMatrix();
        char bodovi[10];
        glColor3f(0.9,0.25,0);
        glRasterPos2f(445,510);

        sprintf(bodovi, "%d", rezultat);
        unsigned len = strlen(bodovi);
        for (int i=0; i<len; i++)
          glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, bodovi[i]);
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
    glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopMatrix();
}

void gameOver()
{

// Ukoliko je igrac ostao bez zivota - prikazi Game over na bilbordu
if(brojPromasaja>9)
{

glPushMatrix();
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, textures[4]);

  glBegin(GL_QUADS);

    glTexCoord2f(0, 1);
    glVertex3f(2.4, 2.3, 1.2);

    glTexCoord2f(0,0);
    glVertex3f(1.65, 1.65, 1.2);

    glTexCoord2f(1, 0);
    glVertex3f(1.65, 1.63, 1.82);

    glTexCoord2f(1, 1);
    glVertex3f(2.4, 2.3, 1.82);
   glEnd();

glDisable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, 0);
glPopMatrix();
}
}

/*
---------------------------------------
            Utilities
---------------------------------------
*/


void reinicijalizacija()
{
        srand(time(NULL));
        indd[0]=1;
        for(int i=1;i<8;i++)
            indd[i]=0;
        for(int i=0;i<10;i++)
            indZivota[i]=0;
        for(int i=0;i<8;i++){
            parr[i]=0.0001;
            }
        for(int i=0;i<32;i++){
            pogodio[i]=0;
            lock[i]=0;
            gotova[i]=0;
            yKoord[i]=0;
            zKoord[i]=0;}
        for(int i=0;i<4;i++)
            promasio[i]=0;
        brojPromasaja=0;
        prviTalas=0;
        pocetakIgre=0;
        rezultat=0;
        kamera=1;
    }


//  Randomizacija postojanja nota

int verovatnoca()
{
    if(!prviTalas)
    {
        prviTalas=1;
        return izabranaBrzina;
    }
    int broj= rand() % 100;
    if (broj<75)
        return -1;
    return izabranaBrzina;
}

// U zavisnosti od polozaja dobosa - registruj pogodak/promasaj i dodaj bodove/oduzmi zivot
void reaguj(int i)
{
    int znak =0;
    for(int j=0;j<32;j+=4)
    {
        if((yKoord[i+j]>5.5 && yKoord[i+j]<=6.3) )
        {
            pogodio[i+j] = 1;
            znak=1;
            rezultat+=50;
            break;
        }
    }
    if(!znak)
        {
            promasio[i]=1;
            brojPromasaja++;
        }
        vreme[i]=time(0);
}



void iscrtajTalasNota()
{

for(int i=0;i<8;i++)
{
// U koliko je odgovarajuci talas aktivan
if(indd[i])
{
    for(int j=4*i;j<4*i+4;j++)
    {
        // Po potrebi generisi brzinu/postojanje njegovih dobosa
        if(!gotova[j])
        {
            brzina[j]=verovatnoca();
            //brzina[j]=0;
            gotova[j]=1;
            //printf("%d ",brzina1);
        }

        // Iscrtaj dobos ili ga privremeno ukloni iz vidnog polja
        if(brzina[j] != -1)
            nota(trake[j%4],brzina[j],j,i);
        else
            yKoord[j]=6.9;
    }
}
}

}


/*
---------------------------------------
            On timer funkcije
---------------------------------------
*/


void mehanizamTalasa()
{

//Za svaki talas
for(int i=0;i<8;i++)
{

// Ukoliko je svaki dobos zavrsio sa prikazom
if (yKoord[4*i]>6.5 && yKoord[4*i+1]>6.5 && yKoord[4*i+2]>6.5 && yKoord[4*i+3]>6.5)
    {
    // Postaviti indikator talasa na neaktivan
    indd[i]=0;

    // Restartuj parametre dobosa
    for(int j=4*i;j<4*i+4;j++)
    {
        yKoord[j]= -2;
        gotova[j]=0;
        lock[j]=0;
        pogodio[j]=0;
    }

    }
// Ukoliko je svaki dobos presao odgovarajucu distancu i naredni talas nije aktivan - aktiviraj naredni talas
if (yKoord[4*i]> 0.1 && yKoord[4*i+1]> 0.1 && yKoord[4*i+2]> 0.1 && yKoord[4*i+3]> 0.1 && !indd[(i+1)%8] )
    {
        indd[(i+1)%8]=1;
        parr[(i+1)%8]=0.0001;
    }

}

}



void promaseneNote()
{

int promasajLock=0;

 for(int i=0;i<32;i++)
    {
       // Ukoliko igrac uopste nije reagovao na notu - zabelezi promasaj
       if(!lock[i] && !pogodio[i] && brzina[i] != -1  && yKoord[i]>6.3 && yKoord[i]<6.5 )
            {
                if(!promasajLock)
                {
                    brojPromasaja++;
                    promasajLock=1;
                }
                promasio[i%4]=1;
                vreme[i%4]=time(0);
                lock[i]=1;
            }
    }

}

void proveraKrajaIgre()
{

if(brojPromasaja >9)
{
    animation_ongoing = 0;
    printf("Vas rezultat je = %u \n",rezultat);
    if(rezultat>highScore)
        highScore=rezultat;
    printf("Trenutni High Score = %u \n",highScore);
    printf("-----------------------------\n");
}
}
