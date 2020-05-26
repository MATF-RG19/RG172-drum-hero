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
static double parametarZivota= 0.0001;
static double parr[8]={0.0001,0.000,0.000,0.000,0.000,0.000,0.000,0.000};
static double yKoord[32],zKoord[32];

static int indd[8]={1,0,0,0,0,0,0,0};
static double brzine[4][3] ={{0.8,0.7,35},{1.3,1,50},{1.95,1.5,100},{2.6,2,130},{3.6,2.5,170}}; //parametri rotacije i translacije razlicitih brzina
static double trake[4][4]  ={{0.9,0.3,0.9,0.3},{0.3,0.9,0.3,0.3},{-0.3,1,0.8,0},{-0.9,0.3,0.3,0.9}}; //polozaj+boja(rgb)
static int gotova[32];
static int brzina[32];

static int indZivota[10];

static int pogodio[32];
static int promasio[4];
static int lock[32];
static int lock2[8];

static int prviTalas;
static unsigned pocetakIgre;

static unsigned rezultat =0;

static time_t vreme[32];
static time_t promenaTezine;

static int brojPromasaja;

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

    brzina[0]=1;
    promenaTezine = time(0);
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
// DOBOS

void dobos(double r, double g, double b)
{
glPushMatrix();

glScalef(0.3,0.3,0.3);

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
//NOTA

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

// VEROVATNOCA -- (ubaciti jos brzina i jedan talas)

int verovatnoca()
{
    //srand(time(NULL));
    if(!prviTalas)
    {
        prviTalas=1;
        return 1;
    }
    int broj= rand() % 100;
    if (broj<75)
        return -1;
    //broj= rand() % 100;
    return 1;
    /*if (broj<35)
        return 0;
    if(broj<70)
        return 1;
    if(broj<90)
        return 2;
    else
        return 3;*/
    /*else
        return 3;*/


}
void linija(int ind,int p)
{
    glPushMatrix();

        glColor3f(1,1,1);


        if(time(NULL)*1000 - vreme[ind]*1000 > 1)
        {
            glColor3f(1,1,1);
            vreme[ind]=time(0);
            promasio[ind]=0;
        }

        if(pogodio[ind] || pogodio[ind+4] || pogodio[ind+8] || pogodio[ind+12] || pogodio[ind+16] || pogodio[ind+20] || pogodio[ind+24] || pogodio[ind+28] )
            glColor3f(0,0.9,0);

        if(promasio[ind])
            glColor3f(0.9,0,0);

        glTranslatef(1.25 - ((ind*4)+ p)*0.156,4.8,0);
        glScalef(0.156, 0.4, 0.31);
        glutSolidCube(1);


    glPopMatrix();

}

void prelaz(int ind)
{
    linija(ind,1);
    linija(ind,3);
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
            0, 6.2 ,4,
            0, 0, 0,
            0, 0, 1
        );

//ose


//staza
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5 );
    glScalef(2.5, 10, 0.3);
    glutSolidCube(1);
    glPopMatrix();
//PRELAZ

for(int i =0; i<4; i++)
    prelaz(i);


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



//bilbord

    glPushMatrix();

    //tabla
    glPushMatrix();
    glColor3f(0.4, 0.4, 0.4);


    glTranslatef(2.5,1,1);
    glRotatef(40,0,0,1);
    glScalef(1.5, 0.1, 1);

    glutSolidCube(1);
    glPopMatrix();

    //okvir
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    if(brojPromasaja >9)
        glColor3f(0.9, 0, 0);

    glTranslatef(2.49,1,1);
    glRotatef(40,0,0,1);
    glScalef(1.3, 0.2, 0.8);

    glutSolidCube(1);
    glPopMatrix();

    //stubic
    glPushMatrix();
    glColor3f(0.4, 0.4, 0.4);

    glTranslatef(2.5,1,0);
    glScalef(0.1, 0.1, 1.5);
    glutSolidCube(1);
    glPopMatrix();


    glPopMatrix();

