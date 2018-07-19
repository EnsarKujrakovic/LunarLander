#ifndef GROUND_H
#define GROUND_H
#include <list>
#include <windows.h>
#include <stdio.h>
#include "resource.h"
#define WIDTH 800
#define HEIGHT 600
class Ground
{
    public:
        Ground();
        virtual ~Ground();
        void generateTerrain();
        void render(HDC);
        std::list<POINT> getPoints();
        bool isPlatform(POINT);
        void setPlatformWidth(double);
        double getPlatformWidth();
        HBITMAP hbmBackground;
        POINT terrainPolygon [100];
        POINT platformPosition;
    private:
        std::list<POINT> points;
        double platformWidth = 100;
        double screenWidth = WIDTH;
        double screenHeight = HEIGHT;


};

#endif // GROUND_H
