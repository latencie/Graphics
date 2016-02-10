/* Computer Graphics, Assignment 4, Positioning the camera
 *
 * Filename ........ lookat.c
 * Description ..... Contains the re-programmed lookAt function
 * Created by ...... Jurgen Sturm 
 *
 * Student name ....
 * Student email ... 
 * Collegekaart ....
 * Date ............
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */
#include <GL/glut.h>   
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

 
/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif


// returns the length of a vector
double return_norm(GLdouble x, GLdouble y, GLdouble z)
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void myLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
              GLdouble centerX, GLdouble centerY, GLdouble centerZ,
              GLdouble upX, GLdouble upY, GLdouble upZ) 
{
    // translate object with -VRP
    centerX -= eyeX;
    centerY -= eyeY;
    centerZ -= eyeZ;
    
    // create camera coordinate system
    
    // normalize & create cz
    double norm = return_norm(centerX, centerY, centerZ);
    GLdouble cz[] =  {centerX/norm, centerY/norm, centerZ/norm};
    
    // calculate direction of cx
    GLdouble cx[] =  {cz[1]*upZ-cz[2]*upY, 
                      -cz[0]*upZ+cz[2]*upX, 
                      cz[0]*upY-cz[1]*upX}; 
                      
    // normalize cx                
    norm = return_norm(cx[0], cx[1], cx[2]);
    cx[0] = cx[0]/norm;
    cx[1] = cx[1]/norm;
    cx[2] = cx[2]/norm;
    
    // calculate cy
    GLdouble cy[] =  {cx[1]*cz[2]-cx[2]*cz[1], 
                      -cx[0]*cz[2]+cx[2]*cz[0], 
                      cx[0]*cz[1]-cx[1]*cz[0]};
        
    // create rotation matrix
    GLfloat R[16] = 
    {
        cx[0], cy[0], -cz[0], 0.,
        cx[1], cy[1], -cz[1], 0.,
        cx[2], cy[2], -cz[2], 0.,
        0., 0., 0., 1.
    };

    glMultMatrixf(R);
}
