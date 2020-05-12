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

//parametri
static double animation_ongoing;
static double parr[2]={0.0001,0.000};
static double yKoord[8],zKoord[8];

static int indd1=1;
static int indd2=0;

static const double brzine[4][3] ={{1.3,1,50},{1.95,1.5,100},{2.6,2,130},{3.6,2.5,170}};
static int gotova1,gotova2,gotova3,gotova4,gotova11,gotova21,gotova31,gotova41;
static int brzina1,brzina2,brzina3,brzina4,brzina11,brzina21,brzina31,brzina41;

//dimenzije prozora
static int window_width, window_height;

//callback funkcije init
static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int value);


int main(int argc, char **argv)
{
    // GLUT inicijalizacija
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // Podesavanje prozora
    glutInitWindowSize(600, 800);
    glutInitWindowPosition(540, 100);
    glutCreateWindow(argv[0]);

    // Callback funkcije
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    //parametri init
    animation_ongoing=0;
    srand(time(NULL));
    // OpenGL inicijalizacija
    glClearColor(0.1, 0.1, 0.1, 0);
    glEnable(GL_DEPTH_TEST);


    // Ulazak u glavnu petlj
    glutMainLoop();

    return 0;
}

static void on_reshape(int width, int height)
{
    /* Pamte se sirina i visina prozora. */
    window_width = width;
    window_height = height;

//pogled
    glViewport(0, 0, window_width, window_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
            80,
            window_width/(double)window_height,
            0.1, 100000);

}

void dobos(double r, double g, double b)
{
glPushMatrix();

glScalef(0.35,0.35,0.35);

glPushMatrix();
    glColor3f(1,0.99,0.99);
    glRotatef(90,1,0,0);
    glTranslatef(0,1.23,0);
    glScalef(0.49,0.001,0.49);
    glutSolidSphere(1,100,100);

glPopMatrix();


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

}

void prvanota(int brz, int indeks, int parametar)
{
    glPushMatrix();

    yKoord[indeks]= -2+ brzine[brz][1]*parr[parametar];
    zKoord[indeks] = 0.4+fabs(sin(2.5*brzine[brz][0]*parr[parametar]));

    glTranslatef(0.9,yKoord[indeks]-1,zKoord[indeks]);
    glRotatef(-brzine[brz][2]*parr[parametar],0.1,0,0);

    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(0.3,0.9,0.3);
    glPopMatrix();

    glPopMatrix();

}

