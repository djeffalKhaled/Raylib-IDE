// Handles all screen related functions
#ifndef SCREEN_H
#define SCREEN_H
#include "../raylib.h"

void centerWindow(int screenWidth, int screenHeight) {
    // credit to omegapy
    int monitor = GetCurrentMonitor();
    int monitorWidth = GetMonitorWidth(monitor); 
    int monitoHeight = GetMonitorHeight(monitor); 
    SetWindowPosition((int)(monitorWidth / 2) - (int)(screenWidth / 2), (int)(monitoHeight / 2) - (int)(screenHeight / 2));
}

// Gets all cases of screen sizes
Vector2 getScreenSize(int initScreenWidth, int initScreenHeight) {
    Vector2 screen = {GetScreenWidth(), GetScreenHeight()};
    if (IsWindowFullscreen()) {
        int monitor = GetCurrentMonitor();
        screen.x = GetMonitorWidth(monitor); screen.y = GetMonitorHeight(monitor);
    }
    return screen;
}

void handleScreenSize(int screenWidth, int screenHeight) {
    if (IsKeyPressed(KEY_F) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
 	{
        if (!IsWindowFullscreen()) {
            int monitor = GetCurrentMonitor();
            SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
            ToggleFullscreen();
        } else {
            ToggleFullscreen();
            centerWindow(screenWidth, screenHeight);
            SetWindowSize(screenWidth, screenHeight);
        }
    }
}

// Allows mouse scrolling of a rectangle object -- mainly for textArea
Rectangle setScrollable(Rectangle rect, int scrollSpeed) {
    int posY = rect.y;
    posY += (int)(GetMouseWheelMove()*scrollSpeed);
    rect.height -= (int)(GetMouseWheelMove() *  scrollSpeed);
    rect.y = posY;
    return rect;
}


#endif // SCREEN_H