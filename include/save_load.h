#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H
#include <stdio.h>
#include <stdlib.h>
#include "../raylib.h"
#include "raylib_print.h"
#include "sds.h"
#include "strings.h"


void save(sds strout, sds fileName) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("FILE IO: Failure to create file!\n");
        fclose(file);
        return;
    }

    fputs(strout, file);
    
    fclose(file);
}
sds load(sds fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("FILE IO: Failure to create file!\n");
    }

    sds strin = sdsnew("");

    sds strLine = sdsnew("strLine");

    while (fgets(strLine, sizeof(strLine), file) != NULL) {
        strin = sdscat(strin, strLine);
    }

    fclose(file);
    return strin;
}


// PAGES SAVE AND LOAD
sds formatPageName(int index) {
    sds name = sdsnew("page");
    name = sdscat(name, intToStr(index)); // page[0..length]
    name = sdscat(name, ".txt"); // page[0..length].txt
    return name;
}
void savePages(sds* texts, int length) {
    // the names go by page[].txt
    for (int i = 0; i < length; i++) {
        sds fileName = formatPageName(i);
        save(texts[i], fileName);
        printf("SAVE NUMBER: %s\n", fileName);
        printf("SAVE CONTENT: %s\n", texts[i]);
    }
}
sds* loadPages(sds* texts, int length) {
    sds userText = sdsnew("");
    for (int i = 0; i < length; i++) {
        sds fileName = formatPageName(i);
        userText = load(fileName);
        texts[i] = userText;
        printf("LOAD NUMBER: %s\n", fileName);
        printf("LOAD CONTENT: %s\n", texts[i]);
    }
    return texts;
}





// Depricated
void saveToText(sds strout) {
    // ONLY CALL ONCE!

    FILE *file = fopen("save.txt", "w");
    if (file == NULL) {
        printf("FILE IO: Failure to create file!\n");
        fclose(file);
        return;
    }

    fputs(strout, file);
    
    fclose(file);
}


sds loadFromText() {
    FILE *file = fopen("save.txt", "r");
    if (file == NULL) {
        printf("FILE IO: Failure to create file!\n");
    }

    sds strin = sdsnew("");

    sds strLine = sdsnew("strLine");

    while (fgets(strLine, sizeof(strLine), file) != NULL) {
        strin = sdscat(strin, strLine);
    }

    fclose(file);
    return strin;
}



#endif // SAVE_LOAD_H