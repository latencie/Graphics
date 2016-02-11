/* Computer Graphics, Assignment, Translations, Rotations and Scaling
 *
 * Filename ........ transformations.c
 * Description ..... Contains the re-programmed translation, rotation and scaling functions
 * Student name Gracia Michelle & Lars Lokhoff
 * Student email michellegracia@gmail.com & lars.lokhoff@hotmail.com
 * Collegekaart & 10606165
 * Date 12-02-2016
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include "transformations.h"

/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

//This function returns the norm of a vector (x, y, z)
double return_norm(GLfloat x, GLfloat y, GLfloat z)
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

//This function applies the scaling matrix to the teapot by 
//putting the factors in the right place of the matrix
void myScalef(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat M[16] =
    {
        x, 0.0, 0.0, 0.0,
        0.0, y, 0.0, 0.0,
        0.0, 0.0, z, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    glMultMatrixf(M);
}

//This function creates the translation matrix to move the teapot around
void myTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat M[16] =
    {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        x, y, z, 1.0
    };

    glMultMatrixf(M);
}

//This function rotates the teapot following the steps from the assignment
void myRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat u[3], v[3], w[3], t[3], smallest;
    GLdouble norm;
    int smallest_index;
    
    // Store the incoming rotation axis in w and normalize w
    norm = return_norm(x, y, z);
    w[0] = x / norm;
    w[1] = y / norm;
    w[2] = z / norm;


    // Compute the value of t, based on w
    t[0] = w[0];
    t[1] = w[1];
    t[2] = w[2];

    //Here we find the smalles value of t, this needs to be changed to 1
    if(t[0] < t[1]) {
        smallest = t[0];
        smallest_index = 0;
    }

    else {
        smallest = t[1];
        smallest_index = 1;
    }

    if(smallest > t[2]) {
        smallest_index = 2;
    }

    //Change the smalles value to 1
    t[smallest_index] = 1;

    // Compute u = t x w
    u[0] = t[1] * w[2] - t[2] * w[1];
    u[1] = t[2] * w[0] - t[0] * w[2];
    u[2] = t[0] * w[1] - t[1] * w[0];

    // Normalize u
    norm = return_norm(u[0], u[1], u[2]);
    u[0] = u[0] / norm;
    u[1] = u[1] / norm;
    u[2] = u[2] / norm;

    // Compute v = w x u
    v[0] = w[1] * u[2] - w[2] * u[1];
    v[1] = w[2] * u[0] - w[0] * u[2];
    v[2] = w[0] * u[1] - w[1] * u[0];

    // Specify matrix A
    GLfloat A[16] =
    {
        u[0], u[1], u[2], 0.0,
        v[0], v[1], v[2], 0.0,
        w[0], w[1], w[2], 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    // Convert 'angle' to radians
    angle = angle * M_PI / 180.0;

    // Specify matrix B
    GLfloat B[16] =
    {
        cos(angle), sin(angle), 0.0, 0.0,
        -sin(angle), cos(angle), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    // Specify matrix C
    GLfloat C[16] =
    {
        u[0], v[0], w[0], 0.0,
        u[1], v[1], w[1], 0.0,
        u[2], v[2], w[2], 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    glMultMatrixf(A);
    glMultMatrixf(B);
    glMultMatrixf(C);
}

