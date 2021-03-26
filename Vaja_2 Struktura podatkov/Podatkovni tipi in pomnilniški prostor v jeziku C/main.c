#include "podatki.c"

int main(){
    //Calling function to allocate memory
    uint16_t* pom = rezerviraj(6);

    //Calling function to insert values into memory
    vstavi(pom);

    //Calling function to print values
    izpis(pom);

    //Calling function to free memory
    brisi(pom);
}