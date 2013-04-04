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


#endif // FOO_H
