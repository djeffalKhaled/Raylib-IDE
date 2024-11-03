#ifndef RAYLIB_PRINT_H
#define RAYLIB_PRINT_H
#include "../raylib.h"

void raylib_print(char* strout) {
    DrawText(strout, 0, 0, 50, RED);
}
void raylib_println(char* strout, Vector2 vect ) {
    DrawTextEx(GetFontDefault(), strout, vect, 50, 10, RED);   
}

void raylib_Debug(char* strout, int offset) {
    DrawText(strout, offset, 0, 20, BLACK);
}

void raylib_textCursor(Vector2 vect) {
    DrawTextEx(GetFontDefault(), "|", vect, 50, 20, GRAY);   
}





#endif // RAYLIB_PRINT_H