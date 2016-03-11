/* Computer Graphics, Assignment, Volume rendering with cubes/points/isosurface
 *
 * Student name ....
 * Student email ...
 * Collegekaart ....
 * Date ............
 * Comments ........
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "marching_tetrahedra.h"

/* Compute a linearly interpolated position where an isosurface cuts
   an edge between two vertices (p1 and p2), each with their own
   scalar value (v1 and v2) */

static vec3
interpolate_points(unsigned char isovalue, vec3 p1, vec3 p2, unsigned char v1, unsigned char v2)
{
    /* Initially, simply return the midpoint between p1 and p2.
       So no real interpolation is done yet */

    return v3_add(v3_multiply(p1, 0.5), v3_multiply(p2, 0.5));
}

/* Using the given iso-value generate triangles for the tetrahedron
   defined by corner vertices v0, v1, v2, v3 of cell c.

   Store the resulting triangles in the "triangles" array.

   Return the number of triangles created (either 0, 1, or 2).

   Note: the output array "triangles" should have space for at least
         2 triangles.
*/

static int
generate_tetrahedron_triangles(triangle *triangles, unsigned char isovalue, cell c, int v0, int v1, int v2, int v3)
{
    // TODO store triangles in triangles-pointer

    // TODO return number of triangles
    return 0;
}

/* Generate triangles for a single cell for the given iso-value. This function
   should produce at most 6 * 2 triangles (for which the "triangles" array should
   have enough space).

   Use calls to generate_tetrahedron_triangles().

   Return the number of triangles produced
*/

int
generate_cell_triangles(triangle *triangles, cell c, unsigned char isovalue)
{
    int num_tri = 0;
    
    // get cell vertex combinations that form tetrahedrons
    vec3 *tetrahedrons = malloc(24* sizeof(vec3));
    tetrahedrons[0] = c.p[0];
    tetrahedrons[1] = c.p[1];
    tetrahedrons[2] = c.p[3];
    tetrahedrons[3] = c.p[7];
    
    tetrahedrons[4] = c.p[0];
    tetrahedrons[5] = c.p[7];
    tetrahedrons[6] = c.p[6];
    tetrahedrons[7] = c.p[2];
    
    tetrahedrons[8] = c.p[0];
    tetrahedrons[9] = c.p[1];
    tetrahedrons[10] = c.p[7];
    tetrahedrons[11] = c.p[5];
    
    tetrahedrons[12] = c.p[0];
    tetrahedrons[13] = c.p[4];
    tetrahedrons[14] = c.p[5];
    tetrahedrons[15] = c.p[7];
    
    tetrahedrons[16] = c.p[0];
    tetrahedrons[17] = c.p[3];
    tetrahedrons[18] = c.p[7];
    tetrahedrons[19] = c.p[2];
    
    tetrahedrons[20] = c.p[0];
    tetrahedrons[21] = c.p[7];
    tetrahedrons[22] = c.p[6];
    tetrahedrons[23] = c.p[4];
    
    // for each tetrahedron in the cell, generate the appropriate triangles
    for (int i = 0; i < 24; i+=4)
    {
        // get B values
        double v0 = (c.value[tetrahedrons[i]] > isovalue);
        double v1 = (c.value[tetrahedrons[i+1]] > isovalue);
        double v2 = (c.value[tetrahedrons[i+2]] > isovalue);
        double v3 = (c.value[tetrahedrons[i+3]] > isovalue);
        
        // store triangles at pointer, get number of triangles for count
        num_tri += generate_tetrahedron_triangles(triangles, isovalue, c, v0, v1, v2, v3);
    }
    
    // free mallocs, return number of triangles
    free(tetrahedrons);
    return num_tri;
}
