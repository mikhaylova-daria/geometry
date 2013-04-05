#include "libr.h"
using namespace std;

int main()
{
    Point<double> a;
    Point<double> b;
    Point<double> c;
    cout<< "Координаты точки a через пробел: ";
    cin>>a;
   /* b = a;
    cout<<"a = "<<a<<" b = "<<b<<"\n";
    Point<double> c = a + b;
    cout <<"c = a + b = "<< c <<"\n";
    double dist = c.distance(b);
    cout<<"distance between c and b: " <<dist<<"\n";
    double lengt = a.length();
    cout << "length vector a: " << lengt<<"\n";*/
    cout<< "Координаты точки c через пробел: ";
    cin>>c;
    Segment<double> seg1(a, c);
    cout<<"отрезок  a-c: " <<seg1<<'\n';
    cout<<"Координты отрезка, с которым будем пересекать с-b: ";
    Segment<double> seg2;
    cin>>seg2;
    cout<<" отрезки пересекаются: ";
    std::vector <Point <double> > inter_0;
    inter_0 = seg1.intersection(seg2);
    if (inter_0.empty()) {
        cout << "пусто"<<'\n';
    } else {
        for (int i = 0; i < inter_0.size(); ++i) {
            cout<<inter_0[i]<<" ";
        }
        cout<<"\n";
    }
   // cout<<seg1.intersects(seg2)<<'\n';
    Point<double> null(0,0);
    Circle <double> crc1;
    cout << "ведите координаты центра окружности и радиус через пробел: ";
    cin >> crc1;
    std::vector< Point<double> > inter_1 = crc1.intersection(seg1);
    cout << "пересечение с отрезком "<<seg1<< " : ";
    if (inter_1.empty()) {
        cout << "пусто"<<'\n';
    } else {
        for (int i = 0; i < inter_1.size(); ++i) {
            cout<<inter_1[i]<<" ";
        }
        cout<<"\n";
    }

    return 0;
}

