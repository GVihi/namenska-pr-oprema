#include "podatki.h"
#include <stdio.h>
#include <stdlib.h>

uint16_t* rezerviraj(int velikostZlogi){
    //Allocating memory
    //4 char, 1 float, 1 int32 equals to 12B, which should be same as size of uint16_t multiplied by 6,
    //but it isn't for some reason: malloc(): corrupted top size
    uint16_t* pomnilnik = (uint16_t*) malloc((sizeof(uint16_t) * velikostZlogi) + 1);

    //Setting every allocated memory address to 23608
    for(int i = 0; i < 12; i++){
        *(uint16_t*) &pomnilnik[i] = 23608;
    }

    return pomnilnik;
}

void brisi(uint16_t* pomnilnik){
    //Frees memory
    free(pomnilnik);
}

uint16_t* vstavi(uint16_t* pomnilnik){
    //Initializing variables
    char x = 'X';
    char p = 'P';
    char o = 'O';
    float pi = 3.141592;
    uint32_t n = 23608;
    char em = '!';

    //Setting memory locations to variables values
    *(char*) &pomnilnik[0] = *(char*) &x;
    *(char*) &pomnilnik[1] = *(char*) &p;
    *(char*) &pomnilnik[2] = *(char*) &o;
    *(float*) &pomnilnik[3] = *(float*) &pi;
    *(uint32_t*) &pomnilnik[7] = *(uint32_t*) &n; //"Skipping" 4,5,6 because floats size is 4Bytes, therefore 3+4 = 7
    *(char*) &pomnilnik[11] = *(char*) &em; // --||--
    
}

void izpis(uint16_t* pomnilnik){
    //Printing variables
    printf("%c \n", (char)* (char*) &pomnilnik[0]);
    printf("%c \n", (char)* (char*) &pomnilnik[1]);
    printf("%c \n", (char)* (char*) &pomnilnik[2]);
    printf("%f \n", (float)* (float*) &pomnilnik[3]);
    printf("%d \n", (uint32_t)* (uint32_t*) &pomnilnik[7]); //"Skipping" 4,5,6 because floats size is 4Bytes, therefore 3+4 = 7
    printf("%c \n", (char)* (char*) &pomnilnik[11]); // --||--
}