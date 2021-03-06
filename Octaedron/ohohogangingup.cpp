#include <GL/freeglut.h>
#include <iostream>
#include <fstream>

#include <CImg.h> //подгрузка текстур

GLfloat alrRotX, alrRotY;
GLfloat XROTATE = 0, YROTATE = -0.1;
GLfloat rotateAbit = 1, deltaRotAbit = 0.3;
GLfloat pos[4]{1,0,3.2f,1};
int dmode = 1;
float diverge = 0.05;
bool turnsphere = false;
GLfloat range = -5;

void draw3();
void draw4();
void draw7();


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

    glEnable(GL_BLEND); //Enable blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.

    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0,0,-10);
    draw3();
    draw4();
    draw7();

}
GLfloat AlphaChannel = 1.f;

GLuint glLabs[4];
void draw3()
{
    glDeleteLists(glLabs[0], 1);

    glLabs[0] = glGenLists(5);

    if(!glIsList(glLabs[0]))
    {
        std::cerr << "CRITICAL ERROR glGENLISTS!!!!!!!!!!\n";
        return;
    }

    glNewList(glLabs[0],GL_COMPILE);

    if(AlphaChannel == 1.f)
        glDepthMask(GL_TRUE);
    else glDepthMask(GL_FALSE);


    glBegin(GL_TRIANGLES);
    glColor4f(1.0,0.55,0.0,AlphaChannel);    //// оранжевый
    glNormal3f(1,1,1);
    glVertex3f( 1 + diverge, 0 + diverge, 0 + diverge);
    glVertex3f( 0 + diverge, 1 + diverge, 0 + diverge);
    glVertex3f( 0 + diverge, 0 + diverge, 1 + diverge);


    glColor4f(1.0,0.92,0.0, AlphaChannel);    //// желтый
    glNormal3f(-1,1,-1);
    glVertex3f( 1+diverge, 0-diverge, 0+diverge);
    glVertex3f( 0+diverge,-1-diverge, 0+diverge);
    glVertex3f( 0+diverge, 0-diverge, 1+diverge);


    glColor4f(0.8,0.0,0.8, AlphaChannel);    //// фиолет
    glNormal3f(-1,-1,1);
    glVertex3f(-1-diverge, 0-diverge, 0+diverge);
    glVertex3f( 0-diverge,-1-diverge, 0+diverge);
    glVertex3f( 0-diverge, 0-diverge, 1+diverge);

    glColor4f(0.55f,0.22f,0.28f, AlphaChannel);    //// красный
    glNormal3f(1,1,1);
    glVertex3f(-1-diverge, 0-diverge, 0-diverge);
    glVertex3f( 0-diverge,-1-diverge, 0-diverge);
    glVertex3f( 0-diverge, 0-diverge,-1-diverge);

    glColor4f(0.0,1.0,0.0, AlphaChannel);    ////зеленый
    glNormal3f(1,-1,-1);
    glVertex3f(-1-diverge, 0+diverge, 0+diverge);
    glVertex3f( 0-diverge, 1+diverge, 0+diverge);
    glVertex3f( 0-diverge, 0+diverge, 1+diverge);

    glColor4f(0.0,0.9,0.9, AlphaChannel);    //// голубой
    glNormal3f(-1,-1,1);
    glVertex3f( 1+diverge, 0+diverge, 0-diverge);
    glVertex3f( 0+diverge, 1+diverge, 0-diverge);
    glVertex3f( 0+diverge, 0+diverge,-1-diverge);

    glColor4f(0.0,0.0,1.0, AlphaChannel);    //// синий
    glNormal3f(1,-1,-1);
    glVertex3f( 1+diverge, 0-diverge, 0-diverge);
    glVertex3f( 0+diverge,-1-diverge, 0-diverge);
    glVertex3f( 0+diverge, 0-diverge,-1-diverge);


    glNormal3f(-1,1,-1);
    glColor4f(1.0,0.0,0.0, AlphaChannel);
    glVertex3f(-1-diverge, 0+diverge, 0-diverge);

    glColor4f(0.0,1.0,0.0, AlphaChannel);
    glVertex3f( 0-diverge, 1+diverge, 0-diverge);

    glColor4f(0.0,0.0,1.0, AlphaChannel);
    glVertex3f( 0-diverge, 0+diverge,-1-diverge);

    glEnd();
    glDepthMask(GL_TRUE);

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
        
        glColor4f(1.f,1.f,1.f,1.f);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_NEAREST );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_NEAREST );
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texts[i].width, texts[i].height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                     texts[i].data);
    }

    delete src;

    glDeleteLists(glLabs[1], 1);
    glLabs[1] = glGenLists(5);

    if(!glIsList(glLabs[1]))
    {
        std::cerr << "CRITICAL ERROR glGENLISTS!!!!!!!!!!\n";
        return;
    }




    glNewList(glLabs[1],GL_COMPILE);

    if(AlphaChannel == 1.f)
        glDepthMask(GL_TRUE);
    else glDepthMask(GL_FALSE);

    glColor4f(1,1,1,AlphaChannel);

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
        glDepthMask(GL_TRUE);
    glEndList();

    glDeleteLists(glLabs[2], 1);
    glLabs[2] = glGenLists(5);

    if(!glIsList(glLabs[2]))
    {
        std::cerr << "CRITICAL ERROR glGENLISTS!!!!!!!!!!\n";
        return;
    }

    glNewList(glLabs[2],GL_COMPILE);

    if(AlphaChannel == 1.f)
        glDepthMask(GL_TRUE);
    else glDepthMask(GL_FALSE);

    glColor4f(1.f,1.f,1.f,AlphaChannel);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1,1,1);
    glTexCoord2f(0, 0);     glVertex3f(1+diverge,0+diverge,0+diverge);
    glTexCoord2f(1, 0);     glVertex3f(0+diverge,1+diverge,0+diverge);
    glTexCoord2f(0.5, 1);   glVertex3f(0+diverge,0+diverge,1+diverge);
    glEnd();

    glColor4f(1.f,1.f,1.f,AlphaChannel);
    glBindTexture(GL_TEXTURE_2D, textures[7]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1,1,-1);
    glTexCoord2f(0, 0);     glVertex3f( 1+diverge, 0-diverge, 0+diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0+diverge,-1-diverge, 0+diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0+diverge, 0-diverge, 1+diverge);
    glEnd();

    glColor4f(1.f,1.f,1.f,AlphaChannel);
    glBindTexture(GL_TEXTURE_2D, textures[7]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1,-1,1);
    glTexCoord2f(0, 0);     glVertex3f(-1-diverge, 0-diverge, 0+diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0-diverge,-1-diverge, 0+diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0-diverge, 0-diverge, 1+diverge);
    glEnd();

    glColor4f(1.f,1.f,1.f,AlphaChannel);
    glBindTexture(GL_TEXTURE_2D, textures[7]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1,-1,-1);
    glTexCoord2f(0, 0);     glVertex3f(-1-diverge, 0+diverge, 0+diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0-diverge, 1+diverge, 0+diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0-diverge, 0+diverge, 1+diverge);
    glEnd();

    glColor4f(1.f,1.f,1.f,AlphaChannel);
    glBindTexture(GL_TEXTURE_2D, textures[7]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1,-1,1);
    glTexCoord2f(0, 0);     glVertex3f( 1+diverge, 0+diverge, 0-diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0+diverge, 1+diverge, 0-diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0+diverge, 0+diverge,-1-diverge);
    glEnd();

    glColor4f(1.f,1.f,1.f,AlphaChannel);
    glBindTexture(GL_TEXTURE_2D, textures[7]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1,-1,-1);
    glTexCoord2f(0, 0);     glVertex3f( 1+diverge, 0-diverge, 0-diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0+diverge,-1-diverge, 0-diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0+diverge, 0-diverge,-1-diverge);
    glEnd();

    glColor4f(1.f,1.f,1.f,AlphaChannel);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_TRIANGLES);
    glNormal3f(1,1,1);
    glTexCoord2f(0, 0);     glVertex3f(-1-diverge, 0-diverge, 0-diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0-diverge,-1-diverge, 0-diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0-diverge, 0-diverge,-1-diverge);
    glEnd();

    glColor4f(1.f,1.f,1.f,AlphaChannel);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_TRIANGLES);
    glNormal3f(-1,1,-1);
    glTexCoord2f(0, 0);     glVertex3f(-1-diverge, 0+diverge, 0-diverge);
    glTexCoord2f(1, 0);     glVertex3f( 0-diverge, 1+diverge, 0-diverge);
    glTexCoord2f(0.5, 1);   glVertex3f( 0-diverge, 0+diverge,-1-diverge);

    glEnd();
        glDepthMask(GL_TRUE);
    glEndList();
}

