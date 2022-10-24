#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int sequentialSearch(int array[], int length, int searchValue);

int main() {

    int Data_Array[100000];

    for(int i = 0; i < 100000; i++) {
        Data_Array[i] = rand() % 100000; // randomize values
    }

    clock_t t = clock();
    sequentialSearch(Data_Array, 100000, 42);
    t = clock() - t;

    printf("%d\n", t);

    t = clock();
    for(int i = 0; i < 10000000; i++) {
        int k = i * 2;
    }
    t = clock() - t;

    printf("%d\n", t);

    return 0;
}

int sequentialSearch(int array[], int length, int searchValue) {
            
    clock_t t = clock();

    for(int i = 0; i < length; i++) {
        if(array[i] == searchValue) { // if value found, return index
            printf("%d\n", t);
            t = clock() - t;
            return i; 
        }
    }

    t = clock() - t;
    printf("%d\n", t);
    return -1; // returns -1 if searchValue does not appear in array
}