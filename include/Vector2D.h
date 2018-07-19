#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <algorithm>

class Vector2D
{
    public:
        Vector2D();
        //virtual ~Vector2D();

        void SetAngle(double angle);  // postavlja _x i _y projekcije zavisno od ugla (angle)
        double GetAngle(); // vraca trenutnu vrijednost ugla u radijanima, koristeći projekcije _x i _y
        void SetLength(double length); // postavlja _x i _y projekcije zavisno od duzine (length)
        double GetLength(); // vraca trenutnu duzinu vektora, koristeci projekcije _x i _y
        Vector2D Add(const Vector2D& other); // dodaje vektor other na trenutni i vraca novi vektor
        Vector2D Substract(const Vector2D& other); // oduzima trenutni vektor od vektora other i vraca novi vektor
        Vector2D Multiply(int value); // mnozi trenutni vektor sa konstantom value i vraca novi vektor
        Vector2D Divide(int value); // dijeli trenutni vektor sa konstantom i vraca novi vektor
        void AddTo(const Vector2D& other); // dodaje vektor other na trenutni
        void SubstractFrom(const Vector2D& other); // oduzima vektor other od trenutnog
        void MultiplyBy(int value);     // mnozi trenutni vektor sa skalarom value
        void DivideBy(int value); // dijeli trenutni vektor sa skalarom value
        double GetX();
        double GetY();
        void SetX(double x);
        void SetY(double y);

    private:
        double _x = 0;
        double _y = 0;

};
bool linesIntersect(POINT x1, POINT y1, POINT x2, POINT y2);
int CCW(POINT a, POINT b, POINT c);
bool onSegment(POINT p, POINT q, POINT r);
int orientation(POINT p, POINT q, POINT r);
#endif // VECTOR2D_H
