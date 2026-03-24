#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"

typedef enum {
    CODE, SLASH, STRING, CHAR, 
    SINGLE_COMMENT, MULTI_COMMENT, MULTI_COMMENT_END
} State;


void remove_comments(FILE* file){
    int c;
    State state = CODE;

    while((c = fgetc(file)) != EOF){

        switch (state){

        case CODE:
            if (c == '/') state = SLASH;
            else if (c == '"') { state = STRING; putchar(c); }
            else if (c == '\'') { state = CHAR; putchar(c); }
            else putchar(c);
            break;
        
        case SLASH:
            if (c == '/') state = SINGLE_COMMENT;
            else if (c == '*') state = MULTI_COMMENT;
            else { putchar('/'); state = CODE; }
            break;

        case STRING:
            putchar(c);
            if (c == '"') state = CODE;
            break;

        case CHAR:
            putchar(c);
            if (c == '\'') state = CODE;
            break;

        case SINGLE_COMMENT:
            if (c == '\n') state = CODE;
            putchar('\n');
            break;

        case MULTI_COMMENT:
            if (c == '*') state = MULTI_COMMENT_END;
            break;
        
        case MULTI_COMMENT_END:
            if (c == '/') state = CODE;
            else if (c == '*') state = MULTI_COMMENT_END;
            else state = MULTI_COMMENT;
            break;
        }
    }

    putchar('\n');
}

int main(int argc, char** argv){
    FILE* target;
    char file_name[100];

    if(argc > 1){
        snprintf(file_name, sizeof(file_name), "%s", argv[1]);
    }
    else{
        if (scanf("%99s", file_name) != 1) {
            error_exit("Error: Could not read input.\n");
        }
    }
    
    target = fopen(file_name, "r");
    if (target == NULL) {
        error_exit("Error: File %s not in the directory.\n", file_name);
    }

    remove_comments(target);

    return 0;
}

