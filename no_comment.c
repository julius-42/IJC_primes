/*
no_comment.c
Autor: Julius Kundrat FIT
Prelozene: gcc 13.3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"

typedef enum {
    CODE, SLASH, STRING, CHAR, STR_ESC, CHAR_ESC,
    SINGLE_COMMENT, MULTI_COMMENT, MULTI_COMMENT_END
} State;

/* Uses Finite State Machine to remove single-line and multi-line comments in C code
 * Prints the new commentless code into the stdout
 */
void remove_comments(FILE* file){
    int c;
    State state = CODE;

    while((c = fgetc(file)) != EOF){

        switch (state){
        
        // Normal C code: prints everything and looks for other states
        case CODE:
            if (c == '/') state = SLASH;
            else if (c == '"') { state = STRING; putchar(c); }
            else if (c == '\'') { state = CHAR; putchar(c); }
            else putchar(c);
            break;
        
        // Last char was '/', checks the next char and sets the state accordingly
        case SLASH:
            if (c == '/') state = SINGLE_COMMENT;
            else if (c == '*') state = MULTI_COMMENT;
            else { 
                putchar('/'); 
                if (c == '"') state = STRING;
                else if (c == '/') state = SLASH;
                else if (c == '\'') state = CHAR;
                else { putchar(c); state = CODE; }
            }
            break;

        // Inside a "string" - prints everything until closing double quote
        case STRING:
            putchar(c);
            if (c == '"') state = CODE;
            else if (c == '\\') state = STR_ESC;
            break;
        
        // Inside a 'char' - prints everything until closing quote
        case CHAR:
            putchar(c);
            if (c == '\'') state = CODE;
            else if (c == '\\') state = CHAR_ESC;
            break;

        // Prints the escape character and returns to STRING state
        case STR_ESC:
            putchar(c);
            state = STRING;
            break;

        // Prints the escape character and returns to CHAR state
        case CHAR_ESC:
            putchar(c);
            state = CHAR;
            break;

        // Inside a single line comment - skips everything until the next newline
        case SINGLE_COMMENT:
            if (c == '\n'){ state = CODE; putchar('\n'); }
            break;

        // Inside a multi line comment - skips everything and checks for *
        case MULTI_COMMENT:
            if (c == '*') state = MULTI_COMMENT_END;
            break;
        
        // Once '*' was found in multi line comment, checks for '/' or '*' to set the state accordingly
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
    FILE* target = NULL;
    char file_name[4096];

    // Reads the file name from the argument if set
    if(argc > 1){
        snprintf(file_name, sizeof(file_name), "%s", argv[1]);
    }
    // Asks user to input a file name
    else{
        printf("Enter a file name: ");

        if (fgets(file_name, sizeof(file_name), stdin) == NULL) {
            error_exit("Error: Could not read input.\n");
        }

        file_name[strcspn(file_name, "\n")] = '\0';
    }
    
    // Opens file and handles error
    target = fopen(file_name, "r");
    if (target == NULL) {
        error_exit("Error: File %s not in the directory.\n", file_name);
    }

    remove_comments(target);

    fclose(target);
    return 0;
}

