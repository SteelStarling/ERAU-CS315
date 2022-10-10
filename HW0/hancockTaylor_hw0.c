/*
 * File:    hancockTaylor_hw0.c
 * Project: Working with linked lists and how to traverse them
 * Author:  Taylor Hancock
 * Version: 19 September, 2022 
 */

#include <stdio.h>  /* for printf */
#include <stdlib.h> /* for malloc, free, NULL */
#include "link.h"

typedef struct {
    Link* head;
} LinkedList;

/* helper functions */
Link* getNewLink(int value, Link* next);
void tailRecursivePrint(const Link* l);

/* functions on a LinkedList */
void listInit(LinkedList* list);
void listAddValue(LinkedList* list, int value);
void listAddArray(LinkedList* list, const int array[], int arrayLen);
void listPrint(const LinkedList* list);
void listPrintReverse(const LinkedList* list);
int  listGetSum(const LinkedList* list);
void listFree(LinkedList* list);

/* initialize the variable(s) in the LinkedList */
void listInit(LinkedList* list) {
    if (list != NULL)
        list->head = NULL;
}

/* list function that uses tail recursive helper function */
void listPrintReverse(const LinkedList* list) {
    tailRecursivePrint(list->head);
    printf("\n");
}

int main() {
    LinkedList myList;
    int array[6] = {7, 1, -4, 16, 0, 3};
    int arrLen = 6;
    listInit(&myList);
    listAddValue(&myList, -2);
    listPrint(&myList);
    listAddArray(&myList, array, arrLen);
    listPrint(&myList);
    printf("The sum is: %d\n", listGetSum(&myList));
    listFree(&myList);
    if (myList.head == NULL) {
        printf("Problem with listFree(): myList isn't empty!\n");
    }
    return EXIT_SUCCESS;
}


/* Function: getNewLink
 * Purpose:  Adds a new link to the linked list with specified value, returning a pointer to itself
 * Argument: value - int containing value for next link
 * Argument: next  - Link* pointing to next value to link to
 * Returns:  Returns a pointer to itself
 */
Link* getNewLink(int value, Link* next) {
    /* allocate memory to newLink */
    Link* newLink = (Link*)malloc(sizeof(Link));

    /* fill newLink with data */
    newLink->next = next;
    newLink->value = value;

    /* return pointer to newly created link */
    return newLink;
}

/* Function: tailRecursivePrint
 * Purpose:  Prints the values of a LinkedList in reverse order via recursion
 * Argument: l - Link* pointing to the Link to print this time
 * Returns:  N/A
 */
void tailRecursivePrint(const Link* l) {
    if(l != NULL) {
        tailRecursivePrint(l->next);
        printf("%3d", l->value);
    }
}

/* Function: listAddValue
 * Purpose:  Adds a value to a LinkedList
 * Argument: list  - pointer to the LinkedList to fill
 * Argument: value - the value to add to the LinkedList
 * Returns:  N/A
 */
void listAddValue(LinkedList* list, int value) {
    /* check for null pointer */
    if(list != NULL) {
        list->head = getNewLink(value, list->head);
    } else {
        perror("ERROR: listAddValue: list is NULL pointer\n");
    }
}

/* Function: listAddArray
 * Purpose:  Adds the values of an array to a LinkedList
 * Argument: list     - pointer to the LinkedList to fill
 * Argument: array    - array to fill the LinkedList with
 * Argument: arrayLen - length of the array to fill the LinkedList with
 * Returns:  N/A
 */
void listAddArray(LinkedList* list, const int array[], int arrayLen) {
    int i = 0;
    
    /* check for null pointer */
    if(list != NULL) {
        /* loop through array filling list */
        for(i = 0; i < arrayLen; ++i) {
            listAddValue(list, array[i]);
        }
    } else {
        perror("ERROR: listAddArray: list is NULL pointer\n");
    }
}

/* Function: listPrint
 * Purpose:  Prints the values of a LinkedList
 * Argument: list - pointer to the LinkedList to print
 * Returns:  N/A
 */
void listPrint(const LinkedList* list) {
    Link* cursor;
    
    /* check for null pointer */
    if(list != NULL) {
        for(cursor = list->head; cursor != NULL; cursor = cursor->next) {
            printf("%3d", cursor->value);
        }
        printf("\n");
    } else {
        perror("ERROR: listPrint: list is NULL pointer\n");
    }
}

/* Function: listGetSum
 * Purpose:  Calculates and returns the sum of a LinkedList
 * Argument: list - pointer to the LinkedList to sum
 * Returns:  int containing the sum of the LinkedList
 */
int listGetSum(const LinkedList* list) {
    Link* cursor;
    int sum = 0;
    
    /* check for null pointer */
    if(list != NULL) {
        for(cursor = list->head; cursor != NULL; cursor = cursor->next) {
            sum += cursor->value;
        }
    } else {
        perror("ERROR: listGetSum: list is NULL pointer\n");
    }

    return sum;
}

/* Function: listFree
 * Purpose:  Frees up the space allocated to the specified LinkedList
 * Argument: list - pointer to the LinkedList to free
 * Returns:  N/A
 */
void listFree(LinkedList* list) {
    Link* dead;

    /* check for null pointer */
    if(list != NULL) {
        /* free each item in list */
        while(list->head != NULL) {
            dead = list->head;
            list->head = dead->next;
            free(dead);
        }
    } else {
        perror("ERROR: listFree: list is NULL pointer\n");
    }
}
