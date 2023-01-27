#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "ray.h"

struct intersection_record{ 
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal){
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class intersection{
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, intersection_record& rec) const = 0;
};

#endif