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

        // this vector determines the offset for the point to shade
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
        
        // calculate the offset vector for the shade check
        off_set_vector = v3_add(v3_multiply(ip.n, 0.0001), ip.p);

        // do the shadow ray tracing check early to prevent unnecessary calculations
        if(!shadow_check(off_set_vector, scene_lights[i].position)) {
        
            // calculate the light direction vector
            light_vector = v3_normalize(v3_subtract(scene_lights[i].position, ip.p));

            // check for negative dot product 
            inproduct = v3_dotprod(ip.n, light_vector);

            if(inproduct > 0) {            
                total_intensity += inproduct * scene_lights[i].intensity;
            }
        }

        // calculate the half way vector h
        vec3 h = v3_normalize(v3_add(ip.i, light_vector));

        // calculate the phong component
        phong += pow(v3_dotprod(ip.n, h), alfa) * scene_lights[i].intensity;
    }

    c_f = v3_add(v3_multiply(c_d, scene_ambient_light + k_d * total_intensity), v3_multiply(c_s, k_s * phong));
    
    return c_f;
}


vec3
get_reflected_colour(int level, vec3 lightvector, vec3 position, vec3 normal)
{
    // calculate in which direction light is reflected
    float inproduct = v3_dotprod(lightvector, normal);
    vec3 reflect_vector = v3_subtract(v3_multiply(normal, 2*inproduct), lightvector);
    
    // return reflected colour
    return ray_color(level+1, position, reflect_vector);
}


vec3
shade_reflection(intersection_point ip)
{
    float shade_factor = 0.75;
    float reflect_factor = 0.25;
    vec3 shade, light_vector, reflect_shade = v3_create(0, 0, 0);
    float inproduct;
    
    // calculate 75% matte reflection at this intersection point
    shade = v3_multiply(shade_matte(ip), shade_factor);

    // if ray_level is 0, this is a camera ray
    if (ip.ray_level == 0)
    {
        // for each light source, calculate reflection from other surface
        for (int j = 0; j < scene_num_lights; j ++)
        {
            // check if light source reaches surface
            light_vector = v3_normalize(v3_subtract(scene_lights[j].position, ip.p));
            inproduct = v3_dotprod(light_vector, ip.n);

            if (inproduct > 0)
            {
                // find reflected colour, add to total
                reflect_shade = v3_add(reflect_shade, get_reflected_colour(ip.ray_level, light_vector, ip.p, ip.n));
            }
        }
    }
    
    // if ray_level is higher than 0, this is a reflected light ray
    else
    {   
        // only this reflected ray can cause another reflection
        // TODO is ip.i already a normalized direction vector?
        light_vector = v3_normalize(v3_subtract(ip.i, ip.p));
        reflect_shade = get_reflected_colour(ip.ray_level, light_vector, ip.p, ip.n);
    }
    
    return v3_add(shade, v3_multiply(v3_normalize(reflect_shade), reflect_factor));;
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