void zivoti()
{
    glPushMatrix();



    glTranslatef(2.53,1.5,1.15);
    glRotatef(40,0,0,1);

    for(int i=0;i<5;i++)
    {
        glPushMatrix();
        glPushMatrix();
        glTranslatef(-0.7+i*0.2,0,0);
        glScalef(0.6,0.6,0.6);

        if((brojPromasaja < i+1) && !indZivota[i])
        {
            dobos(0,0.2*i,0);
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
            dobos(1/(i+0.1),0,0);
        }
        else
            indZivota[i+5]=1;
        glPopMatrix();
    }
    glPopMatrix();
}
   zivoti();


for(int i=0;i<8;i++)
{

if(indd[i])
{
    for(int j=4*i;j<4*i+4;j++)
    {

        if(!gotova[j])
        {
            brzina[j]=verovatnoca();
            //brzina[j]=0;
            gotova[j]=1;
            //printf("%d ",brzina1);
        }
        if(brzina[j] != -1)
        {
            nota(trake[j%4],brzina[j],j,i);

        }
        else
            yKoord[j]=6.9;
    }
}
}
    glutSwapBuffers();
}

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

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;


    case 'g':
    case 'G':

        if (!animation_ongoing && !pocetakIgre) {
            pocetakIgre=1;
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

        srand(time(NULL));
        animation_ongoing = 0;
        static int indd[8]={1,0,0,0,0,0,0,0};
        for(int i=0;i<8;i++)
            parr[i]=0.0001;
        static double yKoord[32],zKoord[32];
        srand(time(NULL));
        brojPromasaja=0;
        static int indZivota[10];
        pocetakIgre=0;
        glutPostRedisplay();
        break;

    case 'j':
        reaguj(0);
         break;
    case 'k':
        reaguj(1);
         break;
    case 'l':
        reaguj(2);
        break;
    case ';':
        reaguj(3);
         break;
    }
}

static void on_timer(int value)
{

    if (value != TIMER_ID)

        return;

//parametar inkrement
    for(int i=0;i<8;i++)
        if(indd[i])
            parr[i] +=0.1;
    parametarZivota +=0.1;



//pokretanje talasa nota
for(int i=0;i<8;i++)
{

if (yKoord[4*i]>6.5 && yKoord[4*i+1]>6.5 && yKoord[4*i+2]>6.5 && yKoord[4*i+3]>6.5)
    {

    indd[i]=0;

    for(int j=4*i;j<4*i+4;j++)
    {
        yKoord[j]= -2;
        gotova[j]=0;
        lock[j]=0;
        pogodio[j]=0;
    }

    }

if (yKoord[4*i]> 0.1 && yKoord[4*i+1]> 0.1 && yKoord[4*i+2]> 0.1 && yKoord[4*i+3]> 0.1 && !indd[(i+1)%8] )
    {
        indd[(i+1)%8]=1;
        parr[(i+1)%8]=0.0001;
    }

}

int promasajLock=0;
//promasena nota
 for(int i=0;i<32;i++)
    {


       if(!lock[i] && !pogodio[i] && brzina[i] != -1  && yKoord[i]>6.3 && yKoord[i]<6.5 )
            {
                if(!promasajLock)
                {
                    brojPromasaja++;
                    promasajLock=1;
                }
                promasio[i%4]=1;
                vreme[i%4]=time(0);
                //pogodio[i]=0;
                lock[i]=1;

            }

    }



if(brojPromasaja >9)
{
    animation_ongoing = 0;
    printf("Vas rezultat je=%u \n",rezultat);
}


    //printf(" %lf %lf\n",parr1,parr2);
   /* printf("%lf %lf\n",yKoord[0],yKoord[4]);
    printf("%d %d\n\n",pogodio[0],promasio[0]);*/
    //printf("Broj promasaja je %d iii %d\n",brojPromasaja,prviTalas);
    //for(int i=0;i<8;i++)
/*    printf("%d",indd[i]);
    printf("\n");
    printf("%lf %lf %lf %lf",yKoord[0],yKoord[1],yKoord[2],yKoord[3]);
    printf("\n");
    printf("%lf %lf %lf %lf",yKoord[4],yKoord[5],yKoord[6],yKoord[7]);
    printf("\n");
    printf("\n");
*/
    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}
