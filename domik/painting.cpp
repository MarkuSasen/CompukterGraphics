//
// Created by User on 30.10.2019.
//

#include "painting.h"
#include <GL/freeglut.h>
#include <math.h>

void drawable::draw() {
    glColor4d(c.r,c.g,c.b,c.a);
    glBegin(type);
    for (int i = 0; i < _count; ++i)
    {
        glVertex2d(vertices[i].x,vertices[i].y);
    }
    glEnd();
}

////////////////////////
#define PI 3.14
holm::holm() : drawable() {
    type = GL_TRIANGLE_FAN;
    c = {116.0/255.0,182.0/255.0,0.0,1.0};
    _count = 50;

    vertices = (position*) malloc(sizeof(position) * _count);
    vert2 = (position*) malloc(sizeof(position) * _count);
    vert3 = (position*) malloc(sizeof(position) * _count);

    for(int i = 0; i < _count; ++i)
    {
        vertices[i] = {150.0 - 500.0 * cos((double) i*PI/50.0), 900.0 - 300.0 * sin((double) i * PI/50.0)};
    }

    for(int i = 0; i < _count; ++i)
    {
        vert2[i] = {1000.0 - 700.0 * cos((double) i*PI/50.0), 1000.0 - 500.0 * sin((double) i * PI/50.0)};
    }

    for(int i = 0; i < _count; ++i)
    {
        vert3[i] = {500.0 - 500.0 * cos((double) i*PI/50.0), 1000.0 - 500.0 * sin((double) i * PI/50.0)};
    }
}

void holm::draw() {

    glColor4d(c.r - 44.0/255.0, c.g - 60.0/255.0, c.b ? c.b + 10.0/255.0 : 0.0, 1.0);
    glBegin(type);
    for (int i = 0; i < _count; ++i)
    {
        glVertex2d(vert2[i].x,vert2[i].y);
    }
    glEnd();

    drawable::draw();

    glColor4d(c.r , c.g + 40.0/255.0, 0.0, 1.0);
    glBegin(type);
    for (int i = 0; i < _count; ++i)
    {
        glVertex2d(vert3[i].x,vert3[i].y);
    }
    glEnd();
}

////////////////////////

house::house() {
    type = GL_TRIANGLE_FAN;
    c = {1.0,1.0,1.0,1.0};
    _count = 4;

    vertices = (position*) malloc(sizeof(position) * _count);
    vertices[0] = {500.0,800.0}; vertices[1] = {800.0,800.0}; vertices[2] = {800.0,500.0}; vertices[3] = {500.0,500.0};

    door = (position*) malloc(sizeof(position) * _count);
    door[0] = {550.0,780.0}; door[1] = {650.0,780.0}; door[2] = {650.0,600.0}; door[3] = {550.0,600.0};

    window = (position*) malloc(sizeof(position) * _count);
    window[0] = {680.0,700.0}; window[1] = {750.0,700.0}; window[2] = {750.0,630.0}; window[3] = {680.0,630.0};

    roof = (position*) malloc(sizeof(position) * 3);
    roof[0] = {400.0,550.0}; roof[1] = {900.0,550.0}; roof[2] = {650.0,400.0};
}

void house::draw() {
    drawable::draw();

    glColor4d(c.r - 101.0/255.0,c.g - 127.0/255.0,c.b - 207.0/255.0, 1.0);
    glBegin(type);
    for (int i = 0; i < _count; ++i)
    {
        glVertex2d(door[i].x,door[i].y);
    }
    glEnd();

    glColor4d(0.0, c.g - 200.0/255.0, c.b - 124.0/255.0, 1.0);
    glBegin(type);
    for (int i = 0; i < _count; ++i)
    {
        glVertex2d(window[i].x,window[i].y);
    }
    glEnd();

    glColor4d(c.r - 124.0/255.0, c.g - 235.0/255.0, c.b - 225.0/255.0, 1.0);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; ++i)
    {
        glVertex2d(roof[i].x,roof[i].y);
    }
    glEnd();
}

///////////////////////////////////


sun::sun() {
    type = GL_TRIANGLE_FAN;
    c = {241.0/255.0,239.0/255.0,116.0/255,1.0};
    _count = 50;

    vertices = (position*) malloc(sizeof(position) * _count);

    for(int i = 0; i < _count; ++i)
    {
        vertices[i] = {1100.0 + 100.0 * cos((double)((double(2.0 * i/_count))*PI)), 700.0 - 100.0 * sin((double) (((double)(2.0 * i/_count))*PI))};
    }

}

void sun::draw() {
    drawable::draw();

    glColor4d(c.r ,c.g,c.b, 1.0);
    glBegin(type);
    for (int i = 0; i < _count; ++i)
    {
        glVertex2d(vertices[i].x,vertices[i].y);
    }
    glEnd();

}

///////////////////////////////////

sky::sky() {
    type = GL_QUADS;
    c = {117.f/255.f,134.f/255.f,255.f/255.f,1.f};
    _count = 4;

    vertices = (position*) malloc(sizeof(position) * _count);

    vertices[0] = {0.0,0.0};
    vertices[1] = {1600.0,0.0};
    vertices[2] = {1600.0,900.0};
    vertices[3] = {0.0,900.0};
}

void sky::draw() {
    drawable::draw();
}

///////////////////////////////////

mun::mun() {
    type = GL_TRIANGLE_FAN;
    c = {142.0/255.0,142.0/255.0,142.0/255,1.0};
    _count = 50;

    vertices = (position*) malloc(sizeof(position) * _count);

    for(int i = 0; i < _count; ++i)
    {
        vertices[i] = {450.0 + 100.0 * cos((double)((double(2.0 * i/_count))*PI)), 700.0 - 100.0 * sin((double) (((double)(2.0 * i/_count))*PI))};
    }
}

void mun::draw() {
    drawable::draw();
}

///////////////////////////////////


painting::painting() {
    d = (drawable**) malloc(sizeof(drawable) * 5);
    d[0] = new sky();
    d[1] = new holm();
    d[2] = new house();
    d[3] = new sun();
    d[4] = new mun();
}

void painting::draw() {
    for(int i = 0; i < 3; ++i)
        d[i]->draw();
}

