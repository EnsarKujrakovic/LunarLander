#include "Info.h"

Info::Info()
{
    //ctor
}

Info::~Info()
{
    //dtor
}
void Info::updateInfo(Lander l){
    fuel = l.getFuel();
    positionX = l.getPosition().GetX();
    positionY = l.getPosition().GetY();
    speedX = l.getSpeed().GetX();
    speedY = l.getSpeed().GetY();
    accelerationX = l.getAcceleration().GetX();
    accelerationY = l.getAcceleration().GetY();
    angle = l.getAngle()*180/PI;
}
void Info::render(HDC hdcBuffer){
        SetBkMode(hdcBuffer, TRANSPARENT);
        SIZE sz;
        char str [100];
        SetTextColor(hdcBuffer, RGB(0, 200, 0));
        SetBkColor(hdcBuffer, RGB(0, 0, 0));
        sprintf(str, "Level %d:  %d pts", level, points);
        GetTextExtentPoint32(hdcBuffer, str, strlen(str), &sz);
        TextOut(hdcBuffer, WIDTH-200, 10, str, strlen(str));
        sprintf(str, "Position     x: %d y: %d", positionX, positionY);
        GetTextExtentPoint32(hdcBuffer, str, strlen(str), &sz);
        TextOut(hdcBuffer, WIDTH-200, 25, str, strlen(str));

        sprintf(str, "Velocity     x: %.2f y: %.2f", speedX, speedY);
        GetTextExtentPoint32(hdcBuffer, str, strlen(str), &sz);
        TextOut(hdcBuffer, WIDTH-200, 40, str, strlen(str));

//      sprintf(str, "Acceleration x: %.2f y: %.2f", accelerationX*100, accelerationY*100);
//      GetTextExtentPoint32(hdcBuffer, str, strlen(str), &sz);
//      TextOut(hdcBuffer, WIDTH-200, 55, str, strlen(str));

//      sprintf(str, "Angle:      %.2f", info.angle);
//      GetTextExtentPoint32(hdc, str, strlen(str), &sz);
//      TextOut(hdcBuffer, WIDTH-200, 55, str, strlen(str));

        sprintf(str, "Fuel:       %.2f", fuel);
        if(fuel < 100)  SetTextColor(hdcBuffer, RGB(200, 0, 0));
        GetTextExtentPoint32(hdcBuffer, str, strlen(str), &sz);
        TextOut(hdcBuffer, WIDTH-200, 55, str, strlen(str));
        SetBkMode(hdcBuffer, OPAQUE);
}
