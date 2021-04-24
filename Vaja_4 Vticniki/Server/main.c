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

/*typedef struct{
    int32_t matedata;
    int32_t nameLength;
    int32_t fileSize;
    int32_t hash;
    //char path[nameLength];
    //char byteChunks[fileSize];
    char* path;
    char* byteChunks;
} package;*/

int main(int argc, char** argv){
    int port = atoi(argv[1]);
    

    int sockfd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if(bind(sockfd, (struct sockaddr *)&address, sizeof(address)) <0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if(new_socket = (accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&addrlen))<0){
        perror("accept");
        exit(EXIT_FAILURE);
    }

    char test[1024];
    valread = read(sockfd, test, 1024);
    printf("%s\n", test);
    return 0;
}