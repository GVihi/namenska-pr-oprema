#include "printd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printd(header* format, int i, char* niz){
    char* strings = (char*) malloc(sizeof(format->text) + sizeof(niz));     //Allocating size of text from header structure + size of character array niz
    strcat(strings, *format->text[i]);                                      //Concatenating value from *format->text[i] to strings char array
    strcat(strings, niz);                                                   //Concatenating value from niz to strings char array
    printf("%s\n", strings);                                                //Printing value of strings char array
    free(strings);                                                          //Releasing memory
}