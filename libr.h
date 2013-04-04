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
        T operator * (const Point &);   //скалярное произведение радиус-векторов
        Point& operator= (const Point&);
        bool operator== (const Point &);
        bool operator!=(const Point &);
        double distance(const Point&);
        double length();        // длина радиус-вектора
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

template <class T>
class Segment{
    Point<T> p1;
    Point<T> p2;
    public:
        Segment();
        Segment(const Segment &src);
        Segment(const Point<T> &pnt1,const Point<T> &pnt2);
        Segment& operator=(const Segment& other);
        bool operator==(const Segment &other);
        bool operator!=(const Segment &other);
        double length(void);
        bool has_point(const Point<T> &pnt);

        friend std::ostream& operator<<(std::ostream& stream, const Segment& sgm){
            stream<<"["<<sgm.p1<<", "<<sgm.p2<<"]";
            return stream;
        }
        friend std::istream& operator>>(std::istream& stream, Segment& sgm){
            stream>>sgm.p1;
            stream>>sgm.p2;
            return stream;
        }
};


#include "foo.h"
#endif // LIBR_H
