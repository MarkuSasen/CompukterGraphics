//
// Created by User on 30.10.2019.
//

#ifndef DOMIK_PAINTING_H
#define DOMIK_PAINTING_H

#include <cstdint>

struct color{
    float r,g,b,a;
};
struct position{
    double x,y;
};

struct drawable {

    uint64_t type;
    color c;
    position* vertices; int _count;

    drawable() = default;
    inline virtual void draw();

};

struct holm : public drawable{

    holm();

    void draw() final;

    position* vert2, *vert3;
};

struct house : public drawable {

    house();

    void draw() final;

    position* door, *window, *roof;
};

struct sun : public drawable {

    sun();

    void draw() final;
};

struct mun : public drawable {

    mun();

    void draw() final;
};

struct sky : public drawable {

    sky();

    void draw() final;
};

struct painting {

    painting();

    void draw();

    drawable** d;
};


#endif //DOMIK_PAINTING_H
