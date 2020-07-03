#include <stdio.h>

int originalMap[9][9]; // originalSudokuMap with blank (Blank is indicated with zero)
int sudokuCandidate[9][9][9]; // Candidate for blanks

char originalMapString[9][9]; // Original Sudoku Map (Blank is indicated with space)

void sudokuFormatConverter(){//function that converts original sudoku map in 2D char array to 2D int
	int convertedMap[9][9];
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(originalMapString[i][j]==' '){
				convertedMap[i][j]=0;
			}
			else if(originalMapString[i][j]<='9' && originalMapString[i][j]>='1'){
				convertedMap[i][j]=originalMapString[i][j]-'0';
			}
		}
	}
	
	printf("\nConverted Sudoku:\n");
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			originalMap[i][j]=convertedMap[i][j];
			printf("%d ",convertedMap[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[]) {
	printf("Input the original Sudoku:\n");
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			scanf("%c",&originalMapString[i][j]);
		}
		if(i<8)
			scanf("\n");
	}
	sudokuFormatConverter();
	return 0;
}
