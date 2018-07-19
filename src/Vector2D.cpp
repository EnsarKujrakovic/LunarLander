#include "Vector2D.h"

Vector2D::Vector2D()
{
    //ctor
}

//Vector2D::~Vector2D()
//{
    //dtor
//}
void Vector2D::SetAngle(double angle){
    double l = GetLength();
    _x = l * cos(angle);
    _y = l * sin(angle);
}
double Vector2D::GetAngle(){
    return atan(_y / _x);
}
void Vector2D::SetLength(double length){
    double l = GetLength();
    _x = _x * length / l;
    _y = _y * length / l;
}
double Vector2D::GetLength(){
    return sqrt(_x * _x + _y *_y);
}
Vector2D Vector2D::Add(const Vector2D& other){
    _x = _x + other._x;
    _y = _y + other._y;
    return *this;
}
Vector2D Vector2D::Substract(const Vector2D& other){
    _x = _x - other._x;
    _y = _y - other._y;
    return *this;
}
Vector2D Vector2D::Multiply(int value){
    SetLength(GetLength() * value);
    return *this;
}
Vector2D Vector2D::Divide(int value){
    SetLength(GetLength() * value);
    return *this;
}
void Vector2D::AddTo(const Vector2D& other){
    _x = _x + other._x;
    _y = _y + other._y;
}
void Vector2D::SubstractFrom(const Vector2D& other){
    _x = _x - other._x;
    _y = _y - other._y;
}
void Vector2D::MultiplyBy(int value){
    SetLength(GetLength() * value);
}
void Vector2D::DivideBy(int value){
    SetLength(GetLength() * value);
}
double Vector2D::GetX(){
    return _x;
}
double Vector2D::GetY(){
    return _y;
}
void Vector2D::SetX(double x){
    _x = x;
}
void Vector2D::SetY(double y){
    _y = y;
}
bool linesIntersect(POINT p1, POINT q1, POINT p2, POINT q2){
   // return (CCW(a,b,c)*CCW(a,b,d)<0 && CCW(c,d,b)*CCW(c,d,a)<0);
   // Find the four orientations needed for general and
    // special cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
    return false; // Doesn't fall in any of the above cases
}
int CCW(POINT a, POINT b, POINT c){
    return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}
bool onSegment(POINT p, POINT q, POINT r)
{
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
       return true;
    return false;
}
int orientation(POINT p, POINT q, POINT r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}
