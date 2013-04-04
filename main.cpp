#include "libr.h"
using namespace std;

int main()
{
    Point<int> a;
    Point<int> b;
    cout<< "Координаты точки через пробел: ";
    cin>>a;
    b = a;
    cout<<"a = "<<a<<" b = "<<b<<"\n";
    Point<int> c = a + b;
    cout <<"c = a + b = "<< c <<"\n";
    double dist = c.distance(b);
    cout<<"distance between c and b: " <<dist<<"\n";
    double lengt = a.length();
    cout << "length vector a: " << lengt<<"\n";
    Segment<int> seg1(b, c);
    cout<<"отрезок  c-b: " <<seg1<<'\n';
    cout<<"Координты отрезка, с которым будем пересекать с-b: ";
    Segment<int> seg2;
    cin>>seg2;
    cout<<" отрезки пересекаются(1/0): ";
    cout<<seg1.intersects(seg2);
    return 0;
}

