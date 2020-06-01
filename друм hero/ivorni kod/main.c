#include <stdio.h>
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 20
#define PI 3.1415926535
#define EPSILON 0.01

#include "image.h"
#include "okruzenje.h"
#include "funkcionalnosti.h"


// Parametri igre

double animation_ongoing;
double brzine[4][3] ={{0.8,0.7,35},{1.3,1,50},{1.95,1.5,100},{2.6,2,130},{3.6,2.5,170}}; // parametri rotacije i translacije razlicitih brzina kotrljanja
double trake[4][4]  ={{0.9,0.3,0.9,0.3},{0.3,0.9,0.3,0.3},{-0.3,1,0.8,0},{-0.9,0.3,0.3,0.9}}; // parametri polozaja i boje 4 razlita dobosa

// Atributi nota

int indd[8]={1,0,0,0,0,0,0,0}; // indikatori da li je da li je neki talas dobosa aktivan
double parr[8]={0.0001,0.000,0.000,0.000,0.000,0.000,0.000,0.000}; // paramatri talasa dobosa
double yKoord[32],zKoord[32]; // trenutna pozicija svakog dobosa
int gotova[32]; // indikator da li je gotovo generisanje dobosa za tekuci talas
int brzina[32]; // odabrana brzina za svaki dobos
int pogodio[32]; // indikator da li je nota pogodjena
int promasio[4]; //  indikator da li je u nekoj traci promasena nota
int lock[32]; // lock za pokretanje greske ako se dobos iskotrlja bez bilo kakve reakcije igraca
time_t vreme[32]; //vreme prikaza pogodjene ili promasene note na pesackom prelazu

// Atributi igre
int kamera; // 0-glavni meni, 1-igra
int prviTalas; //generisanje prvog talasa kako bi mogli i ostali
int izabranaBrzina;
unsigned pocetakIgre;
unsigned rezultat =0;
unsigned highScore = 0;
unsigned brojPromasaja;
int indZivota[10]; // indikator za svaki od 10 zivota

// Teksture i osvetljenje
GLuint textures[5];
static GLfloat light_position[] = { 0, -5, 5, 1};
static GLfloat light_diffuse[] = { 1,0.2,0.1,1};

// Dimenzije prozora
int window_width, window_height;

// Callback funkcije init
static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int value);


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(600, 800);
    glutInitWindowPosition(540, 100);
    glutCreateWindow(argv[0]);

    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    srand(time(NULL));
    inicijalizacijaTekstura();
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

static void on_reshape(int width, int height)
{
    window_width = width;
    window_height = height;

    // Pogled
    glViewport(0, 0, window_width, window_height);
    glutReshapeWindow( 600, 800);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
            80,
            window_width/(double)window_height,
            0.1, 100000);
}

static void on_display(void)
{
//Ciscenje ekrana
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

// Igra ili Glavni meni

if(kamera){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            0, 6.2 ,4,
            0, 0, 0,
            0, 0, 1
        );

    glDisable(GL_LIGHTING);
    prikaziRezultat();
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    kolovoz();
    for(int i =0; i<4; i++)
        prelaz(i);
    podloga();
    pozadina();

    bilbord();
    zivoti();
    brzinometar();

    iscrtajTalasNota();

    gameOver();

}
else
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            0, 10 ,5.7,
            0, 10.0001, 0,
            0, 0, 1
        );
    glavniMeni();
}

    glutSwapBuffers();
}


static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;

    // Backspace za povratak u glavni meni
    case 8 :
        if(brojPromasaja>9)
        {
         kamera=0;
         brojPromasaja=0;
        }
        glutPostRedisplay();
        break;

    // Enter za (ponovno) pokretanje
    case 13 :

        if (!animation_ongoing && !pocetakIgre) {
            pocetakIgre=1;
            glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            animation_ongoing = 1;
        }
        else
            break;
        reinicijalizacija();

        break;

    // Sviranje
    case 'a':
    case 'A':
         reaguj(0);
         break;
    case 's':
    case 'S':
        reaguj(1);
         break;
    case 'd':
    case 'D':
        reaguj(2);
        break;
    case 'f':
    case 'F':
        reaguj(3);
         break;
    // Biranje tezine
    case 49:
        if(!kamera)
            izabranaBrzina=0;
        glutPostRedisplay();
        break;
    case 50:
        if(!kamera)
            izabranaBrzina=1;
        glutPostRedisplay();
        break;
    case 51:
        if(!kamera)
            izabranaBrzina=2;
        glutPostRedisplay();
        break;

    }
}

static void on_timer(int value)
{

    if (value != TIMER_ID)

        return;

    for(int i=0;i<8;i++)
        if(indd[i])
            parr[i] +=0.1;

    mehanizamTalasa();
    promaseneNote();
    proveraKrajaIgre();

glutPostRedisplay();

if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}
