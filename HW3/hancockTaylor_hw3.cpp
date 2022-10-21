#include <iostream>
#include <time.h>
#include <random>
using namespace std;

void swap(int *a, int *b);
int partition(int array[], int low, int high);
void quickSort(int array[], int low, int high);
int sequentialSearch(int array[], int length, int searchValue);
int binarySearch(int array[], int min, int max, int searchValue);
void searchSet(int dataArray[], int dataSize, int keyArray[], int keySize);

int main() {

    int dataSize = 0;
    int keySize = 0;
    cout << "Please input the number of elements Data_Array should contain: ";
    cin >> dataSize;
    while(!cin || dataSize <= 0) { // handle errors (value must be < 0)
        cin.clear();
		cin.ignore(INT_MAX, '\n');
        cout << "ERROR: Invalid input! Input must be valid integer < 0!" << endl;
        cout << "Please input the number of elements Data_Array should contain: ";
        cin >> dataSize;
    }

    int* Data_Array = new int[dataSize];

    for(int i = 0; i < dataSize; i++) {
        Data_Array[i] = rand() % 100000; // randomize values
    }

    cout << "Please input the number of elements Key_Array should contain: ";
    cin >> keySize;
    while(!cin || keySize <= 0) { // handle errors (value must be < 0)
        cin.clear();
		cin.ignore(INT_MAX, '\n');
        cout << "ERROR: Invalid input! Input must be valid integer < 0!" << endl;
        cout << "Please input the number of elements Key_Array should contain: ";
        cin >> keySize;
    }

    int* Key_Array = new int[keySize];

    for(int i = 0; i < keySize; i++) {
        Key_Array[i] = rand() % 100000; // randomize values
    }

    searchSet(Data_Array, dataSize, Key_Array, keySize);
}

void searchSet(int dataArray[], int dataSize, int keyArray[], int keySize) {
    clock_t t;
    double time_taken;
    FILE* fp = fopen("results.csv", "w"); // open a csv file

    if(fp == NULL) { // if fopen fails, throw error
        perror("Error opening file");
    }

    fprintf(fp, "Data Size,Key Size\n%d,%d\n", dataSize, keySize); // print sizes used

    fprintf(fp, "Sequential,Binary\n"); // print headers to file

    for(int i = 0; i < keySize; i++) {
        // sequential
        t = clock();
        sequentialSearch(dataArray, dataSize, keyArray[i]); // search (we can discard value because we don't care about them for this instance)
        t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

        fprintf(fp, "%f,", time_taken); // print time to file

        // binary
        t = clock();
        binarySearch(dataArray, 0, dataSize, keyArray[i]); // search (we can discard value because we don't care about them for this instance)
        t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

        fprintf(fp, "%f\n", time_taken); // print time to file
    }

    fclose(fp);
}


void binarySearchSet(int dataArray[], int dataSize, int keyArray[], int keySize) {
    clock_t t;
    t = clock();

    for(int i = 0; i < keySize; i++) {
        binarySearch(dataArray, 0, dataSize, keyArray[i]); // search (we can discard value because we don't care about them for this instance)
    }

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  
    printf("Data_Array took %f seconds to execute \n", time_taken);
}


int sequentialSearch(int array[], int length, int searchValue) {
    for(int i = 0; i < length; i++) {
        if(array[i] == searchValue) { // if value found, return index
            return i; 
        }
    }

    return -1; // returns -1 if searchValue does not appear in array
}


int binarySearch(int array[], int min, int max, int searchValue) {
    if(min <= max) { // only run until all spaces have been checked

        int mid = (min + max) / 2; // get mid point

        if(array[mid] == searchValue) { // if equal, return value
            return mid;
        } else if(array[mid] > searchValue) { // if too big, search lower half
            return binarySearch(array, min, mid - 1, searchValue);
        } else { // if too small, search upper half
            return binarySearch(array, mid + 1, max, searchValue);
        }
    }

    return -1; // returns -1 if searchValue does not appear in array
}


// ----------------- QUICKSORT ALGORITHMS ----------------- //

// function to swap elements
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(int array[], int low, int high) {
    // select the rightmost element as pivot
  int pivot = array[high];
    // pointer for greater element
  int i = (low - 1);
  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
           // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
            // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }
  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
    // return the partition point
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
        // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);
        // recursive call on the left of pivot
    quickSort(array, low, pi - 1);
        // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}
