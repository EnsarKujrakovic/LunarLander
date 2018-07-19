#ifndef LANDER_H
#define LANDER_H
#include "Vector2D.h"
#include "resource.h"
#define PI 3.141592653589793238462643383
#include <cmath>
#include <mmsystem.h>
#include <windows.h>
#define KEYPRESSED(vk_code) (((GetAsyncKeyState(vk_code) & 0x0001) && (GetForegroundWindow() == GetActiveWindow())) ? 1 : 0)
#define KEYDOWN(vk_code) (((GetAsyncKeyState(vk_code) & 0x8000) && (GetForegroundWindow() == GetActiveWindow())) ? 1 : 0)

class Lander
{
    public:
        Lander();
        virtual ~Lander();
        void rotate(double);
        void initialize();
        bool successfulLanding();
        bool outOfFuel();

        Vector2D getPosition();
        Vector2D getSpeed();
        Vector2D getAcceleration();
        double getFuel();
        double getAngle();

        void setPosition(Vector2D);
        void setSpeed(Vector2D);
        void setAcceleration(Vector2D);
        void setFuel(double);
        void burnFuel(double);
        void setAngle(double);
        void updatePosition();

        void render(HDC, HDC, bool);

        HBITMAP hbmLander;
        HBITMAP hbmLanderMask;
        HBITMAP hbmExplosion;
        HBITMAP hbmExplosionMask;
        int landerWidth;
        int landerHeight;
        POINT points [4];
        bool succesfulLanding;
        bool explosion = true;
    private:
        Vector2D position;
        Vector2D speed;
        Vector2D acceleration;
        double fuel = 1000;
        double angle = 0;
};
static double da = 0;
#endif // LANDER_H
