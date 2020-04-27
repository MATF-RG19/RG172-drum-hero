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
static float animation_ongoing;
static float param=0.0001;
static float bounce1=0;
static float bounce2=0;
static float bounce3=0;
static float bounce4=0;
//static float zelenaNota,crvenaNota,zutaNota;

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
            window_width/(float)window_height,
            1, 1000);

}

void dobos2()
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
    
    glColor3f(1,0.2,0.3);
    glRotatef(90,1,0,0);
    glTranslatef(0,1,0);
    for (float u = 0; u < PI; u += PI / 20) {
        glBegin(GL_TRIANGLE_STRIP);
        for (float v = 0; v <= PI*2 + EPSILON; v += PI / 20) {
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
void dobos1()
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
    
    glColor3f(0.2,0.8,0.3);
    glRotatef(90,1,0,0);
    glTranslatef(0,1,0);
    for (float u = 0; u < PI; u += PI / 20) {
        glBegin(GL_TRIANGLE_STRIP);
        for (float v = 0; v <= PI*2 + EPSILON; v += PI / 20) {
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
void dobos3()
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
    
    glColor3f(1,0.5,0);
    glRotatef(90,1,0,0);
    glTranslatef(0,1,0);
    for (float u = 0; u < PI; u += PI / 20) {
        glBegin(GL_TRIANGLE_STRIP);
        for (float v = 0; v <= PI*2 + EPSILON; v += PI / 20) {
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
void dobos4()
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
    
    glColor3f(0.3,0.2,1);
    glRotatef(90,1,0,0);
    glTranslatef(0,1,0);
    for (float u = 0; u < PI; u += PI / 20) {
        glBegin(GL_TRIANGLE_STRIP);
        for (float v = 0; v <= PI*2 + EPSILON; v += PI / 20) {
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

static void on_display(void)
{
//ciscenje ekrana
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
 
//kamera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            0, 2.75, 2.5,
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
    glScalef(2.5, 4.9, 0.3);
    glutSolidCube(1);
    glPopMatrix();
    
//trava
    glPushMatrix();
    glColor3f(0, 0.3, 0);
    glScalef(20, 4.9, 0.29);
    glutSolidCube(1);
    glPopMatrix();

//pozadina
    glPushMatrix();
    glColor3f(0, 0, 0.8);
    
    glTranslatef(0,-2.5,0);
    glScalef(20, 0.1, 10);
    glutSolidCube(1);
    glPopMatrix();

//DOBOSI
    //prva nota
    
    glPushMatrix();
    
    bounce1=fabs(sin(2*param));
    glTranslatef(0.9,-2+param,0.4+bounce1);
    glRotatef(-100*param,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    glColor3f(0.1, 0.8, 0.1);
    dobos1();
    glPopMatrix();
    glPopMatrix();
    //druga
    glPushMatrix();
    
    bounce2=fabs(sin(param));
    glTranslatef(0.3,-2+param,0.4+bounce2);
    glRotatef(-100*param,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    dobos2();
    glPopMatrix();
    glPopMatrix();
    //treca
    glPushMatrix();
    
    bounce3=fabs(cos(2*param));
    glTranslatef(-0.3,-2+param,0.4+bounce3);
    glRotatef(-100*param,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    glColor3f(1, 0.5, 0);
    dobos3();
    glPopMatrix();
    glPopMatrix();
    //cetvrta
    glPushMatrix();
    
    bounce4=fabs(cos(param));
    glTranslatef(-0.9,-2+param,0.4+bounce1);
    glRotatef(-100*param,0.1,0,0);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    glColor3f(0.1, 0.1, 0.8);
    dobos4();
    glPopMatrix();
    glPopMatrix();
    
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
        param=0.0001;
        glutPostRedisplay();
        break;
        
    }
}

static void on_timer(int value)
{
    
    if (value != TIMER_ID)
        return;
    

    param += 0.1;
    
    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}
