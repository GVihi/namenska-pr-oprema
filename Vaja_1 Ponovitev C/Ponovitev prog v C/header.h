//Not much to say. Defining struct header
typedef struct {
    int size;
    char* tag[3][3];        //char array with 3 elements, size 3
    char* text[3][128];     //char array with 3 elements, size 128
} header;