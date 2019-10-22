//
// Created by User on 06.10.2019.
//

#include "tetris.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>
#include <algorithm>
#include <chrono>

#include "properties.ini"



using namespace std;
int tetris::state = 0;




field::field() : drawable(){
    cell = new GLfloat[TETRIS_ROWS * TETRIS_COLUMNS * 4 * 2];
    _field = new GLfloat[TETRIS_ROWS * TETRIS_COLUMNS * 4 * 2];
    f_col = new GLfloat[TETRIS_ROWS * TETRIS_COLUMNS * 4 * 3];

    displaylist = 0;

    cell[0] = (GLfloat) TETRIS_OFFSETX;
    cell[1] = (GLfloat) TETRIS_OFFSETY;
    cell[2] = (GLfloat) TETRIS_OFFSETX + STORONA;
    cell[3] = (GLfloat) TETRIS_OFFSETY;
    cell[4] = (GLfloat) TETRIS_OFFSETX + STORONA;
    cell[5] = (GLfloat) TETRIS_OFFSETY + STORONA;
    cell[6] = (GLfloat) TETRIS_OFFSETX;
    cell[7] = (GLfloat) TETRIS_OFFSETY + STORONA;


    for(int i = 8; i < TETRIS_COLUMNS * 8; i++) {
        if (i % 2 && (i % 8 == 1 || i % 8 == 3)) {
            cell[i] = TETRIS_OFFSETY;
        } else if (i % 2 && (i % 8 == 7 || i % 8 == 5)) {
            cell[i] = cell[5];
        } else if (!(i % 2)) {
            cell[i] = cell[i - 8] + STORONA;
        }
    }

    for(int i = TETRIS_COLUMNS * 8; i < TETRIS_ROWS * TETRIS_COLUMNS * 8; i+=2)
    {
        cell[i] = cell[i % (TETRIS_COLUMNS * 8)];
    }
    for(int i = TETRIS_COLUMNS * 8 + 1; i < TETRIS_ROWS * TETRIS_COLUMNS * 8; i+=2)
    {
        cell[i] = cell[i - TETRIS_COLUMNS * 8] + STORONA;
    }

    memcpy(_field, cell, TETRIS_ROWS * TETRIS_COLUMNS * 4 * 2 * sizeof(GLfloat));

    for(int i = 0; i < TETRIS_ROWS * TETRIS_COLUMNS * 4 * 3; i+=3)
    {
        f_col[i] = zaliv[0];
        f_col[i+1] = zaliv[1];
        f_col[i+2] = zaliv[2];
    }
    //memset(f_col, 1, TETRIS_ROWS * TETRIS_COLUMNS * 4 * 3);
}

void field::display() {

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2,GL_FLOAT,0,_field);
    glColorPointer(3,GL_FLOAT,0,f_col);

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glDrawArrays(GL_QUADS,0,TETRIS_ROWS*TETRIS_COLUMNS*4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    if(tetris::state) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, cell);
        glLineWidth(5.f);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_QUADS, 0, TETRIS_ROWS * TETRIS_COLUMNS * 4);
    } else ;

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

GLfloat * field::getBlock(int x, int y){

    if(y < TETRIS_ROWS && x < TETRIS_COLUMNS)
        return &cell[3 * (y * TETRIS_COLUMNS + x)];
    else throw "OUT_OF_RANGE";
}

GLfloat *field::getColor(int x, int y) {

    if(x < TETRIS_COLUMNS && y < TETRIS_ROWS)
    {
        return &f_col[(y * TETRIS_COLUMNS + x)*3*4];
    }
}

field::~field() {
    delete cell;
    delete _field;
    delete f_col;
}

void field::clear(GLfloat r, GLfloat g, GLfloat b) {
    for(int i = 0; i < TETRIS_ROWS * TETRIS_COLUMNS * 4 * 3; i+=3)
    {
        f_col[i] = r;
        f_col[i+1] = g;
        f_col[i+2] = b;
    }
}

/////////////////////////////
/////////////////////////////
/////////////////////////////


