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
#ifndef VECTOR
    #include <vector>
    #define VECTOR
#endif

struct Straight{
    double a;
    double b;
    double c;
};

template <typename T> class Sigment;
template <typename T>
class Point{
public:
    T x;
    T y;
public:
        Point();
        Point(const Point &fpoint);
        Point(const T & _x, const T & _y);
        Point operator + (const Point &);
        Point operator- (const Point &);
        T operator * (const Point &);   //скалярное произведение радиус-векторов
        Point operator * (T); // растяжение радиус - вектора
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
        friend class Sigment<T>;
};

template <typename T>
class Segment{
public:
    Point<T> p1;
    Point<T> p2;
    public:
        Segment();
        Segment(const Segment &);
        Segment(const Point<T> &pnt1,const Point<T> &pnt2);
        Segment& operator=(const Segment& other);
        bool operator==(const Segment &other);
        bool operator!=(const Segment &other);
        double length(void);
        bool has_point(Point<T> &pnt);
        bool intersects( Segment<T> &sgm); //есть ли пересечение
        std::vector< Point <double> > intersection (Segment arg);

        friend std::ostream& operator<<(std::ostream& stream, const Segment& sgm){
            stream<<"["<<sgm.p1<<", "<<sgm.p2<<"]";
            return stream;
        }
        friend std::istream& operator>>(std::istream& stream, Segment& sgm){
            stream>>sgm.p1;
            stream>>sgm.p2;
            return stream;
        }
        friend bool build_of_straight (Point<T> x1, Point<T> x2, Straight &str);
};

template <typename T>
bool build_of_straight (Point <T> , Point<T> , Straight &);

template <typename T>
class AFigure{
public:
    AFigure()  {;}
    ~AFigure() {;}
   // virtual bool has_point() = 0;
   // virtual std::vector< Point<T> > intersection() = 0;
};

template <typename T>
class Circle: public AFigure<T>
{
    Point<T> center;
    double radius;
public:
    Circle()
    {
        center.x=0;
        center.y=0;
        radius=0;
    }
    Circle(Point<T> _center, double _radius){
        center=_center;
        radius=_radius;
    }
    Circle(Point<T> _center, Point<T> _belonging): center(_center){
        radius=pow((_center.x-_belonging.x)*(_center.x-_belonging.x)+(_center.y-_belonging.y)*(_center.y-_belonging.y),0.5);
    }
    ~Circle(){;}

    bool has_point(Point<T> &pnt) {
        Segment<T> sgm(center,pnt);
        return (sgm.length() <= radius);
    }

    std::vector< Point<T> > intersection(Segment<T> sgm){
         std::vector< Point<T> > answer;
         if (has_point(sgm.p1) && has_point(sgm.p2)) {
             answer.clear();
             return answer;
         }
         Straight str;
         bool change_the_origin = false;
         if (!((center.x  == 0 ) && (center.y == 0))) { // Перенос начала координат в центр окружности
             change_the_origin = true;
             sgm.p1 = sgm.p1 - center;
             sgm.p2 = sgm.p2 - center;
         }
         if (!build_of_straight (sgm.p1, sgm.p2, str)) { // вырожденный отрезок
             if (this->has_point(sgm.p1)) {
                 answer.push_back(sgm.p1);
                 return answer;
             }
         }
         double x_0 (- (str.a * str.c) / (str.a * str.a + str.b * str.b));
         double y_0(- (str.b * str.c) / (str.a * str.a + str.b * str.b));
         if ((str.c * str.c) > (radius * radius * (str.a * str.a + str.b * str.b) + 0,0000001)) {
             answer.clear();
             return answer;
         } else {
             double p = str.c * str.c - radius * radius * (str.a * str.a + str.b * str.b);
             if ((-0,0000001 < p) && (p < 0,0000001)) {
                 Point <double> pnt(x_0, y_0);
                 answer.push_back(pnt);
                 return answer;
             } else {
                 double d = radius * radius - str.c * str.c / (str.a * str.a + str.b * str.b);
                 double mult = sqrt (d / (str.a * str.a + str.b * str.b));
                 Point<double> pnt_1(x_0 + str.b * mult, y_0 - str.a * mult);
                 Point <double> pnt_2 (x_0 - str.b * mult, y_0 + str.a * mult);
                 if (change_the_origin) {
                    pnt_1 = pnt_1 + center;
                    pnt_2 = pnt_2 + center;
                    sgm.p1 = sgm.p1 + center;
                    sgm.p2 = sgm.p2 + center;
                 }
                 if (sgm.has_point(pnt_1)) {
                    answer.push_back(pnt_1);
                 }
                 if (sgm.has_point(pnt_2)) {
                     answer.push_back(pnt_2);
                 }
                 return answer;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& stream, Circle circ){
        stream<<"Центр:"<<circ.center<<", радиус:"<<circ.radius;
        return stream;
    }
    friend std::istream& operator>>(std::istream& stream, Circle& circ){
        stream>>circ.center;
        stream>>circ.radius;
        return stream;
    }
};




#include "foo.h"
#endif // LIBR_H
