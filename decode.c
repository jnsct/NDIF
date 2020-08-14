#include <stdio.h>
#include <math.h>
#include "libbmp.h"
#include "libbmp.c"

struct info{
	int X, Y; // Size of X and Y (resolution)
	int* xArr;
	int* yArr; // Nonogram values of X and Y
};

typedef struct info Struct;

Struct readFile(char* fileName){
	Struct s;
	s.X = 0;
	s.Y = 0;
	FILE *inPtr;
	inPtr = fopen(fileName, "r");
	if (inPtr == NULL){
		printf("ERROR: FILE NOT FOUND\n");
		return s;
	}
	int tempX = (int) fgetc(inPtr) - '0';
	int tempY = (int) fgetc(inPtr) - '0';

	for(int i = 0; i < tempX+tempY; i++){
		if(i < tempX){
			s.X += (fgetc(inPtr) - '0') * ((int) pow(10, (tempX - i - 1)));
		}
		else{
			s.Y += (fgetc(inPtr) - '0') * ((int) pow(10, (tempY - i - 1 + tempX)));
		}
	}
	s.xArr = malloc(s.X * sizeof(int));
	s.yArr = malloc((200)* sizeof(int));

	int EOFCheck = 0;
	int EOA = 0; //end of array
	int num;
	int n = 0;
	int* subArr = malloc((200)* sizeof(int));
	fgetc(inPtr);
	while(!EOFCheck){
		num = (int) fgetc(inPtr) - '0';
		if(num == -38){
			n++;
		}
		else if(num == -49){
			EOFCheck = 1;
		}
		else if(num == -4){
			if(n < s.X){
				subArr[0] = s.xArr[n-1];
			}
			else{
				//Figure out why it only works with n-8 (2^3?)
				subArr[0] = s.yArr[n-8];
			}
			int i = 1;
			while(num != -38){
				num = (int) fgetc(inPtr) - '0';
				subArr[i] = num;
				num = (int) fgetc(inPtr) - '0';
				printf("%i,%i, num is %i\n",subArr[0],subArr[1], num);
			}
		}
		else if(n < s.X){
			s.xArr[n] = num;
		}
		else{
			s.yArr[n - s.X] = num;
		}
	}
	return s;

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

	Struct s;

	s = readFile("/home/john/CLionProjects/NDIF/input.txt");

	printf("Resolution is %ix%i\n", s.X, s.Y);


	for(int i = 0; i < s.X; i++){
		printf("%i ", s.xArr[i]);
	}
	printf("\n");
	for(int i = 0; i < s.Y; i++){
		printf("%i ", s.yArr[i]);
	}
}
