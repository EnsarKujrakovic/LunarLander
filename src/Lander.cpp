#include "Lander.h"

Lander::Lander()
{
    BITMAP bitmap;
    hbmLander = (HBITMAP)LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));
    hbmLanderMask = (HBITMAP)LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP2));

    hbmExplosion = (HBITMAP)LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP3));
    hbmExplosionMask = (HBITMAP)LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP4));

    GetObject(hbmLander, sizeof(BITMAP), &bitmap);
    landerWidth = bitmap.bmWidth/3;
    landerHeight = bitmap.bmHeight;
}
void Lander::initialize(){

    acceleration.SetX(0.00001);
    acceleration.SetY(0);
    speed.SetX(0.01);
    speed.SetY(0);
    position.SetX(50);
    position.SetY(50);
    POINT a = {position.GetX()-landerWidth/2, position.GetY()-landerHeight/2},
          b = {position.GetX()+landerWidth/2, position.GetY()-landerHeight/2},
          c = {position.GetX()-landerWidth/2, position.GetY()+landerHeight/2},
          d = {position.GetX()+landerWidth/2, position.GetY()+landerHeight/2};
    points[0] = a;
    points[1] = b;
    points[2] = c;
    points[3] = d;
    angle = 0;
    da = 0;
}
Lander::~Lander()
{
    //dtor
}
void Lander::rotate(double ang){
    POINT a = {position.GetX()-landerWidth/2, position.GetY()-landerHeight/2},
          b = {position.GetX()+landerWidth/2, position.GetY()-landerHeight/2},
          c = {position.GetX()-landerWidth/2, position.GetY()+landerHeight/2},
          d = {position.GetX()+landerWidth/2, position.GetY()+landerHeight/2};
    points[0] = a;
    points[1] = b;
    points[2] = c;
    points[3] = d;
    setAngle(ang+getAngle());
    POINT center;
    center.x = position.GetX();
    center.y = position.GetY();
    for(int i = 0; i < 4; ++i){
        double tempX = points[i].x - center.x;
        double tempY = points[i].y - center.y;

        double rotatedX = tempX*cos(getAngle()) - tempY*sin(getAngle());
        double rotatedY = tempX*sin(getAngle()) + tempY*cos(getAngle());

        points[i].x = rotatedX + center.x;
        points[i].y = rotatedY + center.y;
    }
}
bool Lander::successfulLanding(){
    return succesfulLanding;
}
bool Lander::outOfFuel(){
    return fuel <= 0;
}

Vector2D Lander::getPosition(){
    return position;
}
Vector2D Lander::getSpeed(){
    return speed;
}
Vector2D Lander::getAcceleration(){
    return acceleration;
}
double Lander::getFuel(){
    return fuel;
}
double Lander::getAngle(){
    return angle;
}
void Lander::setPosition(Vector2D p){
    position = p;
}
void Lander::setSpeed(Vector2D s){
    speed = s;
}
void Lander::setAcceleration(Vector2D a){
    acceleration = a;
}
void Lander::setFuel(double f){
    fuel = f;
}
void Lander::burnFuel(double fbr){
    fuel -= fbr;
    if(fuel <= 0) fuel = 0;
}
void Lander::setAngle(double a){
    angle = a;
    if ((angle >= 2*PI) || (angle <= -2*PI)) angle = fmod(angle, 2*PI);
    if (angle < 0) angle = 2*PI + angle;
}
void Lander::updatePosition(){
    speed.SetY(speed.GetY()+0.001667);
    if(KEYDOWN(VK_UP)){
        if(!outOfFuel()){
            acceleration.SetLength(0.01);
            speed.AddTo(acceleration);
            burnFuel(0.5);
        }
    }
    position.AddTo(speed);

    rotate(0);
    rotate(da);
    if(KEYDOWN(VK_RIGHT)){
        da = PI/720;
        if(!outOfFuel()){
            rotate(PI/180);
            burnFuel(0.05);
        }
    }
    if(KEYDOWN(VK_LEFT)){
        da = -PI/720;
        if(!outOfFuel()){
            rotate(-PI/180);
            burnFuel(0.05);
        }
    }
    if(KEYDOWN(VK_SPACE)){
        if(!outOfFuel()){
            if (angle > (3*PI/2-PI/10)&& angle< (3*PI/2+PI/30)){
            rotate(-angle+3*PI/2);
            da = 0;
            }
        }
    }
     acceleration.SetAngle(angle);
}
void Lander::render(HDC hdcBuffer, HDC hdcMem, bool landed){
 //   HBITMAP hbmOldMem = (HBITMAP)SelectObject(hdcMem, hbmLander);
 //   PlgBlt(hdcBuffer, points, hdcMem, 0, 0, landerWidth, landerHeight, hbmLanderMask, 0, 0);
 //   DeleteObject(hbmOldMem);
    if(!(landed && !succesfulLanding)){
        static int i = 0;
        int j = 0;
        if (i < 10) j = 1; else j = 2;
        if(KEYDOWN(VK_UP) && !outOfFuel()) j = 0;
        HBITMAP hbmOldMem = (HBITMAP)SelectObject(hdcMem, hbmLander);
        PlgBlt(hdcBuffer, points, hdcMem, j*landerWidth, 0, landerWidth, landerHeight, hbmLanderMask, 0*landerWidth, 0);
        DeleteObject(hbmOldMem);
        i+=1; if(i == 20) i = 0;
    }else{
        if(explosion){
            static int k = 0;
            HBITMAP hbmOldMem = (HBITMAP)SelectObject(hdcMem, hbmExplosion);
            PlgBlt(hdcBuffer, points, hdcMem, k*landerWidth, 0, landerWidth, landerHeight, hbmExplosionMask, k*landerWidth, 0);
            DeleteObject(hbmOldMem);
            if (k == 0) PlaySound(MAKEINTRESOURCE(IDS_WAVE1), GetModuleHandle(NULL), SND_RESOURCE|SND_ASYNC);
            ++k; if(k == 25){k = 0; explosion = false;}
        }
    }
}
