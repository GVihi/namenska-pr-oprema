#include "printd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printd(header* format, int i, char* niz){
    char* strings = (char*) malloc(sizeof(format->text) + sizeof(niz));
    strcat(strings, *format->text[i]);
    strcat(strings, niz);
    printf("%s\n", strings);
    free(strings);
}