#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (abs(a-b) < eps) return 0;
    return a-b;
}

struct Point
{
    double x, y;
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    
    Point operator+(Point b) {
        return Point(x + b.x, y + b.y);
    }
    
    Point operator-(Point b) {
        return Point(x - b.x, y - b.y);
    }
    
    Point operator*(double fac) {
        return Point(x * fac, y * fac);
    }
    
    Point operator/(double fac) {
        return Point(x / fac, y / fac);
    }

    double operator&(Point b) { return x * b.x + y * b.y; }
    // dot operator
    double operator^(Point b) { return x * b.y - y * b.x; }
    // cross operator
    
    bool operator==(Point b) const {
        return fcmp(x, b.x) == 0 && fcmp(y, b.y) == 0;
    }
    
    bool operator<(Point b) const {
        if (fcmp(x, b.x) == 0)
            return y < b.y;
        return x < b.x;
    }

    double norm() { return *this & *this; }    // 歐 式 長 度 平 方
    Point prep() { return Point(-y, x); } // 左 旋 直 角 法 向 量
};

// for pointOnSegment
bool collinearity(Point p1, Point p2, Point p3) {
    return fcmp((p1 - p3) ^ (p2 - p3)) == 0;
}

// for pointOnSegment
bool btw(Point p1, Point p2, Point p3) {
    return fcmp((p1 - p3) & (p2 - p3)) <= 0;
}

bool pointOnSegment(Point p1, Point p2, Point p3) {
    return collinearity(p1, p2, p3) && btw(p1, p2, p3);
}

struct Line
{
    Point sp, ep;
    
    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}
    Line(double x1, double y1, double x2, double y2) : sp(Point(x1, y1)), ep(Point(x2, y2)) {}
    
    Point vec() { return ep - sp; }

    double ori(Point src) { 
        return (ep - sp) ^ (src - sp);
    }
    
    // Regard a line as a function
    Point operator()(double x) { // A + AB * x = the point position.
        return sp + vec() * x;
    }

    bool isSegProperIntersection(Line l) {
        return l.ori(sp) * l.ori(ep) < 0 and ori(l.sp) * ori(l.ep) < 0;
    }

    bool isSegIntersection(Line l) {
        // hsp = 1, hep = 2, lsp = 3, lep = 4
        double hlsp = ori(l.sp);
        double hlep = ori(l.ep);
        double lhsp = l.ori(sp);
        double lhep = l.ori(ep);
        if(fcmp(hlsp, 0) == 0 and fcmp(hlep,0) == 0)
            return isPointOnSeg(l.sp) || isPointOnSeg(l.ep) || l.isPointOnSeg(sp) || l.isPointOnSeg(ep);

        return fcmp(hlsp * hlep) <= 0 and fcmp(lhsp * lhep) <= 0;
    }
    
    bool isPointOnSegProperly(Point p) {
        return fcmp(ori(p)) == 0 and fcmp(((sp - p) & (ep - p))) < 0;
    }
    bool isPointOnSeg(Point p) {
        return fcmp(ori(p)) == 0 and fcmp((sp - p) & (ep - p)) <= 0;
    }

    // notice you should check Segment intersect or not;
    // be careful divided by 0, like l entirely on Line
    Point getIntersection(Line l){
        double hlsp = -ori(l.sp);
        double hlep = ori(l.ep);
        return ((l.sp * hlep) + (l.ep * hlsp)) / (hlsp + hlep);
    }
    
    Point projection(Point p) {
        return operator()(((p - sp) & vec()) / vec().norm());
    }
    
    double distance(Point p) {
        return Line(projection(p), p).vec().norm();
    }
};

// sort by radian, the left is smaller for parallel lines
auto radCmp = [](Line A, Line B) 
{
    Point a = A.vec(), b = B.vec();
    auto sgn = [](Point t) { return (t.y == 0 ? t.x : t.y) < 0; }; // 0 for in [0, pi), 1 for [pi, 2*pi).
    if (sgn(a) != sgn(b)) // in different side
        return sgn(a) < sgn(b);
    else if (abs(a ^ b) == 0) // same 
        return B.ori(A.sp) > 0;
    return (a ^ b) > 0;
};


// 以原點極角排序逆時針排一圈。最好用整數做，不然應該會有誤差
// 以某點須對點集合做offset 處理
inline bool up (point p) {
  return p.y > 0 or (p.y == 0 and p.x >= 0);
}

sort(v.begin(), v.end(), [] (point a, point b) {
  return up(a) == up(b) ? a.x * b.y > a.y * b.x : up(a) < up(b);
});