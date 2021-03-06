#ifndef FOO_H
#define FOO_H


//------------ТОЧКА-----------

Point::Point(): x(0), y(0) {;}


Point::Point(const Point &fpoint): x(fpoint.x), y(fpoint.y) {;}


Point::Point(const double & _x, const double & _y):x(_x), y(_y) {;}


Point Point::operator + (const Point &a) const{
    Point b(x + a.x, y + a.y);
    return b;
}


Point Point::operator - (const Point &a)const{
    Point b (x - a.x, y - a.y);
    return b;
}

// перпендикулярное скалярное произведение (векторное произведение)

double Point::operator * (const Point &a) const{
    return (this->x) * a.y - a.x * (this->y);
}


Point Point::operator * (double a) const{
    Point answer;
    answer.x = (this->x) * a;
    answer.y = (this->y)*a;
    return answer;
}


Point& Point::operator = (const Point& other) {
    x=other.x;
    y=other.y;
    return *this;
}


bool Point::operator == (const Point &other) const{
    bool answer = ((x == other.x)&&(y == other.y));
    return answer;
}


bool Point::operator != (const Point &other)const {
    bool answer = !(*this==other);
    return answer;
}


double Point::distance(const Point &a)const{
    double _distance;
    _distance = sqrt((this->x - a.x) * (this->x - a.x) + (this->y - a.y) * (this->y - a.y));
    return _distance;
}


double Point::length()const{
    double _length = sqrt(x*x + y*y);
    return _length;
}





//--------------ОТРЕЗОК--------



Segment::Segment() {;}


Segment::Segment(const Segment &fsegment): p1(fsegment.p1), p2(fsegment.p2) {;}


Segment::Segment(const Point &pnt1,const Point &pnt2): p1(pnt1), p2(pnt2){;}



Segment& Segment::operator=(const Segment& other) {
    p1=other.p1;
    p2=other.p2;
    return *this;
}


bool Segment::operator == (const Segment &other)const{
    bool answer = ((p1==other.p1)&&(p2==other.p2));
    return answer;
}


bool Segment::operator!=(const Segment &other) const{
    bool answer = !(*this==other);
    return answer;
}



double Segment::length(void)const {
    double answer = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y-p2.y));
    return answer;
}


//   Принадлежность точки отрезку
bool Segment::has_point( const Point &pnt)const {
    if ((pnt == this->p1) || (pnt == this->p2)) {
        return true;
    }
     Point a = p2 - p1;      // перенос в начало координат, получаем радиус-вектор (единичный направляющий)
     Point b = pnt - p1;     //перенос в начало координат, получаем радиус-вектор (единичный направляющий)
     double scalar_pr = a * b;
     if ((scalar_pr > 0.0001)||(a.x * b.x < 0) || (a.y * b.y < 0)||(a.length() < b.length())) {
         return false;
     }
     return true;
}

// алгоритм подсмотрен : http://teormech.blogspot.ru/2011/07/blog-post.html

bool Segment::intersects( const Segment &sgm)const {
    Point u (this->p2 - this->p1);
    Point v(sgm.p2 - sgm.p1);
    Point w (this->p1 - sgm.p1);
    double s_1 = v * w;
    double s_2 = v * u;
    double t_1 = u * w;
    double t_2 = u * v;
    double s, t;
     if (s_2 == 0)  {  // отрезки лежат на параллельных прямых, или на одной прямой
         if ((this->has_point(sgm.p1)) || (this->has_point(sgm.p2)) || (sgm.has_point (this->p1)) || (sgm.has_point(this -> p2))){ //если пересекаются
            return true;
         } else {
             return false;
         }
     } else {
         s = - s_1 / s_2;
         t =  t_1 / t_2;
         if (((s >= -1) && (s <= 1)) && ((t >= -1) && (t <= 1))){
             Point point(((this -> p1.x) + (this->p2.x - this->p1.x) * s), ((this -> p1.y) + (this->p2.y - this->p1.y) * s));
             if ((this->has_point(point)) && (sgm.has_point(point))){
                return true;
             } else {
                 return false;
             }
         } else {
             return false;
         }
     }
}

//------ПРЯМАЯ - ПОСТРОЕНИЕ ПО ТОЧКАМ


bool build_of_straight (const Point& x1, const Point & x2,  Straight &str)
{

    str.b = -1;
    if (x1 == x2){
            return false;
    }
    if ((x1.y != x2.y) && (x1.x != x2.x)){
        str.a = (x1.y - x2.y) / (x1.x - x2.x);
        str.c = x2.y - str.a * x2.x;
        if (str.c == 0) {
            str.c = 0;
        }
    } else {
        if (x1.y == x2.y){
            str.a = 0;
            str.c = x1.y;
        } else {
            str.b = 0;
            str.a = 1;
            str.c = -x1.x;
        }
    }
    return true;
}


std::vector< Point> Segment::intersection (const Segment & sgm)const {
    std::vector< Point > answer;
    answer.clear();
    Point  u (this->p2 - this->p1);
    Point  v(sgm.p2 - sgm.p1);
    Point  w (this->p1 - sgm.p1);
    double s_1 = v * w;
    double s_2 = v * u;
    double t_1 = u * w;
    double t_2 = u * v;
    double s, t;
     if (s_2 == 0)  {  // отрезки лежат на параллельных прямых, или на одной прямой
         if ((this->has_point(sgm.p1)) || (this->has_point(sgm.p2)) || (sgm.has_point (this->p1)) || (sgm.has_point(this -> p2))){ //если пересекаются
            if (this->has_point(sgm.p1)){
                answer.push_back(sgm.p1);
            }
            if ((this->p1 != sgm.p1) && (sgm.has_point (this->p1))) {
                answer.push_back(this-> p1);
            }
            if ((this->p2 != sgm.p1) && (this->p2 != this->p1) && (sgm.has_point (this->p2))) {
                answer.push_back(this-> p2);
            }
            if((this->p2 != sgm.p2) && (this->p1 != sgm.p2) && (sgm.p1 != sgm.p2) && (sgm.has_point (this->p2))){
                answer.push_back (sgm.p2);
            }

            return answer;
         } else {
             return answer;
         }
     } else {
         s = - s_1 / s_2;
         t = - t_1 / t_2;
         if (((s >= -1) && (s <= 1)) || ((t >= -1) && (t <= 1))){
             Point point(((this -> p1.x) + (this->p2.x - this->p1.x) * s), ((this -> p1.y) + (this->p2.y - this->p1.y) * s));
             if ((this->has_point(point)) && (sgm.has_point(point))){
                 answer.push_back(point);
                return answer;
             } else {
                 return answer;
             }
         } else {
             return answer;
         }
     }

}




#endif // FOO_H
