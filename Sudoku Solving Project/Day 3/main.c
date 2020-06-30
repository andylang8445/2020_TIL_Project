#include <stdio.h>

int originalMap[9][9]; // originalSudokuMap with blank (Blank is indicated with zero)
int sudokuCandidate[9][9][9]; // Candidate for blanks
int candidateCnt[9][9];

char originalMapString[9][9]; // Original Sudoku Map (Blank is indicated with space)

void initialize(){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			candidateCnt[i][j]=0;
		}
	}
}

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

void CandidateMappingAdd(){
	for(int i=0;i<9;i++) {
		for(int j=0;j<9;j++) {
			for(int k=0;k<9;k++) {
				if(originalMap[i][j]==0) {
					sudokuCandidate[i][j][k]=1;
				}
				else {
					sudokuCandidate[i][j][k]=0;
				}
			}
			if(originalMap[i][j]==0) {
				for(int k=0;k<9;k++) {
					sudokuCandidate[i][j][originalMap[i][k]-1]--;
					sudokuCandidate[i][j][originalMap[k][j]-1]--;
				}
			}
		}
	}
	for(int i=0;i<9;i++) {
		for(int j=0;j<9;j++) {
			if(originalMap[i][j]==0){
				printf("Candidate(s) for (%d,%d): ",i,j);
				for(int k=0;k<9;k++) {
					if(sudokuCandidate[i][j][k]>0){
						candidateCnt[i][j]++;
						printf("%d: %d, ",(k+1),sudokuCandidate[i][j][k]);
					}
				}
				printf("\n");
			}
		}
		printf("aa ");
	}
}

int checkSudoku() { //Function that checks if the sudoku is suitable to the rule.
	int horizontal, vertical, squared;
	int tempSudokuLinearCheck[9];
	
	horizontal = vertical = squared = 0;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			tempSudokuLinearCheck[j]=originalMap[i][j];
		}
		for(int m;m<8;m++){
			for(int n=m+1;n<9;n++){
				if(tempSudokuLinearCheck[m]>tempSudokuLinearCheck[n]){
					int tmp=tempSudokuLinearCheck[m];
					tempSudokuLinearCheck[m]=tempSudokuLinearCheck[n];
					tempSudokuLinearCheck[n]=tmp;
				}
			}
		}
		for(int j=0;j<8;j++){
			if(tempSudokuLinearCheck[j]+1!=tempSudokuLinearCheck[j+1]){
				horizontal=1;
			}
		}
		
		for(int j=0;j<9;j++){
			tempSudokuLinearCheck[j]=originalMap[j][i];
		}
		for(int m;m<8;m++){
			for(int n=m+1;n<9;n++){
				if(tempSudokuLinearCheck[m]>tempSudokuLinearCheck[n]){
					int tmp=tempSudokuLinearCheck[m];
					tempSudokuLinearCheck[m]=tempSudokuLinearCheck[n];
					tempSudokuLinearCheck[n]=tmp;
				}
			}
		}
		for(int j=0;j<8;j++){
			if(tempSudokuLinearCheck[j]+1!=tempSudokuLinearCheck[j+1]){
				vertical=1;
			}
		}
	}
	
	// Square Check
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			tempSudokuLinearCheck[0]=originalMap[(i*3)][(j*3)];
			tempSudokuLinearCheck[1]=originalMap[(i*3)][(j*3)+1];
			tempSudokuLinearCheck[2]=originalMap[(i*3)][(j*3)+2];
			tempSudokuLinearCheck[3]=originalMap[(i*3)+1][(j*3)];
			tempSudokuLinearCheck[4]=originalMap[(i*3)+1][(j*3)+1];
			tempSudokuLinearCheck[5]=originalMap[(i*3)+1][(j*3)+2];
			tempSudokuLinearCheck[6]=originalMap[(i*3)+2][(j*3)];
			tempSudokuLinearCheck[7]=originalMap[(i*3)+2][(j*3)+1];
			tempSudokuLinearCheck[8]=originalMap[(i*3)+2][(j*3)+2];
			
			for(int m;m<8;m++){
				for(int n=m+1;n<9;n++){
					if(tempSudokuLinearCheck[m]>tempSudokuLinearCheck[n]){
						int tmp=tempSudokuLinearCheck[m];
						tempSudokuLinearCheck[m]=tempSudokuLinearCheck[n];
						tempSudokuLinearCheck[n]=tmp;
					}
				}
			}
			for(int k=0;k<8;k++){
				if(tempSudokuLinearCheck[k]+1!=tempSudokuLinearCheck[k+1]){
					squared=1;
				}
			}
		}
	}
	
	printf("Vertical Check: ");
	if(vertical==1)
		printf("FAIL");
	else
		printf("PASS");
	printf("\nHorizontal Check: ");
	if(vertical==1)
		printf("FAIL");
	else
		printf("PASS");
	printf("\nSquare Check: ");
	if(vertical==1)
		printf("FAIL");
	else
		printf("PASS");
}

int main(int argc, char* argv[]) {
	initialize();
	printf("Input the original Sudoku:\n");
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			scanf("%c",&originalMapString[i][j]);
		}
		if(i<8)
			scanf("\n");
	}
	sudokuFormatConverter();
	CandidateMappingAdd();
	checkSudoku();
	printf("\n\nCandidate Cnt Map:\n");
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			printf("%d ",candidateCnt[i][j]);
		}
		printf("\n");
	}
	return 0;
}
