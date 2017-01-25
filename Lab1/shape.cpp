#include "shape.h"

Shape::Shape()
{
    this->height = 10;
    this->width = 10;
}

int Shape::getHeight(){
    return this->height;
}

int Shape::getWidth(){
    return this->width;
}
