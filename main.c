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
static double param1,param2,param3,param4;
static double parr1,parr2,parr3,parr4;
static double dy1,dz1,dy2,dz2,dy3,dz3,dy4,dz4;
static double bounce1=0;
static double bounce2=0;
static double bounce3=0;
static double bounce4=0;

//static double zelenaNota,crvenaNota,zutaNota;

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
            1, 1000);

}

void dobos(double r, double g, double b)
{
    glPushMatrix();

glScalef(0.5,0.5,0.5);

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
    
void prvanota()
{
    glPushMatrix();
    
    param1=1.3*parr1;
    bounce1=fabs(sin(2.5*param1));
    
    dy1= -2+ parr1;
    dz1 = 0.4+bounce1;

    glTranslatef(0.9,dy1-1,dz1);
    glRotatef(-50*parr1*2.3,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(0.3,0.9,0.3);
    glPopMatrix();
    glPopMatrix();

}
void druganota()
{
    glPushMatrix();
    
    param2=1.95*parr2;
    bounce2=fabs(sin(2.5*param2));
    
    dy2= -2+ 1.5*parr2;
    dz2 = 0.4+bounce2;
    
    glTranslatef(0.3,dy2-1,dz2);
    glRotatef(-100*parr2,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(0.9,0.3,0.3);
    glPopMatrix();
    glPopMatrix();
}

void trecanota()
{
    glPushMatrix();
    
    param3=2.6*parr3;
    bounce3=fabs(sin(2.5*param3));
    
    dy3= -2+ 2*parr3;
    dz3 = 0.4+bounce3;
    
    glTranslatef(-0.3,dy3-1,dz3);
    glRotatef(-130*parr3,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos(1,0.8,0);
    glPopMatrix();
    glPopMatrix();
}


void cetvrtanota()
{
     glPushMatrix();
    
    param4=3.6*parr4;
    bounce4=fabs(sin(2.5*param4));
    
    dy4= -2+ 2.5*parr4;
    dz4 = 0.4+bounce4;
    
    glTranslatef(-0.9,dy4-1,dz4);
    glRotatef(-170*parr4,0.1,0,0);
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
            -3, 6.5 ,3,
            0, 0, 0,
            0, 0, 1
        );
/*
//ose    
        glBegin(GL_LINES);

        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(0,0,10);
        glEnd();
*/
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
        glVertex3f(-10,5.3,1.5);
        glVertex3f(10,5.3,1.5);
    glEnd();
    
    //donja
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(-10,5.58,1.5);
        glVertex3f(10,5.58,1.5);
    glEnd();

    prvanota();
    druganota();
    trecanota();
    cetvrtanota();
    
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
        parr3=0.0001;
        parr4=0.0001;
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
    parr1 +=0.1;
    parr2 +=0.1;
    parr3 +=0.1;
    parr4 +=0.1;
    
    if (dy1>6.5)
    {
        parr1=0.0001;
        
    }  
    if (dy2>6.5)
    {
        parr2=0.0001;
       
    }  
    if (dy3>6.5)
    {
        parr3=0.0001;
        
    }  
    if (dy4>6.5)
    {
        parr4=0.0001;
       
    } 
    
    
    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}
