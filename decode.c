#include <stdio.h>
#include <math.h>
#include "libbmp.h"
#include "libbmp.c"

struct info{
	int X, Y; // Size of X and Y (resolution)
	int *xArr;
	int *yArr; // Nonogram values of X and Y
} info;


typedef struct info Struct;

Struct readFile(char* fileName){
	Struct s;
	s.X = 0;
	s.Y = 0;
	FILE *inPtr;
	inPtr = fopen(fileName, "r");
	int num;
	if (inPtr == NULL){
		printf("ERROR: FILE NOT FOUND\n");
		return s;
	}
	const int X = (int) fgetc(inPtr) - '0'; // Magnitude of X
	const int Y = (int) fgetc(inPtr) - '0'; // Magnitude of Y
	const int MSUB = (int) fgetc(inPtr) - '0'; // Magnitude of the size of the largest substring in x
	int i = 0;
	while(num != -38){
		num = fgetc(inPtr) - '0';
		if(num != -38) {
			if (i < X) {
				s.X += num * ((int) pow(10, (X - i - 1)));
			}
			else{
				s.Y += num * ((int) pow(10, (Y - i - 1 + X)));
			}
			i++;
		}
	}
	int *xArr = calloc(s.X, sizeof(int));
	int *yArr = calloc(s.Y, sizeof(int));
	int hold = -1;
	int EOFCheck = 0;
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
			free(tSArr);
		}


		// adding individual values to array
		else{
			if (n < s.X) {
				if(hold != -1){
					xArr[n] = (int *) hold;
					hold = num;
				}
				else{hold = num;}

			}
			else{
				if(hold != -1){
					yArr[n - s.X] = (int*) hold;
					hold = num;
				}
				else{hold = num;}
			}
		}
	}
	s.xArr = xArr;
	s.yArr = yArr;
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

	for(int i = 0; i<8; i++) {
		printf("%i: %i\n", i, s.xArr[i]);
	}
}
