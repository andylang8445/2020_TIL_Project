---
title:  "Sudoku Solving Project"
date:   2020-06-14 23:26:40
categories:
- Programming
- 2020 Project
- On-going Project
- TIL
tags:
- C
- Xcode
- Algorithm
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