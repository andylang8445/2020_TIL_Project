---
title:  "Sudoku Solving Project"
date:   2020-06-22 01:43:40
categories:
- Programming
- 2020 Project
- On-going Project
- TIL
tags:
- C
- Xcode
- Algorithm
- Grade 12
---
# Overview
* The goal of this project is to create the program that can solve most of the sudoku faster than an average human using C/C++ programming language

# Planing
## Pseudo Code
1. Start Program
2. Get initial 9*9 sudoku map from user
3. Count the number of blanks and save it to a variable blankCnt
4. Create an 3 demational array with size of 9X9X9 and initiallize it with 0
5. Check 3*3 box, horizontal and vertical line for one missing blank
    * If a blank has been filled out, decrease blankCnt by one
6. Add numbers that are possible to fit in a blank to 3D array we have created
7. Erase the numbers in the candidate array according to sudoku rules(Duplicates in 3X3 box, horizontal line, and vertical line)
8. If there is only one candidate in the 3D array for a blank, write that number into the original array
    * If a blank has been filled out, decrease blankCnt by one
9. If blankCnt is equal to zero, finish the program
10. If blankCnt is a negative integer, print error to the screen and finish the program
11. If blankCnt is a positive integer, goto step 7
12. If the program has finished without any errors, print the filled sudoku and how long did it take

# Programming
## Day 1
June 20th, 2020
```cpp
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
```

## Day 2
June 21st, 2020

There are some errors in checkSudoku fucntion(method)
```c
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
					if(sudokuCandidate[i][j][k]>0)
						printf("%d: %d, ",(k+1),sudokuCandidate[i][j][k]);
				}
				printf("\n");
			}
		}
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
	return 0;
}
```

## Day 3
June 29, 2020
```c
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
```
## Day 4
July 1, 2020
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <conio.h>

#define row 9
#define col 9
#define depth 9

int originalMap[row][col]; // originalSudokuMap with blank (Blank is indicated with zero)
int sudokuCandidate[row][col][depth]; // Candidate for blanks
int candidateCnt[row][col];
int totCandidateCnt = 0;

char originalMapString[row][col]; // Original Sudoku Map (Blank is indicated with space)

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
					int tmp = tempSudokuLinearCheck[m];
					tempSudokuLinearCheck[m] = tempSudokuLinearCheck[n];
					tempSudokuLinearCheck[n] = tmp;
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
					int tmp = tempSudokuLinearCheck[m];
					tempSudokuLinearCheck[m] = tempSudokuLinearCheck[n];
					tempSudokuLinearCheck[n] = tmp;
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
						int tmp = tempSudokuLinearCheck[m];
						tempSudokuLinearCheck[m] = tempSudokuLinearCheck[n];
						tempSudokuLinearCheck[n] = tmp;
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
	_getch();
	return 0;
}
```
The program can solve teh sudokus with one candidate on one blank.
It has been checked running on VS community 2015
# Logs
## Current Errors
### Error when inputting blank on the last digit of each row
When the sudoku has the last digit of each row blank, it does not detect it has a valid char.
## Resolved Errors
### Known Error in CandidateMappingAdd() function
Unable to identify on GroomIDE.
Need farther inspection on IDEs (Xcode, VS)

## Day 3
### Known Error in CandidateMappingAdd() function
Unable to identify on GroomIDE.
Need farther inspection on IDEs (Xcode, VS)
## Day 4
### Error when inputting blank on the last digit of each row
When the sudoku has the last digit of each row blank, it does not detect it has a valid char.
