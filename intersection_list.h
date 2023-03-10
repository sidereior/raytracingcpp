#ifndef INTERSECTION_LIST_H
#define INTERSECTION_LIST_H

#include <memory>
#include <vector>
#include "intersection.h"

using std::make_shared;
using std::shared_ptr;

class intersection_list : public intersection
{
public:
    intersection_list() {}
    intersection_list(shared_ptr<intersection> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<intersection> object) { objects.push_back(object); }

    virtual bool hit(const ray &r, double t_min, double t_max, intersection_record &rec) const override;

public:
    std::vector<shared_ptr<intersection>> objects;
};

bool intersection_list::hit(const ray& r, double t_min, double t_max, intersection_record& rec) const
{
    //why is the inherited member not allowed
    intersection_record temp_rec;
    bool intersection_anything = false;
    auto closest_so_far = t_max;
    for (const auto& object : objects)
    {
        if (object->hit(r, t_min, closest_so_far, temp_rec))
        {
            intersection_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return intersection_anything;
}

#endif