void olala(GLfloat x, GLfloat y, GLfloat z) {
    int p = 11;
    glNormal3f(1,1,1);

    for(int i = 0; i<p; i+=2)
    {
        glNormal3f(1,1,1);
        glBegin(GL_POLYGON);

        glVertex3f( x/p*i       ,y-y/p*i    ,0          );
        glVertex3f( 0           ,y-y/p*i    ,z/p*i      );
        glVertex3f( 0           ,y-y/p*(i+1),z/p*(i+1)  );
        glVertex3f( x/p*(i+1)   ,y-y/p*(i+1),0          );

        glEnd();
    }
};


void draw7() {

    glDeleteLists(glLabs[3], 1);
    glLabs[3] = glGenLists(5);

    if (!glIsList(glLabs[3])) {
        std::cerr << "CRITICAL ERROR glGENLISTS!!!!!!!!!!\n";
        return;
    }

    glNewList(glLabs[3],GL_COMPILE);

    glPushMatrix();

    if(AlphaChannel == 1.f)
        glDepthMask(GL_TRUE);
    else glDepthMask(GL_FALSE);

    glMatrixMode(GL_MODELVIEW);

        glTranslatef(diverge,diverge,diverge);
        glColor4f(1.0f,0.0f,0.0f,AlphaChannel);
        olala(1.f,1.f,1.f);
        glTranslatef(-diverge,-diverge,-diverge);
        glRotatef(90.f,0.0f,1.0f,0.0f);

        glTranslatef(diverge,diverge,diverge);
        glColor4f(1.0f,0.5f,0.0f,AlphaChannel);
        olala(1.f,1.f,1.f);
        glTranslatef(-diverge,-diverge,-diverge);
        glRotatef(90.f,0.0f,1.0f,0.0f);

        glTranslatef(diverge,diverge,diverge);
        glColor4f(1.0f,0.9f,0.0f,AlphaChannel);
        olala(1.f,1.f,1.f);
        glTranslatef(-diverge,-diverge,-diverge);
        glRotatef(90.f,0.0f,1.0f,0.0f);

        glTranslatef(diverge,diverge,diverge);
        glColor4f(0.0f,1.0f,0.0f,AlphaChannel);
        olala(1.f,1.f,1.f);
        glTranslatef(-diverge,-diverge,-diverge);
        glRotatef(90.f,0.0f,1.0f,0.0f);

        glRotatef(180.f,1.0f,0.0f,0.0f);

        glTranslatef(diverge,diverge,diverge);
        glColor4f(0.0f,0.9f,0.9f,AlphaChannel);
        olala(1.f,1.f,1.f);
        glTranslatef(-diverge,-diverge,-diverge);
        glRotatef(90.f,0.0f,1.0f,0.0f);

        glTranslatef(diverge,diverge,diverge);
        glColor4f(0.0f,0.0f,1.0f,AlphaChannel);
        olala(1.f,1.f,1.f);
        glTranslatef(-diverge,-diverge,-diverge);
        glRotatef(90.f,0.0f,1.0f,0.0f);

        glTranslatef(diverge,diverge,diverge);
        glColor4f(0.8f,0.0f,0.8f,AlphaChannel);
        olala(1.f,1.f,1.f);
        glTranslatef(-diverge,-diverge,-diverge);
        glRotatef(90.f,0.0f,1.0f,0.0f);

        glTranslatef(diverge,diverge,diverge);
        glColor4f(1.0f,0.0f,0.0f,AlphaChannel);
        olala(1.f,1.f,1.f);
        glTranslatef(-diverge,-diverge,-diverge);
        glDepthMask(GL_TRUE);
    glPopMatrix();

    glEndList();
}


