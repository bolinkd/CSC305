#ifndef HITABLE_LIST
#define HITABLE_LIST

#include "hitable.h"

class hitable_list : public hitable {
public:
    hitable **list;
    int size;

    hitable_list() {}
    hitable_list(hitable **_list, int _size) { list = _list; size = _size; }
    virtual bool hit(const ray &r, float t_min, float t_max, hitrecord &rec) const;
};

bool hitable_list::hit(const ray &r, float t_min, float t_max, hitrecord &rec) const {
    hitrecord tempRec;
    bool hit = false;
    double closest = t_max;
    for(int i=0;i<this->size;i++){
        if( list[i]->hit(r, t_min, closest, tempRec)) {
            hit = true;
            closest = tempRec.t;
            rec = tempRec;
        }
    }
    return hit;
}

#endif // HITABLE_LIST

