#ifndef LIBR_H
#define LIBR_H
#ifndef MATH_H
    #include <math.h>
    #define MATH_H
#endif
#ifndef IOSTREAM
    #include  <iostream>
    #define IOSTREAM
#endif
template <typename T>
class Point{
    T x;
    T y;

public:
        Point();
        Point(const Point &fpoint);
        Point(const T & _x, const T & _y);
        Point operator + (const Point &);
        Point operator- (const Point &);
        Point& operator= (const Point&);
        bool operator== (const Point &);
        bool operator!=(const Point &);
        double distance(const Point&);
        double length();
        friend std::ostream& operator<<(std::ostream& stream, const Point& pnt){
            stream<<"("<<pnt.x<<"; "<<pnt.y<<")";
            return stream;
        }

        friend std::istream& operator>>(std::istream& stream, Point& pnt){
            stream>>pnt.x;
            stream>>pnt.y;
            return stream;
        }

};


#include "foo.h"
#endif // LIBR_H
