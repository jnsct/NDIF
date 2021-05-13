#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "libbmp.h"
#include "libbmp.c"

readFile(char* fileName){
        FILE *inPtr;
        access(fileName, F_OK) == 0 ? inPtr = fopen(fileName, "r") : printf("ERROR: FILE NOT FOUND \n");
        return img;
        int num;
        const unsigned short SIZE = (unsigned short) fgetc(inPtr); // size of image (only need one value since it's a square)
        const unsigned short MSUB = (unsigned short) fgetc(inPtr); // size of the largest substring in x
        int i = 0;
        int notEnd = 1
        while(num != -38){
                num = fgetc(inPtr) - '0';
                if(num != -38) {
                        if (i < X) {
                                img.X += num * ((int) pow(10, (X - i - 1)));
                        }
                        else{
                                img.Y += num * ((int) pow(10, (Y - i - 1 + X)));
                        }
                        i++;
                }
        }
        notEnd = 1
        int *xArr = calloc(img.X, sizeof(int));
        int *yArr = calloc(img.Y, sizeof(int));
        int hold = -1;
        int n = -1;
        while(!EOFCheck){
                num = (int) fgetc(inPtr) - '0';
                // catching the end of the line
                if(num == -38){
                        n++;
		}
                // catching the end of the file
                else if(num == -49){
                        EOFCheck = 1;
                }
                // processing subarrays
                else if(num == -4){
                        int *tSArr =  calloc(MSUB, sizeof(int)); //temporary subarray
                        tSArr[0] = hold;
                        fgetc(inPtr) - '0';
                        i = 1;
                        while(num >= 0){
                                tSArr[i] = num;
                                num = (int) fgetc(inPtr) - '0';
                                i++;
                        }
                        int *sArr = malloc(2 * sizeof(int)); //final subarray
                        for(int k = 0; k < i; k++){
                                sArr[k] = tSArr[k];
                        }
                        free(sArr);
                }


                // adding individual values to array
                else{
                        if (n < img.X) {
                                if(hold != -1){
                                        xArr[n] = (int *) hold;
                                        hold = num;
                                }
                                else{hold = num;}

                        }
                        else{
                                if(hold != -1){
                                        yArr[n - img.X] = (int*) hold;
					                                        hold = num;
                                }
                                else{hold = num;}
                        }
                }
        }
        img.xArr = xArr;
        img.yArr = yArr;
        return img;

}

void certainCells(int in[], int size, int out[], int c){
        //int c determines if any cells are certain
        if(in[0] == 8){
                c = 1;
                for(int n = 0; n < 8; n++){
                        out[n] = 1;
                }
        }
}




int main() {
        readFile("input");
}
