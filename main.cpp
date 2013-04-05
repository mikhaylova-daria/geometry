#include "libr.h"
using namespace std;

int main()
{
    Point<double> a;
    Point<double> b;
    cout<< "Координаты точки через пробел: ";
    cin>>a;
    b = a;
    cout<<"a = "<<a<<" b = "<<b<<"\n";
    Point<double> c = a + b;
    cout <<"c = a + b = "<< c <<"\n";
    double dist = c.distance(b);
    cout<<"distance between c and b: " <<dist<<"\n";
    double lengt = a.length();
    cout << "length vector a: " << lengt<<"\n";
    Segment<double> seg1(b, c);
    cout<<"отрезок  c-b: " <<seg1<<'\n';
    cout<<"Координты отрезка, с которым будем пересекать с-b: ";
    Segment<double> seg2;
    cin>>seg2;
    cout<<" отрезки пересекаются(1/0): ";
    cout<<seg1.intersects(seg2)<<'\n';
    Point<double> null(0,0);
    Circle <double> crc1;
    cout << "ведите координаты центра окружности и радиус через пробел: ";
    cin >> crc1;
    /*std::vector< Point<double> > inter_1 = crc1.intersection(seg1);
    cout << "пересечение с отрезком "<<seg1<< " : ";
    if (inter_1.empty()) {
        cout << "пусто"<<'\n';
    } else {
        for (int i = 0; i < inter_1.size(); ++i) {
            cout<<inter_1[i]<<" ";
        }
        cout<<"\n";
    }*/

    return 0;
}