void druganota(int brz, int indeks, int parametar)
{
    glPushMatrix();

    yKoord[indeks]= -2+ brzine[brz][1]*parr[parametar];
    zKoord[indeks] = 0.4+fabs(sin(2.5*brzine[brz][0]*parr[parametar]));

    glTranslatef(0.3,yKoord[indeks]-1,zKoord[indeks]);
    glRotatef(-brzine[brz][2]*parr[parametar],0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(0.9,0.3,0.3);
    glPopMatrix();
    glPopMatrix();
}

void trecanota(int brz, int indeks, int parametar)
{
    glPushMatrix();

    yKoord[indeks]= -2+ brzine[brz][1]*parr[parametar];
    zKoord[indeks] = 0.4+fabs(sin(2.5*brzine[brz][0]*parr[parametar]));

    glTranslatef(-0.3,yKoord[indeks]-1,zKoord[indeks]);
    glRotatef(-brzine[brz][2]*parr[parametar],0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(1,0.8,0);
    glPopMatrix();
    glPopMatrix();
}

void cetvrtanota(int brz, int indeks, int parametar)
{
    glPushMatrix();

    yKoord[indeks]= -2+ brzine[brz][1]*parr[parametar];
    zKoord[indeks] = 0.4+fabs(sin(2.5*brzine[brz][0]*parr[parametar]));

    glTranslatef(-0.9,yKoord[indeks]-1,zKoord[indeks]);
    glRotatef(-brzine[brz][2]*parr[parametar],0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(0.3,0.3,0.9);
    glPopMatrix();
    glPopMatrix();
}

int verovatnoca()
{
    //srand(time(NULL));

    int broj= rand() % 100;
    if(broj<25)
        return 0;
    if(broj<50)
        return 1;
    if(broj<75)
        return 2;
    else
        return 3;


}

static void on_display(void)
{
//ciscenje ekrana
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

   /*     glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);*/

//kamera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            0, 5.9 ,5,
            0, 0, 0,
            0, 0, 1
        );

//ose
        glBegin(GL_LINES);

        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(0,0,10);
        glEnd();
//staza
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5 );
    glScalef(2.5, 10, 0.3);
    glutSolidCube(1);
    glPopMatrix();

//trava
    glPushMatrix();
    glColor3f(0, 0.3, 0);
    glScalef(100, 500, 0.29);
    glutSolidCube(1);
    glPopMatrix();

//pozadina
    glPushMatrix();
    glColor3f(0, 0, 0.8);

    glTranslatef(0,-2.5,0);
    glScalef(100, 0.1, 500);
    glutSolidCube(1);
    glPopMatrix();

//pesacki

    //gornja
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(-10,4.6,0.3);
        glVertex3f(10,4.6,0.3);
    glEnd();

    //donja
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(-10,5,0.3);
        glVertex3f(10,5,0.3);
    glEnd();
//  prvi talas
if(indd1)
{

    if(!gotova1)
    {
        brzina1=verovatnoca();
        gotova1=1;
        //printf("%d ",brzina1);
    }
    prvanota(brzina1,0,0);


    if(!gotova2)
    {
        brzina2=verovatnoca();
        gotova2=1;
        //printf("%d ",brzina2);
    }
    druganota(brzina2,1,0);

    if(!gotova3)
    {
        brzina3=verovatnoca();
        gotova3=1;
        //printf("%d ",brzina3);,0
    }
    trecanota(brzina3,2,0);

    if(!gotova4)
    {
        brzina4=verovatnoca();
        //printf("%d ",brzina4);
        gotova4=1;
    }
    cetvrtanota(brzina4,3,0);
}
//drugi talas

if(indd2)
    {

        if(!gotova11)
        {
            brzina11=verovatnoca();
            gotova11=1;
            //printf("%d ",brzina11);
        }
        prvanota(brzina11,4,1);


        if(!gotova21)
        {
            brzina21=verovatnoca();
            gotova21=1;
            //printf("%d ",brzina21);
        }
        druganota(brzina21,5,1);

        if(!gotova31)
        {
            brzina31=verovatnoca();
            gotova31=1;
            //printf("%d ",brzina31);
        }
        trecanota(brzina31,6,1);

        if(!gotova41)
        {
            brzina41=verovatnoca();
            //printf("%d ",brzina41);
            gotova41=1;
        }
        cetvrtanota(brzina41,7,1);
    }

    glutSwapBuffers();
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;

    case 'g':
    case 'G':

        if (!animation_ongoing) {
            glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            animation_ongoing = 1;
        }
        break;

    case 's':
    case 'S':

        animation_ongoing = 0;
        break;

    case 'r':
    case 'R':

        animation_ongoing = 0;
        parr[0]=0.0001;
        parr[1]=0.0001;
        indd1=1;
        indd2=0;
        srand(time(NULL));
        glutPostRedisplay();
        break;

    }
}

static void on_timer(int value)
{

    if (value != TIMER_ID)
        return;

    if(indd1)
        parr[0] +=0.1;
    if(indd2)
        parr[1] +=0.1;



if (yKoord[0]>5.8 && yKoord[1]>5.8 && yKoord[2]>5.8 && yKoord[3]>5.8 && indd1)
    {
        parr[0]=0.0001;
        indd1=0;
        gotova1=0;
        gotova2=0;
        gotova3=0;
        gotova4=0;
    }
if (yKoord[4]>3 && yKoord[5]>3 && yKoord[6]>3 && yKoord[7]>3 && !indd1)
    {
        //parr1=0.0001;
        indd1=1;

    }
if (yKoord[4]>5.8 && yKoord[5]>5.8 && yKoord[6]>5.8 && yKoord[7]>5.8 && indd2)
    {
        indd2=0;
        gotova11=0;
        gotova21=0;
        gotova31=0;
        gotova41=0;
    }
if (yKoord[0]>3 && yKoord[1]>3 && yKoord[2]>3 && yKoord[3]>3 && !indd2)
    {
        parr[1]=0.0001;
        indd2=1;

    }

    /*printf(" %lf %lf\n",parr1,parr2);
    printf("%lf %lf\n",dy1,dy21);
    printf("%d %d\n\n",indd1,indd2);*/


    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}
