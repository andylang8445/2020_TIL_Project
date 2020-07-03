#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define row 9
#define col 9
#define depth 9

int originalMap[row][col]; // originalSudokuMap with blank (Blank is indicated with zero)
int sudokuCandidate[row][col][depth]; // Candidate for blanks
int candidateCnt[row][col];
int totCandidateCnt = 0;

char originalMapString[row][col]; // Original Sudoku Map (Blank is indicated with space)

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void initialize() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			candidateCnt[i][j] = 0;
		}
	}
}

void printCurrentSudoku() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%d ", originalMap[i][j]);
		}
		printf("\n");
	}
}

void sudokuFormatConverter() {//function that converts original sudoku map in 2D char array to 2D int
	int convertedMap[9][9];
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (originalMapString[i][j] == ' ') {
				convertedMap[i][j] = 0;
			}
			else if (originalMapString[i][j] <= '9' && originalMapString[i][j] >= '1') {
				convertedMap[i][j] = originalMapString[i][j] - '0';
			}
		}
	}

	printf("\nConverted Sudoku:\n");
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			originalMap[i][j] = convertedMap[i][j];
			printf("%d ", convertedMap[i][j]);
		}
		printf("\n");
	}
}

int CandidateMappingAdd() {
	totCandidateCnt = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			candidateCnt[i][j] = 0;
			for (int k = 0; k < depth; k++) {
				if (originalMap[i][j] == 0) {
					sudokuCandidate[i][j][k] = 1;
				}
				else {
					sudokuCandidate[i][j][k] = 0;
				}
			}
			if (originalMap[i][j] == 0) {
				for (int k = 0; k < depth; k++) {
					sudokuCandidate[i][j][originalMap[i][k] - 1]--;
					sudokuCandidate[i][j][originalMap[k][j] - 1]--;
				}
			}
		}
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (originalMap[i][j] == 0) {
				printf("Candidate(s) for (%d,%d):\n\t", i, j);
				for (int k = 0; k < 9; k++) {
					if (sudokuCandidate[i][j][k] > 0) {
						candidateCnt[i][j]++;
						totCandidateCnt++;
						printf("%d, ", (k + 1));
					}
				}
				printf("\n");
			}
		}
	}
	return totCandidateCnt;
}

void checkSudoku() { //Function that checks if the sudoku is suitable to the rule.
	int horizontal, vertical, squared;
	int tempSudokuLinearCheck[row];

	horizontal = vertical = squared = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			tempSudokuLinearCheck[j] = originalMap[i][j];
		}
		for (int m = 0; m < (row-1); m++) {
			for (int n = m + 1; n < col; n++) {
				if (tempSudokuLinearCheck[m] > tempSudokuLinearCheck[n]) {
					swap(&tempSudokuLinearCheck[m], &tempSudokuLinearCheck[n]);
				}
			}
		}
		for (int j = 0; j < (row-1); j++) {
			if (tempSudokuLinearCheck[j] + 1 != tempSudokuLinearCheck[j + 1]) {
				horizontal = 1;
				printf("\n\t");
				for (int k = 0; k < col; k++) {
					printf("%d, ", tempSudokuLinearCheck[k]);
				}
				printf("\n");
			}
		}

		for (int j = 0; j < row; j++) {
			tempSudokuLinearCheck[j] = originalMap[j][i];
		}
		for (int m = 0; m < (row-1); m++) {
			for (int n = m + 1; n < col; n++) {
				if (tempSudokuLinearCheck[m] > tempSudokuLinearCheck[n]) {
					swap(&tempSudokuLinearCheck[m], &tempSudokuLinearCheck[n]);
				}
			}
		}
		for (int j = 0; j < (row-1); j++) {
			if (tempSudokuLinearCheck[j] + 1 != tempSudokuLinearCheck[j + 1]) {
				vertical = 1;
			}
		}
	}

	// Square Check
	for (int i = 0; i < (row/3); i++) {
		for (int j = 0; j < (col/3); j++) {


			tempSudokuLinearCheck[0] = originalMap[(i * 3)][(j * 3)];
			tempSudokuLinearCheck[1] = originalMap[(i * 3)][(j * 3) + 1];
			tempSudokuLinearCheck[2] = originalMap[(i * 3)][(j * 3) + 2];
			tempSudokuLinearCheck[3] = originalMap[(i * 3) + 1][(j * 3)];
			tempSudokuLinearCheck[4] = originalMap[(i * 3) + 1][(j * 3) + 1];
			tempSudokuLinearCheck[5] = originalMap[(i * 3) + 1][(j * 3) + 2];
			tempSudokuLinearCheck[6] = originalMap[(i * 3) + 2][(j * 3)];
			tempSudokuLinearCheck[7] = originalMap[(i * 3) +- 2][(j * 3) + 1];
			tempSudokuLinearCheck[8] = originalMap[(i * 3) + 2][(j * 3) + 2];

			for (int m = 0; m < (row-1); m++) {
				for (int n = m + 1; n < col; n++) {
					if (tempSudokuLinearCheck[m] > tempSudokuLinearCheck[n]) {
						swap(&tempSudokuLinearCheck[m], &tempSudokuLinearCheck[n]);
					}
				}
			}
			for (int k = 0; k < (row-1); k++) {
				if (tempSudokuLinearCheck[k] + 1 != tempSudokuLinearCheck[k + 1]) {
					squared = 1;
				}
			}
		}
	}

	printf("Vertical Check: ");
	if (vertical == 1)
		printf("FAIL");
	else
		printf("PASS");
	printf("\nHorizontal Check: ");
	if (horizontal == 1)
		printf("FAIL");
	else
		printf("PASS");
	printf("\nSquare Check: ");
	if (squared == 1)
		printf("FAIL");
	else
		printf("PASS");
}

int fixCandidate() {
	int fix_Cnt = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (candidateCnt[i][j] == 1) {
				for (int k = 0; k < 9; k++) {
					if (sudokuCandidate[i][j][k] == 1) {
						originalMap[i][j] = k + 1;
						fix_Cnt++;

						break;
					}
				}
			}
		}
	}
	printf("%d Errors has been Fixed\nFixed Sudoku:\n", fix_Cnt);
	printCurrentSudoku();

	return fix_Cnt;
}

int main(int argc, char* argv[]) {
	int indicater;
	initialize();
	printf("Input the original Sudoku:\n");
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			scanf("%c", &originalMapString[i][j]);
		}
		if (i < 8)
			scanf("\n");
	}
	sudokuFormatConverter();
	do {
		CandidateMappingAdd();
		printf("\n\nCandidate Cnt Map:\n");
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				printf("%d ", candidateCnt[i][j]);
			}
			printf("\n");
		}
		indicater = fixCandidate();
		checkSudoku();
		if (indicater == totCandidateCnt) {
			break;
		}
	} while (indicater > 0);
	getchar();
	return 0;
}
