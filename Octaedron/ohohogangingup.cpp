#include <GL/freeglut.h>
#include <iostream>
#include <fstream>

#include <CImg.h>

GLfloat alrRotX, alrRotY;
GLfloat XROTATE = 0, YROTATE = -0.1;
GLfloat rotateAbit = 1, deltaRotAbit = 0.1;
GLfloat A = 1.f;
GLfloat pos[4] = {2,0,5.5,1};
int dmode = 1;
float diverge = 0.05;
bool btext = false;
GLfloat range = -5;

void draw3();
void draw4();

void init(void)
{
    glClearColor(0,0,0,1);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_TEXTURE_2D);
    //glShadeModel(GL_FLAT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0,0,range);
    draw3();
    draw4();


}

GLuint glLabs[3];
void draw3()
{
    glLabs[0] = glGenLists(3);

    if(!glIsList(glLabs[0]))
    {
        std::cerr << "CRITICAL ERROR glGENLISTS!!!!!!!!!!\n";
        return;
    }

    glNewList(glLabs[0],GL_COMPILE);

    glBegin(GL_TRIANGLES);

    glColor4f(1.0,0.5,0.0,A);    //// оранжевый
    glNormal3f(1,1,1);
    glVertex3f( 1 + diverge, 0 + diverge, 0 + diverge);
    glVertex3f( 0 + diverge, 1 + diverge, 0 + diverge);
    glVertex3f( 0 + diverge, 0 + diverge, 1 + diverge);


    glColor4f(1.0,0.9,0.0,A);    //// желтый
    glNormal3f(-1,1,-1);
    glVertex3f( 1+diverge, 0-diverge, 0+diverge);
    glVertex3f( 0+diverge,-1-diverge, 0+diverge);
    glVertex3f( 0+diverge, 0-diverge, 1+diverge);


    glColor4f(0.8,0.0,0.8,A);    //// фиолет
    glNormal3f(-1,-1,1);
    glVertex3f(-1-diverge, 0-diverge, 0+diverge);
    glVertex3f( 0-diverge,-1-diverge, 0+diverge);
    glVertex3f( 0-diverge, 0-diverge, 1+diverge);

    glColor4f(0.0,1.0,0.0,A);    ////зеленый
    glNormal3f(1,-1,-1);
    glVertex3f(-1-diverge, 0+diverge, 0+diverge);
    glVertex3f( 0-diverge, 1+diverge, 0+diverge);
    glVertex3f( 0-diverge, 0+diverge, 1+diverge);

    glColor4f(0.0,0.9,0.9,A);    //// голубой
    glNormal3f(-1,-1,1);
    glVertex3f( 1+diverge, 0+diverge, 0-diverge);
    glVertex3f( 0+diverge, 1+diverge, 0-diverge);
    glVertex3f( 0+diverge, 0+diverge,-1-diverge);

    glColor4f(0.0,0.0,1.0,A);    //// синий
    glNormal3f(1,-1,-1);
    glVertex3f( 1+diverge, 0-diverge, 0-diverge);
    glVertex3f( 0+diverge,-1-diverge, 0-diverge);
    glVertex3f( 0+diverge, 0-diverge,-1-diverge);

    glColor4f(1.0,0.0,0.0,A);    //// красный
    glNormal3f(1,1,1);
    glVertex3f(-1-diverge, 0-diverge, 0-diverge);
    glVertex3f( 0-diverge,-1-diverge, 0-diverge);
    glVertex3f( 0-diverge, 0-diverge,-1-diverge);

    glNormal3f(-1,1,-1);
    glColor4f(1.0,0.0,0.0,A);
    glVertex3f(-1-diverge, 0+diverge, 0-diverge);

    glColor4f(0.0,1.0,0.0,A);
    glVertex3f( 0-diverge, 1+diverge, 0-diverge);

    glColor4f(0.0,0.0,1.0,A);
    glVertex3f( 0-diverge, 0+diverge,-1-diverge);

    glEnd();

    glEndList();

}

typedef struct T_GL_DATA {
    size_t width, height;
    unsigned char *data;
} TGL;

