#include "libr.h"
using namespace std;

int main()
{
    Point<int> a;
    Point<int> b;
    cin>>a;
    b = a;
    cout<<"a = "<<a<<" b = "<<b<<"\n";
    a = a + b;
    cout <<"a = "<< a <<"\n";
    double dist = a.distance(b);
    cout<<"distance between a and b: " <<dist<<"\n";
    double lengt = a.length();
    cout << "length vector a" << lengt<<"\n";
    return 0;
}

