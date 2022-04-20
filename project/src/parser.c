#include "parser.h"

/*int searchKeyWord(char* contain, char key_word[]) {
    for(int i = 0; i < strlen(contain) - strlen(key_word); i++){
        bool found_key = false;
        for(int j = 0; j < strlen(key_word); j++){
            if(contain[i + j] != key_word[j]){
                found_key = false;
                j = 0;
                i++;
            } else {
                found_key = true;
            }
        }
        if(found_key){
            return i;
        }
    }
    return -1;
}*/

int readFile(const char* path_file) {
    FILE* from_create = fopen(path_file, "r+");
    char* is_getc = malloc(sizeof(char)*LEN);
    fgets(is_getc, LEN, from_create);
    char* token = strtok(is_getc, ",; \n\r");
    while(token != NULL){
        printf("%s\n", token);
        token = strtok(NULL, ",; \n\r");
    }
    
    fclose(from_create);
    free(is_getc);
    return 0;
}

/*Info* createInfo() {
    Info* letter;
    letter = malloc(sizeof(Info));
    for (size_t i = 0; i < LEN; i++) {
        letter->From[i] = 0;
        letter->To[i] = 0;
        letter->Date[i] = 0;
        letter->Content_Type[i] = 0;
    }
    return letter;
}

void freeInfo(Info* letter){
    free(letter);
}

Info* recordInfo(char* is_gets, Info* letter) {
    for(int i = 0; i < strlen(is_gets); i++)

}

int printInfo(Info* letter) {
    printf("|%s %s %s %s|", letter->From, letter->To, letter->Date, letter->Content_Type);
    return 0;
}*/