figure::figure(figures _t) : _type(_t), rotation(0){

    switch (_t) {
        case fG :
            mmmm[0] = std::make_pair(1,0);
            mmmm[1] = std::make_pair(0,0);
            mmmm[2] = std::make_pair(0,1);
            mmmm[3] = std::make_pair(0,2);
            color[0] = 162.f/255.f, color[1] = 162.f/255.f; color[2] = 0.f; break;
        case Gf :
            mmmm[0] = std::make_pair(0,0);
            mmmm[1] = std::make_pair(1,0);
            mmmm[2] = std::make_pair(1,1);
            mmmm[3] = std::make_pair(1,2);
            color[0] = 255.f/255.f, color[1] = 69.f/255.f; color[2] = 0.f; break;
        case fI :
            mmmm[0] = std::make_pair(0,0);
            mmmm[1] = std::make_pair(0,1);
            mmmm[2] = std::make_pair(0,2);
            mmmm[3] = std::make_pair(0,3);
            color[0] = 162.f/255.f, color[1] = 0.f; color[2] = 162.f/255.f; break;
        case fZ :
            mmmm[0] = std::make_pair(0,0);
            mmmm[1] = std::make_pair(1,0);
            mmmm[2] = std::make_pair(1,1);
            mmmm[3] = std::make_pair(2,1);
            color[0] = 143.f/255.f, color[1] = 0.f; color[2] = 0.f; break;
        case Zf :
            mmmm[0] = std::make_pair(2,0);
            mmmm[1] = std::make_pair(1,0);
            mmmm[2] = std::make_pair(1,1);
            mmmm[3] = std::make_pair(0,1);
            color[0] = 218.f/255.f, color[1] = 165.f/255.f; color[2] = 32.f/255.f; break;
        case fT :
            mmmm[0] = std::make_pair(0,0);
            mmmm[1] = std::make_pair(0,1);
            mmmm[2] = std::make_pair(1,1);
            mmmm[3] = std::make_pair(0,2);
            color[0] = 0.f, color[1] = 128.f/255.f; color[2] = 0.f; break;
        case fQ :
            mmmm[0] = std::make_pair(0,0);
            mmmm[1] = std::make_pair(1,0);
            mmmm[2] = std::make_pair(1,1);
            mmmm[3] = std::make_pair(0,1);
            color[0] = 0.f, color[1] = 0.f; color[2] = 177.f/255.f; break;
        default: break;
    }

}


figure::figure(const figure &f) : _type(f._type), mmmm(f.mmmm){
    memcpy(color,f.color,3 * sizeof(GLfloat));
}

void figure::right() {

    for(auto &e  : mmmm)
        if(e.first + 1 >= TETRIS_COLUMNS)
            return;

    for(auto &e : mmmm)
    {
        e = std::make_pair(e.first + 1, e.second);
    }
}

void figure::left() {

    for(auto &e  : mmmm)
        if(e.first - 1 < 0)
            return;

    for(auto &e : mmmm)
    {
        e = std::make_pair(e.first - 1, e.second);
    }
}

void figure::down() {
    for(auto &e : mmmm)
    {
        e = std::make_pair(e.first, e.second + 1);
    }
}

void figure::up(){
    for(auto &e : mmmm)
    {
        e = std::make_pair(e.first, e.second - 1);
    }
}

void figure::rotate() {
    std::array<std::pair<int,int>,3> ass = {
            // 1 -> 0
            std::make_pair(mmmm[1].first - mmmm[0].first,mmmm[1].second - mmmm[0].second),
            // 2 -> 1
            std::make_pair(mmmm[2].first - mmmm[1].first,mmmm[2].second - mmmm[1].second),
            // 3 -> 2
            std::make_pair(mmmm[3].first - mmmm[2].first,mmmm[3].second - mmmm[2].second)
    };
    std::array<std::pair<int,int>,4> reserve;
    std::copy(mmmm.begin(),mmmm.end(),reserve.begin());
    ////    1 2
    ////      3 4
    ////                RIGHT => DOWN; DOWN => LEFT; LEFT => UP; UP => RIGHT
    ////      1
    ////    3 2
    ////    4

    rotation++;

    switch(_type)
    {
        case Zf:
        {
            if(rotation%2) {
                mmmm[0].first--;
                rotateOCL(ass);
            }
            else {
                mmmm[0].first++;
                rotateCL(ass);
            }

            break;
        }
        case fZ:
        {
            if(rotation%2) {
                mmmm[0].first++;
                rotateCL(ass);
            }
            else {
                mmmm[0].first--;
                rotateOCL(ass);
            }

            break;
        }
        case fI:
        {
            if(rotation%2) {
                rotateOCL(ass);
            }
            else {
                rotateCL(ass);
            }
            break;
        }
        case Gf:
        case fG:
        {
            if(rotation%4 == 1) {
                mmmm[0].first++;
                mmmm[0].second++;
            }else if (rotation%4 == 2){
                mmmm[0].first--;
                mmmm[0].second++;
            }else if (rotation%4 == 3){
                mmmm[0].first--;
                mmmm[0].second--;
            }else if (rotation%4 == 0){
                mmmm[0].first++;
                mmmm[0].second--;
            }
                rotateCL(ass);
                break;
        }
        case fT:
        {
            if(rotation%4 == 1) {
                mmmm[0].first+=2;
            }else if (rotation%4 == 2){
                mmmm[0].second+=2;
            }else if (rotation%4 == 3){
                mmmm[0].first-=2;
            }else if (rotation%4 == 0){
                mmmm[0].second-=2;
            }
            rotateCL(ass);
            break;
        }
        default: break;
    }

    for(int i = 0; i < 4; i++)
    {
        if(mmmm[i].first >= TETRIS_COLUMNS || mmmm[i].first < 0 || mmmm[i].second >= TETRIS_ROWS || mmmm[i].second < 0)
        {
            rotation--;
            mmmm.swap(reserve);
            break;
        }
    }
}

