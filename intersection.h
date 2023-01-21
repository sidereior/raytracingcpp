#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "ray.h"

struct intersection_record{ 
    point3 p;
    vec3 normal;
    double t;
};

class intersection{
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, intersection_record& rec) const = 0;
};

#endif