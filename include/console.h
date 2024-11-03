#ifndef CONSOLE_H
#define CONSOLE_H
#include <stdio.h>
#include <stdlib.h>
#include "../raylib.h"
#include "sds.h"
void DeleteFile(sds);
/*CamlCase for functions from now is used as default*/

/* KHALED-DESC: Compile and Execute 
Using popen we can execute system functions, in this case is gcc
In the compile part, we want to capture the case of an error if gcc ouputs it
gcc outputs its error in stderr however popen's fgets can only capture stdout
In the gcc compile command we redirect gcc's stderr to stdout using 2>&1
which allows the fgets to read and capture it, getting the error as string
finally I found a use for systeme d'exploitation lol
*/

// Compiles and Executes
sds CompileAndExecute() {
    DeleteFile("temp_executable.exe");

    // Compiles .c into .exe
    FILE *command = popen("gcc -o temp_executable userprogram.c 2>&1", "r");
    if (command == NULL) return "IDEPRINT_EXIT: POPEN GCC COMPILE ERROR";
    sds consoleLine = sdsnew(""); sds consoleOutput = sdsnew("");
    while (fgets(consoleLine, sizeof(consoleLine), command) != NULL) {
        printf("%s\n", consoleLine);
        consoleOutput = sdscat(consoleOutput, consoleLine);        
    }
    pclose(command);

    // Executes the .exe
    command = popen("temp_executable.exe", "r");
    consoleOutput = sdscat(consoleOutput, "\n");
    if (command == NULL) sdscat(consoleOutput, "CANNOT FIND EXECUTABLE!");

    while (fgets(consoleLine, sizeof(consoleLine), command) != NULL) {
        printf("%s\n", consoleLine);
        consoleOutput = sdscat(consoleOutput, consoleLine);        
    }
    pclose(command);
    
    printf("IDEPRINT_EXEC: %s \n", consoleOutput);
    return consoleOutput;
}

void DeleteFile(sds fileName) {
    if (remove(fileName) == 0) {
        printf("IDE_FILE_DELETE: Deleted file %s\n", fileName);
        return;
    } else printf("IDE_FILE_DELETE: Cannot delete file %s\n", fileName);
}

void StringToCFile(sds userText, sds filename) {
    printf("USERRRRRTEXXXXXXXXXXT: %s\n", userText);
    FILE *cfile = fopen(filename, "w");
    if (cfile == NULL) {
        printf("IDE_FILE_TXTTOC: Cannot open cfile in %s\n", filename); fclose(cfile);
        return;
    }
    
    fputs(userText, cfile);
    fclose(cfile);
    // No other checks, I'll gcc handle it for me.
}

// Compiles and Executes the user's written text at the current page
sds ExecuteUserText(sds userText) {
    StringToCFile(userText, "userprogram.c");
    sds output = CompileAndExecute();
    return output;
}



// Currently there is no way to save all pages into different c files 
// This function is an attempt and is for now deprecated
int TextFileToCFile(sds textFileName) {
    FILE *textFile = fopen(textFileName, "r");
    if (textFile == NULL) {
        printf("IDE_FILE_TXTTOC: Error opening input file\n"); fclose(textFile);
        return 0;
    }

    FILE *cfile = fopen("userprogram.c", "w");
    if (cfile == NULL) {
        printf("IDE_FILE_TXTTOC: Cannot open cfile in\n"); fclose(cfile);
        return 0;
    }

    // Reads from textFile and copies it to cfile
    char line[256]; 
    while (fgets(line, sizeof(line), textFile) != NULL) {
        fprintf(textFile, "%s", line); 
    }

    fclose(textFile); fclose(cfile);
    printf("IDE_FILE_TXTTOC: Copied text file into a c file");
    return 1;
}





#endif