GLboolean lm = true;

void display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glPushMatrix();
        glLoadIdentity();

        glTranslatef(0, 0, -10);

            glRotatef(rotateAbit, 0.0f, 0.3f, 0.0f);
            glTranslatef(pos[0], pos[1], pos[2]);
            glLightfv(GL_LIGHT0, GL_POSITION, pos);


        glColor4d(1.0, 1.0, 1.0, 1.0);
        GLUquadricObj *quad = gluNewQuadric();
        gluQuadricDrawStyle(quad, GLU_LINE);
        gluSphere(quad, 0.25, 10, 10);

    glPopMatrix();


    ////////////////////////////////////////////////

//    glLoadIdentity();

    glRotatef(alrRotY,1.0,0.0,0.0);
    glRotatef(alrRotX,0.0,1.0,0.0);

    //glColor4d(1.0,1.0,1.0,1.0);
    glIsEnabled(GL_TEXTURE_2D) ?
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE) : void();


    if(dmode == 2 || dmode == 3)
        glCallList(glLabs[dmode-1]);
    else if(dmode == 4) {
        glCallList(glLabs[3]);
        //glPushMatrix();

//        if(AlphaChannel == 1.f)
//            glDepthMask(GL_TRUE);
//        else glDepthMask(GL_FALSE);
//
//        glTranslatef(diverge,diverge,diverge);
//        glColor4f(1.0f,0.0f,0.0f,AlphaChannel);
//        olala(1.f,1.f,1.f);
//        glTranslatef(-diverge,-diverge,-diverge);
//        glRotatef(90.f,0.0f,1.0f,0.0f);
//
//        glTranslatef(diverge,diverge,diverge);
//        glColor4f(1.0f,0.5f,0.0f,AlphaChannel);
//        olala(1.f,1.f,1.f);
//        glTranslatef(-diverge,-diverge,-diverge);
//        glRotatef(90.f,0.0f,1.0f,0.0f);
//
//        glTranslatef(diverge,diverge,diverge);
//        glColor4f(1.0f,0.9f,0.0f,AlphaChannel);
//        olala(1.f,1.f,1.f);
//        glTranslatef(-diverge,-diverge,-diverge);
//        glRotatef(90.f,0.0f,1.0f,0.0f);
//
//        glTranslatef(diverge,diverge,diverge);
//        glColor4f(0.0f,1.0f,0.0f,AlphaChannel);
//        olala(1.f,1.f,1.f);
//        glTranslatef(-diverge,-diverge,-diverge);
//        glRotatef(90.f,0.0f,1.0f,0.0f);
//
//        glRotatef(180.f,1.0f,0.0f,0.0f);
//
//        glTranslatef(diverge,diverge,diverge);
//        glColor4f(0.0f,0.9f,0.9f,AlphaChannel);
//        olala(1.f,1.f,1.f);
//        glTranslatef(-diverge,-diverge,-diverge);
//        glRotatef(90.f,0.0f,1.0f,0.0f);
//
//        glTranslatef(diverge,diverge,diverge);
//        glColor4f(0.0f,0.0f,1.0f,AlphaChannel);
//        olala(1.f,1.f,1.f);
//        glTranslatef(-diverge,-diverge,-diverge);
//        glRotatef(90.f,0.0f,1.0f,0.0f);
//
//        glTranslatef(diverge,diverge,diverge);
//        glColor4f(0.8f,0.0f,0.8f,AlphaChannel);
//        olala(1.f,1.f,1.f);
//        glTranslatef(-diverge,-diverge,-diverge);
//        glRotatef(90.f,0.0f,1.0f,0.0f);
//
//        glTranslatef(diverge,diverge,diverge);
//        glColor4f(1.0f,0.0f,0.0f,AlphaChannel);
//        olala(1.f,1.f,1.f);
//        glTranslatef(-diverge,-diverge,-diverge);
//        glDepthMask(GL_TRUE);
//
//        glPopMatrix();
    }
    else if(dmode == 1){
    glCallList(glLabs[0]);
//        if(AlphaChannel == 1.f)
//            glDepthMask(GL_TRUE);
//        else glDepthMask(GL_FALSE);

//        glBegin(GL_TRIANGLES);
//        glColor4f(1.0,0.55,0.0,AlphaChannel);    //// оранжевый
//        glNormal3f(1,1,1);
//        glVertex3f( 1 + diverge, 0 + diverge, 0 + diverge);
//        glVertex3f( 0 + diverge, 1 + diverge, 0 + diverge);
//        glVertex3f( 0 + diverge, 0 + diverge, 1 + diverge);
//
//
//        glColor4f(1.0,0.92,0.0, AlphaChannel);    //// желтый
//        glNormal3f(-1,1,-1);
//        glVertex3f( 1+diverge, 0-diverge, 0+diverge);
//        glVertex3f( 0+diverge,-1-diverge, 0+diverge);
//        glVertex3f( 0+diverge, 0-diverge, 1+diverge);
//
//
//        glColor4f(0.8,0.0,0.8, AlphaChannel);    //// фиолет
//        glNormal3f(-1,-1,1);
//        glVertex3f(-1-diverge, 0-diverge, 0+diverge);
//        glVertex3f( 0-diverge,-1-diverge, 0+diverge);
//        glVertex3f( 0-diverge, 0-diverge, 1+diverge);
//
//        glColor4f(0.55f,0.22f,0.28f, AlphaChannel);    //// красный
//        glNormal3f(1,1,1);
//        glVertex3f(-1-diverge, 0-diverge, 0-diverge);
//        glVertex3f( 0-diverge,-1-diverge, 0-diverge);
//        glVertex3f( 0-diverge, 0-diverge,-1-diverge);
//
//        glColor4f(0.0,1.0,0.0, AlphaChannel);    ////зеленый
//        glNormal3f(1,-1,-1);
//        glVertex3f(-1-diverge, 0+diverge, 0+diverge);
//        glVertex3f( 0-diverge, 1+diverge, 0+diverge);
//        glVertex3f( 0-diverge, 0+diverge, 1+diverge);
//
//        glColor4f(0.0,0.9,0.9, AlphaChannel);    //// голубой
//        glNormal3f(-1,-1,1);
//        glVertex3f( 1+diverge, 0+diverge, 0-diverge);
//        glVertex3f( 0+diverge, 1+diverge, 0-diverge);
//        glVertex3f( 0+diverge, 0+diverge,-1-diverge);
//
//        glColor4f(0.0,0.0,1.0, AlphaChannel);    //// синий
//        glNormal3f(1,-1,-1);
//        glVertex3f( 1+diverge, 0-diverge, 0-diverge);
//        glVertex3f( 0+diverge,-1-diverge, 0-diverge);
//        glVertex3f( 0+diverge, 0-diverge,-1-diverge);
//
//
//        glNormal3f(-1,1,-1);
//        glColor4f(1.0,0.0,0.0, AlphaChannel);
//        glVertex3f(-1-diverge, 0+diverge, 0-diverge);
//
//        glColor4f(0.0,1.0,0.0, AlphaChannel);
//        glVertex3f( 0-diverge, 1+diverge, 0-diverge);
//
//        glColor4f(0.0,0.0,1.0, AlphaChannel);
//        glVertex3f( 0-diverge, 0+diverge,-1-diverge);
//
//        glEnd();
//        glDepthMask(GL_TRUE);

    }

    glFlush();

    gluDeleteQuadric(quad);
}
GLfloat incX = 0, incY = 0;
void loop(int time)
{
    if(lm)
        if(!turnsphere)
            rotateAbit += deltaRotAbit;
        else rotateAbit -= deltaRotAbit;
    //if(alrRotX != 0)  alrRotX+=incX;
    //if(alrRotY != 0)  alrRotY+=incY;

    glutPostRedisplay();
    glutTimerFunc(15,loop,15);
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

        if(AlphaChannel == 1.f)
            glDepthMask(GL_TRUE);
        else glDepthMask(GL_FALSE);

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
        case '3':
            dmode = 3;
            glEnable(GL_TEXTURE_2D);
            break;
        case '4':
            dmode = 4;
            glDisable(GL_TEXTURE_2D);
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
        case 'p':
            lm = !lm;
            break;
        case 'b':
            turnsphere = !turnsphere;
            break;
        case 'f':
            if(AlphaChannel == 1.f) {
                AlphaChannel = 0.5f;
                draw3();
                draw4();
                draw7();
            } else {
                AlphaChannel = 1.f;
                draw3();
                draw4();
                draw7();
            }
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
    glDeleteTextures(8, textures);
    glDeleteLists(glLabs[0],4);
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