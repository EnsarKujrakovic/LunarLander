#include "Ground.h"
#include <random>
Ground::Ground()
{
    BITMAP bitmap;
    hbmBackground = (HBITMAP)LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP5));
}

Ground::~Ground()
{
    //dtor
}
void Ground::generateTerrain(){
    points.clear();
    int maxheight = 0;
    POINT p;
    for (int w = 0; w < screenWidth-80;){
        p.x = w;
        p.y = ((double)rand()/(double)RAND_MAX)*HEIGHT*0.55;
        points.push_back(p);
        w+=((double)rand()/(double)RAND_MAX)*80 + platformWidth;
        if (p.y > maxheight) maxheight = p.y;
    }
    p.x = screenWidth;
    p.y = ((double)rand()/(double)RAND_MAX)*HEIGHT*0.55;
    points.push_back(p);
    if (p.y > maxheight) maxheight = p.y;

    for(std::list<POINT>::iterator p = points.begin(); p != points.end();++p){
        p->y = p->y + (HEIGHT - maxheight - 45);
    }
    std::random_device random_device;
    std::mt19937 engine{random_device()};
    std::uniform_int_distribution<int> dist(0, points.size() - 1);
    std::list<POINT>::iterator pit = points.begin();
    std::advance(pit, dist(engine));
    platformPosition = *pit; pit++;
    p.x = platformPosition.x + platformWidth;
    p.y = platformPosition.y;
    points.insert(pit, p);
    POINT tmp = {0, HEIGHT};
    terrainPolygon[0] = tmp;
    int i = 1;
    for(std::list<POINT>::iterator p = points.begin(); p != points.end();++p){
        terrainPolygon[i++] = *p;
    }
    tmp = {WIDTH, HEIGHT};
    terrainPolygon[i] = tmp;

}
std::list<POINT> Ground::getPoints(){
    return points;
}
bool Ground::isPlatform(POINT p){
    return p.x == platformPosition.x;
}
void Ground::setPlatformWidth(double w){
    platformWidth = w;
}
double Ground::getPlatformWidth(){
    return platformWidth;
}
void Ground::render(HDC hdcBuffer){
    POINT p;
    HPEN pen1 = CreatePen(PS_SOLID, 2, RGB(50, 50, 50));
    HPEN pen2 = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
    HPEN oldpen;
    HBRUSH brush = CreateSolidBrush(RGB(50, 50, 50));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdcBuffer, brush);
    oldpen = (HPEN) SelectObject(hdcBuffer, pen1);

    Polygon(hdcBuffer, terrainPolygon, points.size()+2);

    oldpen = (HPEN) SelectObject(hdcBuffer, pen2);
    MoveToEx(hdcBuffer, platformPosition.x, platformPosition.y, NULL);
    LineTo(hdcBuffer, platformPosition.x+getPlatformWidth(), platformPosition.y);
    DeleteObject(pen1);
    DeleteObject(pen2);
    DeleteObject(oldpen);
    DeleteObject(brush);
    DeleteObject(oldBrush);

}
