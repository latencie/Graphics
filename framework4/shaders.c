/* Computer Graphics and Game Technology, Assignment Ray-tracing
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
#include <stdio.h>
#include <stdlib.h>
#include "shaders.h"
#include "perlin.h"
#include "v3math.h"
#include "intersection.h"
#include "scene.h"
#include "quat.h"
#include "constants.h"

// shade_constant()
//
// Always return the same color. This shader does no real computations
// based on normal, light position, etc. As such, it merely creates
// a "silhouette" of an object.

vec3
shade_constant(intersection_point ip)
{
    return v3_create(1, 0, 0);
}

vec3
shade_matte(intersection_point ip)
{
    float total_intensity = 0;
    float inproduct;
    vec3 light_vector, off_set_vector;
    
    // for each light source, calculate inproduct light source and normal ip.n
    for (int j = 0; j < scene_num_lights; j ++)
    {
        light_vector = v3_normalize(v3_subtract(scene_lights[j].position, ip.p));
        inproduct = v3_dotprod(ip.n, light_vector);

        //This vector determines the offset for the point to shade
        off_set_vector = v3_add(v3_multiply(ip.n, 0.0001), ip.p);

        if (inproduct > 0)
        {
            if(!shadow_check(off_set_vector, scene_lights[j].position)) {
                total_intensity += inproduct * scene_lights[j].intensity;
            }
        }
    } 
    
    vec3 shade = v3_create(1, 1, 1); 
    shade = v3_multiply(shade, total_intensity);
    
    return shade;
}

vec3
shade_blinn_phong(intersection_point ip)
{
    float k_d = 0.8;
    float k_s = 0.5;
    float total_intensity = 0.0;
    float phong = 0.0;
    float inproduct;
    int alfa = 50;
    vec3 c_d = v3_create(1, 0, 0);
    vec3 c_s = v3_create(1, 1, 1);
    vec3 c_f, off_set_vector, light_vector;

    for(int i = 0; i < scene_num_lights; i++) {
        //Calculate the light direction vector
        light_vector = v3_normalize(v3_subtract(scene_lights[i].position, ip.p));

        //Calculate the offset vector for the shade
        off_set_vector = v3_add(v3_multiply(ip.n, 0.0001), ip.p);

        //check for negative dot product 
        inproduct = v3_dotprod(ip.n, light_vector);

        if(inproduct > 0) {
            //Do the shadow ray tracing check
            if(!shadow_check(off_set_vector, scene_lights[i].position)) {
                total_intensity += inproduct * scene_lights[i].intensity;
            }
        }

        //Now we calculate the half way vector h
        vec3 h = v3_normalize(v3_add(ip.i, light_vector));

        //calculate the phong component
        phong += pow(v3_dotprod(ip.n, h), alfa) * scene_lights[i].intensity;
    }

    c_f = v3_add(v3_multiply(c_d, scene_ambient_light + k_d * total_intensity), v3_multiply(c_s, k_s * phong));
    
    return c_f;
}

vec3
shade_reflection(intersection_point ip)
{
    return v3_create(1, 0, 0);
}

// Returns the shaded color for the given point to shade.
// Calls the relevant shading function based on the material index.
vec3
shade(intersection_point ip)
{
  switch (ip.material)
  {
    case 0:
      return shade_constant(ip);
    case 1:
      return shade_matte(ip);
    case 2:
      return shade_blinn_phong(ip);
    case 3:
      return shade_reflection(ip);
    default:
      return shade_constant(ip);

  }
}

// Determine the surface color for the first object intersected by
// the given ray, or return the scene background color when no
// intersection is found
vec3
ray_color(int level, vec3 ray_origin, vec3 ray_direction)
{
    intersection_point  ip;

    // If this ray has been reflected too many times, simply
    // return the background color.
    if (level >= 3)
        return scene_background_color;

    // Check if the ray intersects anything in the scene
    if (find_first_intersection(&ip, ray_origin, ray_direction))
    {
        // Shade the found intersection point
        ip.ray_level = level;
        return shade(ip);
    }

    // Nothing was hit, return background color
    return scene_background_color;
}
