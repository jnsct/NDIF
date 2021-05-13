#include <stdio.h>
#include <sys/stat.h>

int main()
{
        struct stat results;

        char* name = "in.bin";
        FILE *img;

        //determine size of file in order to define the number of elements to read
        if(stat(name, &results) == 0)
                printf("size is %ld\n", results.st_size);
        else {
                printf("ERROR: FILE NOT FOUND\n");
                return -1;
        }

        img = fopen(name, "rb");
        char imgC;
        while(imgC != EOF){
                imgC = 0x00;
                while(imgC != 0x0A){
                        printf(imgC == 0x31 ? "X" : "0");
                        imgC = (char) getc(img);
                        printf("%X\n", imgC);
                }
                printf("\n");
        }

        printf("\n");

}
