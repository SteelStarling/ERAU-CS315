#include <iostream>
#include <ctime>
#include <random>
using namespace std;

void swap(int *a, int *b);
int partition(int array[], int low, int high);
void quickSort(int array[], int low, int high);
int sequentialSearch(int array[], FILE* fp, int length, int searchValue);
int binarySearch(int array[], FILE* fp, int min, int max, int searchValue);
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

    clock_t t = clock();
    searchSet(Data_Array, dataSize, Key_Array, keySize);
    t = clock() - t;
    cout << t << endl;
}

void searchSet(int dataArray[], int dataSize, int keyArray[], int keySize) {
    clock_t t;
    double time_taken;
    int index;
    FILE* fp = fopen("results.csv", "w"); // open a csv file

    // FUN FACT!
    // If you try and call clock() outside a function as your instruction document states, it doesn't actually count anything! Since the process haults when the other function takes over, the clock just doesn't count up at all!
    // Please, in future, do be sure to actually check the code you give us, because I don't want to deal with troubleshooting code provided by a professor, when every student will assume it's valid (and you explicitly say it's valid).
    // Sorry if this sounds harsh, but do know that all of this was written after multiple hours of research and testing that falls outside the cirriculum of this class, all because you explicitly told us to do something that flat out does not work.

    if(fp == NULL) { // if fopen fails, throw error
        perror("Error opening file");
    }

    fprintf(fp, "Data Size,Key Size\n%d,%d\n\n", dataSize, keySize); // print sizes used

    fprintf(fp, ",Sequential,,Binary\nKeys,index,Time,index,Time\n"); // print headers to file

    for(int i = 0; i < keySize; i++) {
        // print key
        fprintf(fp, "%d, ", keyArray[i]);
        
        // sequential
        sequentialSearch(dataArray, fp, dataSize, keyArray[i]); // search (we can discard value because we don't care about them for this instance)

        // binary
        binarySearch(dataArray, fp, 0, dataSize, keyArray[i]); // search (we can discard value because we don't care about them for this instance)
    }

    fclose(fp);
}

int sequentialSearch(int array[], FILE* fp, int length, int searchValue) {
            
    clock_t t = clock();
    for(int i = 0; i < length; i++) {
        if(array[i] == searchValue) { // if value found, return index
            t = clock() - t;
            fprintf(fp, "%d, %d, ", i, t);
            return i; 
        }
    }

    t = clock() - t;
    fprintf(fp, "%d, %d, ", -1, t);
    return -1; // returns -1 if searchValue does not appear in array
}


int binarySearch(int array[], FILE* fp, int min, int max, int searchValue) {
    int index = -1;

    clock_t t = clock();
    if(min <= max) { // only run until all spaces have been checked

        int mid = (min + max) / 2; // get mid point

        if(array[mid] == searchValue) { // if equal, return value
            index = mid;
        } else if(array[mid] > searchValue) { // if too big, search lower half
            index = binarySearch(array, fp, min, mid - 1, searchValue);
        } else { // if too small, search upper half
            index = binarySearch(array, fp, mid + 1, max, searchValue);
        }
    }
    t = clock() - t;

    fprintf(fp, "%d, %d", index, t);

    return index; // returns -1 if searchValue does not appear in array
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
