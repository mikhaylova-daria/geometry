#ifndef FOO_H
#define FOO_H

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
Point<T> Point<T>::operator- (const Point &a){
    Point b (x - a.x, y - a.y);
    return b;
}


template <typename T>
T Point<T>::operator*(const Point<T> &a) {
    return (this->x)*a.y - a.x*(this->y);
}

template <typename T>
Point<T>& Point<T>::operator= (const Point<T>& other) {
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


template <class T>
Segment<T>::Segment() {;}

template <class T>
Segment<T>::Segment(const Segment &fsegment): p1(fsegment.p1), p2(fsegment.p2) {;}

template <class T>
Segment<T>::Segment(const Point<T> &pnt1,const Point<T> &pnt2): p1(pnt1), p2(pnt2){;}


template <class T>
Segment<T>& Segment<T>::operator=(const Segment& other) {
    p1=other.p1;
    p2=other.p2;
    return *this;
}

template <class T>
bool Segment<T>::operator == (const Segment &other){
    bool answer = ((p1==other.p1)&&(p2==other.p2));
    return answer;
}

template <class T>
bool Segment<T>::operator!=(const Segment &other) {
    bool answer = !(*this==other);
    return answer;
}


template <class T>
double Segment<T>::length(void) {
    double answer = sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y));
    return answer;
}


template <class T>
bool Segment<T>::has_point(const Point<T> &pnt) {
     Point<T> a = p2 - p1;      // перенос в начало координат, получаем радиус-вектор
     Point<T> b = pnt - p1;     //перенос в начало координат, получаем радиус-вектор
     T scalar_pr = a * b;
     if ((scalar_pr != 0)||(a.x * b.x < 0) || (a.y * b.y < 0)||(a.length() < b.length())) {
         return false;
     }
     return true;
}



#endif // FOO_H
