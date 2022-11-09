
// Author: Taylor Hancock
// Project: Assignment 4

// As a note, the example solutions you show on your assignment is missing isFull in the queue data sheet, pop never says to return the value, and your example input for queue has incorrect outputs.
// Hopefully, the text files are formatted correctly, because you told us to remove all the messages displayed to the user, so I have, meaning it may be quite hard to understand)


#include <list> // use doubly linked lists (as included in the C++ STL)
#include <iostream>
#include <fstream> // for fileio
#include <exception> // for exceptions
using namespace std;


// max length for both class
#define MAX_LENGTH 5

// I created a class, because it made sense to me to do it semi-properly this way
class Stack {
private:
    int maxLen; // holds max length of stack
    int length; // holds current length of stack
    int* array; // array of values in stack
public:

    Stack(int maxLen) {
        this->maxLen = maxLen;
        length = 0;
        this->array = new int[maxLen];
    }

    // returns true if empty, false otherwise
    bool isEmpty() {
        return (length == 0);
    }

    // returns true if the stack is full, false otherwise
    bool isFull() {
        return (length == maxLen);
    }

    // returns the current filled length of the stack
    int size() {
        return length;
    }

    // returns the last ("top") value in the stack
    int top() {
        if(length <= 0) { // handle errors
            throw length_error("List Empty");
        }
        
        return array[length - 1];
    }

    // returns the last ("top") value in the stack as well
    int peek() {
        return top();
    }

    // adds a value to the top of the stack
    void push(int value) {
        if(length >= maxLen) { // length should never raise above max
            throw out_of_range("Max Length Reached");
        }

        array[length] = value;
        length++;
    }

    // removes the top element of the stack and returns it
    int pop() {
        if(length <= 0) { // length should never drop below 0
            throw length_error("List Empty");
        }

        length--;
        int value = array[length]; // save value to be returned later
        array[length] = 0;

        return value;
    }

    // prints stack elements
    void display() {
        cout << "Stack: ";
        for(int i = 0; i < length; i++) {
            cout << array[i];

            if(i != length - 1) { // only print commas if not the last
                cout << ", ";
            }
        }
        cout << endl;
    }
};

// I created a class here as well, to ensure consistency and make things work better with my Object-Oriented loving brain
class Queue {
private:
    int maxLen; // holds max length
    list<int> linkedlist; // holds linkedlist
public:

    // creates a new queue
    Queue(int maxLen) {
        this->maxLen = maxLen; // sets max length for linkedlist
    }

    // returns true if empty, false otherwise
    bool isEmpty() {
        return (linkedlist.size() == 0);
    }

    // returns true if the queue is full, false otherwise
    bool isFull() {
        return (linkedlist.size() == maxLen);
    }

    // returns the current filled length of the queue
    int size() {
        return linkedlist.size();
    }

    // returns the first ("front") value in the queue
    int front() {
        if(linkedlist.size() == 0) { // handle if the linkedlist is too small
            throw length_error("List Empty");;
            return 0;
        }
        
        return linkedlist.front(); // get first value
    }

    // returns the first ("front") value in the queue as well
    int offer() {
        return front();
    }

    // adds a value to the queue
    void enqueue(int value) {
        if(linkedlist.size() >= maxLen) { // length should never raise above max
            throw out_of_range("Max Length Reached");
        }

        linkedlist.push_back(value); // add value to end of linkedlist
    }

    // removes and returns the top element of the queue
    int dequeue() {
        if(linkedlist.size() <= 0) { // length should never drop below 0
            throw length_error("List Empty");;
        }

        int value = linkedlist.front(); // save value to be returned later
        linkedlist.pop_front(); // remove value from front of linkedlist
        
        return value;
    }

    // prints queue elements
    void display() {
        cout << "Queue: ";
        for(auto const &i : linkedlist) { // print each value in linked list, because C++ 11 is *magic*
            cout << i;

            if(i != linkedlist.back()) { // only print commas if not the last
                cout << ", ";
            }
        }
        cout << endl;
    }
};

// print the user menu for queues
static void printStackMenu() {
    cout << "Stack Commands:" << endl
            << "   1. isEmpty()" << endl
            << "   2. isFull()" << endl
            << "   3. size()" << endl
            << "   4. top()" << endl
            << "   5. push()" << endl
            << "   6. pop()" << endl
            << "   7. display" << endl
            << "   8. exit" << endl;
}

