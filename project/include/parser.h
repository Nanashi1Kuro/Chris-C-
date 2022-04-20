#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LEN 100

typedef struct Info {
    char From[LEN];
    char To[LEN];
    char Date[LEN];
    char Content_Type[LEN];
} Info;

int readFile(const char* path_file); // Read file

Info* createInfo(); // Create struct Info and fullfill 0
void freeInfo(Info* letter);
//int searchKeyWord(char* contain, char key_word[]);
/*Info* recordInfo(); // Fullfill Info with information from letter
int printInfo();*/



#endif  // PROJECT_INCLUDE_PARSER_H_
