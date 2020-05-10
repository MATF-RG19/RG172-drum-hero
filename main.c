#include <stdio.h>
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
static double param=0.0001;
static double param1,param11,param21,param2,param31,param3,param41,param4;
static double parr1,parr2;
static double dy1,dz1,dy2,dz2,dy3,dz3,dy4,dz4;
static double dy11,dz11,dy21,dz21,dy31,dz31,dy41,dz41;
static double bounce1,bounce11,bounce2,bounce21,bounce3,bounce31,bounce4,bounce41;

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
    glutInitWindowSize(800, 800);
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
    
void prvanota(int brz)
{
    glPushMatrix();
    
    param1=brzine[brz][0]*parr1;
    bounce1=fabs(sin(2.5*param1));
    
    dy1= -2+ brzine[brz][1]*parr1;
    dz1 = 0.4+bounce1;

    glTranslatef(0.9,dy1-1,dz1);
    glRotatef(-brzine[brz][2]*parr1,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(0.3,0.9,0.3);
    glPopMatrix();
    glPopMatrix();

}
void druganota(int brz)
{
    glPushMatrix();
    
    param2=brzine[brz][0]*parr1;
    bounce2=fabs(sin(2.5*param2));
    
    dy2= -2+ brzine[brz][1]*parr1;
    dz2 = 0.4+bounce2;
    
    glTranslatef(0.3,dy2-1,dz2);
    glRotatef(-brzine[brz][2]*parr1,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(0.9,0.3,0.3);
    glPopMatrix();
    glPopMatrix();
}

void trecanota(int brz)
{
    glPushMatrix();
    
    param3=brzine[brz][0]*parr1;
    bounce3=fabs(sin(2.5*param3));
    
    dy3= -2+ brzine[brz][1]*parr1;
    dz3 = 0.4+bounce3;
    
    glTranslatef(-0.3,dy3-1,dz3);
    glRotatef(-brzine[brz][2]*parr1,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(1,0.8,0);
    glPopMatrix();
    glPopMatrix();
}


void cetvrtanota(int brz)
{
    glPushMatrix();
    
    param4=brzine[brz][0]*parr1;
    bounce4=fabs(sin(2.5*param4));
    
    dy4= -2+ brzine[brz][1]*parr1;
    dz4 = 0.4+bounce4;
    
    glTranslatef(-0.9,dy4-1,dz4);
    glRotatef(-brzine[brz][2]*parr1,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(0.3,0.3,0.9);
    glPopMatrix();
    glPopMatrix();
}
//drugi talas

void prvanota2(int brz)
{
    glPushMatrix();
    
    param11=brzine[brz][0]*parr2;
    bounce11=fabs(sin(2.5*param11));
    
    dy11= -2+ brzine[brz][1]*parr2;
    dz11 = 0.4+bounce11;

    glTranslatef(0.9,dy11-1,dz11);
    glRotatef(-brzine[brz][2]*parr2,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(0.3,0.9,0.3);
    glPopMatrix();
    glPopMatrix();

}
void druganota2(int brz)
{
    glPushMatrix();
    
    param21=brzine[brz][0]*parr2;
    bounce21=fabs(sin(2.5*param21));
    
    dy21= -2+ brzine[brz][1]*parr2;
    dz21 = 0.4+bounce21;
    
    glTranslatef(0.3,dy21-1,dz21);
    glRotatef(-brzine[brz][2]*parr2,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(0.9,0.3,0.3);
    glPopMatrix();
    glPopMatrix();
}

void trecanota2(int brz)
{
    glPushMatrix();
    
    param31=brzine[brz][0]*parr2;
    bounce31=fabs(sin(2.5*param31));
    
    dy31= -2+ brzine[brz][1]*parr2;
    dz31 = 0.4+bounce31;
    
    glTranslatef(-0.3,dy31-1,dz31);
    glRotatef(-brzine[brz][2]*parr2,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(1,0.8,0);
    glPopMatrix();
    glPopMatrix();
}


void cetvrtanota2(int brz)
{
    glPushMatrix();
    
    param41=brzine[brz][0]*parr2;
    bounce41=fabs(sin(2.5*param41));
    
    dy41= -2+ brzine[brz][1]*parr2;
    dz41 = 0.4+bounce41;
    
    glTranslatef(-0.9,dy41-1,dz41);
    glRotatef(-brzine[brz][2]*parr2,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(0.3,0.3,0.9);
    glPopMatrix();
    glPopMatrix();
}
static void on_display(void)
{
//ciscenje ekrana
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
 
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
        brzina1=rand()%4;
        gotova1=1;
        //printf("%d ",brzina1);
    }
    prvanota(brzina1);
    
      
    if(!gotova2)
    {
        brzina2=rand()%4;
        gotova2=1;
        //printf("%d ",brzina2);
    }
    druganota(brzina2);
    
    if(!gotova3)
    {
        brzina3=rand()%4;
        gotova3=1;
        //printf("%d ",brzina3);
    }
    trecanota(brzina3);
    
    if(!gotova4)
    {
        brzina4=rand()%4;
        //printf("%d ",brzina4);
        gotova4=1;
    }
    cetvrtanota(brzina4);
}
//drugi talas

if(indd2)
    {
        
        if(!gotova11)
        {
            brzina11=rand()%4;
            gotova11=1;
            //printf("%d ",brzina11);
        }
        prvanota2(brzina11);
        
        
        if(!gotova21)
        {
            brzina21=rand()%4;
            gotova21=1;
            //printf("%d ",brzina21);
        }
        druganota2(brzina21);
        
        if(!gotova31)
        {
            brzina31=rand()%4;
            gotova31=1;
            //printf("%d ",brzina31);
        }
        trecanota2(brzina31);
        
        if(!gotova41)
        {
            brzina41=rand()%4;
            //printf("%d ",brzina41);
            gotova41=1;
        }
        cetvrtanota2(brzina41);
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
    
    for(int i=0;i<2;i++)
    {
        animation_ongoing = 0;
        param=0.0001;
        parr1=0.0001;
        parr2=0.0001;
        indd1=1;
        indd2=0;
        glutPostRedisplay();
        break;
    }
    }
}

static void on_timer(int value)
{
    
    if (value != TIMER_ID)
        return;
    

    param += 0.1;
    if(indd1)
        parr1 +=0.1;
    if(indd2)
        parr2 +=0.1;
    
    
if (dy1>3.5 && dy2>3.5 && dy3>3.5 && dy4>3.5 && !indd2)
    {
        indd2=1;
    }
if (dy11>3.5 && dy21>3.5 && dy31>3.5 && dy41>3.5 && !indd1)
    {
        indd1=1;
    }
if (dy1>5.8 && dy2>5.8 && dy3>5.8 && dy4>5.8)
    {
        parr1=0.0001;
        gotova1=0;
        gotova2=0;
        gotova3=0;
        gotova4=0;
    }
if (dy11>5.8 && dy21>5.8 && dy31>5.8 && dy41>5.8)
    {
        parr2=0.0001;
        gotova11=0;
        gotova21=0;
        gotova31=0;
        gotova41=0;
    }

    //printf("%lf %lf %lf\n", param,parr1,parr2);
    
    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}
