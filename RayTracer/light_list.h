#ifndef LIGHT_LIST
#define LIGHT_LIST

#include "hitable.h"
#include "light.h"

class light_list {
public:
    light **list;
    int size;

    light_list() {}
    light_list(light **_list, int _size) { list = _list; size = _size; }

    virtual bool hit(hitrecord &orec, float t_min, float t_max, hitrecord &lrec, hitable *world) const;
};

bool light_list::hit(hitrecord &orec, float t_min, float t_max, hitrecord &lrec, hitable *world) const {
    hitrecord tempRec;
    bool hit = false;
    for(int i=0;i<this->size;i++){
        if( list[i]->hit(orec, tempRec, world)) {
            hit = true;
            lrec = tempRec;
        }
    }
    return hit;
}


#endif // LIGHT_LIST

