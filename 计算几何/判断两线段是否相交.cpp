#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
struct Point {
    double x,y;
    Point(){}
    Point(double x,double y) {
        this -> x = x;
        this -> y = y;
    }
    Point operator+(Point a)
    {
        return Point(x + a.x,y + a.y);
    }
    Point operator-(Point a)
    {
        return Point(x - a.x,y - a.y);
    }
    Point operator*(double t)
    {
        return Point(x * t,y * t);
    }
    double operator*(Point a)
    {
        return x * a.y - y * a.x;
    }
    Point operator/(double t)
    {
        return Point(x / t,y / t);
    }
    double operator^(Point a)
    {
        return x * a.x + y * a.y;
    }
    double vl()
    {
        return sqrt(x * x + y * y);
    }
}sta,ed;


double dis(Point p1,Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}


struct Line {
    Point a,b;
    Line(){};
    Line(Point a,Point b) {
        this -> a = a;
        this -> b = b;
    }
    double Len() {
        return dis(a,b);
    }
}a[maxn];

Point Intersection(Line X,Line Y) { //算直线交点
    Point v = X.a - X.b;
    Point w = Y.a - Y.b;
    Point u = X.a - Y.a;
    double t = (w * u) / (v * w);
    return X.a + v * t;
}

int same(double x,double y) {
    if(fabs(x - y) < eps) return true;
    return false;
}

int sign(double x) {
    if(x < -eps) {
        return -1;
    } else if(x > eps) return 1;
    return 0;
}

bool judge(Line line1, Line line2) { //判断两线段是否相交
    Point AD = line1.a - line2.a;
    Point AC = line1.a - line2.b;
    Point AB = line1.a - line1.b;
        
    Point CA = line2.a - line1.a;
    Point CB = line2.a - line1.b;
    Point CD = line2.a - line2.b;
    if((CD * CA) * (CD * CB) <= 0 && (AB * AC) * (AB * AD) <= 0) {
        return true;
    }
    return false;
}