#include "printd.c"

header format ={
    .size = 3,
    .tag[0] = "INF",
    .tag[1] = "DBG",
    .tag[2] = "ERR",
    .text[0] = "INFO: ",
    .text[1] = "DEBUG: ",
    .text[2] = "ERROR: "
};

int main(int argc, char** argv){
    printd(&format, 1, "To je test za 23608");
    return 0;
}