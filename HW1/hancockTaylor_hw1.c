/**************************************************
 * File:      hancockTaylor_hw1.c
 * Author:    Taylor Hancock
 * Purpose:   
 * Version:   1.0 Oct 07, 2022
 * Resources: 
 **************************************************/

#include <stdio.h>

#define A_ROWS 2
#define A_COLS 2
#define B_ROWS 2
#define B_COLS 3
#define C_ROWS 2
#define C_COLS 3

int main() {
    // initialize matrix a
    int a[A_ROWS][A_COLS] = {{1, 2}, {3, 4}};

    printf("A = /  1  2 \\\n    \\  3  4 /\n\n");

    // initialize matrix b
    int b[B_ROWS][B_COLS] = {{5, 6, 7}, {8, 9, 10}};

    printf("B = /  5  6  7 \\\n    \\  8  9 10 /\n\n");

    // initialize matrix c to zero (awaiting values)
    int c[C_ROWS][C_COLS] = {{0, 0, 0}, {0, 0, 0}};

    // handle each x y pair
    for(int y = 0; y < C_ROWS; y++) {
        // print symbols to make brackets around matrix
        if(y == 0) {
            printf("C = / ");
        } else if (y == C_ROWS - 1) {
            printf("    \\ ");
        } else {
            printf("    | ");
        }
        
        for(int x = 0; x < C_COLS; x++) {
            // add the multiplied results from each segment
            for(int i = 0; i < C_ROWS; i++) {
                c[y][x] += a[y][i] * b[i][x];
            }

            // print value
            printf("%2d ", c[y][x]);
        }

        // print symbols to make closing brackets around matrix
        if(y == 0) {
            printf("\\");
        } else if (y == C_ROWS - 1) {
            printf("/");
        } else {
            printf("|");
        }
        printf("\n");
    }

    return 0;
}