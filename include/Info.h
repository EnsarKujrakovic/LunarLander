#ifndef INFO_H
#define INFO_H
#include "Lander.h"
#include "Ground.h"
#include <string>
class Info
{
    public:
        Info();
        virtual ~Info();
        int level = 1;
        double fuel;
        double angle;
        int points = 0;
        int positionX;
        int positionY;
        double speedX;
        double speedY;
        double accelerationX;
        double accelerationY;
        void updateInfo(Lander l);
        void render(HDC);

};

#endif // INFO_H
