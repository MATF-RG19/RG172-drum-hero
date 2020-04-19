#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 20

//parametri
static float animation_ongoing;
static float param=0.0001;
static float zelenaNota,crvenaNota,zutaNota;

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
}

static void on_display(void)
{
//ciscenje ekrana
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

//pogled
    glViewport(0, 0, window_width, window_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
            80,
            window_width/(float)window_height,
            1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            0, 2.75, 2.5,
            0, 0, 0,
            0, 0, 1
        );

    //staza
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5 );
    glScalef(2, 4.9, 0.3);
    glutSolidCube(1);
    glPopMatrix();
    
    //trava
    glPushMatrix();
    glColor3f(0, 0.3, 0);
    glScalef(10, 4.9, 0.29);
    glutSolidCube(1);
    glPopMatrix();

    //pozadina
    glPushMatrix();
    glColor3f(0, 0, 0.8);
    
    glTranslatef(0,-2.5,0);
    glScalef(10, 0.1, 10);
    glutSolidCube(1);
    glPopMatrix();
    
    //zelena nota
    zelenaNota=param;
    glTranslatef(0,zelenaNota,0);
    glPushMatrix();
    glColor3f(0, 0.9, 0);
    glTranslatef(0.7,-2,0.5);
    glutSolidSphere(0.2,10,10);
    glPopMatrix();
    
    //crvena nota
    crvenaNota=param/2;
    glTranslatef(0,crvenaNota,0);
    glPushMatrix();
    glColor3f(0.9, 0, 0);
    glTranslatef(0,-2,0.5);
    glutSolidSphere(0.2,10,10);
    glPopMatrix();
    
    //zuta nota
    zutaNota=param/3;
    glTranslatef(0,zutaNota,0);
    glPushMatrix();
    glColor3f(1, 0.8, 0);
    glTranslatef(-0.7,-2,0.5);
    glutSolidSphere(0.2,10,10);
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
