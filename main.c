// https://github.com/djeffalKhaled/Raylib-IDE
#include "raylib.h" // CREDIT TO RAY
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "raydraw.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/sds.c"
#include "include/sds.h" // CREDIT TO ANTIREZ, YOU SAVED ME
#include "include/sdsalloc.h"
#include "include/await.h"

// Self libraries:
#include "include/strings.h"
#include "include/raylib_print.h"
#include "include/save_load.h"
#include "include/screen.h"
#include "include/console.h"



int main(void) {
    // INITS
    int initScreenWidth = 1500;
    int initScreenHeight = 800;
    int scrollSpeed = 15;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    // COLOR DATA (last ff relates to transparency) Dark theme for now disabled
    Color textBgColor = WHITE; //GetColor(0x303030ff);
    Color consoleBgColor = LIGHTGRAY; //GetColor(0x181818ff);
    Color borderColor = GRAY; //GetColor(0x101010ff);

    // RECTS
    Rectangle saveRect = {0, 0, 200, 50};
    Rectangle loadRect = {200, 0, 200, 50};
    Rectangle newRect = {400, 0, 200, 50};
    Rectangle emptyRect = {600, 0, 200, 50};
    Rectangle executeRect = {800, 0, 200, 50};
    Rectangle prevRect = {1000, 0, 50, 50};
    Rectangle nextRect = {1050, 0, 50, 50};
    

    Rectangle textArea = {50, 100, initScreenWidth - 50, (initScreenHeight - 50) - 50};


    // Writing
    sds userText = sdsnew(""); 
    sds cursor = sdsnew("");
    int pagesLength = 10; // maximum pages
    sds *texts = (sds*)malloc(sizeof(sds) * pagesLength);
    texts = initStringArray(texts, pagesLength); // init to empty
    int pageIndex = 0;
    int page = 1;

    // Console
    sds consoleLog = sdsnew("");
    Rectangle consoleTextArea = {50, 600, initScreenWidth - 50, (initScreenHeight - 50) - 50};

    
    InitWindow(initScreenWidth, initScreenHeight, "Raylib IDE");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        handleScreenSize(initScreenWidth, initScreenHeight);

        Vector2 screen = getScreenSize(initScreenWidth, initScreenHeight);
        int screenWidth = screen.x;
        int screenHeight = screen.y;

        // Update sizes for fullscreen resizing
        Rectangle textEditorRect = {0, 50, screenWidth, (screenHeight - 300)};
        Rectangle consoleRect = {0, 50, screenWidth, (screenHeight - 50)};
        Rectangle consoleTitleRect = {0, 50, screenWidth - 1250, (screenHeight - 250)};
        Rectangle consoleTitleArea = {50, 560, screenWidth - 50, (screenHeight - 50) - 50};
        // allows text scroll
        textArea = setScrollable(textArea, scrollSpeed); 
        textArea.width = screenWidth - 50; // doesn't support height reposition yet
        consoleTextArea = setScrollable(consoleTextArea, scrollSpeed); 
        consoleTextArea.width = screenWidth - 50; 
        consoleTitleArea.width = screenWidth - 50;


        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("RAYLIB-IDE", screenWidth - 200, 10, 30, BLUE);


        // Console
        if (GuiButton(executeRect, "#206#Execute")) {
            consoleLog = ExecuteUserText(userText);
            printf("IDE_EXECUTEPAGE: %s", consoleLog);
        }
        // Console Text
        GuiDrawRectangle(consoleRect, 10, borderColor, consoleBgColor); // console background
        DrawTextBoxed(GetFontDefault(), consoleLog, consoleTextArea, 30, 10, true, BLACK);
        GuiDrawRectangle(consoleTitleRect, 10, GRAY, WHITE);
        DrawTextBoxed(GetFontDefault(), "CONSOLE:", consoleTitleArea, 20, 10, true, BLACK);
        

        // Attempt at a text cursor
        //int width = MeasureText(userText, 50);
        //Vector2 vect2 = {width, 50};
        //raylib_textCursor(vect2);

        
        // main writing script
        char charUserText = GetCharPressed();
        raylib_Debug(charToString(charUserText), screenWidth - 100);
        userText = sdscat(userText, charToString(charUserText));

        GuiDrawRectangle(textEditorRect, 10, borderColor, textBgColor); // textArea background
        cursor = appendCursorAtmp1(sdslen(userText));
        DrawTextBoxed(GetFontDefault(), userText, textArea, 40, 10, true, BLACK);
        DrawTextBoxed(GetFontDefault(), cursor, textArea, 40, 10, true, RED);

        // Text Details Section
        DrawText(intToStr(sdslen(userText)), 50, screenHeight - 50, 30, BLACK);
        DrawText(intToStr(GetFPS()), screenWidth / 2, screenHeight - 50, 30, GREEN);
        DrawText(intToStr(page), screenWidth - 50, screenHeight - 50, 30, BLACK);
        
        if (GetKeyPressed() == KEY_ENTER) {
            userText = sdscat(userText, "\n");
        }   

        if (IsKeyDown(KEY_RIGHT_SHIFT)) {
            delay(100);
            sdsrange(userText, 0, strlen(userText) - 2); // removes the last char using substring
            if (sdslen(userText) == 1) userText = sdsnew("");
        }

        if (IsKeyDown(KEY_TAB)) {
            userText = sdscat(userText, "\t");
        }


        
        // Settings ---GUI---
        if (GuiButton(saveRect, "#02#Save")) {
            savePages(texts, pagesLength);
        }
        if (GuiButton(loadRect, "#04#Load")) {
            if (loadPages(texts, pagesLength) != NULL) {
                texts = loadPages(texts, pagesLength);
                pageIndex = 0; page = 1;
                userText = texts[pageIndex];
            };
            printf("FILE LOAD: %s\n", userText);
        }

        if (GuiButton(newRect, "#08#New")) {
            // removes all pages content
            texts = initStringArray(texts, pagesLength);
            userText = sdsnew("");
            printf("TEXT: Init All pages\n");
        }
        if (GuiButton(emptyRect, "#143#Empty")) {
            // removes current page content
            userText = sdsnew("");
            texts[pageIndex] = sdsnew("");
            printf("TEXT: Init Current Page\n");
        }


        // Pages
        if (GuiButton(prevRect, "#118#")) {
            if (pageIndex > 0) {
                pageIndex--; page--;
                userText = texts[pageIndex];
                printf("PAGE INDEX: %d\n", pageIndex);
            }
        }
        if (GuiButton(nextRect, "#119#")) {
            if (pageIndex < pagesLength) {
                texts[pageIndex] = userText;
                if (pageIndex != (pagesLength - 1)) {
                    pageIndex++; page++;
                    userText = texts[pageIndex];
                }
                printf("PAGE INDEX: %d\n", pageIndex);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
