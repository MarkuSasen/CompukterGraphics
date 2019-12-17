//
// Created by User on 17.12.2019.
//

#ifndef OCTAEDRON_STRUCTURES_H
#define OCTAEDRON_STRUCTURES_H

#include <GL/freeglut.h>



typedef struct {

    GLdouble vertexes[24 * 3];
    GLdouble color[24 * 3];


    void draw(double x0, double y0, double z0)
    {

        glNormal3d(1,1,1);

        for(int i = 0; i < 72; i+=3)
        {

            glBegin(GL_TRIANGLES);

                glColor3d( color[i], color[i+1], color[i+2] );
                glVertex3d( x0 + vertexes[i], y0 + vertexes[i+1], z0 + vertexes[i+2] );
                i+=3;
                glColor3d( color[i], color[i+1], color[i+2] );
                glVertex3d( x0 + vertexes[i], y0 + vertexes[i+1], z0 + vertexes[i+2] );
                i+=3;
                glColor3d( color[i], color[i+1], color[i+2] );
                glVertex3d( x0 + vertexes[i], y0 + vertexes[i+1], z0 + vertexes[i+2] );

            glEnd();
        }
    }

} OCT_PARAM;



#endif //OCTAEDRON_STRUCTURES_H
