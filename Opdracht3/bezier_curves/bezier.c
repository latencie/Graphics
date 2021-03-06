/* Computer Graphics, Assignment, Bezier curves
 * Filename ........ bezier.c
 * Description ..... Bezier curves
 * Date ............ 22.07.2009
 * Created by ...... Paul Melis
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

#include <math.h>
#include "bezier.h"
#include <stdio.h>

/*
 * return factorial of integer
 */
int return_factorial(int num) 
{
	int fact = 1;

	if(num <= 1) 
	{
		return 1;
	}

	else 
	{
		for(int i = 1; i <= num; i++) 
		{
			fact = fact * i;
		}

		return fact;
	}
}


/* 
 * return the kth Bernstein polynomial of degree n
 */
float return_bernstein(int n, int k, float u) {
	float bernstein;

	bernstein = return_factorial(n) / ((float)return_factorial(k) * return_factorial(n - k));
	bernstein = bernstein * pow(u, k) * pow((1 - u), (n - k));

	return bernstein;
}

/* Given a Bezier curve defined by the 'num_points' control points
 * in 'p' compute the position of the point on the curve for parameter
 * value 'u'.
 *
 * Return the x and y values of the point by setting *x and *y,
 * respectively.
 */

void
evaluate_bezier_curve(float *x, float *y, control_point p[], int num_points, float u)
{
   *x = 0.0;
   *y = 0.0;
    float bernstein;

    for(int i = 0; i < num_points; i++){
    	
    	bernstein = return_bernstein(num_points - 1, i, u);
    	*x += bernstein * p[i].x;
    	*y += bernstein * p[i].y;
    }
}

/* Draw a Bezier curve defined by the control points in p[], which
 * will contain 'num_points' points.
 *
 * Draw the line segments you compute directly on the screen
 * as a single GL_LINE_STRIP. This is as simple as using
 *
 *      glBegin(GL_LINE_STRIP);
 *      glVertex2f(..., ...);
 *      ...
 *      glEnd();
 *
 * DO NOT SET ANY COLOR!
 *
 * The 'num_segments' parameter determines the "discretization" of the Bezier
 * curve and is the number of straight line segments that should be used
 * to approximate the curve.
 *
 * Call evaluate_bezier_curve() to compute the necessary points on
 * the curve.
 */

void
draw_bezier_curve(int num_segments, control_point p[], int num_points)
{
	float x = p[0].x;
	float y = p[0].y;

	glBegin(GL_LINE_STRIP);
 	glVertex2f(x, y);

 	for(int i = 1; i < num_segments; i++){
 		evaluate_bezier_curve(&x, &y, p, num_points, i / (float)num_segments);
 		glVertex2f(x, y);
 	}

 	glVertex2f(p[num_points - 1].x, p[num_points - 1].y);
 	glEnd();
}

/* Find the intersection of a cubic Bezier curve with the line X=x.
   Return 1 if an intersection was found and place the corresponding y
   value in *y.
   Return 0 if no intersection exists.
*/


/*
 * get x_value for certain u
 */
float get_x_value(float *x_u, float *y_u, control_point p[], float u)
{
    evaluate_bezier_curve(x_u, y_u, p, 4, u);
    return *x_u;
}

/* 
 * recursively choose new u until intersection with x is found
 */
float find_u_intersect(float * x_u, float * y, float margin, control_point p[], 
                        float min, float max, float x, int trials)
{
    if (trials != 0)
    {
        // find point between min and max
        float u_1 = (min + max)/2.0;
        
        // get x-value of Bezier curve for this point
        float x_1 = get_x_value(x_u, y, p, u_1);
        
        // compare with x, if within margin: return u_1
        if (fabsf(x - x_1) < margin) 
        {   
            return u_1;
        }
        else
        {
            // get x-value of Bezier curve for left point
            float x_min = get_x_value(x_u, y, p, min);
            
            // check if we should continue with interval right or left of u_1
            float diff_0 = x_min - x;
            float diff_1 = x_1 - x;
            if ( (diff_0 * diff_1) <= 0 )
            {
                // interval left of u_1: run with u_1 as new max
                return find_u_intersect(x_u, y, margin, p, min, u_1, x, trials-1);
            }
            else 
            {
                // interval right of u_1: run with u_1 as new min
                return find_u_intersect(x_u, y, margin, p, u_1, max, x, trials-1);
            } 
        }
    }
    return -1.0;
}    


/*
 * Find the intersection of the Bezier curve and time
 */
int
intersect_cubic_bezier_curve(float *y, control_point p[], float x)
{   
    // create and initialize pointer for x_values
    float x_u = 0.0;
    
    // choose margin and number of trials
    float margin = 0.001;
    int trials = 100;
    
    // get initial min and max
    float min = 0.0;
    float max = 1.0;
    
    // converge to correct value, return signal value -1 if there is none
    float u_1 = find_u_intersect(&x_u, y, margin, p, min, max, x, trials);
    
    if (u_1 != -1.0)
    {
        // *y has already been set to correct value by find_u_intersect()
        
        // intersection was found: return 1 
        return 1;
    }
    
    // intersection was not found: return 0
    return 0;
}
