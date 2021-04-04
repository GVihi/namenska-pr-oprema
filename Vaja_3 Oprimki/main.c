#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct imenik{
    char id[20];
    char telefon[20];
    char ime[20];
    char priimek[20];
    char datum_rojstva[20];
};

int main(int argc, char** argv){
    struct imenik im;
    memset(&im, 0, sizeof(struct imenik));

    char dan[5], mesec[5], leto[5];

    if(strcmp(argv[1], "-c") == 0){
        int fd = open("xpo.dat", O_CREAT, 0660);
        return 0;
    }

    bool podanId = false;
    bool samoId = false;
    bool samoImeInPriimek = false;
    char id[20] = "";

    if(strcmp(argv[1], "-o") == 0){
        int oprimek = (int) argv[2];
        int fd = open("xpo.dat", O_RDWR, 0);
        strcat(im.id, "1");

        /*
        char ch;
        int idCounter = 0;
        for(ch = getc(fd); ch != EOF; ch = getc(fd)){
            if(strcmp(ch, "!") == 0){
                idCounter++;
            }
        }

        printf("Next ID: %d\n", idCounter);
        */

        for(int i = 3; i < argc; i++){
            if(strcmp(argv[i], "-tel") == 0){
                strcpy(im.telefon, argv[i+1]);
                samoId = false;
                samoImeInPriimek = false;
            }
            if(strcmp(argv[i], "-ime") == 0){
                strcpy(im.ime, argv[i+1]);
                samoId = false;
                samoImeInPriimek = true;
            }
            if(strcmp(argv[i], "-priimek") == 0){
                strcpy(im.priimek, argv[i+1]);
                samoId = false;
                samoImeInPriimek = true;
            }
            if(strcmp(argv[i], "-dan") == 0){
                strcpy(dan, argv[i+1]);
                samoId = false;
                samoImeInPriimek = false;
            }
            if(strcmp(argv[i], "-mesec") == 0){
                strcpy(mesec, argv[i+1]);
                samoId = false;
                samoImeInPriimek = false;
            }
            if(strcmp(argv[i], "-leto") == 0){
                strcpy(leto, argv[i+1]);
                samoId = false;
                samoImeInPriimek = false;
            }
            if(strcmp(argv[i], "-id") == 0){
                strcpy(id, argv[i+1]);
                podanId = true;
                samoId = true;
                samoImeInPriimek = false;
            }
        }
        
        if(!podanId && !samoImeInPriimek){
            //write
            printf("%s", "Writing to file \n");
            snprintf(im.datum_rojstva, 20, "%s.%s.%s", dan, mesec, leto);

            lseek(fd, 0, SEEK_END);
            write(fd, &im, sizeof(struct imenik));
            write(fd, "!", sizeof(char));
        }

        struct stat fileProps;
        fstat(fd, &fileProps);
        int nOfEntries = fileProps.st_size;

        if(podanId && !samoId){
            //update
            printf("%s", "Updating entry \n");
        }

        if(samoId){
            //delete
            printf("%s", "Deleting entry \n");
        }

        if(samoImeInPriimek){
            //search
            printf("%s", "Searching... \n");
            int fileOffset = 0;
            struct imenik temp;

            if(strcmp(im.ime, "") != 0 && strcmp(im.priimek, "") != 0){

            while(1){
                int offset = lseek(fd, fileOffset, SEEK_CUR);
                fileOffset = 1;
                if(offset == nOfEntries){
                    close(fd);
                    break;
                }
                read(fd, &temp, sizeof(struct imenik));
                
                if(strcmp(im.ime, temp.ime) == 0 && strcmp(im.priimek, temp.priimek) == 0){
                    printf("%s \t %s \t %s \t %s \t %s \n", temp.id, temp.ime, temp.priimek, temp.telefon, temp.datum_rojstva);
                }
            }
            }

            if(strcmp(im.ime, "") == 0){

            while(1){
                int offset = lseek(fd, fileOffset, SEEK_CUR);
                fileOffset = 1;
                if(offset == nOfEntries){
                    close(fd);
                    break;
                }
                read(fd, &temp, sizeof(struct imenik));
                
                if(strcmp(im.priimek, temp.priimek) == 0){
                    printf("%s \t %s \t %s \t %s \t %s \n", temp.id, temp.ime, temp.priimek, temp.telefon, temp.datum_rojstva);
                }
            }
            }

            if(strcmp(im.priimek, "") == 0){

            while(1){
                int offset = lseek(fd, fileOffset, SEEK_CUR);
                fileOffset = 1;
                if(offset == nOfEntries){
                    close(fd);
                    break;
                }
                read(fd, &temp, sizeof(struct imenik));
                
                if(strcmp(im.ime, temp.ime) == 0){
                    printf("%s \t %s \t %s \t %s \t %s \n", temp.id, temp.ime, temp.priimek, temp.telefon, temp.datum_rojstva);
                }
            }
            }
        }
        
    }

    return 0;
}