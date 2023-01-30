#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "intersection.h"
#include "vec3.h"

class ellipsoid : public intersection{
    public:
        ellipsoid() {}
        ellipsoid(point3 c, double r) : center(c), radius(r) {};
        virtual bool hit(const ray& r, double t_min, double t_max, intersection_record& rec) const override;
        public:
            point3 center;
            double radius;
};

bool ellipsoid::hit(const ray&r, double t_min, double t_max, intersection_record& rec) const{
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
    //ray normals always point outward
    //then fix the rec
   

    //use intersection record and not hit record
    bool front_face;
    if(dot(r.direction(), rec.normal) < 0){
        front_face = true;
        rec.normal = rec.normal;
    } else {
        front_face = false;
        rec.normal = -rec.normal;
    }
    //shoudl this come beforeor after the if statement?
    //or is if statement needed at all
    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    return true;
}

#endif