#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char** argv){
    int32_t matedata; //metapodatki 
    int32_t nameLength; //dolžina imena zbirke
    int32_t fileSize; //velikost zbirke
    int32_t hash; //hash zbirke
    //char path[nameLength];
    //char byteChunks[fileSize];
    char* filePath; //niz z imenom ali potjo zbirke
    char* byteChunks; //posamezni bajti prenesene zbirke

    char* addr = argv[1];
    int port = atoi(argv[2]);
    char* path = argv[3];

    if(strcmp(addr, "localhost") == 0){
        addr = "127.0.0.1";
    }

    int sockfd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Socket creation error \n");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if(inet_pton(AF_INET, addr, &address.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if(connect(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }

    char* test = "Hello";
    send(sockfd, test, strlen(test), 0);


    return 0;
}