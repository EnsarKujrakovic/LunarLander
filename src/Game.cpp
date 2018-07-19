#include "Game.h"

Game::Game()
{
    lander.initialize();
    ground.generateTerrain();
    lander.updatePosition();
}

Game::~Game()
{
    //dtor
}
void Game::render(HWND hwnd, HDC hdc){

    RECT prc;
    GetClientRect(hwnd, &prc);
    HDC hdcBuffer = CreateCompatibleDC(hdc);
    HDC hdcMem = CreateCompatibleDC(hdc);
    HDC hdcMem2 = CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, prc.right, prc.bottom);
    HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

    //background
    HBITMAP hbmOldMem2 = (HBITMAP)SelectObject(hdcMem2, ground.hbmBackground);
    BitBlt(hdcBuffer, 0, 0, prc.right, prc.bottom, hdcMem2, 0, 0, SRCCOPY);
    DeleteObject(hbmOldMem2);
    DeleteObject(hdcMem2);
    //start screen
    if(mainMenu){
        SetBkMode(hdcBuffer, TRANSPARENT);
        HFONT font, oldfont;
        char str [100];
        sprintf(str, "  Lunar Lander");
        font = (HFONT)CreateFont(80, 50, 0, 0, FW_BLACK, FALSE, FALSE, 0, OEM_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH | FF_SWISS, NULL);
            SetTextColor(hdcBuffer, RGB(0, 0, 200));
        oldfont = (HFONT)SelectObject(hdcBuffer, font);
        SIZE sz;
        SetBkColor(hdcBuffer, RGB(0, 0, 0));
        GetTextExtentPoint32(hdc, str, strlen(str), &sz);
        TextOut(hdcBuffer, WIDTH/2 - sz.cx*4, HEIGHT/2-sz.cy, str, strlen(str));
        font = (HFONT)SelectObject(hdcBuffer, oldfont);

        SetTextColor(hdcBuffer, RGB(0, 0, 200));
        sprintf(str, "New Game [Enter]   Exit [Esc]");
        GetTextExtentPoint32(hdc, str, strlen(str), &sz);
        TextOut(hdcBuffer, WIDTH/2-sz.cx/2, HEIGHT/2+100, str, strlen(str));
        SetBkMode(hdcBuffer, OPAQUE);
        DeleteObject(oldfont);
        DeleteObject(font);
        BitBlt(hdc, 0, 0, prc.right, prc.bottom, hdcBuffer, 0, 0, SRCCOPY);
        DeleteObject(hdcMem);
        DeleteObject(hbmBuffer);
        SelectObject(hdcBuffer, hbmOldBuffer);
        DeleteObject(hbmOldBuffer);
        DeleteObject(hdcBuffer);
        return;
    }

    ground.render(hdcBuffer);
    info.render(hdcBuffer);
    lander.render(hdcBuffer, hdcMem, levelEnd);

        HFONT font, oldfont;
    //landing message
    if(levelEnd){
        SetBkMode(hdcBuffer, TRANSPARENT);
        font = (HFONT)CreateFont(120, 80, 0, 0, FW_BLACK, FALSE, FALSE, 0, OEM_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH | FF_SWISS, NULL);
            COLORREF c = RGB(0, 0, 200);
            SetTextColor(hdcBuffer, c);
        oldfont = (HFONT)SelectObject(hdcBuffer, font);
        SIZE sz;
        char str [100];
        if(!lander.successfulLanding()){
            sprintf(str, " %d Pts", this->points);
            SetBkColor(hdcBuffer, RGB(0, 0, 0));
            GetTextExtentPoint32(hdc, str, strlen(str), &sz);
            TextOut(hdcBuffer,  WIDTH/2 - sz.cx*6, HEIGHT/3, str, strlen(str));
            SetBkColor(hdcBuffer, RGB(0, 0, 0));
        }
        GetTextExtentPoint32(hdc, landingMessage, strlen(landingMessage), &sz);
        TextOut(hdcBuffer, WIDTH/2 - sz.cx*6, HEIGHT/2-sz.cy/2, landingMessage, strlen(landingMessage));
        font = (HFONT)SelectObject(hdcBuffer, oldfont);

        SetTextColor(hdcBuffer, RGB(0, 0, 200));
        if(lander.successfulLanding())
            sprintf(str, "Next Level [Enter]   Back to Menu [Esc]");
        else
            sprintf(str, "Back to Menu [Enter]   Exit[Esc]");
        GetTextExtentPoint32(hdc, str, strlen(str), &sz);
        TextOut(hdcBuffer, WIDTH/2-sz.cx/2, HEIGHT/2+100, str, strlen(str));
        SetBkMode(hdcBuffer, OPAQUE);
        DeleteObject(oldfont);
        DeleteObject(font);
    }
    BitBlt(hdc, 0, 0, prc.right, prc.bottom, hdcBuffer, 0, 0, SRCCOPY);


    //delete objects
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hbmOldBuffer);
    DeleteObject(hdcBuffer);


}
void Game::restart(){
    lander.initialize();
    lander.setFuel(1000);
    ground.setPlatformWidth(100);
    paused = false;
    levelEnd = false;
    mainMenu = true;
    points = 0;
    ground.generateTerrain();
    info.level = level;
    info.points = points;
    lander.explosion = true;
    sound = true;
}
void Game::nextLevel(){
    points += lander.getFuel()*level;
    lander.setFuel(lander.getFuel() + 500-100*level);
    if(lander.getFuel() <  500) lander.setFuel(500);
    ground.setPlatformWidth(ground.getPlatformWidth()-level*5);
    if(ground.getPlatformWidth() < 50) ground.setPlatformWidth(50);
    lander.initialize();
    paused = false;
    levelEnd = false;
    ground.generateTerrain();
    info.level = level;
    info.points = points;
}
void Game::gameLoop(HWND hwnd, HDC hdc){
    if(mainMenu){
        render(hwnd, hdc);
        static int track = IDS_WAVE2;
        if(KEYPRESSED(0x4D)){
            PlaySound(NULL, NULL, NULL);
            if(track == NULL) track = IDS_WAVE2;
            else track = NULL;
            PlaySound(MAKEINTRESOURCE(track), GetModuleHandle(NULL), SND_RESOURCE|SND_LOOP|SND_ASYNC);sound = false;
        }

        if(sound){PlaySound(MAKEINTRESOURCE(track), GetModuleHandle(NULL), SND_RESOURCE|SND_LOOP|SND_ASYNC);sound = false;}
        if(KEYPRESSED(VK_RETURN)){level = 1; mainMenu = false; PlaySound(NULL, NULL, SND_ASYNC);}
        if(KEYPRESSED(VK_ESCAPE)){exit(0);}
        return;
    }
    if(levelEnd){

        if(lander.succesfulLanding){
            if(KEYPRESSED(VK_ESCAPE)){level = 1; restart();}
            if(KEYPRESSED(VK_RETURN)){++level;nextLevel();}
        }else{
            if(KEYPRESSED(VK_ESCAPE)){exit(0);}
            if(KEYPRESSED(VK_RETURN)){level = 1;restart();}
        }

    }
    if(checkCollision()){
            if(ground.isPlatform(collisionPosition)
               && lander.getSpeed().GetY() < 0.2
               && lander.getAngle() > (3*PI/2-PI/10)
               && lander.getAngle() < (3*PI/2+PI/30)){
                landed(true);
            }else
                landed(false);
                paused = true;
                levelEnd = true;
           // paused = true;
    }
    if(KEYPRESSED(VK_RETURN)){paused  = !paused;}
    if(KEYPRESSED(VK_ESCAPE)){restart();}
        if(!paused){
            lander.updatePosition();
        }
        info.updateInfo(lander);
        render(hwnd, hdc);
}
bool Game::checkCollision(){
    std::list<POINT>::iterator it = ground.getPoints().begin();
    while(it->x < WIDTH){
        std::list<POINT>::iterator i2 = ++it;
            --it;
            if((*i2).x < 1 || (*i2).x >8000 || (*i2).y < 1 || (*i2).y > 8000) return false;
            if(linesIntersect(lander.points[0], lander.points[1], *it, *i2) ||
               linesIntersect(lander.points[1], lander.points[3], *it, *i2) ||
               linesIntersect(lander.points[2], lander.points[3], *it, *i2) ||
               linesIntersect(lander.points[0], lander.points[2], *it, *i2) ||
               lander.getPosition().GetX() < lander.landerWidth/2 ||
               lander.getPosition().GetX() > WIDTH - lander.landerWidth/2 ||
               lander.getPosition().GetY() < lander.landerWidth/2 ||
               lander.getPosition().GetY() > HEIGHT - lander.landerWidth/2
               ) {
                collisionPosition.x = it->x;
                collisionPosition.y = it->y;
                return true;
                }
            ++it;
       }
    return false;
}
void Game::landed(bool l){
    if(l){
        sprintf(landingMessage, "  Landed  ");
        lander.succesfulLanding = true;
    }
    else{
        sprintf(landingMessage, " Crashed  ");
        lander.succesfulLanding = false;
    }
}
