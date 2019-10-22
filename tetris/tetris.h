//
// Created by User on 06.10.2019.
//

#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H

#include <GL/gl.h>
#include <utility>
#include <array>
#include <list>


class drawable{
public:
    virtual void display() = 0;

    GLuint displaylist;
};


enum figures { fT = 0, fI, fZ, fQ, fG, Zf, Gf, NUL };

class field;

class figure {
    enum VEC { LEFT = -1, RIGHT = 1, UP = -1, DOWN = 1 };

    int rotation;

    void rotateCL(const std::array<std::pair<int,int>,3>& ass);
    void rotateOCL(const std::array<std::pair<int,int>,3>& ass);
public:
    std::array<std::pair<int,int>,4> mmmm; figures _type; GLfloat color[3];

    figure(figures _t);
    figure(const figure& f);

    void right();
    void left();

    void down();
    void up();

    void rotate();
};

class field : public drawable {
    friend class tetris;
    GLfloat zaliv[3] = {(GLfloat) 56.f/255.f,(GLfloat) 12.f/255.f,(GLfloat) 12.f/255.f };
public:
    GLfloat *cell, *_field, *f_col;

    field();
    void display() final;

    GLuint list;

    GLfloat * getBlock(int x, int y);
    GLfloat* getColor(int x, int y);

    void clear(GLfloat r,GLfloat g,GLfloat b);

    ~field();
};

#include <random>

class tetris : public drawable{
    GLfloat nex[4*4 * 4*2], nex_pol[4*4 * 4*2], nex_c[4*4 * 4 * 3];
public:
    void display() final;

    tetris();

    void update();
    field f_; figure *_curr; std::list<figure> building; figures _next; static int state; int score;
};

#endif //TETRIS_TETRIS_H
