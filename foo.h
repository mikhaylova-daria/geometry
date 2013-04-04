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

#endif // FOO_H