void figure::rotateCL(const std::array<std::pair<int,int>,3>& ass) {

    for(int i = 1; i < 4; i++)
    {
        switch(ass[i-1].first){
            case RIGHT:
                mmmm[i].second = mmmm[i-1].second + 1;
                if(ass[i-1].second == 0) mmmm[i].first = mmmm[i-1].first;
                break;
            case LEFT:
                mmmm[i].second = mmmm[i-1].second - 1;
                if(ass[i-1].second == 0) mmmm[i].first = mmmm[i-1].first;
                break;
            default:
                break;
        }
        switch(ass[i-1].second){
            case UP:
                mmmm[i].first = mmmm[i-1].first + 1;
                if(ass[i-1].first == 0) mmmm[i].second = mmmm[i-1].second;
                break;
            case DOWN:
                mmmm[i].first = mmmm[i-1].first - 1;
                if(ass[i-1].first == 0) mmmm[i].second = mmmm[i-1].second;
                break;
            default:
                break;
        }
    }
}

void figure::rotateOCL(const std::array<std::pair<int,int>,3>& ass) {

    for(int i = 1; i < 4; i++)
    {
        switch(ass[i-1].first){
            case RIGHT:
                mmmm[i].second = mmmm[i-1].second - 1;
                if(ass[i-1].second == 0) mmmm[i].first = mmmm[i-1].first;
                break;
            case LEFT:
                mmmm[i].second = mmmm[i-1].second + 1;
                if(ass[i-1].second == 0) mmmm[i].first = mmmm[i-1].first;
                break;
            default:
                break;
        }
        switch(ass[i-1].second){
            case UP:
                mmmm[i].first = mmmm[i-1].first - 1;
                if(ass[i-1].first == 0) mmmm[i].second = mmmm[i-1].second;
                break;
            case DOWN:
                mmmm[i].first = mmmm[i-1].first + 1;
                if(ass[i-1].first == 0) mmmm[i].second = mmmm[i-1].second;
                break;
            default:
                break;
        }
    }
}



/////////////////////////////
/////////////////////////////
/////////////////////////////
#include <random>

void tetris::display() {
    update();
    f_.display();

    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2,GL_FLOAT,0,nex_pol);
    glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(3,GL_FLOAT,0,nex_c);

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glDrawArrays(GL_QUADS,0,64);

    glDisableClientState(GL_VERTEX_ARRAY);

    glColor3f(0.f,0.f,0.f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2,GL_FLOAT,0,nex);

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDrawArrays(GL_QUADS,0,128);

    glDisableClientState(GL_VERTEX_ARRAY);
}