GLuint textures[8];
TGL texts[8];
using namespace cimg_library;
void draw4()
{
    const char* txrs[]{ "wall.bmp",
                        "billi.bmp",
                        "wood.bmp",
                        "grass.bmp",
                        "terrain.bmp",
                        "dirt.bmp",
                        "diamonds.bmp",
                        "ricardo.bmp"};

    CImg<unsigned char> *src = new CImg<unsigned char>();




    glGenTextures(8, textures);
    for(int i = 0; i < 8; i++) {
        src->load_bmp(txrs[i]);

        texts[i].width = src->width();
        texts[i].height = src->height();
        texts[i].data = new unsigned char[src->size()];
        memcpy(texts[i].data, src->data(), src->size());
        std::cout << src->size() << std::endl;

        src->clear();

        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_NEAREST );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_NEAREST );
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texts[i].width, texts[i].height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                     texts[i].data);
    }

    delete src;

    glLabs[1] = glGenLists(3);

    if(!glIsList(glLabs[1]))
    {
        std::cerr << "CRITICAL ERROR glGENLISTS!!!!!!!!!!\n";
        return;
    }

    glNewList(glLabs[1],GL_COMPILE);


    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1,1,1);
    glTexCoord2f(0, 0);     glVertex3f(1+diverge,0+diverge,0+diverge);
    glTexCoord2f(1, 0);     glVertex3f(0+diverge,1+diverge,0+diverge);
    glTexCoord2f(0.5, 1);   glVertex3f(0+diverge,0+diverge,1+diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1,1,-1);
    glTexCoord2f(0, 0);     glVertex3f( 1+diverge, 0-diverge, 0+diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0+diverge,-1-diverge, 0+diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0+diverge, 0-diverge, 1+diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1,-1,1);
    glTexCoord2f(0, 0);     glVertex3f(-1-diverge, 0-diverge, 0+diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0-diverge,-1-diverge, 0+diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0-diverge, 0-diverge, 1+diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1,-1,-1);
    glTexCoord2f(0, 0);     glVertex3f(-1-diverge, 0+diverge, 0+diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0-diverge, 1+diverge, 0+diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0-diverge, 0+diverge, 1+diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1,-1,1);
    glTexCoord2f(0, 0);     glVertex3f( 1+diverge, 0+diverge, 0-diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0+diverge, 1+diverge, 0-diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0+diverge, 0+diverge,-1-diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1,-1,-1);
    glTexCoord2f(0, 0);     glVertex3f( 1+diverge, 0-diverge, 0-diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0+diverge,-1-diverge, 0-diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0+diverge, 0-diverge,-1-diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[6]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1,1,1);
    glTexCoord2f(0, 0);     glVertex3f(-1-diverge, 0-diverge, 0-diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0-diverge,-1-diverge, 0-diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0-diverge, 0-diverge,-1-diverge);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[7]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1,1,-1);
    glTexCoord2f(0, 0);     glVertex3f(-1-diverge, 0+diverge, 0-diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0-diverge, 1+diverge, 0-diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0-diverge, 0+diverge,-1-diverge);

    glEnd();

    glEndList();

}

void display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glLoadIdentity();


    glTranslatef(0,0,range);
    glRotatef(rotateAbit,0.0,1.0,0.0);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glTranslatef(pos[0], pos[1], pos[2]);


    glColor4d(1.0,1.0,1.0,1.0);
    GLUquadricObj *quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_LINE);
    gluSphere(quad, 0.25, 10, 10);
    glPopMatrix();
    ////////////////////////////////////////////////

//    glLoadIdentity();

    glRotatef(alrRotY,1.0,0.0,0.0);
    glRotatef(alrRotX,0.0,1.0,0.0);

    glColor4d(1.0,1.0,1.0,1.0);
    glIsEnabled(GL_TEXTURE_2D) ?
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE) : void();
    glCallList(glLabs[dmode-1]);

    glFlush();

    gluDeleteQuadric(quad);
}
GLfloat incX = 0, incY = 0;
void loop(int time)
{
    rotateAbit += deltaRotAbit;
    //if(alrRotX != 0)  alrRotX+=incX;
    //if(alrRotY != 0)  alrRotY+=incY;

    glutPostRedisplay();
    glutTimerFunc(5,loop,5);
}



void reshape(int w, int h)
{
    if (h == 0 || w == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(30.0,(GLdouble)w/(GLdouble)h,1,20);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,w,h);
}

void keyboard(unsigned char c, int x, int y)
{

    switch(c)
    {

        case 'l':
            glIsEnabled(GL_LIGHT0) ? glDisable(GL_LIGHT0) : glEnable(GL_LIGHT0);
            break;

        case '1':
            dmode = 1;
            glDisable(GL_TEXTURE_2D);
            break;
        case '2':
            dmode = 2;
            glEnable(GL_TEXTURE_2D);
            break;

        case 'd':
            alrRotX+=0.1;
            incX = alrRotX;
            break;
        case 'a':
            alrRotX-=0.1;
            incX = alrRotX;
            break;
        case 'w':
            alrRotY+=0.1;
            incX = alrRotY;
            break;
        case 's':
            alrRotY-=0.1;
            incX = alrRotY;
            break;
        case 'q':
            alrRotY = alrRotX = incX = incY = 0;
            break;
        case 'z':
            //glEnable(GL_BLEND);
            //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //glDisable(GL_DEPTH_TEST);
            A == 1.0 ? A = 0.4f : A=1.f;
            break;

    }
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA|GLUT_ALPHA);
    glutInitWindowSize(1600,900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutTimerFunc(100,loop,100);

    glutMainLoop();

    glDisable(GL_DEPTH_TEST);

    glDeleteLists(glLabs[0],2);
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