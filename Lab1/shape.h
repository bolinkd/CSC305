#ifndef SHAPE_H
#define SHAPE_H


class Shape
{
public:
    Shape();
    virtual int Area() = 0;
    int getWidth();
    int getHeight();
private:
    int width;
    int height;
};

#endif // SHAPE_H
