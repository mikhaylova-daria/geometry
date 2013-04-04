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
    cout <<"c = a+ b = "<< c <<"\n";
    double dist = c.distance(b);
    cout<<"distance between c and b: " <<dist<<"\n";
    double lengt = a.length();
    cout << "length vector a: " << lengt<<"\n";
    Segment<int> seg1(c,b);
    cout<<"отрезок  c-b: " <<seg1<<'\n';
    return 0;
}

