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
#include <arpa/inet.h>
#include <openssl/md5.h>
   
int main(int argc, char** argv)
{
    int32_t metadata; //meta podatki
    int32_t nameLength; //dolžina imena zbirke
    int32_t fileSize; //velikost zbirke
    int32_t hash; //hash zbirke
    char* path; //niz z imenom ali potjo zbirke
    char* byte; //posamezni bajti prenesene zbirke

    char* addr = argv[1];
    int port = atoi(argv[2]);
    path = argv[3];

    if(strcmp(addr, "localhost") == 0){
        addr = "127.0.0.1";
    }

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, addr, &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    unsigned char c[MD5_DIGEST_LENGTH];

    FILE *fd;
    fd = fopen(path, "rb");
    int connfd = 0;

    MD5_CTX mdContext;
    int bytes;
    unsigned char data[1024];

    MD5_Init (&mdContext);
    while ((bytes = fread (data, 1, 1024, fd)) != 0)
    MD5_Update (&mdContext, data, bytes);
    MD5_Final (c,&mdContext);

    if(fd == NULL)
    {
        printf("Error opening file");
        return 1;
    }

    fseek(fd, 0L, SEEK_END);
    fileSize = ftell(fd);
    rewind(fd);

    printf("File size: %d\n", fileSize);

    while(1){
        unsigned char buff[256] = {0};
        int nread = fread(buff,1,256,fd);

        if(nread > 0)
        {
            printf("Sending \n");
            write(sock, buff, nread);
        }

        if (nread < 256)
        {
            if (feof(fd))
                printf("End of file\n");
            if (ferror(fd))
                printf("Error reading\n");
            break;
        }
    }

    //send(sock , hello , strlen(hello) , 0 );
    //printf("Hello message sent\n");
    //valread = read( sock , buffer, 1024);
    //printf("%s\n",buffer );
    printf("%s", "Hash of file: ");
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) printf("%02x", c[i]);
    printf("\n");
    return 0;
}