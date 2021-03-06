/* tokenizer.c
 *
 * CS 270-01.Bolden..........Ethan Hinkle
 * 20 September, 2021........hink9661@vandals.uidaho.edu
 *
 * This is the main() file for the assigment 1 dealing with taking a
 * C string and parsing it into tokens
 *--------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_ARR_LENGTH 255
#define MAX_ARR_HEIGHT 63

/* prototypes*/
int makearg(char *, char ***);
int notToken(char);

/* main */
int main() {
    char **args;
    char *str;
    printf("Please enter a string: ");
    str = malloc(MAX_ARR_LENGTH * sizeof(char));
    fgets(str, MAX_ARR_LENGTH, stdin);
    int i, argc;
    argc = makearg(str,&args);
    if(argc == -1){
        printf("An error occurred.");
    }else {
        printf("There are %i tokens in the given string.\n", argc);
        printf("----------------------------------------\n");
        for(i = 0; i < argc; i++){ /* increments args to the next spot in memory */
            printf("%s\n", args[i]);
        }
    }
    return 0;
}

/* functions */
int makearg(char *s, char ***args){ /* takes the string and parses it into tokens */
    int sindex = 0; /* current index of s */
    int tindex = 0; /* current index of the current token */
    int aindex = 0; /* current array index of args, nummber of tokens */
    int i;
    *args = malloc(MAX_ARR_HEIGHT * sizeof(char*)); /* allocates memory for args */
    for ( i = 0; i < MAX_ARR_HEIGHT; i++ ){
        *(*args + i) = malloc(MAX_ARR_LENGTH * sizeof(char));
    }
    do{ /* do while to allow for new token aindex increment when at EOF */
        if(notToken(s[sindex])){
            args[0][aindex][tindex] = s[sindex]; // assigns next character for token */
            tindex ++; /* next char for token */
        }else{
            if(notToken(s[sindex-1])){ /* only runs if prev char was not a token separator */
                aindex ++; /* next token in args */
            }
            tindex = 0; /* reset token place to 0*/
        }
        sindex ++; /* next char in input array */
        if(aindex >= MAX_ARR_HEIGHT || tindex >=  MAX_ARR_LENGTH){ /* go outside args memory bounds */
            return -1;
        }
    }while(s[sindex-1] != '\0'); /* checks prev value for end of file */
    return aindex;
}

int notToken(char c){ /* checks if the character ends the current token or ends the file */
    if(c != ' ' && c != '\n' && c != '\0'){
        return 1;
    }
    return 0;
}
