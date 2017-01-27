#include "light.h"

light::light()
{

}

light::light(vec3 _p, vec3 _c){
    this->color = _c;
    this->point = _p;
}
