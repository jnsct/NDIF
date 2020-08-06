#include <stdio.h>
#include <math.h>
#include "libbmp.h"
#include "libbmp.c"

void readFile(char* fileName, int* xOut, int* yOut){
	int X;
	int Y;
	int xSz;
	int ySz;
	FILE *inPtr;
	inPtr = fopen(fileName, "r");
	if (inPtr == NULL){
		printf("ERROR: FILE NOT FOUND");
		return;
	}


	xSz = (int) fgetc(inPtr) - '0';
	ySz = (int) fgetc(inPtr) - '0';

	for(int i = 0; i < xSz+ySz; i++){
		if(i < xSz){
			X += (fgetc(inPtr) - '0') * ((int) pow(10, (xSz - i - 1)));
		}
		else{
			Y += (fgetc(inPtr) - '0') * ((int) pow(10, (ySz - i - 1 + xSz)));
		}
	}
	printf("Resolution is %ix%i\n", X, Y);

	int EOFCheck = 1;
	int num;
	int i = 0;
	fgetc(inPtr);
	while(EOFCheck){
		num = (int) fgetc(inPtr) - '0';
		printf("%i\n", num);
		if(num == -38){
			i++;
		}
		else if(num == -49){
			EOFCheck = 0;
		}
		else if(i < X){
//TODO figure out how to handle these arrays (variable size array?)
			//xOut[i] = num;
		}
		else{
			//yOut[i] = num;
		}
	}

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
	int* X;
	int* Y;

	readFile("/home/john/CLionProjects/NDIF/input.txt",X,Y);
}
