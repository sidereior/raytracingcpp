
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "intersection.h"
#include "intersection_list.h"
#include "ellipsoid.h"
#include <iostream>

int main() {
    const auto aspect_ratio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    auto viewport_height = 2.0;
    auto vertical = vec3(0, viewport_height, 0);
    auto origin = point3(0,0,0);
    auto viewport_width = aspect_ratio * viewport_height;
    auto horizontal = vec3(viewport_width, 0, 0);
    auto focal_length = 1.0;
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0,0,focal_length);
    intersection_list world;
    world.add(std::make_shared<ellipsoid>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<ellipsoid>(point3(0,-100.5,-1), 100));
    //rows written top to bottom
    //pixels in each row written left to right
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for(int j = image_height-1; j >= 0; --j) {
        //((int)((((image_height-1)/j)))/2.55)
       std::cerr << "\rprogress: " << j << ' ' << std::flush;
        for(int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r,world);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\ncomplete\n";
}

color ray_color(const ray& r, const intersection& world){
    intersection_record rec;
    if(world.hit(r, 0, 2147483645, rec)){
        return 0.5*(rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}



double hit_sphere(const point3& center, double radius, const ray& r){
    //this can be simplified later
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc,oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if (discriminant < 0){
        return -1.0;
    } else {
        return (-b - sqrt(discriminant)) / (2.0*a);
    }

    //return (discriminant > 0);
    /*
    if(discriminant < 0)
    {
        return -1.0;
    }
    else {
        return (-b - sqrt(discriminant)) / (2.0*a);
    }
    */
}

