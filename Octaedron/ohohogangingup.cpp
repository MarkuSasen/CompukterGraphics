#include <GL/freeglut.h>
#include <iostream>

GLfloat alrRotX, alrRotY;
GLfloat XROTATE = 0, YROTATE = -0.1;
GLfloat rotateAbit = 1, deltaRotAbit = 0.1;

GLfloat pos[4] = {2,0,5.5,1};

GLfloat range = -5;


void init(void)
{
    glClearColor(0,0,0,0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0,0,range);
    glRotatef(rotateAbit,0.0,1.0,0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glTranslatef(pos[0], pos[1], pos[2]);


    glColor3f(1.0,1.0,1.0);
    GLUquadricObj *quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_LINE);
    gluSphere(quad, 0.5, 10, 10);

    ////////////////////////////////////////////////

    glLoadIdentity();
    glTranslatef(0,0,range);
    glRotatef(alrRotX,1.0,0.0,0.0);
    glRotatef(alrRotY,0.0,1.0,0.0);

    glBegin(GL_TRIANGLES);


            glColor3f(1.0,0.5,0.0);    //// оранжевый
            glNormal3f(1,1,1);
            glVertex3f( 1, 0 + 0.1, 0 + 0.1);
            glVertex3f( 0 + 0.1, 1 + 0.1, 0 + 0.1);
            glVertex3f( 0 + 0.1, 0 + 0.1, 1 + 0.1);


            glColor3f(1.0,0.9,0.0);    //// желтый
            glNormal3f(-1,1,-1);
            glVertex3f( 1+0.1, 0-0.1, 0+0.1);
            glVertex3f( 0+0.1,-1-0.1, 0+0.1);
            glVertex3f( 0+0.1, 0-0.1, 1+0.1);


            glColor3f(0.8,0.0,0.8);    //// фиолет
            glNormal3f(-1,-1,1);
            glVertex3f(-1-0.1, 0-0.1, 0+0.1);
            glVertex3f( 0-0.1,-1-0.1, 0+0.1);
            glVertex3f( 0-0.1, 0-0.1, 1+0.1);

            glColor3f(0.0,1.0,0.0);    ////зеленый
            glNormal3f(1,-1,-1);
            glVertex3f(-1-0.1, 0+0.1, 0+0.1);
            glVertex3f( 0-0.1, 1+0.1, 0+0.1);
            glVertex3f( 0-0.1, 0+0.1, 1+0.1);

            glColor3f(0.0,0.9,0.9);    //// голубой
            glNormal3f(-1,-1,1);
            glVertex3f( 1+0.1, 0+0.1, 0-0.1);
            glVertex3f( 0+0.1, 1+0.1, 0-0.1);
            glVertex3f( 0+0.1, 0+0.1,-1-0.1);

            glColor3f(0.0,0.0,1.0);    //// синий
            glNormal3f(1,-1,-1);
            glVertex3f( 1+0.1, 0-0.1, 0-0.1);
            glVertex3f( 0+0.1,-1-0.1, 0-0.1);
            glVertex3f( 0+0.1, 0-0.1,-1-0.1);

            glColor3f(1.0,0.0,0.0);    //// красный
            glNormal3f(1,1,1);
            glVertex3f(-1-0.1, 0-0.1, 0-0.1);
            glVertex3f( 0-0.1,-1-0.1, 0-0.1);
            glVertex3f( 0-0.1, 0-0.1,-1-0.1);

            glNormal3f(-1,1,-1);

            glColor3f(1.0,0.0,0.0);
            glVertex3f(-1-0.1, 0+0.1, 0-0.1);

            glColor3f(0.0,1.0,0.0);
            glVertex3f( 0-0.1, 1+0.1, 0-0.1);

            glColor3f(0.0,0.0,1.0);
            glVertex3f( 0-0.1, 0+0.1,-1-0.1);

    glEnd();


    glFlush();

    gluDeleteQuadric(quad);
}

void loop(int time)
{
    rotateAbit += deltaRotAbit;
    alrRotX += XROTATE;
    alrRotY += YROTATE;

    glutPostRedisplay();
    glutTimerFunc(5,loop,5);
}



void reshape(int w, int h)
{
    if (h == 0 || w == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(90.0,(GLdouble)w/(GLdouble)h,1,20);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,w,h);
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1600,900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutTimerFunc(100,loop,100);

    glutMainLoop();

    glDisable(GL_DEPTH_TEST);
    return 0;
}

/* //Back up
                    -400.0, 100.0, -100.0,
                    -100.0, 225.0, -100.0,
                    -100.0, 100.0, -225.0,

                    //////////////////////////////////2
                    //Left down
                     -400.0, -100.0, -100.0,
                     -100.0, -225.0, -100.0,
                     -100.0, -100.0, -225.0,

                    //////////////////////////////////3
                    //Right down
                    -400.0, 100.0, 100.0,
                    -100.0, 225.0, 100.0,
                    -100.0, 100.0, 225.0,

                    //////////////////////////////////4
                    //Front down
                    -400.0, -100.0, 100.0,
                    -100.0, -225.0, 100.0,
                    -100.0, -100.0, 225.0,

                    //////////////////////////////////5
                    400.0, 100.0, -100.0,
                    100.0, 225.0, -100.0,
                    100.0, 100.0, -225.0,

                    //////////////////////////////////6
                    400.0, -100.0, -100.0,
                    100.0, -225.0, -100.0,
                    100.0, -100.0, -225.0,

                    //////////////////////////////////7

                    //Front up
                    400.0, -100.0, 100.0,
                    100.0, -225.0, 100.0,
                    100.0, -100.0, 225.0,

                    //////////////////////////////////8

                    //Right up
                    400.0, 100.0, 100.0,
                    100.0, 225.0, 100.0,
                    100.0, 100.0, 225.0,
*/

/*
 *                     /////////////////
                    /////////////////   VERTEXES
                    /////////////////

                    //////////////////////////////////1
                    //Back up
                    1.0, 0.0, 0.0,
                    0.0, 1.0, .0,
                    0.0, 0.0, 1.0,

                    //////////////////////////////////2
                    //Left down
                     1.0, 0.0, 0.0,
                     0.0, -1.0, 0.0,
                     0.0, 0.0, 1.0,

                    //////////////////////////////////3
                    //Right down
                    -1.0, 0.0, 0.0,
                    0.0, -1.0, 0.0,
                    0.0, 0.0, 1.0,

                    //////////////////////////////////4
                    //Front down
                    -1.0, 0.0, 0.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, 1.0,

                    //////////////////////////////////5
                    1.0, 0.0, 0.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, -1.0,

                    //////////////////////////////////6
                    1.0, 0.0, 0.0,
                    0.0, -1.0, 0.0,
                    0.0, 0.0, -1.0,

                    //////////////////////////////////7

                    //Front up
                    -1.0, -0.0, 0.0,
                    0.0, -1.0, 0.0,
                    0.0, 0.0, -1.0,

                    //////////////////////////////////8

                    //Right up
                    -1.0, 0.0, 0.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, -1.0,
 */