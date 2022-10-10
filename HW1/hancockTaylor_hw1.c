/**************************************************
 * File:      hancockTaylor_hw1.c
 * Author:    Taylor Hancock
 * Purpose:   
 * Version:   1.0 Oct 07, 2022
 * Resources: 
 **************************************************/

#include <stdio.h>

#define ARR1_WIDTH 2
#define ARR1_HEIGHT 2
#define ARR2_WIDTH 3
#define ARR2_HEIGHT 2

void printMatrix(int** matrix, int width, int height);
int** mult(int** a, int widthA, int heightA, int** b, int widthB, int heightB);

int main() {
    int a[][] = {{1, 2}, {3, 4}};
    int b[][] = {{5, 6, 7}, {8, 9, 10}};

    printMatrix(a, ARR1_WIDTH, ARR1_HEIGHT);
    printMatrix(b, ARR2_WIDTH, ARR2_HEIGHT);

    int c = mult(a, ARR1_WIDTH, ARR1_HEIGHT, b, ARR2_WIDTH, ARR2_HEIGHT);

    printMatrix(c, ARR2_WIDTH, ARR2_HEIGHT);

    return 0;
}

void printMatrix(int** matrix, int width, int height) {
    if(height == 1) {
        // open matrix
        printf("{");

        // print matrix
        for(int x = 0; x < width; x++) {
            printf("%d", x);
            if(x != width - 1) {
                printf(",");
            }
        }

        // close matrix
        printf("}");
    } else {
        for(int y = 0; y < height; y++) {
            // print the right thing to make the matrix box
            if(y == 0) {
                printf("/");
            } else if (y == height - 1) {
                printf("\\");
            } else {
                printf("|");
            }

            // print matrix
            for(int x = 0; x < width; x++) {
                printf("%d", x);
                if(x != width - 1) {
                    printf(",");
                }
            }

            // print the right thing to close the matrix box
            if(y == 0) {
                printf("\\");
            } else if (y == height - 1) {
                printf("/");
            } else {
                printf("|");
            }
        }
    }
}

// mult returns 0 if invalid input is given
int** mult(const int** a, const int widthA, const int heightA, const int** b, const int widthB, const int heightB) {
    const int maxWidth = (widthA > widthB ? widthA : widthB); //using ternary because it simplifies things
    const int maxHeight = (heightA > heightB ? heightA : heightB);
    int c[maxWidth][maxHeight];
    return 0;
}