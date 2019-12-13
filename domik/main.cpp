#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
#include "painting.h"
#define PI 3.14

painting *f = new painting();
int _timet = 0, counter = 0;
void init(){
    glOrtho(0.f,1600.f,900.f,0.f,0.f,1.f);
    glClearColor(117.f/255.f,134.f/255.f,255.f/255.f,1.f);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    f->draw();
        glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glTranslatef(1300.0 * cos((double)((double(2.0 * counter / 1000 / 10))*PI)), -700.0 * sin((double) (((double)(2.0 * counter / 1000 / 10))*PI)),0.f);

            f->d[3]->draw();

        glPopMatrix();

        glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glTranslatef(1300.0 * cos((double)PI + ((double(2.0 * counter / 1000 / 10))*PI)), -700.0 * sin((double) PI + (((double)(2.0 * counter / 1000 / 10))*PI)),0.f);

        f->d[4]->draw();

        glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void timer(int time){
    _timet += time;
    counter += time;
    if(_timet >= 200*PI/2)
    {
        _timet = 0;
        for(int i = 0; i < 3; ++i)
        {
            auto &e = f->d[i]->c;
            float cosinus = 0.05f * cos((double)((double(2.0 * counter / 1000 / 10))*PI)),
            sinus = sin((double) (((double)(2.0 * counter / 1000 / 10))*PI));
            if(cosinus > 0 && sinus > 0)
                e = {e.r + 0.5f*cosinus,e.g + 0.5f*cosinus,e.b + 0.5f*cosinus,e.a};//{e.r - 10.f/255.f,e.g - 10.f/255.f,e.b - 10.f/255.f,e.a};
            else if(sinus > 0 && cosinus < 0)
                e = {e.r + 0.5f*cosinus,e.g + 0.5f*cosinus,e.b + 0.5f*cosinus,e.a};
            else if(sinus < 0 && cosinus < 0)
                e = {e.r + 2.f*cosinus,e.g + 2.f*cosinus,e.b + 2.f*cosinus,e.a};
            else if(sinus < 0 && cosinus > 0)
                e = {e.r + 2.f*cosinus,e.g + 2.f*cosinus,e.b + 2.f*cosinus,e.a};
        }
        //1300.0 + 100.0 * cos((double)((double(2.0 * i/_count))*PI)), 150.0 - 100.0 * sin((double) (((double)(2.0 * i/_count))*PI))
//        position delta = {10.0 * cos((double)((double(2.0 * counter / 1000 / 10))*PI)), 10.0 * sin((double) (((double)(2.0 * counter / 1000 / 10))*PI))};
//        for(int i = 0; i < f->d[3]->_count; i++){
//            auto &e = f->d[3]->vertices[i];
//            e = {e.x + delta.x, e.y + delta.y};
//}
        glutPostRedisplay();
    }
    glutTimerFunc(400,timer,400);
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(1600,900);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutCreateWindow("Domik.exe");
    init();


    glutDisplayFunc(display);
    glutTimerFunc(200,timer,200);
    glutMainLoop();

    return 0;
}