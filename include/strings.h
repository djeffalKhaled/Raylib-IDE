#ifndef STRINGS_H
#define STRINGS_H
// SELF MADE STRING LIBRARY THAT IS NOW SEMI-DEPRICATED IN PLACE OF SDS (i suck at c strings)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sds.h"

typedef char* string;

// allocates 256 lines of characters for the string
string newStr() {
    string str = (string)malloc(sizeof(char) * 256);
    if (str == NULL) exit(1);
    return str;
}

// allocates space based on maximum size of the string
string newStr_size(int size) {
    if (size <= 0) return NULL;
    string str = (string)malloc(sizeof(char) * size);
    if (str == NULL) exit(1);
    return str;
}

// Reallocate memory updating the string's maximum size
string updateStr_size(string str, int size) {
    if (size <= 0) return NULL;
    str = (string)realloc(str, sizeof(char) * size);
    if (str == NULL) exit(1);
    return str;
}

// reads a line of string sized at 256 characters
string scanStr() {
    string str = newStr();
    fgets(str, 256, stdin); 
    // Removes the new line
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
    return str;
}

// reads a line of string sized at size
string scanStr_size(int size) {
    string str = newStr();
    fgets(str, size, stdin);
    // Removes the new line
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
    return str;
}

// reads a word of string
string scanWordStr() {
    string str = newStr();
    scanf("%s", str);
    return str;
}

// prints the prompt and reads a line of string sized at 256 characters
string input(string prompt) {
    printf("%s\n", prompt);
    string str = newStr();
    fgets(str, 256, stdin);
    // Removes the new line
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
    return str;
}
string charToString(char val) {
    string str = newStr();
    sprintf(str, "%c", val);
    return str;
}

string concatenate(string str1, string str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    string str1_newsize = newStr_size(len1 + len2 + 1);
    str1_newsize = str1;
    strcat(str1_newsize, str2);
    return str1_newsize;
}

char charAtIndex(string str, int index) {
    return str[index];
}

string intToStr(int val) {
    string str = newStr();
    sprintf(str, "%d", val);
    return str;
}
string floatToStr(float val) {
    string str = newStr();
    sprintf(str, "%f", val);
    return str;
}
string doubleToStr(float val) {
    string str = newStr();
    sprintf(str, "%lf", val);
    return str;
}

int length(string str) {
    int i = 0;
    while (str[i] != '\0') i++;
    return i;
}

// prints the string with a new line
void println(string str) {
    printf("%s\n", str);
}


// only sds function
sds* initStringArray(sds* texts, int length) {
    for (int i = 0; i < length; i++) {
        texts[i] = sdsnew("");
    }
    return texts;
}

sds appendCursorAtmp1(int appendIndex) {
    sds cursor = sdsnew("\xC2\xA0"); // Non breaking space UTF8
    for (int i = 0; i < appendIndex; i++) {
        cursor = sdscat(cursor, " ");
    }
    cursor = sdscat(cursor, "|"); // the cursor
    return cursor;
}

#endif // STRING_H