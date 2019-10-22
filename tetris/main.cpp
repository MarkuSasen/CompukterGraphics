#include <iostream>

#include <GL/freeglut.h>
#include "tetris.h"
#include "properties.ini"
#include <algorithm>

using namespace std;

GLfloat spin = 0.0f;
GLuint list_field;

tetris tet;
int tint = 0;


void loop(int interval) {
    tint += interval;
    if(tint >= 1000)
    {
        tint = 0;
        tet._curr->down();
        glutPostRedisplay();
    }
    if(tetris::state)
        glutTimerFunc(200,loop,interval);
}


void init(){

    glClearColor((GLfloat) 59/255	,(GLfloat) 59/255	, (GLfloat) 59/255,0.61);
    glShadeModel(GL_FLAT);
    glOrtho(0.f,1000.f,0.f,800.f,-1.f,1.f);

//    tet.displaylist = glGenLists(1);
//    glNewList(t.displaylist,GL_COMPILE);
//        t.display();
//    glEndList();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    tet.display();

    glFlush();
     glutSwapBuffers();
}

void update()
{
//    glDeleteLists(1,2);
//    t.displaylist = glGenLists(1);
//    glNewList(t.displaylist,GL_COMPILE);
//    t.display();
//    glEndList();
//
//    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    if(!tetris::state) return;
        switch(key)
        {
            case 's' : tet._curr->down();
                glutPostRedisplay();
                break;
            case 'a':
                for(auto &e : tet._curr->mmmm)
                {
                    if(std::count_if(tet.building.begin(),tet.building.end(),[&e](figure fig){
                        for(auto &p : fig.mmmm)
                            if(e.first - 1 == p.first && e.second == p.second) return true; return false;
                    }))
                        return;
                }
                tet._curr->left();
                glutPostRedisplay();
                break;
            case 'd' :
                for(auto &e : tet._curr->mmmm)
                {
                    if(std::count_if(tet.building.begin(),tet.building.end(),[&e](figure fig){
                        for(auto &p : fig.mmmm)
                            if(e.first + 1 == p.first && e.second == p.second) return true; return false;
                    }))
                        return;
                }
                tet._curr->right();// tet._curr.post(&tet.f_);
                glutPostRedisplay();
                break;
            case 'r' :
                for(auto &e : tet._curr->mmmm)
                {
                    if(std::count_if(tet.building.begin(),tet.building.end(),[&e](figure fig){
                        for(auto &p : fig.mmmm)
                            if((e.first + 1 == p.first || e.first - 1 == p.first) && e.second == p.second)
                                return true; return false;
                    }))
                        return;
                }
                tet._curr->rotate();// tet._curr.post(&tet.f_);
                glutPostRedisplay();
                break;
            default :
                break;
        }
}

void reshape(int w, int h){

    glViewport(0,0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-50.0,50.0,-50.0,50.0,-1.0,1.0);
    glOrtho(0.f,1000.f,1000.f,0.f,0.f,1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

int main(int argc, char** argv) {

    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize ( 1000 , 800 );
    glutInitWindowPosition(100,100);

    glutCreateWindow("Cyber-Tetris");
    init();

    //glutIdleFunc(loop);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(400,loop,400);
    glutMainLoop();

    return 0;
}