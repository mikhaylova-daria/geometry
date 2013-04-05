#ifndef FOO_H
#define FOO_H


//------------ТОЧКА-----------
template <typename T>
Point<T>::Point(): x(0), y(0) {;}

template <typename T>
Point<T>::Point(const Point &fpoint): x(fpoint.x), y(fpoint.y) {;}


template <typename T>
Point<T>::Point(const T & _x, const T & _y):x(_x), y(_y) {;}

template <typename T>
Point<T> Point<T>::operator + (const Point &a) {
    Point b(x + a.x, y + a.y);
    return b;
}

template <typename T>
Point<T> Point<T>::operator - (const Point &a){
    Point b (x - a.x, y - a.y);
    return b;
}

// перпендикулярное скалярное произведение
template <typename T>
T Point<T>::operator * (const Point<T> &a) {
    return (this->x) * a.y - a.x * (this->y);
}

template <typename T>
Point<T> Point<T>::operator * (T a) {
    Point answer;
    answer.x = (this->x) * a;
    answer.y = (this->y)*a;
    return answer;
}

template <typename T>
Point<T>& Point<T>::operator = (const Point<T>& other) {
    x=other.x;
    y=other.y;
    return *this;
}

template <typename T>
bool Point<T>::operator == (const Point &other) {
    bool answer = ((x == other.x)&&(y == other.y));
    return answer;
}

template <typename T>
bool Point<T>::operator != (const Point &other) {
    bool answer = !(*this==other);
    return answer;
}

template <typename T>
double Point<T>::distance(const Point<T> &a){
    double _distance;
    _distance = sqrt((this->x - a.x) * (this->x - a.x) + (this->y - a.y) * (this->y - a.y));
    return _distance;
}

template <typename T>
double Point<T>::length(){
    double _length = sqrt(x*x + y*y);
    return _length;
}





//--------------ОТРЕЗОК--------


template <typename T>
Segment<T>::Segment() {;}

template <typename T>
Segment<T>::Segment(const Segment &fsegment): p1(fsegment.p1), p2(fsegment.p2) {;}

template <typename T>
Segment<T>::Segment(const Point<T> &pnt1,const Point<T> &pnt2): p1(pnt1), p2(pnt2){;}


template <typename T>
Segment<T>& Segment<T>::operator=(const Segment& other) {
    p1=other.p1;
    p2=other.p2;
    return *this;
}

template <typename T>
bool Segment<T>::operator == (const Segment &other){
    bool answer = ((p1==other.p1)&&(p2==other.p2));
    return answer;
}

template <typename T>
bool Segment<T>::operator!=(const Segment &other) {
    bool answer = !(*this==other);
    return answer;
}


template <typename T>
double Segment<T>::length(void) {
    double answer = sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
    return answer;
}


template <typename T>
bool Segment<T>::has_point(Point<T> &pnt) {
     Point<T> a = p2 - p1;      // перенос в начало координат, получаем радиус-вектор (единичный направляющий)
     Point<T> b = pnt - p1;     //перенос в начало координат, получаем радиус-вектор (единичный направляющий)
     T scalar_pr = a * b;
     if ((scalar_pr != 0)||(a.x * b.x < 0) || (a.y * b.y < 0)||(a.length() < b.length())) {
         return false;
     }
     return true;
}

// алгоритм подсмотрен : http://teormech.blogspot.ru/2011/07/blog-post.html
template <typename T>
bool Segment<T>::intersects( Segment<T> &sgm) {
    Point <T> u (this->p2 - this->p1);
    Point <T> v(sgm.p2 - sgm.p1);
    Point <T> w (this->p1 - sgm.p1);
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
         t = - t_1 / t_2;
         if (((s >= -1) && (s <= 1)) || ((t >= -1) && (t <= 1))){
             Point<T> point(((this -> p1.x) + (this->p2.x - this->p1.x) * s), ((this -> p1.y) + (this->p2.y - this->p1.y) * s));
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

template <typename T>
bool build_of_straight (Point<T> x1, Point<T> x2, Straight &str)
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

template <typename T>
std::vector< Point <double> > Segment<T>::intersection (Segment sgm) {
    std::vector< Point <T> > answer;
    answer.clear();
    Point <T> u (this->p2 - this->p1);
    Point <T> v(sgm.p2 - sgm.p1);
    Point <T> w (this->p1 - sgm.p1);
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
             Point<T> point(((this -> p1.x) + (this->p2.x - this->p1.x) * s), ((this -> p1.y) + (this->p2.y - this->p1.y) * s));
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

// ---------- ОКРУЖНОСТЬ
/*template <typename T>
std::vector< Point<T> > Circle<T>::intersection(Segment<T> sgm){
        std::vector< Point<T> > answer;
         if (has_point(sgm.p1) && has_point(sgm.p2)) {
             answer.clear();
             return answer;
         }
         Straight str;
         bool change_the_origin = false;
         if (!((center.x  == 0 ) && (center.y == 0))) { // Перенос начала координат в центр окружности
             change_the_origin = true;
             sgm.p1 = sgm.p1 + center;
             sgm.p2 = sgm.p2 + center;
         }
         if (!build_of_straight (sgm.p1, sgm.p2, str)) { // вырожденный отрезок
             if (this->has_point(sgm.p1)) {
                 answer.push_back(sgm.p1);
                 return answer;
             }
         }

         double x_0 (- (str.a * str.c) / (str.a * str.a + str.b * str.b));
         double y_0(- (str.b * str.c) / (str.a * str.a + str.b * str.b));
         if ((str.c * str.c) > (radius * radius * (str.a * str.a + str.b * str.b) + 0,0001)) {
             answer.clear();
             return answer;
         } else {
             double p = str.c * str.c - radius * radius * (str.a * str.a + str.b * str.b);
             if ((-0,0001 < p) && (p < 0,0001)) {
                 Point <double> pnt(x_0, y_0);
                 answer.push_back(pnt);
                 return answer;
             } else {
                 double d = radius * radius - str.c * str.c / (str.a * str.a + str.b * str.b);
                 double mult = sqrt (d / (str.a * str.a + str.b * str.b));
                 Point<double> pnt_1(x_0 + str.b * mult, x_0 - str.b * mult);
                 Point <double> pnt_2 (y_0 - str.a * mult, y_0 + str.a * mult);
                 if (change_the_origin) {
                    pnt_1 = pnt_1 - center;
                     pnt_2 = pnt_2 - center;
                 }
                 answer.push_back(pnt_1);
                 answer.push_back(pnt_2);
                 return answer;
            }
        }
}*/

#endif // FOO_H