// handle user inputs for stacks
static void parseStack() {
    int input = 0;
    Stack s(MAX_LENGTH);
    while(input != 8) { // loop until told to exit
        printStackMenu();
        cout << "Input your command: ";
        cin >> input;

        while(!cin) { // handle invalid input
            cin.clear();
            cin.ignore(INT_MAX, '\n');

            cout << endl << "ERROR: Invalid input, please input a valid integer!" << endl;
            printStackMenu();
            cout << "Input your command: ";
            cin >> input;
        }

        int value = 0; // defined outside switch statement to prevent "jump to case label" errors
        
        switch(input) {
            case 1:
                cout << "isEmpty(): " << s.isEmpty() << endl;
                break;
            case 2:
                cout << "isFull(): " << s.isFull() << endl;
                break;
            case 3:
                cout << "size(): " << s.size() << endl;
                break;
            case 4:
                try {
                    value = s.top();
                    cout << "top(): " << value << endl;
                } catch(length_error) {
                    cout << "top() illegal because stack is empty!" << endl;
                }
                break;
            case 5:
                cout << "Enter a value to be pushed: ";
                cin >> value;

                while(!cin) { // handle invalid input
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');

                    cout << endl << "ERROR: Invalid input, please input a valid integer!" << endl;
                    cout << "Enter a value to be pushed: ";
                    cin >> value;
                }

                try{
                    s.push(value);
                    cout << "Pushed " << value << " onto stack" << endl;
                } catch(out_of_range) {
                    cout << "push(" << value << ") illegal because stack is full!" << endl;
                }
                break;
            case 6:
                try {
                    value = s.pop();
                    cout << "Popped " << value << " from stack" << endl;
                } catch(length_error) {
                    cout << "pop() illegal because stack is empty!" << endl;
                }
                break;
            case 7:
                s.display();
                break;
        }
    }
}

// print the user menu for queues
static void printQueueMenu() {
    cout << "Queue Commands:" << endl
            << "   1. isEmpty()" << endl
            << "   2. isFull()" << endl
            << "   3. size()" << endl
            << "   4. front()" << endl
            << "   5. enqueue()" << endl
            << "   6. dequeue()" << endl
            << "   7. display()" << endl
            << "   8. exit" << endl;
}

// handle user inputs for queues
static void parseQueue() {
    int input = 0;
    Queue q(MAX_LENGTH);
    while(input != 8) { // loop until told to exit
        printQueueMenu();
        cout << "Input your command: ";
        cin >> input;

        while(!cin) { // handle invalid input
            cin.clear();
            cin.ignore(INT_MAX, '\n');

            cout << "ERROR: Invalid input, please input a valid integer!" << endl;
            printQueueMenu();
            cout << "Input your command: ";
            cin >> input;
        }

        int value = 0; // defined outside switch statement to prevent "jump to case label" errors
        
        switch(input) {
            case 1:
                cout << "isEmpty(): " << q.isEmpty() << endl;
                break;
            case 2:
                cout << "isFull(): " << q.isFull() << endl;
                break;
            case 3:
                cout << "size(): " << q.size() << endl;
                break;
            case 4:
                try {
                    cout << "front(): " << q.front() << endl;
                } catch(length_error) {
                    cout << "front() illegal because queue is empty!" << endl;
                }
                break;
            case 5:
                cout << "Enter a value to be enqueued: ";
                cin >> value;

                while(!cin) { // handle invalid input
                    cin.ignore(INT_MAX, '\n');
                    cin.clear();

                    cout << endl << "ERROR: Invalid input, please input a valid integer!" << endl;
                    cout << "Enter a value to be enqueued: ";
                    cin >> value;
                }

                try {
                q.enqueue(value);
                cout << "Enqueued " << value << " into queue" << endl;
                } catch(out_of_range) {
                    cout << "enqueue() illegal because queue is full!" << endl;
                }
                break;
            case 6:
                try {
                    value = q.dequeue();
                    cout << "Dequeued " << value << " from queue" << endl;
                } catch(length_error) {
                    cout << "dequeue() illegal because queue is empty!" << endl;
                }
                break;
            case 7:
                q.display();
                break;
        }
    }
}

int main() {
    // comment out one to run the other (should be obvious, but I figured it warranted stating, since I did it all in one program rather than two)
    //parseStack();
    parseQueue();

    return 0;
}

