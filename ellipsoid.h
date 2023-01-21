#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "intersection.h"
#include "vec3.h"

class sphere : public intersection{
    public:
        sphere() {}
        sphere(point3 c, double r) : center(c), radius(r) {};
        virutal bool hit(const ray& r, double t_min, double t_max, intersection_record& rec) cosnt override;
        public:
            point3 center;
            double radius;
};

bool sphere::intersection(const ray&r, double t_min, double t_max, intersection_record& rec) const{
    vec3 origincenter = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(origincenter, r.direction());
    auto c = origincenter.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if(discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if(root < t_min || t_max < root){
        root = (-half_b + sqrtd) / a;
        if(root < t_min || t_max < root)
            return false;
    }
    //then fix the rec
}
