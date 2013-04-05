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


class Point{
        double x;
        double y;
public:
    friend class Segment;
    friend class AFigure;
    friend class Circle;
    friend bool build_of_straight (Point x1, Point x2, Straight &str);
        Point();
        Point(const Point &fpoint);
        Point(const double & _x, const double & _y);
        Point operator + (const Point &);
        Point operator- (const Point &);
        double operator * (const Point &);   //скалярное произведение радиус-векторов
        Point operator * (double); // растяжение радиус - вектора
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


class Segment{
    Point p1;
    Point p2;
    public:
        friend class AFigure;
        friend class Circle;
        Segment();
        Segment(const Segment &);
        Segment(const Point &pnt1,const Point &pnt2);
        Segment& operator=(const Segment& other);
        bool operator==(const Segment &other);
        bool operator!=(const Segment &other);
        double length(void);
        bool has_point(Point &pnt);
        bool intersects( Segment &sgm); //есть ли пересечение
        std::vector< Point > intersection (Segment arg);

        friend std::ostream& operator<<(std::ostream& stream, const Segment& sgm){
            stream<<"["<<sgm.p1<<", "<<sgm.p2<<"]";
            return stream;
        }
        friend std::istream& operator>>(std::istream& stream, Segment& sgm){
            stream>>sgm.p1;
            stream>>sgm.p2;
            return stream;
        }
        friend bool build_of_straight (Point x1, Point x2, Straight &str);
};


bool build_of_straight (Point , Point , Straight &);


class AFigure{
public:
    AFigure()  {;}
    ~AFigure() {;}
    virtual bool has_point(Point &pnt) = 0;
    virtual std::vector< Point > intersection(Segment sgm) = 0;
};


class Circle: public AFigure
{
    Point center;
    double radius;
public:
    Circle(): center(0,0), radius(0) {;}
    Circle(Point _center, double _radius): center (_center), radius(_radius){;}
    Circle(Point _center, Point _belonging): center(_center){
        radius=sqrt((_center.x - _belonging.x)*(_center.x - _belonging.x)+(_center.y - _belonging.y)*(_center.y - _belonging.y));
    }
    ~Circle(){;}

    virtual bool has_point(Point &pnt) {
        Segment sgm(center,pnt);
        return (sgm.length() <= radius);
    }

    virtual std::vector< Point > intersection(Segment sgm){
         std::vector< Point > answer;
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
                 Point  pnt(x_0, y_0);
                 answer.push_back(pnt);
                 return answer;
             } else {
                 double d = radius * radius - str.c * str.c / (str.a * str.a + str.b * str.b);
                 double mult = sqrt (d / (str.a * str.a + str.b * str.b));
                 Point pnt_1(x_0 + str.b * mult, y_0 - str.a * mult);
                 Point pnt_2 (x_0 - str.b * mult, y_0 + str.a * mult);
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