tetris::tetris() : drawable(), f_(), building(), score(0) {

    tetris::state = 1;

    std::srand(std::chrono::system_clock::now().time_since_epoch().count());

    _curr = new figure(static_cast<figures>(rand() % 7));
    _next = static_cast<figures>(rand() % 7);

    for (int i = 0; i < TETRIS_COLUMNS / 2; i++)
        _curr->right();


    nex[0] = (GLfloat) 10.f;
    nex[1] = (GLfloat) TETRIS_OFFSETY;
    nex[2] = (GLfloat) nex[0] + STORONA;
    nex[3] = (GLfloat) TETRIS_OFFSETY;
    nex[4] = (GLfloat) nex[2];
    nex[5] = (GLfloat) TETRIS_OFFSETY + STORONA;
    nex[6] = (GLfloat) 10.f;
    nex[7] = (GLfloat) TETRIS_OFFSETY + STORONA;


    for (int i = 8; i < 4 * 8; i++) {
        if (i % 2 && (i % 8 == 1 || i % 8 == 3)) {
            nex[i] = TETRIS_OFFSETY;
        } else if (i % 2 && (i % 8 == 7 || i % 8 == 5)) {
            nex[i] = TETRIS_OFFSETY + STORONA;
        } else if (!(i % 2)) {
            nex[i] = nex[i - 8] + STORONA;
        }
    }

    for (int i = 32; i < 128; i += 2) {
        nex[i] = nex[i % (4 * 8)];
    }
    for (int i = 32 + 1; i < 128; i += 2) {
        nex[i] = nex[i - 4 * 8] + STORONA;
    }

    for (int i = 0; i < 4 * 4 * 4 * 3; i += 3) {
        nex_c[i] = 1.f;
        nex_c[i + 1] = 1.f;
        nex_c[i + 2] = 1.f;
    }

    memcpy(nex_pol, nex, 128 * sizeof(GLfloat));


    figure temp(_next);
    for(int i = 0; i < 4 * 4 * 4 * 3; i++)
    {
        nex_c[i] = 1.f;
    }
    temp.right();
    for (auto &f : temp.mmmm) {
        GLfloat *tt = &nex_c[(f.second * 4 + f.first)*3*4];
        for(int i = 0; i < 12; i++)
            tt[i] = temp.color[i%3];
    }

}



void tetris::update() {

    for (auto &e : _curr->mmmm) {
        if (std::count_if(building.begin(), building.end(), [&e](figure fig) {
            for (auto &p : fig.mmmm)
                if (e == p) return true;
            return false;
        }) || e.second >= TETRIS_ROWS) {
            std::srand(std::chrono::system_clock::now().time_since_epoch().count());
            _curr->up();
            building.push_back(*_curr);
            for(auto &h : _curr->mmmm)
            {
                if(h.second == 0)
                    state = 0;
            }
            delete _curr;
            _curr = new figure(_next);
            for (int i = 0; i < TETRIS_COLUMNS / 2; i++)
                _curr->right();

            _next = static_cast<figures>(rand() % 7);

            figure temp(_next);
            for(int i = 0; i < 4 * 4 * 4 * 3; i++)
            {
                nex_c[i] = 1.f;
            }
            temp.right();
            for (auto &f : temp.mmmm) {
                GLfloat *tt = &nex_c[(f.second * 4 + f.first)*3*4];
                for(int i = 0; i < 12; i++)
                    tt[i] = temp.color[i%3];
            }

            break;
        }
    }

    f_.clear(f_.zaliv[0], f_.zaliv[1], f_.zaliv[2]);
    for (auto &e : _curr->mmmm) {
        GLfloat *c = f_.getColor(e.first, e.second);
        for (int i = 0; i < 12; i++) {
            c[i] = _curr->color[i % 3];
        }
    }

    int *count = new int[TETRIS_ROWS];
    memset(count, 0, TETRIS_ROWS * sizeof(int));

    for (auto &e : building) {
        for (auto &p : e.mmmm) {
            if(p.first == -1) continue;
            GLfloat *c = f_.getColor(p.first, p.second);
            for (int i = 0; i < 12; i++) {
                c[i] = e.color[i % 3];
            }

            count[p.second]++;
        }
    }

    for (int i = 0; i < TETRIS_ROWS; i++)
        if (count[i] >= TETRIS_COLUMNS) {
            for (auto &e : building) {
                for (auto &p : e.mmmm) {
                    if (p.second == i) {
                        p = std::make_pair(-1, -1);
                        score+=10;
                    }
                }

                for (auto &p : e.mmmm) {
                    if (p.second < i && p.second >= 0)
                    {
                        p.second++;
                    }
                }

            }

        }

        glutSetWindowTitle(std::string("Cyber-Tetris, score: ").append(to_string(score)).c_str());

}

