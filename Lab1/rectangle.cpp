#include "rectangle.h"

Rectangle::Rectangle()
{

}

int Rectangle::Area(){
    return Shape::getHeight() * Shape::getWidth();
}

