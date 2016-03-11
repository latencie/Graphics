/* Computer Graphics, Assignment, Volume rendering with cubes/points/isosurface
 *
 * Student name Gracia Redder & Lars Lokhoff
 * Student email graciamichelle@gmail.com
 * Collegekaart 0478660 & 10606165
 * Date 11 - 03 - 2016
 * 
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
    int b1 =0, b2 =0, b3 =0, b4 = 0;

    //check what values B are
    if(c.value[v0] > isovalue)
        b1 = 1;

    if(c.value[v1] > isovalue)
        b2 = 1;

    if(c.value[v2] > isovalue)
        b3 = 1;

    if(c.value[v3] > isovalue)
        b4 = 1;

    //Go through all cases that are shown in figure 10
    if((b1 == 0 && b2 == 0 && b3 == 0 && b4 == 1) || (b1 == 1 && b2 == 1 && b3 == 1 && b4 == 0)) {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v0], c.p[v2], c.value[v0], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v0], c.p[v3], c.value[v0], c.value[v3]);

        return 1;
    }

    if((b1 == 0 && b2 == 0 && b3 == 1 && b4 == 0) || (b1 == 1 && b2 == 1 && b3 == 0 && b4 == 1)) {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v1], c.p[v3], c.value[v1], c.value[v3]);

        return 1;
    }

    if((b1 == 0 && b2 == 1 && b3 == 0 && b4 == 0) || (b1 == 1 && b2 == 0 && b3 == 1 && b4 == 1)) {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v2], c.value[v0], c.value[v2]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v2], c.p[v3], c.value[v2], c.value[v3]);

        return 1;
    }

    if((b1 == 1 && b2 == 0 && b3 == 0 && b4 == 0) || (b1 == 0 && b2 == 1 && b3 == 1 && b4 == 1)) {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v3], c.p[v0], c.value[v2], c.value[v2]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v3], c.value[v2], c.value[v1]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v2], c.p[v3], c.value[v2], c.value[v0]);

        return 1;
    }

    if((b1 == 0 && b2 == 0 && b3 == 1 && b4 == 1) || (b1 == 1 && b2 == 1 && b3 == 0 && b4 == 0)) {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v1], c.p[v3], c.value[v1], c.value[v3]);

        triangles[1].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[1].p[1] = interpolate_points(isovalue, c.p[v0], c.p[v2], c.value[v0], c.value[v2]);
        triangles[1].p[2] = interpolate_points(isovalue, c.p[v0], c.p[v3], c.value[v0], c.value[v3]);


        return 2;
    }

    if((b1 == 0 && b2 == 1 && b3 == 0 && b4 == 1) || (b1 == 1 && b2 == 0 && b3 == 1 && b4 == 0)) {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v0], c.p[v2], c.value[v0], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v0], c.p[v3], c.value[v0], c.value[v3]);

        triangles[1].p[0] = interpolate_points(isovalue, c.p[v2], c.p[v0], c.value[v2], c.value[v0]);
        triangles[1].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        triangles[1].p[2] = interpolate_points(isovalue, c.p[v2], c.p[v3], c.value[v2], c.value[v3]);


        return 2;
    }

    if((b1 == 0 && b2 == 0 && b3 == 1 && b4 == 1) || (b1 == 1 && b2 == 1 && b3 == 0 && b4 == 0)) {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v2], c.p[v0], c.value[v2], c.value[v0]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v2], c.p[v3], c.value[v2], c.value[v3]);

        triangles[1].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[1].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        triangles[1].p[2] = interpolate_points(isovalue, c.p[v1], c.p[v3], c.value[v1], c.value[v3]);


        return 2;
    }

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
    int tetrahedrons[24];
    tetrahedrons[0] = 0;
    tetrahedrons[1] = 1;
    tetrahedrons[2] = 3;
    tetrahedrons[3] = 7;
    
    tetrahedrons[4] = 0;
    tetrahedrons[5] = 7;
    tetrahedrons[6] = 6;
    tetrahedrons[7] = 2;
    
    tetrahedrons[8] = 0;
    tetrahedrons[9] = 1;
    tetrahedrons[10] = 7;
    tetrahedrons[11] = 5;
    
    tetrahedrons[12] = 0;
    tetrahedrons[13] = 4;
    tetrahedrons[14] = 5;
    tetrahedrons[15] = 7;
    
    tetrahedrons[16] = 0;
    tetrahedrons[17] = 3;
    tetrahedrons[18] = 7;
    tetrahedrons[19] = 2;
    
    tetrahedrons[20] = 0;
    tetrahedrons[21] = 7;
    tetrahedrons[22] = 6;
    tetrahedrons[23] = 4;
    
    // for each tetrahedron in the cell, generate the appropriate triangles
    for (int i = 0; i < 24; i+=4)
    {
        // get B values
        int v0 = tetrahedrons[i];
        int v1 = tetrahedrons[i+1];
        int v2 = tetrahedrons[i+2];
        int v3 = tetrahedrons[i+3];
        
        // store triangles at pointer, get number of triangles for count
        num_tri += generate_tetrahedron_triangles(triangles, isovalue, c, v0, v1, v2, v3);
    }
    
    return num_tri;
}
