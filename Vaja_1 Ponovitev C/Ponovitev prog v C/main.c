#include "printd.c"

//Initializing structure header with following values:
header format ={
    .size = 3,
    .tag[0] = "INF",
    .tag[1] = "DBG",
    .tag[2] = "ERR",
    .text[0] = "INFO: ",
    .text[1] = "DEBUG: ",
    .text[2] = "ERROR: "
};

//main function
int main(int argc, char** argv){
    printd(&format, 1, "To je test za 23608");   //Calling function void printd(header* format, int i, char* niz) from printd.c
    return 0;
}

//GitHub Repository: https://github.com/GVihi/namenska-pr-oprema/tree/main/Vaja_1%20Ponovitev%20C/Ponovitev%20prog%20v%20C